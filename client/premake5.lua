project "client"
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
		"../core/include",
		"../vendor/SimConnect/include"
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
