#include "cpch.h"

#include <core/request/WriteRequest.h>
#include <core/simconnect/SimVar.h>

namespace core::request
{
    void WriteRequest::addSimVar(std::shared_ptr<simconnect::interfaces::ISimVar>& simvar) noexcept
    {
        m_simvars.push_back(simvar);
    }

    void WriteRequest::addSimVars(std::vector<std::shared_ptr<simconnect::interfaces::ISimVar>>& simvars) noexcept
    {
        m_simvars.insert(m_simvars.end(), simvars.begin(), simvars.end());
    }

    std::vector<std::shared_ptr<simconnect::interfaces::ISimVar>>& WriteRequest::simVars() noexcept
    {
        return m_simvars;
    }

    void WriteRequest::removeSimVar(const std::shared_ptr<simconnect::interfaces::ISimVar>& simvar) noexcept
    {
        std::erase(m_simvars, simvar);
    }
}
