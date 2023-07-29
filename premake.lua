workspace "HazelEngine"
	configurations {
		"Debug", 
		"Release",
		"Dist"			-- 发行版
	}
	architecture "x64"

outputdir = "%(cfg.buildcfg)-%(cfg.system)-%(cfg.architecture)"

project "Hazel"
	
	location "Hazel"									-- Project path
	kind "SharedLib"									-- 类型 输出dll
	language "C++"	

	targetdir ("bin/" .. outputdir .. "/%(prj.name)")	-- output directory
	objdir ("bin-int/" .. outputdir .. "/%(prj.name)")	-- intermedia directory: .obj file

	files												-- Source files
	{
		"%(prj.name)/src/**.h",
		"%(pfj.name)/src/**.cpp"
	}
	
	includedirs
	{
		"%(prj.name)/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "10.0 (latest installed version)"

		define
		{
			"HAZEL_BUILD_DLL",
			"HAZEL_PLATFORM_WINDOWS"
		}
		
		postbuildcommand
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		define "HAZEL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		define "HAZEL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		define "HAZEL_DIST"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir "bin/" .. outputdir .. "/%(prj.name)"
	objdir "bin/" .. outputdir .. "/%(prj.name)"

	files												-- source file
	{
		"%(prj.name)/src/**.h",
		"%(prj.name)/src/**.cpp"
	}

	includedirs											-- include directory
	{
		"Hazel/vendor/spdlog/include",
		"Hazel/src"
	}

	links
	{
		"Hazel"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0 (latest installed version)"

		define
		{
			"HAZEL_PLATFORM_WINDOWS",

		}

	filter "configurations:Debug"
		define "HAZEL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		define "HAZEL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		define "HAZEL_DIST"
		optimize "On"


