solution "Muta"
	configurations { "Debug", "Release" }

	configuration "Debug"
		defines { "DEBUG" }
		flags   { "Symbols" }

    configuration "Release"
		defines { "RELEASE" }
		flags   { "Optimize" }

	project "dyad"
		kind "StaticLib"
		language "C"
        files { "../thirdparty/dyad/**.c" }
		includedirs { "../thirdparty/dyad/" }

	project "muta"
		kind "ConsoleApp"
		language "C"
		files { "../src/**.c" }
		links { "dyad" }
		libdirs { "." }
		includedirs { "../src/", "../thirdparty/dyad/" }
