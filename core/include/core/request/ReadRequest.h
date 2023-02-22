#pragma once

#include <core/interfaces/IRequest.h>

namespace core::request
{
    /**
     * @brief A class to make a read request for the simulator.
     */
    class ReadRequest final : public core::interfaces::IRequest
    {
        // Serialization
        START_SERIALIZATION(ReadRequest)
            json::json simvars = json::json::array();
            for (const auto& simvar : m_simvars)
                simvars.push_back(SERIALIZE_PTR(simconnect::SimVar, simvar));
            obj["simvars"] = simvars;
            obj["type"] = "ReadRequest";
        END_SERIALIZATION

        START_DESERIALIZATION(ReadRequest)
            for (const auto& simvar : object["simvars"])
                m_simvars.push_back(DESERIALIZE_PTR(simconnect::SimVar, simvar));
        END_DESERIALIZATION

    public:
        /**
        * @brief Adds a single simvar to the request.
         * @param simvar The shared pointer to the simvar.
         */
        void addSimVar(std::shared_ptr<simconnect::SimVar>& simvar) noexcept override;

        /**
        * @brief Adds a vector of simvars to the request.
         * @param simvars The vector of simvars shared pointers.
         */
        void addSimVars(std::vector<std::shared_ptr<simconnect::SimVar>>& simvars) noexcept override;

        /**
        * @brief Removes a single simvar from the request.
        * @param simvar The shared pointer to the simvar to remove.
         */
        void removeSimVar(const std::shared_ptr<simconnect::SimVar>& simvar) noexcept override;

        /**
         * @brief Returns the type of request (Read or Write).
         */
        [[nodiscard]] Type requestType() const noexcept override { return request_type; }

        /**
         * @brief Gets the current added simvars to the request.
      * @return The vector of simvars shared pointers.
         */
        [[nodiscard]] std::vector<std::shared_ptr<simconnect::SimVar>>& simVars() noexcept override;

    private:
        static constexpr Type request_type = Type::Read;
    };
}
