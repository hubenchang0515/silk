cmake_minimum_required(VERSION 3.4)

project(silk VERSION 0.0.1 LANGUAGES C)

option(UNIT_TEST "build unit test" OFF)

if (NOT SILK_ASSERT_MODE)
        set(SILK_ASSERT_MODE 0)
endif(NOT SILK_ASSERT_MODE)

set(SILK_COMPILE_OPTIONS $<$<C_COMPILER_ID:MSVC>:/W4 /WX /D_CRT_SECURE_NO_WARNINGS /DSILK_ASSERT_MODE=${SILK_ASSERT_MODE}>
                         $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -DSILK_ASSERT_MODE=${SILK_ASSERT_MODE}>)

aux_source_directory("src/silk" SILK_SRC)

file(GLOB SILK_HEADER "${CMAKE_SOURCE_DIR}/src/silk/*.h")

set(STATIC_LIB_TARGET ${PROJECT_NAME}_static)
set(SHARED_LIB_TARGET ${PROJECT_NAME}_shared)
                         
add_library(${STATIC_LIB_TARGET} STATIC ${SILK_SRC})
add_library(${SHARED_LIB_TARGET} SHARED ${SILK_SRC})

set_target_properties(${STATIC_LIB_TARGET} 
                        PROPERTIES 
                        OUTPUT_NAME     ${PROJECT_NAME}
                        C_STANDARD      99
                        PUBLIC_HEADER   "${SILK_HEADER}"
                        COMPILE_OPTIONS "${SILK_COMPILE_OPTIONS}"
                        )

set_target_properties(${SHARED_LIB_TARGET} 
                        PROPERTIES 
                        OUTPUT_NAME     ${PROJECT_NAME}
                        C_STANDARD      99
                        PUBLIC_HEADER   "${SILK_HEADER}"
                        COMPILE_OPTIONS "${SILK_COMPILE_OPTIONS}"
                        )


install(TARGETS ${STATIC_LIB_TARGET} ${SHARED_LIB_TARGET}
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})


if (UNIT_TEST)
        set(UNIT_TEST_NAME ${PROJECT_NAME}_unit_test)

        set(UNIT_TEST_COMPILE_OPTIONS $<$<C_COMPILER_ID:MSVC>:/W4 /WX /D_CRT_SECURE_NO_WARNINGS /DSILK_ASSERT_MODE=${SILK_ASSERT_MODE}>
                                        $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -DSILK_ASSERT_MODE=${SILK_ASSERT_MODE} -g -fprofile-arcs -ftest-coverage>)

        set(UNIT_TEST_LINK_LIBRARIES $<$<C_COMPILER_ID:MSVC>:>
                                        $<$<NOT:$<C_COMPILER_ID:MSVC>>:gcov>)

        aux_source_directory("src/test" TEST_SRC)

        add_executable(${UNIT_TEST_NAME} ${TEST_SRC} ${SILK_SRC})

        set_target_properties(${UNIT_TEST_NAME} 
                                PROPERTIES 
                                C_STANDARD          99
                                INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/src/
                                COMPILE_OPTIONS     "${UNIT_TEST_COMPILE_OPTIONS}"
                                LINK_LIBRARIES      "${UNIT_TEST_LINK_LIBRARIES}")

        add_custom_target(rm-coverage
                        COMMAND $(RM) -rf ./coverage || (exit 0)
                        )

        add_custom_target(rm-gcda
                        COMMAND $(RM) -rf `find . -name *.gcda` || (exit 0)
                        )
        
        add_custom_target(coverage
                        COMMAND ./${UNIT_TEST_NAME} && lcov -c -d . -o coverage.info --rc lcov_branch_coverage=1 && genhtml --branch-coverage -o ./coverage coverage.info 
                        DEPENDS ${UNIT_TEST_NAME} rm-coverage rm-gcda
                        )

        add_custom_target(memcheck
                        COMMAND valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./${UNIT_TEST_NAME}
                        DEPENDS ${UNIT_TEST_NAME}
                        )
endif(UNIT_TEST)