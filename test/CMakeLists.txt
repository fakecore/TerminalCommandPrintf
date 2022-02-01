

find_library(GTEST_LIB gtest)

message("${GTEST_LIB}")

add_executable(test CommandTest.cpp )

target_link_libraries(test  ${GTEST_LIB} ${LIBRARY_OUTPUT_PATH}/libterminalcommand.so)