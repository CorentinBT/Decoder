# avoid thirdparty library's tests
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(TBB_BUILD_TESTS OFF CACHE INTERNAL "")

add_subdirectory(tbb)
add_subdirectory(json)
