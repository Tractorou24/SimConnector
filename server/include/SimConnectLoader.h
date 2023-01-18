#pragma once

#include <SimConnect/SimConnect.h>

class SimConnectLoader final
{
public:
    /**
     * @brief Loads SimConnect dynamically from project's root SimConnect.dll 
     */
    static void LoadSimConnect();

    /**
     * @brief Free the module used to get simconnect functions DLL address
     */
    static void UnloadSimConnect();

public:
    static simconnect::raw::HANDLE module;
};
