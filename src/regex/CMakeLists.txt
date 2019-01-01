set(LIB_HEADERS)
set(LIB_SOURCES)
# set(APP_HEADERS)
# set(APP_SOURCES)

set(LIBRARY_NAME regex)

add_library(${LIBRARY_NAME} SHARED ${LIB_SOURCES})

set_target_properties(${LIBRARY_NAME} PROPERTIES
  VERSION ${VERSION}  # ${VERSION} was defined in the main CMakeLists.
  FRAMEWORK FALSE
  PUBLIC_HEADER "${LIB_HEADERS}" # specify the public headers
)

# set(APPLICATION_NAME proj_name_stub)
# add_executable(${APPLICATION_NAME} ${APP_SOURCES})
# target_link_libraries(${APPLICATION_NAME} ${LIBRARY_NAME})
