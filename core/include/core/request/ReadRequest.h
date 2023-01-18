#pragma once

#include <core/interfaces/IRequest.h>

namespace core::request
{
    class ReadRequest final : public core::interfaces::IRequest
    {
    public:
        void addSimVar(std::shared_ptr<simconnect::interfaces::ISimVar>& simvar) noexcept override;
        void addSimVars(std::vector<std::shared_ptr<simconnect::interfaces::ISimVar>>& simvars) noexcept override;
        [[nodiscard]] Type requestType() const noexcept override { return request_type; }
        [[nodiscard]] std::vector<std::shared_ptr<simconnect::interfaces::ISimVar>>& simVars() noexcept override;
        void removeSimVar(const std::shared_ptr<simconnect::interfaces::ISimVar>& simvar) noexcept override;

    private:
        static constexpr Type request_type = Type::Read;
    };
}
