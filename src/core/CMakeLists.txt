add_library(core STATIC
	STCEncoder.h
	STCEncoder.cpp
	matcher.h
	matcher.cpp
	decoder.h
	decoder.cpp
)

if(MVSC)
	target_link_libraries(core PRIVATE common tbb_static)
else()
	target_link_libraries(core PRIVATE common tbb)
endif()