project(Google_Tests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ..)

add_library(JagoLib ../jago/JagoUtils.cpp)

add_executable(Google_Tests_Run tests/JagoUtilsTest.cpp)
target_link_libraries(Google_Tests_Run JagoLib gtest gtest_main)