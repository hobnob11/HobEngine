-- premake5.lua
workspace "HobEngine"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "HobEngine"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "HobEngine"