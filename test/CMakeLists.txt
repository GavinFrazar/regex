file(GLOB_RECURSE TEST_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
set(ALL_TESTS)
foreach(FILE ${TEST_FILES})
    string(REGEX REPLACE "[./]" "_" NAME ${FILE}) # create exe name
    add_executable(${NAME} ${FILE})
    target_link_libraries(${NAME} regex_lib Catch2::Catch2)
    add_test(NAME ${NAME} COMMAND ${NAME})
endforeach(FILE ${TEST_FILES})

include(CTest)