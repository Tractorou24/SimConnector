#pragma once

#include <core/interfaces/IRequest.h>

namespace core::request
{
    /**
	 * @brief A class to make a write request for the simulator.
	 */
    class WriteRequest final : public core::interfaces::IRequest
    {
    public:
        /**
         * @brief Adds a single simvar to the request.
         * @param simvar The shared pointer to the simvar.
         */
        void addSimVar(std::shared_ptr<simconnect::interfaces::ISimVar>& simvar) noexcept override;

        /**
         * @brief Adds a vector of simvars to the request.
         * @param simvars The vector of simvars shared pointers.
         */
        void addSimVars(std::vector<std::shared_ptr<simconnect::interfaces::ISimVar>>& simvars) noexcept override;

        /**
         * @brief Removes a single simvar from the request.
         * @param simvar The shared pointer to the simvar to remove.
         */
        void removeSimVar(const std::shared_ptr<simconnect::interfaces::ISimVar>& simvar) noexcept override;

        /**
         * @brief Returns the type of request (Read or Write)
         */
        [[nodiscard]] Type requestType() const noexcept override { return request_type; }

        /**
         * @brief Gets the current added simvars to the request.
         * @return The vector of simvars shared pointers.
         */
        [[nodiscard]] std::vector<std::shared_ptr<simconnect::interfaces::ISimVar>>& simVars() noexcept override;

    private:
        static constexpr Type request_type = Type::Write;
    };
}
