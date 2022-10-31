# find_conan_packages(<packages...>)
#
# Finds packages imported by conan and loads its package-specific details.
#
# --- Parameters ---
#
# packages             List of packages imported by conan to find.

function(find_conan_packages)
  foreach(arg IN LISTS ARGN)
    set(finder ${CMAKE_BINARY_DIR}/Find${arg}.cmake)
    if(EXISTS ${finder})
      include(${finder})
    else()
      message(FATAL_ERROR "The file ${finder} doesn't exist, you have to run conan install first or use conan.cmake")
    endif()
  endforeach()
endfunction()
