cmake_minimum_required(VERSION 3.13)

function(add_day)
    set(options)
    set(oneValueArgs FOLDER)
    set(multiValueArgs SOURCES INCLUDES LIBRARIES)
    cmake_parse_arguments(ADD_DAY "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_executable(${ADD_DAY_FOLDER} ${ADD_DAY_FOLDER}/${ADD_DAY_SOURCES})
    
    target_link_libraries(${ADD_DAY_FOLDER} PUBLIC fmt::fmt-header-only)

    if (ADD_DAY_LIBRARIES)
        target_link_libraries(${ADD_DAY_FOLDER} PUBLIC ${ADD_DAY_LIBRARIES})
    endif()

    if (MSVC)
        set_target_properties(${ADD_DAY_FOLDER} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${ADD_DAY_FOLDER})
    endif()

endfunction()
