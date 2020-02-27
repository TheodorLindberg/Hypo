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
IncludeDir["GSL"] = "vendor/GSL/include"

IncludeDir["GLFW"] = "HypoWindow/vendor/GLFW/include"

IncludeDir["stb_image"] = "Hypo3D/vendor/stb_image/include"
IncludeDir["glad"] = "Hypo3D/vendor/glad/include"
IncludeDir["assimp"] = "Hypo3D/vendor/assimp/include"

IncludeDir["HypoSystem"] = "HypoSystem/src"
IncludeDir["HypoWindow"] = "HypoWindow/src"
IncludeDir["Hypo3D"] = "Hypo3D/src"
IncludeDir["Graphics"] = "HypoGraphics/src"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
group "Dependencies"
include "Hypo3D/vendor/glad"
include "HypoWindow/vendor/GLFW"
include "vendor/imgui"

group ""
project "HypoSystem"
	location "HypoSystem"
    kind "SharedLib"
    language "C++"
    staticruntime "on"
    
	targetdir ("bin/" .. outputdir)
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "systempch.h"
	pchsource "HypoSystem/src/systempch.cpp"
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
		"HYPO_SYSTEM_EXPORTS"
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
		"HypoSystem"
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
		"%{IncludeDir.HypoSystem}",
		"%{IncludeDir.HypoWindow}",
		"%{IncludeDir.Hypo3D}",
		"%{IncludeDir.GSL}"
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



project "HypoGraphics"
	location "HypoGraphics"
	kind "SharedLib"
	language "C++"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir)
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "graphicspch.h"
	pchsource "HypoGraphics/src/graphicspch.cpp"
	links
	{
		"GLFW",
		"glad",
		"ImGui",
		"HypoSystem",
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
		"%{IncludeDir.HypoSystem}",
		"%{IncludeDir.HypoWindow}",
		"%{IncludeDir.HypoGraphics}",
		"%{IncludeDir.Hypo3D}",
		"%{IncludeDir.GSL}"
	}
	defines
	{
		"HYPO_PLATFORM_WINDOWS",
		"_CRT_SECURE_NO_WARNINGS",
		"HYPO_GRAPHICS_EXPORTS"
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
		"HypoSystem",
		"HypoGraphics"
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
		"%{IncludeDir.HypoSystem}",
		"%{IncludeDir.HypoWindow}",
		"%{IncludeDir.HypoGrahpics}",
		"%{IncludeDir.Hypo3D}",
		"%{IncludeDir.GSL}"
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
		"HypoSystem",
		"HypoWindow",
		"HypoGraphics",
		"Hypo3D",
		"glad"
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
		"%{IncludeDir.glad}",

		"%{IncludeDir.HypoWindow}",
		"%{IncludeDir.HypoSystem}",
		"%{IncludeDir.Graphics}",
		"%{IncludeDir.Hypo3D}",
		"%{IncludeDir.GSL}"


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
