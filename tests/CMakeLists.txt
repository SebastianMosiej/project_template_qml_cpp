IF( ( CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID MATCHES "GNU") AND NOT WIN32)
  SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_COVERAGE}")
  SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_COVERAGE}")  
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories($ENV{QTDIR}
                    ${Qt5Test_INCLUDE_DIRS}
                    ${PROJECT_SOURCE_DIR}/src
                    ${PROJECT_SOURCE_DIR}/tools)

#####################
SET ( SOURCES_MAIN
      main.cpp
      TestRunner.h )

add_executable(${PROJECT_NAME}_ut ${TEST_SRCS})
set_property(TARGET ${PROJECT_NAME}_ut PROPERTY CXX_STANDARD 11)

target_link_libraries(${PROJECT_NAME}_ut Qt6::Test ${PROJECT_NAME}_lib
                      logs_helper_lib)
target_include_directories(${PROJECT_NAME}_ut PUBLIC ${Qt5Core_INCLUDE_DIRS})

ADD_TEST(NAME UT COMMAND ${PROJECT_NAME}_ut)
