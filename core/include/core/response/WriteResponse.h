#pragma once

#include <core/interfaces/IResponse.h>

namespace core::response
{
    class WriteResponse final : public interfaces::IResponse
    {
    public:
        void checkValid() const override;
        void push(const std::shared_ptr<simconnect::interfaces::ISimVar>& simvar) override;
        [[nodiscard]] std::shared_ptr<simconnect::interfaces::ISimVar> pop() noexcept override;
        [[nodiscard]] response::Type responseType() const noexcept override { return response_type; }

    private:
        static constexpr Type response_type = Type::Write;
    };
}
