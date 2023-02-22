#pragma once

#include <core/interfaces/IRequest.h>
#include <core/interfaces/IResponse.h>

#include <core/events/Signal.h>

namespace core::interfaces
{
    class IConnection
    {
    public:
        IConnection() = default;
        virtual ~IConnection() = default;

        IConnection(const IConnection& other) = delete;
        IConnection(IConnection&& other) noexcept = delete;
        IConnection& operator=(const IConnection& other) = delete;
        IConnection& operator=(IConnection&& other) noexcept = delete;

        [[nodiscard]] virtual bool connect() noexcept = 0;
        [[nodiscard]] virtual bool send(const IRequest* request) noexcept = 0;

        core::Signal<const std::shared_ptr<IResponse>> responseSignal;
    };
}
