#pragma once

#include <core/interfaces/IResponse.h>

namespace core::response
{
	/**
     * @brief A class received from the simulator after a ReadRequest.
     */
    class ReadResponse final : public interfaces::IResponse
    {
        // Serialization
        START_SERIALIZATION(ReadResponse)
        json::json simvars = json::json::array();
        for (const auto& simvar : m_simvars)
            simvars.push_back(SERIALIZE_PTR(simconnect::SimVar, simvar));
        obj["simvars"] = simvars;
        END_SERIALIZATION

        START_DESERIALIZATION(ReadResponse)
        for (const auto& simvar : object["simvars"])
            ptr->m_simvars.push_back(DESERIALIZE_PTR(simconnect::SimVar, simvar));
        END_DESERIALIZATION

    public:
	    /**
		 * @brief Checks if the response is valid.
		 * @exception std::bad_response if the response is not valid.
         */
        void checkValid() const override;

	    /**
		 * @brief Pushes a simvar to the response.
		 * @param simvar The shared pointer simvar to push.
         */
        void push(const std::shared_ptr<simconnect::SimVar>& simvar) override;

	    /**
         * @brief Pops a simvar from the response.
		 * @return The shared pointer simvar popped.
         */
        [[nodiscard]] std::shared_ptr<simconnect::SimVar> pop() noexcept override;

	    /**
		 * @brief Gets the response type (Read or Write).
         */
        [[nodiscard]] response::Type responseType() const noexcept override { return response_type; }

    private:
        static constexpr Type response_type = Type::Read;
    };
}
