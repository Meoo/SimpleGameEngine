
-- SFML2 options
newoption {
  trigger     = "sfml_directory",
  value       = "path",
  description = "SFML2 base directory (must contains include directory)"
}

if not _OPTIONS["sfml_directory"] then
  _OPTIONS["sfml_directory"] = ""
end

newoption {
  trigger     = "sfml_bin_directory",
  value       = "path",
  description = "[Optional] SFML2 binaries directory (must contains lib directory)"
}

if not _OPTIONS["sfml_bin_directory"] then
  _OPTIONS["sfml_bin_directory"] = _OPTIONS["sfml_directory"]
end

newoption {
  trigger     = "sfml_static",
  value       = "bool",
  description = "[Default=false] Link SFML2 as a static library",
  allowed = {
    { "true",   "Static linkage enabled" },
    { "false",  "Static linkage disabled" },
  }
}

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

function bool_default(value, default)
  if not value then return default end
  if value:lower() == "true" then return true end
  if value:lower() == "false" then return false end
  error (value.." is not a valid boolean value")
end

-- SFML2 directories and configuration
local SFML_INC_DIR  = _OPTIONS["sfml_directory"].."/include"
local SFML_LIB_DIR  = _OPTIONS["sfml_bin_directory"].."/lib"
local SFML_STATIC   = bool_default(_OPTIONS["sfml_static"], false)

-- Output directories
local BIN_DIR       = _OPTIONS["output_directory"]
local OBJ_DIR       = BIN_DIR.."/obj"
local MAKE_DIR      = BIN_DIR.."/make"

-- Enable profiling with gprof on GNU GCC
local GPROF         = bool_default(_OPTIONS["gprof"], false)

-- Enable static linking of stdlib
local STDLIB_STATIC = bool_default(_OPTIONS["stdlib_static"], false)

-- SFML2 useful link function
function sfml_links(tab, dbg, static)
  local suffix = (static and "-s" or "") .. (dbg and "-d" or "")
  for _, v in pairs(tab) do
    links("sfml-" .. v .. suffix)
  end
end

-- ///////////////////////////////////////////////////// --

solution "SimpleGameEngine"
  configurations { "Debug", "Release" }

  targetdir(BIN_DIR)
  objdir   (OBJ_DIR)

  includedirs { SFML_INC_DIR }
  libdirs     { SFML_LIB_DIR }

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
  location(MAKE_DIR)

  files       { "src/**.cpp" }
  includedirs { "src" }

  sfml_libs = { "graphics", "audio", "window", "system" }
  if SFML_STATIC then
    defines { "SFML_STATIC" }
  end

  configuration "Debug"
    kind "ConsoleApp"
    sfml_links(sfml_libs, true, SFML_STATIC)

  configuration "Release"
    kind "WindowedApp"
    sfml_links(sfml_libs, false, SFML_STATIC)

  configuration "not Windows"
    -- may require sndfile and openal
    -- also, is it enough for Mac?
    links { "pthread", "X11", "GL", "Xrandr", "freetype", "GLEW", "jpeg" }
