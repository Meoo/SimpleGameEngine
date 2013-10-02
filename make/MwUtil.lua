-- Variables:
--      MWUTIL_DIR
--      MWUTIL_INCLUDE_DIR

-- SFML2 options
newoption {
  trigger     = "mwutil_directory",
  value       = "path",
  description = "MwUtil base directory (must contain src directory)"
}

-- ///////////////////////////////////////////////////// --

MWUTIL_DIR          = _OPTIONS["mwutil_directory"] or ""
MWUTIL_INCLUDE_DIR  = MWUTIL_DIR .. "/src"

-- ///////////////////////////////////////////////////// --

if _OPTIONS["sfml_directory"] ~= "" then
  -- Check directory validity
  local m = os.matchfiles(MWUTIL_INCLUDE_DIR .."/Mw/Config.hpp")
  if #m == 0 then
    print("Not a valid MwUtil include directory : ".. MWUTIL_INCLUDE_DIR)
  end
end
