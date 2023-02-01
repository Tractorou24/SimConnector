#pragma once

#include "cpch.h"

#include <core/ser/serialize.h>
#include <SimConnect/SimConnect.h>

namespace simconnect::details
{
    enum class Definition
    {
        Dummy = 0
    };

    enum class Request
    {
        Dummy = 0
    };

    /**
	* @brief The callback used by simconnect to receive data from the simulator.
	* @param p_data Pointer to a data buffer, to be treated initially as a SIMCONNECT_RECV structure.
	* @param cb_data The size of the data buffer, in bytes.
	* @param p_context Contains the pointer specified by the client in the SimConnect_CallDispatch function call.
	*/
    void CALLBACK simconnect_callback(raw::SIMCONNECT_RECV* p_data, raw::DWORD cb_data, void* p_context);

}

namespace simconnect
{
	/**
     * @brief Any SimConnect Simvar used to make requests and receive responses.
     */
    class SimVar
    {
	    friend class Runner;
        friend void CALLBACK details::simconnect_callback(raw::SIMCONNECT_RECV*, raw::DWORD, void*);

    public:
        /**
         * @brief Instantiates a new SimVar.
         * @param name The name of the SimVar in the simulator.
         * @param units The unit for the Simvar.
		 * @param is_string If the SimVar data response is a string.
         */
        SimVar(std::string name, std::string units, const bool& is_string)
            : m_name(std::move(name)), m_units(std::move(units)), m_is_string(is_string) {}

        /**
         * @return The simulator name of the SimVar.
         */
        [[nodiscard]] std::string name() const noexcept { return m_name; }

        /**
		 * @return The unit of the SimVar.
         */
        [[nodiscard]] std::string units() const noexcept { return m_units; }

        /**
		 * @return If the SimVar data response is a string.
         */
        [[nodiscard]] bool isString() const noexcept { return m_is_string; }

        /**
         * @return If the SimVar was successfully requested and waiting for response.
         */
        [[nodiscard]] bool isPending() const noexcept { return m_is_pending; }

        /**
         * @return The value of the SimVar if not a string.
         */
        [[nodiscard]] double value() const noexcept { return m_double_value; }

        /**
		 * @return The value of the SimVar if it's a string.
         */
        [[nodiscard]] std::string stringValue() const noexcept { return m_string_value; }

    private:
        details::Definition m_definition = details::Definition::Dummy;
        details::Request m_request = details::Request::Dummy;
        std::string m_string_value;
        double m_double_value = 0;

        const std::string m_name, m_units;
        const bool m_is_string = false;
        bool m_is_pending = false;
    };
}
