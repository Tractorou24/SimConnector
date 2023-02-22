#include "cpch.h"

#include <core/response/ResponseFactory.h>

#include "core/response/ReadResponse.h"
#include "core/response/WriteResponse.h"

ResponseFactory::ResponseFactory()
{
    m_factory.registerType("ReadResponse", std::make_unique<ResponseCreator<core::response::ReadResponse>>());
    m_factory.registerType("WriteResponse", std::make_unique<ResponseCreator<core::response::WriteResponse>>());
}

std::unique_ptr<core::interfaces::IResponse> ResponseFactory::create(const std::string& name)
{
    return m_factory.create(name);
}
