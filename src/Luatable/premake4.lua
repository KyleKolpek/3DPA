-- A solution contains projects, and defines the available configurations
solution "Luatable"
	configurations { "Debug", "Release" }
	
   -- A project defines one build target
	project "Luatable"
		kind "SharedLib"
		language "C++"
		files { "**.h", "**.cpp", "**.c"}
		targetdir ("bin/")
		
    configuration "Debug"
		targetname "luatable-d"
		objdir "obj/debug"
		defines { "DEBUG"}
		flags { "Symbols" }
		
    configuration "Release"
		targetname "luatable"
		objdir "obj/release"
		defines { "NDEBUG"}
		flags { "Optimize" }

