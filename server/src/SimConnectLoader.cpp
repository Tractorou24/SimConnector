#include "spch.h"

#include <Windows.h>

#include <iostream>
#include <SimConnectLoader.h>

#define SIMCONNECT_DLL_PATH TEXT("SimConnect.dll")

HANDLE SimConnectLoader::module = nullptr;

void SimConnectLoader::LoadSimConnect()
{
    module = LoadLibrary(SIMCONNECT_DLL_PATH);
    if (!module)
        throw std::runtime_error("Failed to dynamically load SimConnect.dll");
}

void SimConnectLoader::UnloadSimConnect()
{
    if (!FreeLibrary(static_cast<HMODULE>(module)))
        throw std::runtime_error("Failed to dynamically unload SimConnect.dll");
}

// ReSharper disable all
// @formatter:off
namespace simconnect::raw
{
    SIMCONNECTAPI SimConnect_MapClientEventToSimEvent(HANDLE hSimConnect, SIMCONNECT_CLIENT_EVENT_ID EventID, const char* EventName)
    {
        using simconnect_map_client_event_to_sim_event = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_CLIENT_EVENT_ID, const char*);
        return reinterpret_cast<simconnect_map_client_event_to_sim_event>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_MapClientEventToSimEvent"))(hSimConnect, EventID, EventName);
    }

    SIMCONNECTAPI SimConnect_TransmitClientEvent(HANDLE hSimConnect, SIMCONNECT_OBJECT_ID ObjectID, SIMCONNECT_CLIENT_EVENT_ID EventID, DWORD dwData, SIMCONNECT_NOTIFICATION_GROUP_ID GroupID, SIMCONNECT_EVENT_FLAG Flags)
    {
		using simconnect_transmit_client_event = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_OBJECT_ID, SIMCONNECT_CLIENT_EVENT_ID, DWORD, SIMCONNECT_NOTIFICATION_GROUP_ID, SIMCONNECT_EVENT_FLAG);
		return reinterpret_cast<simconnect_transmit_client_event>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_TransmitClientEvent"))(hSimConnect, ObjectID, EventID, dwData, GroupID, Flags);
    }

    SIMCONNECTAPI SimConnect_SetSystemEventState(HANDLE hSimConnect, SIMCONNECT_CLIENT_EVENT_ID EventID, SIMCONNECT_STATE dwState)
    {
		using simconnect_set_system_event_state = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_CLIENT_EVENT_ID, SIMCONNECT_STATE);
		return reinterpret_cast<simconnect_set_system_event_state>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_SetSystemEventState"))(hSimConnect, EventID, dwState);
    }

    SIMCONNECTAPI SimConnect_AddClientEventToNotificationGroup(HANDLE hSimConnect, SIMCONNECT_NOTIFICATION_GROUP_ID GroupID, SIMCONNECT_CLIENT_EVENT_ID EventID, BOOL bMaskable)
    {
		using simconnect_add_client_event_to_notification_group = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_NOTIFICATION_GROUP_ID, SIMCONNECT_CLIENT_EVENT_ID, BOOL);
		return reinterpret_cast<simconnect_add_client_event_to_notification_group>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_AddClientEventToNotificationGroup"))(hSimConnect, GroupID, EventID, bMaskable);
    }

    SIMCONNECTAPI SimConnect_RemoveClientEvent(HANDLE hSimConnect, SIMCONNECT_NOTIFICATION_GROUP_ID GroupID, SIMCONNECT_CLIENT_EVENT_ID EventID)
    {
		using simconnect_remove_client_event = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_NOTIFICATION_GROUP_ID, SIMCONNECT_CLIENT_EVENT_ID);
		return reinterpret_cast<simconnect_remove_client_event>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_RemoveClientEvent"))(hSimConnect, GroupID, EventID);
    }

    SIMCONNECTAPI SimConnect_SetNotificationGroupPriority(HANDLE hSimConnect, SIMCONNECT_NOTIFICATION_GROUP_ID GroupID, DWORD uPriority)
    {
		using simconnect_set_notification_group_priority = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_NOTIFICATION_GROUP_ID, DWORD);
		return reinterpret_cast<simconnect_set_notification_group_priority>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_SetNotificationGroupPriority"))(hSimConnect, GroupID, uPriority);
    }

    SIMCONNECTAPI SimConnect_ClearNotificationGroup(HANDLE hSimConnect, SIMCONNECT_NOTIFICATION_GROUP_ID GroupID)
    {
		using simconnect_clear_notification_group = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_NOTIFICATION_GROUP_ID);
		return reinterpret_cast<simconnect_clear_notification_group>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_ClearNotificationGroup"))(hSimConnect, GroupID);
    }

    SIMCONNECTAPI SimConnect_RequestNotificationGroup(HANDLE hSimConnect, SIMCONNECT_NOTIFICATION_GROUP_ID GroupID, DWORD dwReserved, DWORD Flags)
    {
		using simconnect_request_notification_group = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_NOTIFICATION_GROUP_ID, DWORD, DWORD);
		return reinterpret_cast<simconnect_request_notification_group>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_RequestNotificationGroup"))(hSimConnect, GroupID, dwReserved, Flags);
    }

    SIMCONNECTAPI SimConnect_AddToDataDefinition(HANDLE hSimConnect, SIMCONNECT_DATA_DEFINITION_ID DefineID, const char* DatumName, const char* UnitsName, SIMCONNECT_DATATYPE DatumType, float fEpsilon, DWORD DatumID)
    {
		using simconnect_add_to_data_definition = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_DATA_DEFINITION_ID, const char*, const char*, SIMCONNECT_DATATYPE, float, DWORD);
		return reinterpret_cast<simconnect_add_to_data_definition>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_AddToDataDefinition"))(hSimConnect, DefineID, DatumName, UnitsName, DatumType, fEpsilon, DatumID);
    }

    SIMCONNECTAPI SimConnect_ClearDataDefinition(HANDLE hSimConnect, SIMCONNECT_DATA_DEFINITION_ID DefineID)
    {
		using simconnect_clear_data_definition = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_DATA_DEFINITION_ID);
		return reinterpret_cast<simconnect_clear_data_definition>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_ClearDataDefinition"))(hSimConnect, DefineID);
    }

    SIMCONNECTAPI SimConnect_RequestDataOnSimObject(HANDLE hSimConnect, SIMCONNECT_DATA_REQUEST_ID RequestID, SIMCONNECT_DATA_DEFINITION_ID DefineID, SIMCONNECT_OBJECT_ID ObjectID, SIMCONNECT_PERIOD Period, SIMCONNECT_DATA_REQUEST_FLAG Flags, DWORD origin, DWORD interval, DWORD limit)
    {
		using simconnect_request_data_on_sim_object = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_DATA_REQUEST_ID, SIMCONNECT_DATA_DEFINITION_ID, SIMCONNECT_OBJECT_ID, SIMCONNECT_PERIOD, SIMCONNECT_DATA_REQUEST_FLAG, DWORD, DWORD, DWORD);
		return reinterpret_cast<simconnect_request_data_on_sim_object>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_RequestDataOnSimObject"))(hSimConnect, RequestID, DefineID, ObjectID, Period, Flags, origin, interval, limit);
    }

    SIMCONNECTAPI SimConnect_RequestDataOnSimObjectType(HANDLE hSimConnect, SIMCONNECT_DATA_REQUEST_ID RequestID, SIMCONNECT_DATA_DEFINITION_ID DefineID, DWORD dwRadiusMeters, SIMCONNECT_SIMOBJECT_TYPE type)
    {
		using simconnect_request_data_on_sim_object_type = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_DATA_REQUEST_ID, SIMCONNECT_DATA_DEFINITION_ID, DWORD, SIMCONNECT_SIMOBJECT_TYPE);
		return reinterpret_cast<simconnect_request_data_on_sim_object_type>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_RequestDataOnSimObjectType"))(hSimConnect, RequestID, DefineID, dwRadiusMeters, type);
    }

    SIMCONNECTAPI SimConnect_SetDataOnSimObject(HANDLE hSimConnect, SIMCONNECT_DATA_DEFINITION_ID DefineID, SIMCONNECT_OBJECT_ID ObjectID, SIMCONNECT_DATA_SET_FLAG Flags, DWORD ArrayCount, DWORD cbUnitSize, void* pDataSet)
    {
		using simconnect_set_data_on_sim_object = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_DATA_DEFINITION_ID, SIMCONNECT_OBJECT_ID, SIMCONNECT_DATA_SET_FLAG, DWORD, DWORD, void*);
		return reinterpret_cast<simconnect_set_data_on_sim_object>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_SetDataOnSimObject"))(hSimConnect, DefineID, ObjectID, Flags, ArrayCount, cbUnitSize, pDataSet);
    }

    SIMCONNECTAPI SimConnect_MapInputEventToClientEvent(HANDLE hSimConnect, SIMCONNECT_INPUT_GROUP_ID GroupID, const char* szInputDefinition, SIMCONNECT_CLIENT_EVENT_ID DownEventID, DWORD DownValue, SIMCONNECT_CLIENT_EVENT_ID UpEventID, DWORD UpValue, BOOL bMaskable)
    {
		using simconnect_map_input_event_to_client_event = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_INPUT_GROUP_ID, const char*, SIMCONNECT_CLIENT_EVENT_ID, DWORD, SIMCONNECT_CLIENT_EVENT_ID, DWORD, BOOL);
		return reinterpret_cast<simconnect_map_input_event_to_client_event>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_MapInputEventToClientEvent"))(hSimConnect, GroupID, szInputDefinition, DownEventID, DownValue, UpEventID, UpValue, bMaskable);
    }

    SIMCONNECTAPI SimConnect_SetInputGroupPriority(HANDLE hSimConnect, SIMCONNECT_INPUT_GROUP_ID GroupID, DWORD uPriority)
    {
		using simconnect_set_input_group_priority = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_INPUT_GROUP_ID, DWORD);
		return reinterpret_cast<simconnect_set_input_group_priority>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_SetInputGroupPriority"))(hSimConnect, GroupID, uPriority);
    }

    SIMCONNECTAPI SimConnect_RemoveInputEvent(HANDLE hSimConnect, SIMCONNECT_INPUT_GROUP_ID GroupID, const char* szInputDefinition)
    {
		using simconnect_remove_input_event = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_INPUT_GROUP_ID, const char*);
		return reinterpret_cast<simconnect_remove_input_event>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_RemoveInputEvent"))(hSimConnect, GroupID, szInputDefinition);
    }

    SIMCONNECTAPI SimConnect_ClearInputGroup(HANDLE hSimConnect, SIMCONNECT_INPUT_GROUP_ID GroupID)
    {
		using simconnect_clear_input_group = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_INPUT_GROUP_ID);
		return reinterpret_cast<simconnect_clear_input_group>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_ClearInputGroup"))(hSimConnect, GroupID);
    }

    SIMCONNECTAPI SimConnect_SetInputGroupState(HANDLE hSimConnect, SIMCONNECT_INPUT_GROUP_ID GroupID, DWORD dwState)
    {
		using simconnect_set_input_group_state = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_INPUT_GROUP_ID, DWORD);
		return reinterpret_cast<simconnect_set_input_group_state>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_SetInputGroupState"))(hSimConnect, GroupID, dwState);
    }

    SIMCONNECTAPI SimConnect_RequestReservedKey(HANDLE hSimConnect, SIMCONNECT_CLIENT_EVENT_ID EventID, const char* szKeyChoice1, const char* szKeyChoice2, const char* szKeyChoice3)
    {
        using simconnect_request_reserved_key = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_CLIENT_EVENT_ID, const char*, const char*, const char*);
		return reinterpret_cast<simconnect_request_reserved_key>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_RequestReservedKey"))(hSimConnect, EventID, szKeyChoice1, szKeyChoice2, szKeyChoice3);
    }

    SIMCONNECTAPI SimConnect_SubscribeToSystemEvent(HANDLE hSimConnect, SIMCONNECT_CLIENT_EVENT_ID EventID, const char* SystemEventName)
    {
		using simconnect_subscribe_to_system_event = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_CLIENT_EVENT_ID, const char*);
		return reinterpret_cast<simconnect_subscribe_to_system_event>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_SubscribeToSystemEvent"))(hSimConnect, EventID, SystemEventName);
    }

    SIMCONNECTAPI SimConnect_UnsubscribeFromSystemEvent(HANDLE hSimConnect, SIMCONNECT_CLIENT_EVENT_ID EventID)
    {
		using simconnect_unsubscribe_from_system_event = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_CLIENT_EVENT_ID);
		return reinterpret_cast<simconnect_unsubscribe_from_system_event>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_UnsubscribeFromSystemEvent"))(hSimConnect, EventID);
    }

    SIMCONNECTAPI SimConnect_WeatherRequestInterpolatedObservation(HANDLE hSimConnect, SIMCONNECT_DATA_REQUEST_ID RequestID, float lat, float lon, float alt)
    {
		using simconnect_weather_request_interpolated_observation = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_DATA_REQUEST_ID, float, float, float);
		return reinterpret_cast<simconnect_weather_request_interpolated_observation>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_WeatherRequestInterpolatedObservation"))(hSimConnect, RequestID, lat, lon, alt);
    }

    SIMCONNECTAPI SimConnect_WeatherRequestObservationAtStation(HANDLE hSimConnect, SIMCONNECT_DATA_REQUEST_ID RequestID, const char* szICAO)
    {
		using simconnect_weather_request_observation_at_station = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_DATA_REQUEST_ID, const char*);
		return reinterpret_cast<simconnect_weather_request_observation_at_station>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_WeatherRequestObservationAtStation"))(hSimConnect, RequestID, szICAO);
    }

    SIMCONNECTAPI SimConnect_WeatherRequestObservationAtNearestStation(HANDLE hSimConnect, SIMCONNECT_DATA_REQUEST_ID RequestID, float lat, float lon)
    {
		using simconnect_weather_request_observation_at_nearest_station = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_DATA_REQUEST_ID, float, float);
		return reinterpret_cast<simconnect_weather_request_observation_at_nearest_station>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_WeatherRequestObservationAtNearestStation"))(hSimConnect, RequestID, lat, lon);
    }

    SIMCONNECTAPI SimConnect_WeatherCreateStation(HANDLE hSimConnect, SIMCONNECT_DATA_REQUEST_ID RequestID, const char* szICAO, const char* szName, float lat, float lon, float alt)
    {
		using simconnect_weather_create_station = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_DATA_REQUEST_ID, const char*, const char*, float, float, float);
		return reinterpret_cast<simconnect_weather_create_station>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_WeatherCreateStation"))(hSimConnect, RequestID, szICAO, szName, lat, lon, alt);
    }

    SIMCONNECTAPI SimConnect_WeatherRemoveStation(HANDLE hSimConnect, SIMCONNECT_DATA_REQUEST_ID RequestID, const char* szICAO)
    {
		using simconnect_weather_remove_station = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_DATA_REQUEST_ID, const char*);
		return reinterpret_cast<simconnect_weather_remove_station>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_WeatherRemoveStation"))(hSimConnect, RequestID, szICAO);
    }

    SIMCONNECTAPI SimConnect_WeatherSetObservation(HANDLE hSimConnect, DWORD Seconds, const char* szMETAR)
    {
		using simconnect_weather_set_observation = HRESULT(__cdecl*)(HANDLE, DWORD, const char*);
		return reinterpret_cast<simconnect_weather_set_observation>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_WeatherSetObservation"))(hSimConnect, Seconds, szMETAR);
    }

    SIMCONNECTAPI SimConnect_WeatherSetModeServer(HANDLE hSimConnect, DWORD dwPort, DWORD dwSeconds)
    {
		using simconnect_weather_set_mode_server = HRESULT(__cdecl*)(HANDLE, DWORD, DWORD);
		return reinterpret_cast<simconnect_weather_set_mode_server>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_WeatherSetModeServer"))(hSimConnect, dwPort, dwSeconds);
    }

    SIMCONNECTAPI SimConnect_WeatherSetModeTheme(HANDLE hSimConnect, const char* szThemeName)
    {
		using simconnect_weather_set_mode_theme = HRESULT(__cdecl*)(HANDLE, const char*);
		return reinterpret_cast<simconnect_weather_set_mode_theme>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_WeatherSetModeTheme"))(hSimConnect, szThemeName);
    }

    SIMCONNECTAPI SimConnect_WeatherSetModeGlobal(HANDLE hSimConnect)
    {
		using simconnect_weather_set_mode_global = HRESULT(__cdecl*)(HANDLE);
		return reinterpret_cast<simconnect_weather_set_mode_global>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_WeatherSetModeGlobal"))(hSimConnect);
    }

    SIMCONNECTAPI SimConnect_WeatherSetModeCustom(HANDLE hSimConnect)
    {
		using simconnect_weather_set_mode_custom = HRESULT(__cdecl*)(HANDLE);
		return reinterpret_cast<simconnect_weather_set_mode_custom>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_WeatherSetModeCustom"))(hSimConnect);
    }

    SIMCONNECTAPI SimConnect_WeatherSetDynamicUpdateRate(HANDLE hSimConnect, DWORD dwRate)
    {
		using simconnect_weather_set_dynamic_update_rate = HRESULT(__cdecl*)(HANDLE, DWORD);
		return reinterpret_cast<simconnect_weather_set_dynamic_update_rate>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_WeatherSetDynamicUpdateRate"))(hSimConnect, dwRate);
    }

    SIMCONNECTAPI SimConnect_WeatherRequestCloudState(HANDLE hSimConnect, SIMCONNECT_DATA_REQUEST_ID RequestID, float minLat, float minLon, float minAlt, float maxLat, float maxLon, float maxAlt, DWORD dwFlags)
    {
		using simconnect_weather_request_cloud_state = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_DATA_REQUEST_ID, float, float, float, float, float, float, DWORD);
		return reinterpret_cast<simconnect_weather_request_cloud_state>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_WeatherRequestCloudState"))(hSimConnect, RequestID, minLat, minLon, minAlt, maxLat, maxLon, maxAlt, dwFlags);
    }

    SIMCONNECTAPI SimConnect_WeatherCreateThermal(HANDLE hSimConnect, SIMCONNECT_DATA_REQUEST_ID RequestID, float lat, float lon, float alt, float radius, float height, float coreRate, float coreTurbulence, float sinkRate, float sinkTurbulence, float coreSize, float coreTransitionSize, float sinkLayerSize, float sinkTransitionSize)
    {
		using simconnect_weather_create_thermal = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_DATA_REQUEST_ID, float, float, float, float, float, float, float, float, float, float, float, float, float);
		return reinterpret_cast<simconnect_weather_create_thermal>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_WeatherCreateThermal"))(hSimConnect, RequestID, lat, lon, alt, radius, height, coreRate, coreTurbulence, sinkRate, sinkTurbulence, coreSize, coreTransitionSize, sinkLayerSize, sinkTransitionSize);
    }

    SIMCONNECTAPI SimConnect_WeatherRemoveThermal(HANDLE hSimConnect, SIMCONNECT_OBJECT_ID ObjectID)
    {
		using simconnect_weather_remove_thermal = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_OBJECT_ID);
		return reinterpret_cast<simconnect_weather_remove_thermal>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_WeatherRemoveThermal"))(hSimConnect, ObjectID);
    }

    SIMCONNECTAPI SimConnect_AICreateParkedATCAircraft(HANDLE hSimConnect, const char* szContainerTitle, const char* szTailNumber, const char* szAirportID, SIMCONNECT_DATA_REQUEST_ID RequestID)
    {
		using simconnect_ai_create_parked_atc_aircraft = HRESULT(__cdecl*)(HANDLE, const char*, const char*, const char*, SIMCONNECT_DATA_REQUEST_ID);
		return reinterpret_cast<simconnect_ai_create_parked_atc_aircraft>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_AICreateParkedATCAircraft"))(hSimConnect, szContainerTitle, szTailNumber, szAirportID, RequestID);
    }

    SIMCONNECTAPI SimConnect_AICreateEnrouteATCAircraft(HANDLE hSimConnect, const char* szContainerTitle, const char* szTailNumber, int iFlightNumber, const char* szFlightPlanPath, double dFlightPlanPosition, BOOL bTouchAndGo, SIMCONNECT_DATA_REQUEST_ID RequestID)
    {
		using simconnect_ai_create_enroute_atc_aircraft = HRESULT(__cdecl*)(HANDLE, const char*, const char*, int, const char*, double, BOOL, SIMCONNECT_DATA_REQUEST_ID);
		return reinterpret_cast<simconnect_ai_create_enroute_atc_aircraft>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_AICreateEnrouteATCAircraft"))(hSimConnect, szContainerTitle, szTailNumber, iFlightNumber, szFlightPlanPath, dFlightPlanPosition, bTouchAndGo, RequestID);
    }

    SIMCONNECTAPI SimConnect_AICreateNonATCAircraft(HANDLE hSimConnect, const char* szContainerTitle, const char* szTailNumber, SIMCONNECT_DATA_INITPOSITION InitPos, SIMCONNECT_DATA_REQUEST_ID RequestID)
    {
        using simconnect_ai_create_non_atc_aircraft = HRESULT(__cdecl*)(HANDLE, const char*, const char*, SIMCONNECT_DATA_INITPOSITION, SIMCONNECT_DATA_REQUEST_ID);
        return reinterpret_cast<simconnect_ai_create_non_atc_aircraft>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_AICreateNonATCAircraft"))(hSimConnect, szContainerTitle, szTailNumber, InitPos, RequestID);
    }

    SIMCONNECTAPI SimConnect_AICreateSimulatedObject(HANDLE hSimConnect, const char* szContainerTitle, SIMCONNECT_DATA_INITPOSITION InitPos, SIMCONNECT_DATA_REQUEST_ID RequestID)
    {
		using simconnect_ai_create_simulated_object = HRESULT(__cdecl*)(HANDLE, const char*, SIMCONNECT_DATA_INITPOSITION, SIMCONNECT_DATA_REQUEST_ID);
		return reinterpret_cast<simconnect_ai_create_simulated_object>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_AICreateSimulatedObject"))(hSimConnect, szContainerTitle, InitPos, RequestID);
    }

    SIMCONNECTAPI SimConnect_AIReleaseControl(HANDLE hSimConnect, SIMCONNECT_OBJECT_ID ObjectID, SIMCONNECT_DATA_REQUEST_ID RequestID)
    {
		using simconnect_ai_release_control = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_OBJECT_ID, SIMCONNECT_DATA_REQUEST_ID);
		return reinterpret_cast<simconnect_ai_release_control>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_AIReleaseControl"))(hSimConnect, ObjectID, RequestID);
    }

    SIMCONNECTAPI SimConnect_AIRemoveObject(HANDLE hSimConnect, SIMCONNECT_OBJECT_ID ObjectID, SIMCONNECT_DATA_REQUEST_ID RequestID)
    {
		using simconnect_ai_remove_object = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_OBJECT_ID, SIMCONNECT_DATA_REQUEST_ID);
		return reinterpret_cast<simconnect_ai_remove_object>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_AIRemoveObject"))(hSimConnect, ObjectID, RequestID);
    }

    SIMCONNECTAPI SimConnect_AISetAircraftFlightPlan(HANDLE hSimConnect, SIMCONNECT_OBJECT_ID ObjectID, const char* szFlightPlanPath, SIMCONNECT_DATA_REQUEST_ID RequestID)
    {
		using simconnect_ai_set_aircraft_flight_plan = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_OBJECT_ID, const char*, SIMCONNECT_DATA_REQUEST_ID);
		return reinterpret_cast<simconnect_ai_set_aircraft_flight_plan>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_AISetAircraftFlightPlan"))(hSimConnect, ObjectID, szFlightPlanPath, RequestID);
    }

    SIMCONNECTAPI SimConnect_ExecuteMissionAction(HANDLE hSimConnect, const simconnect::raw::GUID guidInstanceId)
    {
		using simconnect_execute_mission_action = HRESULT(__cdecl*)(HANDLE, const simconnect::raw::GUID);
		return reinterpret_cast<simconnect_execute_mission_action>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_ExecuteMissionAction"))(hSimConnect, guidInstanceId);
    }

    SIMCONNECTAPI SimConnect_CompleteCustomMissionAction(HANDLE hSimConnect, const simconnect::raw::GUID guidInstanceId)
    {
		using simconnect_complete_custom_mission_action = HRESULT(__cdecl*)(HANDLE, const simconnect::raw::GUID);
		return reinterpret_cast<simconnect_complete_custom_mission_action>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_CompleteCustomMissionAction"))(hSimConnect, guidInstanceId);
    }

    SIMCONNECTAPI SimConnect_Close(HANDLE hSimConnect)
    {
		using simconnect_close = HRESULT(__cdecl*)(HANDLE);
		return reinterpret_cast<simconnect_close>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_Close"))(hSimConnect);
    }

    SIMCONNECTAPI SimConnect_RetrieveString(SIMCONNECT_RECV* pData, DWORD cbData, void* pStringV, char** pszString, DWORD* pcbString)
    {
		using simconnect_retrieve_string = HRESULT(__cdecl*)(SIMCONNECT_RECV*, DWORD, void*, char**, DWORD*);
		return reinterpret_cast<simconnect_retrieve_string>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_RetrieveString"))(pData, cbData, pStringV, pszString, pcbString);
    }

    SIMCONNECTAPI SimConnect_GetLastSentPacketID(HANDLE hSimConnect, DWORD* pdwError)
    {
		using simconnect_get_last_sent_packet_id = HRESULT(__cdecl*)(HANDLE, DWORD*);
		return reinterpret_cast<simconnect_get_last_sent_packet_id>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_GetLastSentPacketID"))(hSimConnect, pdwError);
    }

    SIMCONNECTAPI SimConnect_Open(HANDLE* phSimConnect, LPCSTR szName, HWND hWnd, DWORD UserEventWin32, HANDLE hEventHandle, DWORD ConfigIndex)
    {
		using simconnect_open = HRESULT(__cdecl*)(HANDLE*, LPCSTR, HWND, DWORD, HANDLE, DWORD);
		return reinterpret_cast<simconnect_open>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_Open"))(phSimConnect, szName, hWnd, UserEventWin32, hEventHandle, ConfigIndex);
    }

    SIMCONNECTAPI SimConnect_CallDispatch(HANDLE hSimConnect, DispatchProc pfcnDispatch, void* pContext)
    {
        using simconnect_call_dispatch = HRESULT(__cdecl*)(HANDLE, DispatchProc, void*);
        return reinterpret_cast<simconnect_call_dispatch>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_CallDispatch"))(hSimConnect, pfcnDispatch, pContext);
    }

    SIMCONNECTAPI SimConnect_GetNextDispatch(HANDLE hSimConnect, SIMCONNECT_RECV** ppData, DWORD* pcbData)
    {
		using simconnect_get_next_dispatch = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_RECV**, DWORD*);
		return reinterpret_cast<simconnect_get_next_dispatch>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_GetNextDispatch"))(hSimConnect, ppData, pcbData);
    }

    SIMCONNECTAPI SimConnect_RequestResponseTimes(HANDLE hSimConnect, DWORD nCount, float* fElapsedSeconds)
    {
		using simconnect_request_response_times = HRESULT(__cdecl*)(HANDLE, DWORD, float*);
		return reinterpret_cast<simconnect_request_response_times>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_RequestResponseTimes"))(hSimConnect, nCount, fElapsedSeconds);
    }

    SIMCONNECTAPI SimConnect_InsertString(char* pDest, DWORD cbDest, void** ppEnd, DWORD* pcbStringV, const char* pSource)
    {
		using simconnect_insert_string = HRESULT(__cdecl*)(char*, DWORD, void**, DWORD*, const char*);
		return reinterpret_cast<simconnect_insert_string>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_InsertString"))(pDest, cbDest, ppEnd, pcbStringV, pSource);
    }

    SIMCONNECTAPI SimConnect_CameraSetRelative6DOF(HANDLE hSimConnect, float fDeltaX, float fDeltaY, float fDeltaZ, float fPitchDeg, float fBankDeg, float fHeadingDeg)
    {
		using simconnect_camera_set_relative_6dof = HRESULT(__cdecl*)(HANDLE, float, float, float, float, float, float);
		return reinterpret_cast<simconnect_camera_set_relative_6dof>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_CameraSetRelative6DOF"))(hSimConnect, fDeltaX, fDeltaY, fDeltaZ, fPitchDeg, fBankDeg, fHeadingDeg);
    }

    SIMCONNECTAPI SimConnect_MenuAddItem(HANDLE hSimConnect, const char* szMenuItem, SIMCONNECT_CLIENT_EVENT_ID MenuEventID, DWORD dwData)
    {
		using simconnect_menu_add_item = HRESULT(__cdecl*)(HANDLE, const char*, SIMCONNECT_CLIENT_EVENT_ID, DWORD);
		return reinterpret_cast<simconnect_menu_add_item>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_MenuAddItem"))(hSimConnect, szMenuItem, MenuEventID, dwData);
    }

    SIMCONNECTAPI SimConnect_MenuDeleteItem(HANDLE hSimConnect, SIMCONNECT_CLIENT_EVENT_ID MenuEventID)
    {
		using simconnect_menu_delete_item = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_CLIENT_EVENT_ID);
		return reinterpret_cast<simconnect_menu_delete_item>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_MenuDeleteItem"))(hSimConnect, MenuEventID);
    }

    SIMCONNECTAPI SimConnect_MenuAddSubItem(HANDLE hSimConnect, SIMCONNECT_CLIENT_EVENT_ID MenuEventID, const char* szMenuItem, SIMCONNECT_CLIENT_EVENT_ID SubMenuEventID, DWORD dwData)
    {
		using simconnect_menu_add_sub_item = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_CLIENT_EVENT_ID, const char*, SIMCONNECT_CLIENT_EVENT_ID, DWORD);
		return reinterpret_cast<simconnect_menu_add_sub_item>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_MenuAddSubItem"))(hSimConnect, MenuEventID, szMenuItem, SubMenuEventID, dwData);
    }

    SIMCONNECTAPI SimConnect_MenuDeleteSubItem(HANDLE hSimConnect, SIMCONNECT_CLIENT_EVENT_ID MenuEventID, const SIMCONNECT_CLIENT_EVENT_ID SubMenuEventID)
    {
		using simconnect_menu_delete_sub_item = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_CLIENT_EVENT_ID, const SIMCONNECT_CLIENT_EVENT_ID);
		return reinterpret_cast<simconnect_menu_delete_sub_item>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_MenuDeleteSubItem"))(hSimConnect, MenuEventID, SubMenuEventID);
    }

    SIMCONNECTAPI SimConnect_RequestSystemState(HANDLE hSimConnect, SIMCONNECT_DATA_REQUEST_ID RequestID, const char* szState)
    {
		using simconnect_request_system_state = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_DATA_REQUEST_ID, const char*);
		return reinterpret_cast<simconnect_request_system_state>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_RequestSystemState"))(hSimConnect, RequestID, szState);
    }

    SIMCONNECTAPI SimConnect_SetSystemState(HANDLE hSimConnect, const char* szState, DWORD dwInteger, float fFloat, const char* szString)
    {
		using simconnect_set_system_state = HRESULT(__cdecl*)(HANDLE, const char*, DWORD, float, const char*);
		return reinterpret_cast<simconnect_set_system_state>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_SetSystemState"))(hSimConnect, szState, dwInteger, fFloat, szString);
    }

    SIMCONNECTAPI SimConnect_MapClientDataNameToID(HANDLE hSimConnect, const char* szClientDataName, SIMCONNECT_CLIENT_DATA_ID ClientDataID)
    {
		using simconnect_map_client_data_name_to_id = HRESULT(__cdecl*)(HANDLE, const char*, SIMCONNECT_CLIENT_DATA_ID);
		return reinterpret_cast<simconnect_map_client_data_name_to_id>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_MapClientDataNameToID"))(hSimConnect, szClientDataName, ClientDataID);
    }

    SIMCONNECTAPI SimConnect_CreateClientData(HANDLE hSimConnect, SIMCONNECT_CLIENT_DATA_ID ClientDataID, DWORD dwSize, SIMCONNECT_CREATE_CLIENT_DATA_FLAG Flags)
    {
		using simconnect_create_client_data = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_CLIENT_DATA_ID, DWORD, SIMCONNECT_CREATE_CLIENT_DATA_FLAG);
		return reinterpret_cast<simconnect_create_client_data>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_CreateClientData"))(hSimConnect, ClientDataID, dwSize, Flags);
    }

    SIMCONNECTAPI SimConnect_AddToClientDataDefinition(HANDLE hSimConnect, SIMCONNECT_CLIENT_DATA_DEFINITION_ID DefineID, DWORD dwOffset, DWORD dwSizeOrType, float fEpsilon, DWORD DatumID)
    {
		using simconnect_add_to_client_data_definition = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_CLIENT_DATA_DEFINITION_ID, DWORD, DWORD, float, DWORD);
		return reinterpret_cast<simconnect_add_to_client_data_definition>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_AddToClientDataDefinition"))(hSimConnect, DefineID, dwOffset, dwSizeOrType, fEpsilon, DatumID);
    }

    SIMCONNECTAPI SimConnect_ClearClientDataDefinition(HANDLE hSimConnect, SIMCONNECT_CLIENT_DATA_DEFINITION_ID DefineID)
    {
		using simconnect_clear_client_data_definition = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_CLIENT_DATA_DEFINITION_ID);
		return reinterpret_cast<simconnect_clear_client_data_definition>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_ClearClientDataDefinition"))(hSimConnect, DefineID);
    }

    SIMCONNECTAPI SimConnect_RequestClientData(HANDLE hSimConnect, SIMCONNECT_CLIENT_DATA_ID ClientDataID, SIMCONNECT_DATA_REQUEST_ID RequestID, SIMCONNECT_CLIENT_DATA_DEFINITION_ID DefineID, SIMCONNECT_CLIENT_DATA_PERIOD Period, SIMCONNECT_CLIENT_DATA_REQUEST_FLAG Flags, DWORD origin, DWORD interval, DWORD limit)
    {
		using simconnect_request_client_data = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_CLIENT_DATA_ID, SIMCONNECT_DATA_REQUEST_ID, SIMCONNECT_CLIENT_DATA_DEFINITION_ID, SIMCONNECT_CLIENT_DATA_PERIOD, SIMCONNECT_CLIENT_DATA_REQUEST_FLAG, DWORD, DWORD, DWORD);
		return reinterpret_cast<simconnect_request_client_data>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_RequestClientData"))(hSimConnect, ClientDataID, RequestID, DefineID, Period, Flags, origin, interval, limit);
    }

    SIMCONNECTAPI SimConnect_SetClientData(HANDLE hSimConnect, SIMCONNECT_CLIENT_DATA_ID ClientDataID, SIMCONNECT_CLIENT_DATA_DEFINITION_ID DefineID, SIMCONNECT_CLIENT_DATA_SET_FLAG Flags, DWORD dwReserved, DWORD cbUnitSize, void* pDataSet)
    {
		using simconnect_set_client_data = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_CLIENT_DATA_ID, SIMCONNECT_CLIENT_DATA_DEFINITION_ID, SIMCONNECT_CLIENT_DATA_SET_FLAG, DWORD, DWORD, void*);
		return reinterpret_cast<simconnect_set_client_data>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_SetClientData"))(hSimConnect, ClientDataID, DefineID, Flags, dwReserved, cbUnitSize, pDataSet);
    }

    SIMCONNECTAPI SimConnect_FlightLoad(HANDLE hSimConnect, const char* szFileName)
    {
        using simconnect_flight_load = HRESULT(__cdecl*)(HANDLE, const char*);
		return reinterpret_cast<simconnect_flight_load>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_FlightLoad"))(hSimConnect, szFileName);
    }

    SIMCONNECTAPI SimConnect_FlightSave(HANDLE hSimConnect, const char* szFileName, const char* szTitle, const char* szDescription, DWORD Flags)
    {
		using simconnect_flight_save = HRESULT(__cdecl*)(HANDLE, const char*, const char*, const char*, DWORD);
		return reinterpret_cast<simconnect_flight_save>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_FlightSave"))(hSimConnect, szFileName, szTitle, szDescription, Flags);
    }

    SIMCONNECTAPI SimConnect_FlightPlanLoad(HANDLE hSimConnect, const char* szFileName)
    {
		using simconnect_flight_plan_load = HRESULT(__cdecl*)(HANDLE, const char*);
		return reinterpret_cast<simconnect_flight_plan_load>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_FlightPlanLoad"))(hSimConnect, szFileName);
    }

    SIMCONNECTAPI SimConnect_Text(HANDLE hSimConnect, SIMCONNECT_TEXT_TYPE type, float fTimeSeconds, SIMCONNECT_CLIENT_EVENT_ID EventID, DWORD cbUnitSize, void* pDataSet)
    {
		using simconnect_text = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_TEXT_TYPE, float, SIMCONNECT_CLIENT_EVENT_ID, DWORD, void*);
		return reinterpret_cast<simconnect_text>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_Text"))(hSimConnect, type, fTimeSeconds, EventID, cbUnitSize, pDataSet);
    }

    SIMCONNECTAPI SimConnect_SubscribeToFacilities(HANDLE hSimConnect, SIMCONNECT_FACILITY_LIST_TYPE type, SIMCONNECT_DATA_REQUEST_ID RequestID)
    {
		using simconnect_subscribe_to_facilities = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_FACILITY_LIST_TYPE, SIMCONNECT_DATA_REQUEST_ID);
		return reinterpret_cast<simconnect_subscribe_to_facilities>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_SubscribeToFacilities"))(hSimConnect, type, RequestID);
    }

    SIMCONNECTAPI SimConnect_UnsubscribeToFacilities(HANDLE hSimConnect, SIMCONNECT_FACILITY_LIST_TYPE type)
    {
		using simconnect_unsubscribe_to_facilities = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_FACILITY_LIST_TYPE);
		return reinterpret_cast<simconnect_unsubscribe_to_facilities>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_UnsubscribeToFacilities"))(hSimConnect, type);
    }

    SIMCONNECTAPI SimConnect_RequestFacilitiesList(HANDLE hSimConnect, SIMCONNECT_FACILITY_LIST_TYPE type, SIMCONNECT_DATA_REQUEST_ID RequestID)
    {
		using simconnect_request_facilities_list = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_FACILITY_LIST_TYPE, SIMCONNECT_DATA_REQUEST_ID);
		return reinterpret_cast<simconnect_request_facilities_list>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_RequestFacilitiesList"))(hSimConnect, type, RequestID);
    }

    SIMCONNECTAPI SimConnect_TransmitClientEvent_EX1(HANDLE hSimConnect, SIMCONNECT_OBJECT_ID ObjectID, SIMCONNECT_CLIENT_EVENT_ID EventID, SIMCONNECT_NOTIFICATION_GROUP_ID GroupID, SIMCONNECT_EVENT_FLAG Flags, DWORD dwData0, DWORD dwData1, DWORD dwData2, DWORD dwData3, DWORD dwData4)
    {
		using simconnect_transmit_client_event_ex1 = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_OBJECT_ID, SIMCONNECT_CLIENT_EVENT_ID, SIMCONNECT_NOTIFICATION_GROUP_ID, SIMCONNECT_EVENT_FLAG, DWORD, DWORD, DWORD, DWORD, DWORD);
		return reinterpret_cast<simconnect_transmit_client_event_ex1>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_TransmitClientEvent_EX1"))(hSimConnect, ObjectID, EventID, GroupID, Flags, dwData0, dwData1, dwData2, dwData3, dwData4);
    }

    SIMCONNECTAPI SimConnect_AddToFacilityDefinition(HANDLE hSimConnect, SIMCONNECT_DATA_DEFINITION_ID DefineID, const char* FieldName)
    {
		using simconnect_add_to_facility_definition = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_DATA_DEFINITION_ID, const char*);
		return reinterpret_cast<simconnect_add_to_facility_definition>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_AddToFacilityDefinition"))(hSimConnect, DefineID, FieldName);
    }

    SIMCONNECTAPI SimConnect_RequestFacilityData(HANDLE hSimConnect, SIMCONNECT_DATA_DEFINITION_ID DefineID, SIMCONNECT_DATA_REQUEST_ID RequestID, const char* ICAO, const char* Region)
    {
		using simconnect_request_facility_data = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_DATA_DEFINITION_ID, SIMCONNECT_DATA_REQUEST_ID, const char*, const char*);
		return reinterpret_cast<simconnect_request_facility_data>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_RequestFacilityData"))(hSimConnect, DefineID, RequestID, ICAO, Region);
    }

    SIMCONNECTAPI SimConnect_SubscribeToFacilities_EX1(HANDLE hSimConnect, SIMCONNECT_FACILITY_LIST_TYPE type, SIMCONNECT_DATA_REQUEST_ID newElemInRangeRequestID, SIMCONNECT_DATA_REQUEST_ID oldElemOutRangeRequestID)
    {
		using simconnect_subscribe_to_facilities_ex1 = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_FACILITY_LIST_TYPE, SIMCONNECT_DATA_REQUEST_ID, SIMCONNECT_DATA_REQUEST_ID);
		return reinterpret_cast<simconnect_subscribe_to_facilities_ex1>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_SubscribeToFacilities_EX1"))(hSimConnect, type, newElemInRangeRequestID, oldElemOutRangeRequestID);
    }

    SIMCONNECTAPI SimConnect_UnsubscribeToFacilities_EX1(HANDLE hSimConnect, SIMCONNECT_FACILITY_LIST_TYPE type, bool bUnsubscribeNewInRange, bool bUnsubscribeOldOutRange)
    {
		using simconnect_unsubscribe_to_facilities_ex1 = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_FACILITY_LIST_TYPE, bool, bool);
		return reinterpret_cast<simconnect_unsubscribe_to_facilities_ex1>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_UnsubscribeToFacilities_EX1"))(hSimConnect, type, bUnsubscribeNewInRange, bUnsubscribeOldOutRange);
    }

    SIMCONNECTAPI SimConnect_RequestFacilitiesList_EX1(HANDLE hSimConnect, SIMCONNECT_FACILITY_LIST_TYPE type, SIMCONNECT_DATA_REQUEST_ID RequestID)
    {
		using simconnect_request_facilities_list_ex1 = HRESULT(__cdecl*)(HANDLE, SIMCONNECT_FACILITY_LIST_TYPE, SIMCONNECT_DATA_REQUEST_ID);
		return reinterpret_cast<simconnect_request_facilities_list_ex1>(GetProcAddress(static_cast<HMODULE>(SimConnectLoader::module), "SimConnect_RequestFacilitiesList_EX1"))(hSimConnect, type, RequestID);
    }
}
