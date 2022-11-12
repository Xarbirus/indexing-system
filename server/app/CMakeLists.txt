get_filename_component(TARGET_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

add_subdirectory(src)

if(TESTS EQUAL 1)
  add_subdirectory(gtests)
endif()
