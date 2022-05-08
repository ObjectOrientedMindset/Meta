workspace "Meta"
	architecture "x64"


	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"



include "Meta/vendor/Glad"

project "Meta"
	location "Meta"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mtpch.h"
	pchsource "Meta/src/mtpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/imgui/*.h",
		"%{prj.name}/vendor/imgui/*.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/SFML/include",
		"%{prj.name}/vendor/Glad/include",
		"%{prj.name}/vendor",
		"%{prj.name}/src"
	}
	
	libdirs
	{
		"%{prj.name}/vendor/SFML/lib",
		"Glad"
	}

	links
	{
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "c++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MT_PLATFORM_WINDOWS",
			"MT_BUILD_DLL"
		}

	postbuildcommands { ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox") }
	postbuildcommands { ("{COPY} ../vendor/bin/sfml-dll ../bin/" .. outputdir .. "/Sandbox") }

	filter "configurations:Debug"
		defines "MT_DEBUG"
		symbols "On"
		links
		{
			"sfml-system-d.lib",
			"sfml-graphics-d.lib",
			"sfml-window-d.lib",
			"sfml-audio-d.lib",
			"sfml-network-d.lib"
		}

	filter "configurations:Release"
		defines "MT_RELEASE"
		optimize "On"
		links
		{
			"sfml-system.lib",
			"sfml-graphics.lib",
			"sfml-window.lib",
			"sfml-audio.lib",
			"sfml-network.lib"
		}

	filter "configurations:Dist"
		defines "MT_DIST"
		optimize "On"
		links
		{
			"sfml-system.lib",
			"sfml-graphics.lib",
			"sfml-window.lib",
			"sfml-audio.lib",
			"sfml-network.lib"
		}

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Sandbox/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Meta/vendor/spdlog/include",
		"Meta/vendor/SFML/include",
		"Meta/src"
	}

	libdirs
	{
		"Meta/vendor/SFML/lib"
	}

	links
	{
		"Meta"
	}

	filter "system:windows"
		cppdialect "c++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MT_PLATFORM_WINDOWS"
		}

	
	filter "configurations:Debug"
		defines "MT_DEBUG"
		symbols "On"
		links
		{
			"sfml-system-d.lib",
			"sfml-graphics-d.lib",
			"sfml-window-d.lib",
			"sfml-audio-d.lib",
			"sfml-network-d.lib"
		}

	filter "configurations:Release"
		defines "MT_RELEASE"
		optimize "On"
		links
		{
			"sfml-system.lib",
			"sfml-graphics.lib",
			"sfml-window.lib",
			"sfml-audio.lib",
			"sfml-network.lib"
		}

	filter "configurations:Dist"
		defines "MT_DIST"
		optimize "On"
		links
		{
			"sfml-system.lib",
			"sfml-graphics.lib",
			"sfml-window.lib",
			"sfml-audio.lib",
			"sfml-network.lib"
		}