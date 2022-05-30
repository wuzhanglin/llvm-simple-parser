FILE(GLOB_RECURSE SOURCES "*.cpp")
FILE(GLOB_RECURSE HEADERS "*.h")

IF(CMAKE_GENERATOR MATCHES "Xcode")
  add_executable(SimpleParser ${SOURCES} ${HEADERS})
ELSE()
  add_executable(SimpleParser ${SOURCES})
ENDIF()

target_link_libraries(SimpleParser PRIVATE ${llvm_libs})
