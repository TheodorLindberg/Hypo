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
	buildoptions
	{
		-- Multithreaded compiling
		"/MDd"
	}

IncludeDir = {}
IncludeDir["spdlog"] = "vendor/spdlog/include"
IncludeDir["ImGui"] = "vendor/imgui"
IncludeDir["glm"] = "vendor/glm/include"
IncludeDir["GSL"] = "vendor/GSL/include"
IncludeDir["bullet3"] = "vendor/bullet3-2.89/include"

IncludeDir["GLFW"] = "HypoWindow/vendor/GLFW/include"

IncludeDir["stb_image"] = "HypoGraphics/vendor/stb_image/include"
IncludeDir["glad"] = "Hypo3D/vendor/glad/include"
IncludeDir["assimp"] = "Hypo3D/vendor/assimp/include"
IncludeDir["entt"] = "Hypo3D/vendor/entt/include"

IncludeDir["HypoSystem"] = "HypoSystem/src"
IncludeDir["HypoWindow"] = "HypoWindow/src"
IncludeDir["Hypo3D"] = "Hypo3D/src"
IncludeDir["HypoGraphics"] = "HypoGraphics/src"
IncludeDir["HypoNetwork"] = "HypoNetwork/src"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
group "Dependencies"
include "Hypo3D/vendor/glad"
include "HypoWindow/vendor/GLFW"
include "vendor/imgui"
group "Bullet"
include "vendor/bullet3-2.89/src/BulletInverseDynamics"
include "vendor/bullet3-2.89/src/BulletSoftBody"
include "vendor/bullet3-2.89/src/BulletDynamics"
include "vendor/bullet3-2.89/src/BulletCollision"
include "vendor/bullet3-2.89/src/LinearMath"

group ""

project "HypoSystem"
	location "HypoSystem"
    kind "SharedLib"
    language "C++"
    staticruntime "off"
    
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
		"%{IncludeDir.GSL}",
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
	staticruntime "off"
	
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
	

			
project "HypoNetwork"
	location "HypoNetwork"
    kind "SharedLib"
    language "C++"
    staticruntime "off"
    
	targetdir ("bin/" .. outputdir)
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "networkpch.h"
	pchsource "HypoNetwork/src/networkpch.cpp"

	links
	{
		"GLFW",
		"glad",
		"ImGui",
		"HypoSystem",
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
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.HypoSystem}",
		"%{IncludeDir.HypoNetwork}",
		"%{IncludeDir.GSL}"
	}
	defines
	{
		"HYPO_PLATFORM_WINDOWS",
		"_CRT_SECURE_NO_WARNINGS",
		"HYPO_NETWORK_EXPORTS"
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
	staticruntime "off"
	
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
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.HypoSystem}",
		"%{IncludeDir.HypoWindow}",
		"%{IncludeDir.HypoGraphics}",
		"%{IncludeDir.Hypo3D}",
		"%{IncludeDir.GSL}",
		"%{IncludeDir.entt}"
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


project "HypoGraphics"
	location "HypoGraphics"
	kind "SharedLib"
	language "C++"
	staticruntime "off"
	
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
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.HypoSystem}",
		"%{IncludeDir.HypoWindow}",
		"%{IncludeDir.HypoGraphics}",
		"%{IncludeDir.Hypo3D}",
		"%{IncludeDir.GSL}",
		"%{IncludeDir.entt}"
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
	staticruntime "off"
	
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
		"HypoWindow",
		"HypoGraphics",
	}
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.HypoSystem}",
		"%{IncludeDir.HypoWindow}",
		"%{IncludeDir.HypoGraphics}",
		"%{IncludeDir.Hypo3D}",
		"%{IncludeDir.GSL}",
		"%{IncludeDir.entt}"
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


project "SandboxServer"
	location "SandboxServer"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir)
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	links
	{
		"HypoSystem",
		"HypoWindow",
		"HypoNetwork",
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
		"%{IncludeDir.HypoGraphics}",
		"%{IncludeDir.HypoNetwork}",
		"%{IncludeDir.Hypo3D}",
		"%{IncludeDir.GSL}"


	}
	defines
	{
		"HYPO_PLATFORM_WINDOWS",
		"IMGUI_API=__declspec(dllimport)"
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
	staticruntime "off"

	targetdir ("bin/" .. outputdir)
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	libdirs
	{
		"vendor/bullet3-2.89/bin",
	}
	links
	{
		"HypoSystem",
		"HypoWindow",
		"HypoNetwork",
		"HypoGraphics",
		"Hypo3D",
		"glad",

		"BulletDynamics",
		"BulletCollision", 
		"LinearMath"
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
		"%{IncludeDir.bullet3}",

		"%{IncludeDir.HypoWindow}",
		"%{IncludeDir.HypoSystem}",
		"%{IncludeDir.HypoGraphics}",
		"%{IncludeDir.HypoNetwork}",
		"%{IncludeDir.Hypo3D}",
		"%{IncludeDir.GSL}",
		"%{IncludeDir.entt}"


	}
	defines
	{
		"HYPO_PLATFORM_WINDOWS",
		"IMGUI_API=__declspec(dllimport)"
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
	

		
include "Robot/vendor/serial"
		
project "Robot"
location "Robot"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir)
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	links
	{
		"HypoSystem",
		"HypoWindow",
		"HypoGraphics",
		"Hypo3D",
		"glad",
		"Serial"
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
		"%{IncludeDir.HypoGraphics}",
		"%{IncludeDir.HypoNetwork}",
		"%{IncludeDir.Hypo3D}",
		"%{IncludeDir.GSL}",
		"Robot/vendor/serial/include"


	}
	defines
	{
		"HYPO_PLATFORM_WINDOWS",
		"IMGUI_API=__declspec(dllimport)"
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
