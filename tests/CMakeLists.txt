
add_executable(solver_catch_test solver_catch_test.cpp)

target_link_libraries(solver_catch_test PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(solver_catch_test)