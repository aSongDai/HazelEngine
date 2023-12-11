workspace "HazelEngine"
	startproject "Sandbox"

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
IncludeDir["GLFW"]	=	"Hazel/vendor/GLFW/include"
IncludeDir["Glad"]	=	"Hazel/vendor/Glad/include"
IncludeDir["ImGui"] =	"Hazel/vendor/imgui"
IncludeDir["glm"]	=	"Hazel/vendor/glm"

include "Hazel/vendor/GLFW"
include "Hazel/vendor/Glad"
include "Hazel/vendor/imgui"


project "Hazel"
	
	location "Hazel"									-- Project path
	kind "StaticLib"									-- 类型 输出dll SharedLib  -->  切换成静态 StaticLib
	language "C++"	
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")	-- output directory
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")	-- intermedia directory: .obj file

	-- pchheader "Hazelpch.h"
	-- pchsource "Hazel/src/Hazelpch.cpp"

	files												-- Source files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp",
		"%{IncludeDir.glm}/glm/*.hpp",
		"%{IncludeDir.glm}/glm/*.inl"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",

	}

	links{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"  
		systemversion "latest"

		defines
		{
			"HAZEL_BUILD_DLL",
			"HAZEL_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
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
	cppdialect "C++17"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/" .. outputdir .. "/%{prj.name}")

	files												-- source file
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{IncludeDir.glm}/glm/*.hpp",
		"%{IncludeDir.glm}/glm/*.inl"
	}

	includedirs											-- include directory
	{
		"Hazel/vendor/spdlog/include",
		"Hazel/vendor/Glad/include",
		"Hazel/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}"
	}

	links												-- Links of multi project 
	{
		"Hazel"
	}

	filter "system:windows"
		staticruntime "on"
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


