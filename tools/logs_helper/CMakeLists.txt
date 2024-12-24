project(logs_helper)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET ( TOOLS_SRC
  logging_base.cpp
  logging_base.h
  loggers.cpp
  loggers.h  )

IF (WIN32)
  SOURCE_GROUP(tools FILES ${TOOLS_SRC})
endif(WIN32)

add_library(${PROJECT_NAME}_lib STATIC ${TOOLS_SRC} )

target_include_directories(${PROJECT_NAME}_lib SYSTEM PUBLIC
    ${CONAN_INCLUDE_DIRS_SPDLOG}
    ${CONAN_INCLUDE_DIRS_FMT}
    ${Qt5Core_INCLUDE_DIRS}
    )

target_link_libraries(${PROJECT_NAME}_lib Qt5::Core ${CONAN_LIBS_FMT} ${CONAN_LIBS_SPDLOG})
