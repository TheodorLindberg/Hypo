
include "Robot/vendor/serial"
		
project "Robot"
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
