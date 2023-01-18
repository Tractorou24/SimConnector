#pragma once

#include <core/interfaces/IRequest.h>

namespace core::request
{
    class WriteRequest final : public core::interfaces::IRequest
    {
    public:
        void addSimVar(std::shared_ptr<simconnect::interfaces::ISimVar>& simvar) noexcept override;
        void addSimVars(std::vector<std::shared_ptr<simconnect::interfaces::ISimVar>>& simvars) noexcept override;
        [[nodiscard]] std::vector<std::shared_ptr<simconnect::interfaces::ISimVar>>& simVars() noexcept override;
        void removeSimVar(const std::shared_ptr<simconnect::interfaces::ISimVar>& simvar) noexcept override;

        [[nodiscard]] Type requestType() const noexcept override { return request_type; }

    private:
        static constexpr Type request_type = Type::Write;
    };
}
