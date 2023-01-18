project "core"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cpch.h"
	pchsource "src/cpch.cpp"

	files
	{
		"src/**.cpp",
		"include/**.h"
	}

	includedirs
	{
		"src",
		"include",
		"../vendor/SimConnect/include",
		"../vendor/brynet/include",
	}

	-- Used for the brynet library
	defines
	{
		"_SILENCE_CXX20_IS_POD_DEPRECATION_WARNING",
		"_SILENCE_CXX17_C_HEADER_DEPRECATION_WARNING"
	}

	filter "configurations:Debug"
		defines "_DEBUG"
		runtime "Debug"
		symbols "on"
		optimize "off"

	filter "configurations:Release"
		defines "_RELEASE"
		runtime "Release"
		symbols "off"
		optimize "on"
