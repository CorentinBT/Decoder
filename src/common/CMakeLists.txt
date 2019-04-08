add_library(common STATIC
	assert.h
	generator.h
	generator.cpp
	common_types.h
	timer.h
	timer.cpp
	npy/cnpy.h
	npy/cnpy.cpp
)

target_link_libraries(common PUBLIC tbb_static ${ZLIB_LIBRARIES})