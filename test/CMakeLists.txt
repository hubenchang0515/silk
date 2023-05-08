set(UNIT_TEST_NAME ${PROJECT_NAME}_unit_test)

set(UNIT_TEST_COMPILE_OPTIONS $<$<C_COMPILER_ID:MSVC>:/W4 /WX /D_CRT_SECURE_NO_WARNINGS /DSILK_ASSERT_MODE=${SILK_ASSERT_MODE}>
                                $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -DSILK_ASSERT_MODE=${SILK_ASSERT_MODE} -g -fprofile-arcs -ftest-coverage>)

set(UNIT_TEST_LINK_LIBRARIES $<$<C_COMPILER_ID:MSVC>:>
                                $<$<NOT:$<C_COMPILER_ID:MSVC>>:gcov>)

aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/../src"  TEST_SRC)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/../test" TEST_SRC)

add_executable(${UNIT_TEST_NAME} ${TEST_SRC})

set_target_properties(${UNIT_TEST_NAME} 
                        PROPERTIES 
                        C_STANDARD          99
                        INCLUDE_DIRECTORIES "${SILK_HEADER_PATH}"
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