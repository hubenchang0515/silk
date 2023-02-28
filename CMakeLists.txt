cmake_minimum_required(VERSION 3.4)

project(silk VERSION 0.0.1 LANGUAGES C)

option(UNIT_TEST "build unit test" OFF)

aux_source_directory("src/silk" SILK_SRC)
file(GLOB SILK_HEADER "${CMAKE_SOURCE_DIR}/src/silk/*.h")

add_library(${PROJECT_NAME} ${SILK_SRC})
set_target_properties(${PROJECT_NAME} 
                        PROPERTIES 
                        C_STANDARD      99
                        PUBLIC_HEADER   ${SILK_HEADER})

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
                                COMPILE_FLAGS       "-fprofile-arcs -ftest-coverage")
        
        add_custom_target(coverage
                        COMMAND ./silk_unit_test && lcov -c -d . -o coverage.info --rc lcov_branch_coverage=1 && genhtml --branch-coverage -o . coverage.info 
                        )
endif(UNIT_TEST)