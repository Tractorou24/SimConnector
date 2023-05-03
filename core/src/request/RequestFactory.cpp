#include <core/request/RequestFactory.h>

#include "core/request/ReadRequest.h"
#include "core/request/WriteRequest.h"
#include "core/request/RemoveRequest.h"

RequestFactory::RequestFactory()
{
    m_factory.registerType("ReadRequest", std::make_unique<RequestCreator<core::request::ReadRequest>>());
    m_factory.registerType("WriteRequest", std::make_unique<RequestCreator<core::request::WriteRequest>>());
    m_factory.registerType("RemoveRequest", std::make_unique<RequestCreator<core::request::RemoveRequest>>());
}

std::unique_ptr<core::interfaces::IRequest> RequestFactory::create(const std::string& name)
{
    return m_factory.create(name);
}
