#include "cpch.h"

#include <core/response/WriteResponse.h>

void core::response::WriteResponse::checkValid() const
{
    if (m_simvars.empty())
        throw bad_response("WriteResponse::checkValid() - No simvars in response !");
}

void core::response::WriteResponse::push(const std::shared_ptr<simconnect::SimVar>& simvar)
{
    m_simvars.push(simvar);
}

std::shared_ptr<simconnect::SimVar> core::response::WriteResponse::pop() noexcept
{
    auto simvar = m_simvars.top();
    m_simvars.pop();
    return simvar;
}
