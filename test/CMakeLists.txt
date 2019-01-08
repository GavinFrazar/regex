set(UNIT_TEST_LIST
  RangeSetSpec
  RegexSpec
  )

add_library(CATCH_MAIN catch_main.cpp)
 
foreach(NAME IN LISTS UNIT_TEST_LIST)
    add_executable(${NAME}
    ${NAME}.cpp)
    target_link_libraries(${NAME}
      PUBLIC regex_lib Catch2::Catch2 CATCH_MAIN)
    add_test(
        NAME ${NAME}
        COMMAND ${NAME} -s
    )
endforeach()

include(CTest)
