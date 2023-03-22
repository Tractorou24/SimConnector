#include <core/request/ReadRequest.h>
#include <core/simconnect/SimVar.h>

namespace core::request
{
    void ReadRequest::addSimVar(std::shared_ptr<simconnect::SimVar>& simvar) noexcept
    {
        m_simvars.push_back(simvar);
    }

    void ReadRequest::addSimVars(std::vector<std::shared_ptr<simconnect::SimVar>>& simvars) noexcept
    {
        m_simvars.insert(m_simvars.end(), simvars.begin(), simvars.end());
    }

    std::vector<std::shared_ptr<simconnect::SimVar>>& ReadRequest::simVars() noexcept
    {
        return m_simvars;
    }

    void ReadRequest::removeSimVar(const std::shared_ptr<simconnect::SimVar>& simvar) noexcept
    {
        std::erase(m_simvars, simvar);
    }
}
