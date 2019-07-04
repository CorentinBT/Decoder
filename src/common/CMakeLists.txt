add_library(common STATIC
	assert.h
	common_types.h
	timer.h
	timer.cpp
	npy/cnpy.h
	npy/cnpy.cpp
)

target_link_libraries(common PUBLIC ${ZLIB_LIBRARIES})