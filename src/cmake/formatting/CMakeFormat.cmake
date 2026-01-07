include_guard()

set(CMAKE_FORMAT_UTILS_FILES
    "${CMAKE_CURRENT_LIST_DIR}/CMakeFormat.cmake"
    "${CMAKE_CURRENT_LIST_DIR}/ClangFormat.cmake"
    "${CMAKE_CURRENT_LIST_DIR}/../coverage/Coverage.cmake"
    "${CMAKE_CURRENT_LIST_DIR}/../utils/FindPackages.cmake"
    "${CMAKE_CURRENT_LIST_DIR}/../utils/GlobalVariables.cmake"
    "${CMAKE_CURRENT_LIST_DIR}/../utils/TargetLinkFunctions.cmake")

macro(register_format_cmake_file)
  get_property(current_files GLOBAL PROPERTY ALL_CMAKE_FORMAT_FILES_PROPERTY)
  list(APPEND current_files "${CMAKE_CURRENT_LIST_FILE}")
  set_property(GLOBAL PROPERTY ALL_CMAKE_FORMAT_FILES_PROPERTY
                               "${current_files}")
endmacro()

function(create_cmake_format_target)
  get_property(all_files GLOBAL PROPERTY ALL_CMAKE_FORMAT_FILES_PROPERTY)

  list(APPEND all_files ${CMAKE_FORMAT_UTILS_FILES})

  list(REMOVE_DUPLICATES all_files)
  list(SORT all_files)
  list(LENGTH all_files NUM_FILES)

  add_custom_target(
    fix-cmake-format
    COMMAND ${CMAKE_COMMAND} -E echo "Formatting ${NUM_FILES} CMake files"
    COMMAND ${CMAKE_FORMAT} -i ${all_files}
    VERBATIM)

  add_custom_target(
    check-cmake-format
    COMMENT "Check formatting of ${NUM_FILES} CMake files"
    COMMAND ${CMAKE_FORMAT} --check ${all_files}
    VERBATIM)

  message(STATUS "Targets 'fix-cmake-format' and 'check-cmake-format' created")
endfunction()
