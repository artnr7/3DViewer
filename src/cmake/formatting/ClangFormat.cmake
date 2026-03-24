include_guard()

set(ALL_PROJECT_SOURCES
    ""
    CACHE INTERNAL "All source files for formatting")

macro(register_format_sources)
  foreach(FILE ${ARGN})
    list(APPEND ALL_PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${FILE}")
  endforeach()

  set(ALL_PROJECT_SOURCES
      ${ALL_PROJECT_SOURCES}
      CACHE INTERNAL "")
endmacro()

function(create_clang_format_target)
  if(CLANG_FORMAT AND ALL_PROJECT_SOURCES)
    list(REMOVE_DUPLICATES ALL_PROJECT_SOURCES)

    add_custom_target(
      fix-clang-format
      COMMAND
        ${CLANG_FORMAT} -i
        --style="{BasedOnStyle: Google, DisableFormat: false}"
        ${ALL_PROJECT_SOURCES}
      COMMENT "Formatting ${ALL_PROJECT_SOURCES}"
      VERBATIM)
    add_custom_target(
      check-clang-format
      COMMAND ${CLANG_FORMAT} --dry-run --Werror --style=Google
              ${ALL_PROJECT_SOURCES}
      COMMENT "Checking formatting"
      VERBATIM)

    message(
      STATUS "Targets 'fix-clang-format' and 'check-clang-format' created")
  endif()
endfunction()
