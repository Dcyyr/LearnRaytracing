workspace "LearnRayTracing"
	architecture "x86_64"
	startproject "LearnRayTracing"

	configurations
	{
		"Debug",
		"Release"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["glm"] = "LearnRayTracing/vendor/glm"


	project "LearnRayTracing"
		location "LearnRayTracing"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++20"
		staticruntime "on"

		targetdir("bin/" .. outputdir .. "/%{prj.name}")
		objdir("bin-int" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/vendor/glm/glm/**.hpp",
			"%{prj.name}/vendor/glm/glm/**.inl",

		}

		includedirs
		{
			"%{prj.name}/src",
			"%{IncludeDir.glm}"
		}

		filter "system:windows"
			systemversion "latest"


		filter "configurations:Debug"
			defines "RT_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "RT_RELEASE"
			runtime "Release"
			symbols "on"