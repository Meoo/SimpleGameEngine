-- Functions:
--      use_Boost(libs)

-- Boost options
newoption {
  trigger     = "boost_directory",
  value       = "path",
  description = "Boost base directory (must contain boost directory)"
}

newoption {
  trigger     = "boost_bin_directory",
  value       = "path",
  description = "[Optional] Boost build directory (must contains lib directory)"
}

if not _OPTIONS["boost_bin_directory"] then
  _OPTIONS["boost_bin_directory"] = _OPTIONS["boost_directory"] or ""
end

newoption {
  trigger     = "boost_runtime_static",
  value       = "bool",
  description = "[Default=false] Use Boost with standard library linked statically",
  allowed = {
    { "true",   "Static runtime linking enabled" },
    { "false",  "Static runtime linking disabled" },
  }
}

newoption {
  trigger     = "boost_multithread",
  value       = "bool",
  description = "[Default=false] Use Boost multithreading support",
  allowed = {
    { "true",   "Multithreading support enabled" },
    { "false",  "Multithreading support disabled" },
  }
}

-- ///////////////////////////////////////////////////// --

local function bool_default(value, default)
  if not value then return default end
  if value:lower() == "true" then return true end
  if value:lower() == "false" then return false end
  error (value.." is not a valid boolean value")
end

local BOOST_DIR            = _OPTIONS["boost_directory"] or ""
local BOOST_INCLUDE_DIR    = BOOST_DIR
local BOOST_LIBS_DIR       = _OPTIONS["boost_bin_directory"] .."/lib"
local BOOST_RUNTIME_STATIC = bool_default(_OPTIONS["boost_runtime_static"], false)
local BOOST_MULTITHREAD    = bool_default(_OPTIONS["boost_multithread"], false)

-- ///////////////////////////////////////////////////// --

-- Boost version
local BOOST_SYSTEM = ""
local BOOST_VERSION = ""

if _OPTIONS["boost_directory"] then
  local m = os.matchfiles(BOOST_INCLUDE_DIR .."/boost/config.hpp")
  if #m == 0 then
    print("Not a valid Boost directory : ".. BOOST_DIR)
  end

  local m = os.matchfiles(BOOST_LIBS_DIR .."/libboost_*.a")
  if #m == 0 then
    print("No Boost libraries in directory : ".. BOOST_LIBS_DIR)
  else
    m = string.explode(m[1], "-");
    if BOOST_SYSTEM == "" then
      BOOST_SYSTEM = m[2]
    end
    if BOOST_VERSION == "" then
      BOOST_VERSION = string.sub(m[#m], 0, -3)
    end
    print("Using Boost " .. BOOST_VERSION .. " (" .. BOOST_SYSTEM .. ")")
  end
end

-- ///////////////////////////////////////////////////// --

-- Enable Boost
function use_Boost(libs)
  -- Boost paths
  includedirs { BOOST_INCLUDE_DIR }
  libdirs     { BOOST_LIBS_DIR }

  -- Boost libs
  local s = ""
  if BOOST_RUNTIME_STATIC or debug then
    s = "-"
    if BOOST_RUNTIME_STATIC then
      s = s .. "s"
    end
  end

  configuration "Debug"
    for k, v in pairs(libs) do
      if v ~= "main" then
        links("boost_" .. v .. "-" .. BOOST_SYSTEM .. s .. "d-" .. BOOST_VERSION)
      end
    end

  configuration "Release"
    for k, v in pairs(libs) do
      if v ~= "main" then
        links("boost_" .. v .. "-" .. BOOST_SYSTEM .. s .. "-" .. BOOST_VERSION)
      end
    end

  configuration {}
end
