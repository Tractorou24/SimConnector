#pragma once

#include "cpch.h"

#include <SimConnect/SimConnect.h>

namespace simconnect::interfaces
{
    class ISimVar {};

    class ISimVarGroup : public std::vector<std::shared_ptr<ISimVar>> { };
}

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

    void CALLBACK simconnect_callback(raw::SIMCONNECT_RECV*, raw::DWORD, void*);
}

namespace simconnect
{
    class SimVar : public interfaces::ISimVar
    {
        friend class Runner;
        friend void CALLBACK details::simconnect_callback(raw::SIMCONNECT_RECV*, raw::DWORD, void*);

    public:
        SimVar(std::string name, std::string units, const bool& is_string)
            : m_name(std::move(name)), m_units(std::move(units)), m_is_string(is_string) {}

        [[nodiscard]] std::string name() const noexcept { return m_name; }
        [[nodiscard]] std::string units() const noexcept { return m_units; }
        [[nodiscard]] bool isString() const noexcept { return m_is_string; }
        [[nodiscard]] bool isPending() const noexcept { return m_is_pending; }

        [[nodiscard]] double value() const noexcept { return m_double_value; }
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
