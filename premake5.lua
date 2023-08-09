workspace "HazelEngine"
	configurations {
		"Debug", 
		"Release",
		"Dist"			-- 发行版
	}
	architecture "x64"
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"

include "Hazel/vendor/GLFW"

project "Hazel"
	
	location "Hazel"									-- Project path
	kind "SharedLib"									-- 类型 输出dll
	language "C++"	
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")	-- output directory
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")	-- intermedia directory: .obj file

	-- pchheader "Hazelpch.h"
	-- pchsource "Hazel/src/Hazelpch.cpp"

	files												-- Source files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"HAZEL_BUILD_DLL",
			"HAZEL_PLATFORM_WINDOWS"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "HAZEL_DEBUG"
		symbols "On"
		buildoptions "/MDd"

	filter "configurations:Release"
		defines "HAZEL_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "HAZEL_DIST"
		buildoptions "/MD"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/" .. outputdir .. "/%{prj.name}")

	files												-- source file
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs											-- include directory
	{
		"Hazel/vendor/spdlog/include",
		"Hazel/src"
	}

	links												-- Links of multi project 
	{
		"Hazel"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"HAZEL_PLATFORM_WINDOWS",

		}

	filter "configurations:Debug"
		defines "HAZEL_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "HAZEL_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "HAZEL_DIST"
		buildoptions "/MD"
		optimize "On"


