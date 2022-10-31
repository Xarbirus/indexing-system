set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(cxx_colors -fdiagnostics-color=always)
set(cxx_no_errors -Wno-error=missing-declarations)

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

set(cxx_flags
  -fasynchronous-unwind-tables
  -fexceptions)

set(cxx_all_flags
  ${cxx_flags}
  ${cxx_warnings}
  ${cxx_no_errors}
  ${cxx_colors}
  ${cxx_security})

set(cxx_debug_flags ${cxx_all_flags} -O0 -g3)
set(cxx_relwithdebinfo_flags ${cxx_all_flags} -D_FORTIFY_SOURCE=2)
set(cxx_release_flags ${cxx_all_flags})

include(cmake/utils/append_strings.cmake)
set(separator " ")
append_strings(CMAKE_CXX_FLAGS_DEBUG ${separator} ${cxx_debug_flags})
append_strings(CMAKE_CXX_FLAGS_RELWITHDEBINFO ${separator} ${cxx_relwithdebinfo_flags})
append_strings(CMAKE_CXX_FLAGS_RELEASE ${separator} ${cxx_release_flags})
append_strings(CMAKE_EXE_LINKER_FLAGS ${separator} ${cxx_linker_flags})

find_program(CCACHE "ccache")
if(CCACHE)
  set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE})
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif(CCACHE)