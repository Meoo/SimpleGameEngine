
-- Output directories option
newoption {
  trigger     = "output_directory",
  value       = "path",
  description = "[Default=bin] Output directory for the executable"
}

if not _OPTIONS["output_directory"] then
  _OPTIONS["output_directory"] = "bin"
end

-- GNU GProf option
newoption {
  trigger     = "gprof",
  value       = "bool",
  description = "[Default=false] Enable GNU Profiler file generation",
  allowed = {
    { "true",   "GNU Profiler enabled" },
    { "false",  "GNU Profiler disabled" },
  }
}

-- Static stdlib linkage option
newoption {
  trigger     = "stdlib_static",
  value       = "bool",
  description = "[Default=false] Enable static linking of standard libraries",
  allowed = {
    { "true",   "Static linking of stdlib enabled" },
    { "false",  "Static linking of stdlib disabled" },
  }
}

-- ///////////////////////////////////////////////////// --

-- SFML2 directories and configuration
dofile "make/SFML.lua"

-- MwUtil directories and configuration
dofile "make/MwUtil.lua"

-- Boost directories and configuration
dofile "make/Boost.lua"

-- ///////////////////////////////////////////////////// --

local function bool_default(value, default)
  if not value then return default end
  if value:lower() == "true" then return true end
  if value:lower() == "false" then return false end
  error (value.." is not a valid boolean value")
end

-- Output directories
local BIN_DIR       = _OPTIONS["output_directory"]
local OBJ_DIR       = BIN_DIR .."/obj"
local MAKE_DIR      = BIN_DIR .."/make"

-- Enable profiling with gprof on GNU GCC
local GPROF         = bool_default(_OPTIONS["gprof"], false)

-- Enable static linking of stdlib
local STDLIB_STATIC = bool_default(_OPTIONS["stdlib_static"], false)

-- ///////////////////////////////////////////////////// --

solution "SimpleGameEngine"
  configurations { "Debug", "Release" }
  platforms { "native", "x32", "x64" }

  targetdir( BIN_DIR )
  objdir   ( OBJ_DIR )

  includedirs { MWUTIL_INCLUDE_DIR, BOOST_INCLUDE_DIR }

  flags { "ExtraWarnings", "FatalWarnings", "NoRTTI", "NoPCH" }
  
  if STDLIB_STATIC then
    flags { "StaticRuntime" }
  end
  
  if GPROF then
    configuration "GMake"
      buildoptions { "-pg" }
      linkoptions  { "-pg" }
  end

  configuration "Debug"
    flags { "Symbols" }

  configuration "Release"
    flags   { "Optimize" }
    defines { "NDEBUG" }

-- ///////////////////////////////////////////////////// --

project "SGE"
  language "C++"
  location( MAKE_DIR )

  files       { "src/**.cpp" }
  includedirs { "src" }

  use_SFML    { "graphics", "audio", "window", "system" }

  configuration "Debug"
    kind "ConsoleApp"

  configuration "Release"
    kind "WindowedApp"
