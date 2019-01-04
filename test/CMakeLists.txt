set(UNIT_TEST_LIST
  RegexSpec
  RangeSetSpec
  )
 
foreach(NAME IN LISTS UNIT_TEST_LIST)
    add_executable(${NAME}
    catch_main.cpp
    ${NAME}.cpp)
    target_link_libraries(${NAME}
    PUBLIC regex_lib Catch2::Catch2)
    add_test(
        NAME ${NAME}
        COMMAND ${NAME} -s
    )
endforeach()

include(CTest)