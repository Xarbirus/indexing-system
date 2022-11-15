set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  message("Using MSVC")

  add_compile_definitions(__PRETTY_FUNCTION__=__FUNCSIG__)
  add_compile_definitions(_WIN32_WINNT=0x0601)
  add_compile_definitions(UNICODE)
  add_compile_definitions(_UNICODE)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
  add_compile_definitions(_WINSOCK_DEPRECATED_NO_WARNINGS)
  add_compile_definitions(WIN32_LEAN_AND_MEAN)

  set(cxx_warnings /W4 /WX)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  message("Using GNU")

  set(cxx_warnings
    -Werror
    -Wall
    -Wpedantic
    -Wcast-align
    -Wdouble-promotion
    -Wduplicated-branches
    -Wduplicated-cond
    -Wextra
    -Wformat
    -Wformat-security
    -Wextra-semi
    -Wlogical-op
    -Wmisleading-indentation
    -Wnon-virtual-dtor
    -Wnull-dereference
    -Woverloaded-virtual
    -Wstack-protector
    -Wunused
    -Wshadow
    -Wfloat-equal
    -Wconversion
    -Wsign-conversion
    -Wold-style-cast)

  set(cxx_security
    -Werror=format-security
    -fstack-clash-protection
    -fstack-protector-strong
    -fpie)

  set(cxx_no_errors -Wno-error=missing-declarations)
  set(cxx_colors -fdiagnostics-color=always)
  set(cxx_flags -fasynchronous-unwind-tables -fexceptions)

  set(debug_flags -O0 -g3)
endif()

set(cxx_all_flags
  ${cxx_flags}
  ${cxx_warnings}
  ${cxx_no_errors}
  ${cxx_colors}
  ${cxx_security})

set(cxx_debug_flags ${cxx_all_flags} ${debug_flags})
set(cxx_relwithdebinfo_flags ${cxx_all_flags} -D_FORTIFY_SOURCE=2)
set(cxx_release_flags ${cxx_all_flags})

include(cmake/utils/append_strings.cmake)
set(separator " ")
append_strings(CMAKE_CXX_FLAGS_DEBUG ${separator} ${cxx_debug_flags})
append_strings(CMAKE_CXX_FLAGS_RELWITHDEBINFO ${separator} ${cxx_relwithdebinfo_flags})
append_strings(CMAKE_CXX_FLAGS_RELEASE ${separator} ${cxx_release_flags})

find_program(CCACHE "ccache")
if(CCACHE)
  set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE})
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif(CCACHE)