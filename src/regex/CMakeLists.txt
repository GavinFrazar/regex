set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include/regex)
set(LIB_HEADERS
RangeSet.h
Wrapper.h
)
set(LIB_SOURCES
${INCLUDE_PATH}/Regex.h
RangeSet.cpp
Regex.cpp
)
# set(APP_HEADERS)
# set(APP_SOURCES)

set(LIBRARY_NAME regex_lib)

add_library(${LIBRARY_NAME} STATIC ${LIB_SOURCES} ${LIB_HEADERS})
target_include_directories(${LIBRARY_NAME} PUBLIC
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/include
  )
set_target_properties(${LIBRARY_NAME} PROPERTIES
  VERSION ${VERSION}  # ${VERSION} was defined in the main CMakeLists.
  FRAMEWORK FALSE
  PUBLIC_HEADER "${LIB_HEADERS}" # specify the public headers
)

# set(APPLICATION_NAME proj_name_stub)
# add_executable(${APPLICATION_NAME} ${APP_SOURCES})
# target_link_libraries(${APPLICATION_NAME} ${LIBRARY_NAME})
