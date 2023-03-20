cmake_minimum_required(VERSION 3.4)

project(silk VERSION 0.0.1 LANGUAGES C)

option(UNIT_TEST "build unit test" OFF)

aux_source_directory("src/silk" SILK_SRC)
file(GLOB SILK_HEADER "${CMAKE_SOURCE_DIR}/src/silk/*.h")

add_library(${PROJECT_NAME} ${SILK_SRC})

set_target_properties(${PROJECT_NAME} 
                        PROPERTIES 
                        C_STANDARD      99
                        PUBLIC_HEADER   "${SILK_HEADER}")
                        
target_compile_options(${PROJECT_NAME} PRIVATE
                        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
                        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>
                      )

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})


if (UNIT_TEST)
        set(UNIT_TEST_NAME ${PROJECT_NAME}_unit_test)

        aux_source_directory("src/test" TEST_SRC)

        add_executable(${UNIT_TEST_NAME} ${TEST_SRC} ${SILK_SRC})

        set_target_properties(${UNIT_TEST_NAME} 
                                PROPERTIES 
                                C_STANDARD          99
                                INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/src/
                                LINK_LIBRARIES      gcov
                                COMPILE_FLAGS       "-g -pg -fprofile-arcs -ftest-coverage")

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