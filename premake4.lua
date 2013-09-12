
local BIN_DIR    = "bin"
local OBJ_DIR    = "bin/obj"
local MAKE_DIR   = "bin/make"

local SFML_INC_DIR = "D:/Prog/SFML2/include"
local SFML_LIB_DIR = "D:/Prog/SFML2/bin/lib"
local SFML_STATIC  = true

function sfml_links(tab, dbg, static)
    local suffix = (static and "-s" or "") .. (dbg and "-d" or "")
    for _, v in pairs(tab) do
        links("sfml-" .. v .. suffix)
    end
end

solution "SimpleGameEngine"
  configurations { "Debug", "Release" }

  targetdir(BIN_DIR)
  objdir(OBJ_DIR)

  includedirs { SFML_INC_DIR }
  libdirs { SFML_LIB_DIR }

  flags { "ExtraWarnings", "FatalWarnings", "NoRTTI", "NoPCH" }

  configuration "Debug"
    flags { "Symbols" }

  configuration "Release"
    flags { "Optimize" }
    defines { "NDEBUG" }


project "SGE"
  language "C++"
  location(MAKE_DIR)

  files { "src/**.cpp" }
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
    links { "pthread", "X11", "GL", "Xrandr", "freetype", "GLEW", "jpeg" }
