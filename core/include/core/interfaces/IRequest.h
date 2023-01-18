#pragma once

#include <core/events/Signal.h>
#include <core/interfaces/IResponse.h>
#include <core/simconnect/SimVar.h>

namespace core::request
{
    enum class Type
    {
        Read
        , Write
        , Unknown
    };

    // ReSharper disable once CppInconsistentNaming
    class bad_request final : public std::runtime_error
    {
    public:
        explicit bad_request(const std::string& message) : runtime_error(message.c_str()) {}
        explicit bad_request(const char* message) : runtime_error(message) {}
    };
}

namespace core::interfaces
{
    class IRequest
    {
    public:
        IRequest() = default;
        virtual ~IRequest() = default;

        IRequest(const IRequest& other) = delete;
        IRequest(IRequest&& other) noexcept = delete;
        IRequest& operator=(const IRequest& other) = delete;
        IRequest& operator=(IRequest&& other) noexcept = delete;

        [[nodiscard]] virtual std::vector<std::shared_ptr<simconnect::interfaces::ISimVar>>& simVars() noexcept = 0;
        virtual void addSimVar(std::shared_ptr<simconnect::interfaces::ISimVar>& simvar) noexcept = 0;
        virtual void addSimVars(std::vector<std::shared_ptr<simconnect::interfaces::ISimVar>>& simvars) noexcept = 0;
        virtual void removeSimVar(const std::shared_ptr<simconnect::interfaces::ISimVar>& simvar) noexcept = 0;
        [[nodiscard]] virtual request::Type requestType() const noexcept = 0;

        Signal<const std::shared_ptr<IResponse>&> responseSignal;

    protected:
        std::vector<std::shared_ptr<simconnect::interfaces::ISimVar>> m_simvars = {};
    };
}
