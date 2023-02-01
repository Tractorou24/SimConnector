#pragma once

#include <core/interfaces/IResponse.h>

namespace core::response
{
	/**
     * @brief A class received from the simulator after a ReadRequest.
     */
    class ReadResponse final : public interfaces::IResponse
    {
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
