-- Variables:
--      SFML_DIR
--      SFML_STATIC
--      SFML_INCLUDE_DIR
--      SFML_LIBS_DIR
-- Functions:
--      links_SFML(libs, debug)
--      defines_SFML()

-- SFML2 options
newoption {
  trigger     = "sfml_directory",
  value       = "path",
  description = "SFML2 base directory (must contain include directory)"
}

if not _OPTIONS["sfml_directory"] then
  _OPTIONS["sfml_directory"] = ""
end

newoption {
  trigger     = "sfml_bin_directory",
  value       = "path",
  description = "[Optional] SFML2 build directory (must contains lib directory)"
}

if not _OPTIONS["sfml_bin_directory"] then
  _OPTIONS["sfml_bin_directory"] = _OPTIONS["sfml_directory"]
end

newoption {
  trigger     = "sfml_static",
  value       = "bool",
  description = "[Default=false] Link SFML2 as a static library",
  allowed = {
    { "true",   "Static linking enabled" },
    { "false",  "Static linking disabled" },
  }
}

-- ///////////////////////////////////////////////////// --

local function bool_default(value, default)
  if not value then return default end
  if value:lower() == "true" then return true end
  if value:lower() == "false" then return false end
  error (value.." is not a valid boolean value")
end

SFML_DIR            = _OPTIONS["sfml_directory"]
SFML_STATIC         = bool_default(_OPTIONS["sfml_static"], false)
SFML_INCLUDE_DIR    = SFML_DIR .. "/include"
SFML_LIBS_DIR       = _OPTIONS["sfml_bin_directory"] .. "/lib"

-- ///////////////////////////////////////////////////// --

if _OPTIONS["sfml_directory"] ~= "" then
  -- Check directory validity
  local m = os.matchfiles(SFML_INCLUDE_DIR .."/SFML/Config.hpp")
  if #m == 0 then
    error("Not a valid SFML include directory : ".. SFML_INCLUDE_DIR)
  end

  local m = os.matchfiles(SFML_LIBS_DIR .."/libsfml-*.a")
  if #m == 0 then
    error("No SFML libraries in directory : ".. SFML_LIBS_DIR)
  end
end

-- ///////////////////////////////////////////////////// --

-- SFML libraries
function links_SFML(libs, debug)
    local s = ""
    local d = ""
    if SFML_STATIC then
        s = "-s"
    end
    if debug then
        d = "-d"
    end
    for k, v in pairs(libs) do
        if v ~= "main" then
            libs[k] = "sfml-" .. v .. s .. d
        else
            libs[k] = "sfml-" .. v .. d
        end
    end
    links (libs)
end

-- SFML defines
function defines_SFML()
    if SFML_STATIC then
        defines { "SFML_STATIC" }
    else
        defines { "SFML_DYNAMIC" }
    end
end
