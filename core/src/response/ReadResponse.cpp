#include "cpch.h"

#include <core/response/ReadResponse.h>

void core::response::ReadResponse::checkValid() const
{
    if (m_simvars.empty())
        throw bad_response("ReadResponse::checkValid() - No simvars in response !");
}

void core::response::ReadResponse::push(const std::shared_ptr<simconnect::SimVar>& simvar)
{
    m_simvars.push_back(simvar);
}

std::shared_ptr<simconnect::SimVar> core::response::ReadResponse::pop() noexcept
{
    auto simvar = m_simvars.front();
	std::erase(m_simvars, simvar);
    return simvar;
}
