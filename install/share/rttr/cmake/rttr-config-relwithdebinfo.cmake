#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "RTTR::Core" for configuration "RelWithDebInfo"
set_property(TARGET RTTR::Core APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(RTTR::Core PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/librttr_core.so.0.9.7"
  IMPORTED_SONAME_RELWITHDEBINFO "librttr_core.so.0.9.7"
  )

list(APPEND _IMPORT_CHECK_TARGETS RTTR::Core )
list(APPEND _IMPORT_CHECK_FILES_FOR_RTTR::Core "${_IMPORT_PREFIX}/lib/librttr_core.so.0.9.7" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
