#include "cpch.h"

#include <core/request/ReadRequest.h>
#include <core/response/ReadResponse.h>
#include <core/response/WriteResponse.h>
#include <core/simconnect/Runner.h>

namespace simconnect::details
{
    void CALLBACK simconnect_callback(raw::SIMCONNECT_RECV* p_data, raw::DWORD cb_data, void* p_context)
    {
        const auto* runner = Runner::GetInstance();
        switch (p_data->dwID)
        {
        case raw::SIMCONNECT_RECV_ID_EVENT_FRAME:
            {
                for (const auto& request_interface : runner->m_requests)
                {
                    auto* request = reinterpret_cast<core::request::ReadRequest*>(request_interface.get());
                    for (const auto& simvar_interface : request->simVars())
                    {
                        const auto* simvar = reinterpret_cast<SimVar*>(simvar_interface.get());
                        raw::SimConnect_RequestDataOnSimObjectType(runner->m_handle, static_cast<int>(simvar->m_request)
                                                                   , static_cast<int>(simvar->m_definition), 0
                                                                   , raw::SIMCONNECT_SIMOBJECT_TYPE_USER);
                    }
                }
                break;
            }
        case raw::SIMCONNECT_RECV_ID_SIMOBJECT_DATA_BYTYPE:
            {
                auto* data = reinterpret_cast<raw::SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE*>(p_data);

                std::shared_ptr<SimVar> received_simvar = nullptr;
                const auto received_request = std::find_if(runner->m_requests.begin(), runner->m_requests.end()
                                                           , [&](const auto& request_interface)
                                                           {
                                                               const auto& simvars = reinterpret_cast<core::request::ReadRequest*>(
                                                                   request_interface.get())->simVars();
                                                               return std::find_if(simvars.cbegin(), simvars.cend()
                                                                                   , [&](const auto& simvar_interface)
                                                                                   {
                                                                                       const auto* simvar = reinterpret_cast<SimVar*>(
                                                                                           simvar_interface.get());
                                                                                       if (static_cast<raw::DWORD>(simvar->m_definition) ==
                                                                                           data->dwDefineID)
                                                                                       {
                                                                                           received_simvar = simvar_interface;
                                                                                           return true;
                                                                                       }
                                                                                       return false;
                                                                                   }) != simvars.cend();
                                                           });

                if (received_request != runner->m_requests.end())
                {
                    auto* simvar = reinterpret_cast<SimVar*>(received_simvar.get());
                    simvar->m_is_pending = false;
                    if (simvar->m_is_string)
                        simvar->m_string_value = std::string(reinterpret_cast<char*>(&data->dwData));
                    else
                        simvar->m_double_value = *reinterpret_cast<double*>(&data->dwData);
                    break;
                }
                break;
            }
        case raw::SIMCONNECT_RECV_ID_QUIT:
            {
                Runner::GetInstance()->m_quit = true;
                break;
            }
        default:
            break;
        }
    }
}

namespace simconnect
{
    bool Runner::openConnection()
    {
        const auto res = raw::SimConnect_Open(&m_handle, "SimConnect", nullptr, 0, nullptr, 0);
        return res == SIMCONNECT_OK;
    }

    bool Runner::closeConnection()
    {
        const bool res = raw::SimConnect_Close(m_handle) == SIMCONNECT_OK;
        m_handle = nullptr;
        return res;
    }

    Runner* Runner::GetInstance()
    {
        static Runner instance;
        return &instance;
    }

    void Runner::addRequest(std::shared_ptr<core::interfaces::IRequest>& request)
    {
        auto* vars = reinterpret_cast<core::request::ReadRequest*>(request.get());
        for (const auto& var_interface : vars->simVars())
        {
            auto* var = reinterpret_cast<SimVar*>(var_interface.get());
            var->m_definition = static_cast<details::Definition>(m_current_definition++);
            var->m_request = static_cast<details::Request>(m_current_request++);
            var->m_is_pending = registerRequest(request);
        }
        m_requests.push_back(request);
    }

    void Runner::removeRequest(const std::shared_ptr<core::interfaces::IRequest>& request)
    {
        if (!unregisterRequest(request))
            throw std::runtime_error("Failed to unregister request.");
        std::erase(m_requests, request);
    }

    void Runner::pollEvents()
    {
        raw::SimConnect_CallDispatch(m_handle, details::simconnect_callback, nullptr);

        decltype(m_requests)::size_type i = 0;
        while (i < m_requests.size())
        {
            auto* request = reinterpret_cast<core::request::ReadRequest*>(m_requests[i].get());
            if (std::all_of(request->simVars().begin(), request->simVars().end(), [](const auto& simvar_interface)
            {
                const auto* simvar = reinterpret_cast<SimVar*>(simvar_interface.get());
                return !simvar->m_is_pending;
            }))
            {
                std::shared_ptr<core::interfaces::IResponse> response;
                if (request->requestType() == core::request::Type::Read)
                    response = std::make_shared<core::response::ReadResponse>();
                else
                    response = std::make_shared<core::response::WriteResponse>();

                for (const auto& simvar_interface : request->simVars())
                    response->push(simvar_interface);

                request->responseSignal.emitSignal(response);
                i++;
            } else
                i++;
        }
    }

    bool Runner::registerRequest(const std::shared_ptr<core::interfaces::IRequest>& request) const
    {
        if (m_handle == nullptr)
            throw std::runtime_error("SimConnect is not connected.");

        auto* read_request = reinterpret_cast<core::request::ReadRequest*>(request.get());
        for (const auto& simvar_interface : read_request->simVars())
        {
            const auto& var = reinterpret_cast<const SimVar*>(simvar_interface.get());

            if (var->m_is_string)
            {
                const auto res = raw::SimConnect_AddToDataDefinition(m_handle, static_cast<int>(var->m_definition), var->m_name.c_str()
                                                                     , nullptr
                                                                     , raw::SIMCONNECT_DATATYPE_STRING256);
                if (res != SIMCONNECT_OK)
                    return true;
            } else
            {
                const auto res = raw::SimConnect_AddToDataDefinition(m_handle, static_cast<int>(var->m_definition), var->m_name.c_str()
                                                                     , var->m_units.c_str());
                if (res != SIMCONNECT_OK)
                    return true;
            }
        }
        return raw::SimConnect_SubscribeToSystemEvent(m_handle, 0, "Frame") != SIMCONNECT_OK;
    }

    bool Runner::unregisterRequest(const std::shared_ptr<core::interfaces::IRequest>& request) const
    {
        if (m_handle == nullptr)
            return true;

        auto* read_request = reinterpret_cast<core::request::ReadRequest*>(request.get());
        for (const auto& simvar_interface : read_request->simVars())
        {
            const auto& var = reinterpret_cast<const SimVar*>(simvar_interface.get());
            const auto res = raw::SimConnect_ClearClientDataDefinition(m_handle, static_cast<int>(var->m_definition));
            if (res != SIMCONNECT_OK)
                return true;
        }
        return raw::SimConnect_SubscribeToSystemEvent(m_handle, 0, "Frame") != SIMCONNECT_OK;
    }
}
