project "server"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	links
	{
		"core"
	}

	pchheader "spch.h"
	pchsource "src/spch.cpp"

	files
	{
		"src/**.cpp",
		"include/**.h"
	}

	includedirs
	{
		"src",
		"include",
		"../core/include",
		"../vendor/brynet/include",
		"../vendor/SimConnect/include"
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
