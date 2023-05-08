cmake_minimum_required(VERSION 3.4)

project(silk VERSION 0.0.1 LANGUAGES C)

option(UNIT_TEST "build unit test" OFF)

if (NOT SILK_ASSERT_MODE)
        set(SILK_ASSERT_MODE 0)
endif(NOT SILK_ASSERT_MODE)

set(SILK_COMPILE_OPTIONS $<$<C_COMPILER_ID:MSVC>:/W4 /WX /D_CRT_SECURE_NO_WARNINGS /DSILK_ASSERT_MODE=${SILK_ASSERT_MODE}>
                         $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -DSILK_ASSERT_MODE=${SILK_ASSERT_MODE}>)

aux_source_directory("src" SILK_SRC)

set(SILK_HEADER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB SILK_HEADER "${SILK_HEADER_PATH}/silk/*.h")

set(STATIC_LIB_TARGET ${PROJECT_NAME}_static)
set(SHARED_LIB_TARGET ${PROJECT_NAME}_shared)
                         
add_library(${STATIC_LIB_TARGET} STATIC ${SILK_SRC})
add_library(${SHARED_LIB_TARGET} SHARED ${SILK_SRC})

set_target_properties(${STATIC_LIB_TARGET} 
                        PROPERTIES 
                        OUTPUT_NAME             ${PROJECT_NAME}
                        C_STANDARD              99
                        PUBLIC_HEADER           "${SILK_HEADER}"
                        INCLUDE_DIRECTORIES     "${SILK_HEADER_PATH}"
                        COMPILE_OPTIONS         "${SILK_COMPILE_OPTIONS}"
                        )

set_target_properties(${SHARED_LIB_TARGET} 
                        PROPERTIES 
                        OUTPUT_NAME             ${PROJECT_NAME}
                        C_STANDARD              99
                        PUBLIC_HEADER           "${SILK_HEADER}"
                        INCLUDE_DIRECTORIES     "${SILK_HEADER_PATH}"
                        COMPILE_OPTIONS         "${SILK_COMPILE_OPTIONS}"
                        )


install(TARGETS ${STATIC_LIB_TARGET} ${SHARED_LIB_TARGET}
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})

add_library(${PROJECT_NAME} ALIAS ${STATIC_LIB_TARGET})
add_library(${PROJECT_NAME}::static ALIAS ${STATIC_LIB_TARGET})
add_library(${PROJECT_NAME}::shared ALIAS ${SHARED_LIB_TARGET})
target_include_directories(${STATIC_LIB_TARGET} INTERFACE ${SILK_HEADER_PATH})
target_include_directories(${SHARED_LIB_TARGET} INTERFACE ${SILK_HEADER_PATH})

if (UNIT_TEST)
        add_subdirectory(test)
endif(UNIT_TEST)