add_library(core STATIC
	STCEncoder.h
	STCEncoder.cpp
	matcher.h
	matcher.cpp
	decoder.h
	decoder.cpp
)

target_link_libraries(core PRIVATE common tbb_static)