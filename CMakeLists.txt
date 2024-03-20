# Need CMake 3.28
cmake_minimum_required (VERSION 3.28)

# This is the name of the repository
project ("json")

# Set the correct paths
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Set for debug mode
if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
endif ()

add_compile_options(-gdwarf-4 -Wall -Wextra -Wpedantic -Wpointer-arith -Wstrict-prototypes -Wformat-security -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference)

# Find the array module
if ( NOT "${HAS_ARRAY}")
    
    # Add the array directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/array ${CMAKE_SOURCE_DIR}/build/array)

    # Let any parent project know that this project has array
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_ARRAY true PARENT_SCOPE)
        set(ARRAY_INCLUDE_DIR ${ARRAY_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the dict module
if ( NOT "${HAS_DICT}")
    
    # Add the dict directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/dict ${CMAKE_SOURCE_DIR}/build/dict)

    # Let any parent project know that this project has dict
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_DICT true PARENT_SCOPE)
        set(DICT_INCLUDE_DIR ${DICT_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the sync module
if ( NOT "${HAS_SYNC}")

    # Add the sync directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/sync ${CMAKE_SOURCE_DIR}/build/sync)

    # Let any parent project know that this project has sync
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_SYNC true PARENT_SCOPE)
        set(SYNC_INCLUDE_DIR ${SYNC_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the log module
if ( NOT "${HAS_LOG}")

    # Add the log directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/log ${CMAKE_SOURCE_DIR}/build/log)

    # Let any parent project know that this project has log
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_LOG true PARENT_SCOPE)
        set(LOG_INCLUDE_DIR ${LOG_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the base64 module
if ( NOT "${HAS_BASE64}")

    # Add the base64 directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/base64 ${CMAKE_SOURCE_DIR}/build/base64)

    # Let any parent project know that it has the base64 project
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_BASE64 true PARENT_SCOPE)
        set(BASE64_INCLUDE_DIR ${BASE64_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the json module
if ( NOT "${HAS_JSON}")

    # Add the json directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/json ${CMAKE_SOURCE_DIR}/build/json)

    # Let any parent project know that this project has json
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_JSON true PARENT_SCOPE)
        set(JSON_INCLUDE_DIR ${JSON_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the table module
if ( NOT "${HAS_TABLE}")

    # Add the json directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/table ${CMAKE_SOURCE_DIR}/build/table)

    # Let any parent project know that it has the table project
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_TABLE true PARENT_SCOPE)
        set(TABLE_INCLUDE_DIR ${TABLE_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the tuple module
if ( NOT "${HAS_TUPLE}")

    # Add the tuple directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/tuple ${CMAKE_SOURCE_DIR}/build/tuple)

    # Let any parent project know that it has the tuple project
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_TUPLE true PARENT_SCOPE)
        set(TUPLE_INCLUDE_DIR ${TUPLE_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the data module
if ( NOT "${HAS_DATA}")

    # Log
    message("[data] Adding data project")

    # Set the data include
    set(DATA_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

    # Let any parent project know that it has the data project
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_DATA true PARENT_SCOPE)
        set(DATA_INCLUDE_DIR ${DATA_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Add source to this project's executable.
add_executable (data_example "main.c")
add_dependencies(data_example data)
target_include_directories(data_example PUBLIC ${DATA_INCLUDE_DIR} ${JSON_INCLUDE_DIR} ${ARRAY_INCLUDE_DIR} ${CRYPTO_INCLUDE_DIR} ${DICT_INCLUDE_DIR} ${SYNC_INCLUDE_DIR} ${BASE64_INCLUDE_DIR} ${TUPLE_INCLUDE_DIR} ${TABLE_INCLUDE_DIR} ${LOG_INCLUDE_DIR})
target_link_libraries(data_example data table base64 json array dict sync)

# Add source to this project's library
add_library (data SHARED "data.c")
add_dependencies(data table json base64 array dict sync)
target_include_directories(data PUBLIC ${DATA_INCLUDE_DIR} ${JSON_INCLUDE_DIR} ${ARRAY_INCLUDE_DIR} ${CRYPTO_INCLUDE_DIR} ${DICT_INCLUDE_DIR} ${SYNC_INCLUDE_DIR} ${BASE64_INCLUDE_DIR} ${TUPLE_INCLUDE_DIR} ${TABLE_INCLUDE_DIR} ${LOG_INCLUDE_DIR})
target_link_libraries(data PUBLIC table json base64 array dict sync)
