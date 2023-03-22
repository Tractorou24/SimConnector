#pragma once

#include <core/simconnect/SimVar.h>

namespace core::response
{
    enum class Type
    {
        Read,
        Write,
        Unknown
    };

    // ReSharper disable once CppInconsistentNaming
    class bad_response final : public std::runtime_error
    {
    public:
        explicit bad_response(const std::string& message) : runtime_error(message.c_str()) {}
        explicit bad_response(const char* message) : runtime_error(message) {}
    };
}

namespace core::interfaces
{
    class IResponse : public ISerializable<IResponse>
    {
    public:
        IResponse() = default;
        ~IResponse() override = default;

        IResponse(const IResponse& other) = delete;
        IResponse(IResponse&& other) noexcept = delete;
        IResponse& operator=(const IResponse& other) = delete;
        IResponse& operator=(IResponse&& other) noexcept = delete;

        virtual void push(const std::shared_ptr<simconnect::SimVar>& simvar) = 0;
        [[nodiscard]] virtual std::shared_ptr<simconnect::SimVar> pop() noexcept = 0;
        [[nodiscard]] virtual std::size_t size() const noexcept { return m_simvars.size(); }
        virtual void checkValid() const = 0;
        [[nodiscard]] virtual response::Type responseType() const noexcept = 0;

    protected:
        std::vector<std::shared_ptr<simconnect::SimVar>> m_simvars = {};
    };
}
