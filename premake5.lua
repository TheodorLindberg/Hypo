workspace "Hypo"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


IncludeDir = {}
IncludeDir["spdlog"] = "vendor/spdlog/include"
IncludeDir["ImGui"] = "vendor/imgui"
IncludeDir["glm"] = "vendor/glm/include"

IncludeDir["GLFW"] = "HypoWindow/vendor/GLFW/include"

IncludeDir["stb_image"] = "Hypo3D/vendor/stb_image/include"
IncludeDir["glad"] = "Hypo3D/vendor/glad/include"
IncludeDir["assimp"] = "Hypo3D/vendor/assimp/include"

IncludeDir["HypoMain"] = "HypoMain/src"
IncludeDir["HypoWindow"] = "HypoWindow/src"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
group "Dependencies"
include "Hypo3D/vendor/glad"
include "HypoWindow/vendor/GLFW"
include "vendor/imgui"

group ""
project "HypoMain"
	location "HypoMain"
    kind "SharedLib"
    language "C++"
    staticruntime "on"
    
	targetdir ("bin/" .. outputdir)
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "mainpch.h"
	pchsource "HypoMain/src/mainpch.cpp"
	links
	{

	}
    files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	includedirs
	{
        "%{prj.name}/src",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}"
	}
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"HYPO_PLATFORM_WINDOWS",
		"HYPO_MAIN_EXPORTS"
	}

	cppdialect "C++17"
	systemversion "latest"
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		runtime "Release"
		optimize "On"

project "HypoWindow"
	location "HypoWindow"
    kind "SharedLib"
    language "C++"
    staticruntime "on"
    
	targetdir ("bin/" .. outputdir)
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "windowpch.h"
	pchsource "HypoWindow/src/windowpch.cpp"
	links
	{
		"GLFW",
		"glad",
		"ImGui",
		"HypoMain"
	}
    files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	includedirs
	{
        "%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.HypoMain}"
	}
	defines
	{
		"HYPO_PLATFORM_WINDOWS",
		"_CRT_SECURE_NO_WARNINGS",
		"HYPO_WINDOW_EXPORTS"
	}

	cppdialect "C++17"
	systemversion "latest"
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		runtime "Release"
		optimize "On"




project "Hypo3D"
	location "Hypo3D"
	kind "SharedLib"
	language "C++"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir)
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "hypo3dpch.h"
	pchsource "Hypo3D/src/hypo3dpch.cpp"
	links
	{
		"glad",
		"opengl32.lib",
		"ImGui",
		"Hypo3D/vendor/assimp/assimp.lib",
		"HypoMain",
		"HypoWindow"
	}
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.HypoMain}",
		"%{IncludeDir.HypoWindow}"
	}
	defines
	{
		"HYPO_PLATFORM_WINDOWS",
		"_CRT_SECURE_NO_WARNINGS",
		"HYPO_3D_EXPORTS"
	}

	cppdialect "C++17"
	systemversion "latest"
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		runtime "Release"
		optimize "On"




project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir)
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	links
	{
		"HypoMain",
		"HypoWindow"
	}
	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
		"%{prj.name}/res/**",
	}
	includedirs
	{
		"%{prj.name}/src/",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.ImGui}",

		"%{IncludeDir.HypoWindow}",
		"%{IncludeDir.HypoMain}",
		"%{IncludeDir.Hypo3D}",


	}
	defines
	{
		"HYPO_PLATFORM_WINDOWS"
	}
	cppdialect "C++17"
	systemversion "latest"
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		runtime "Release"
		optimize "On"
