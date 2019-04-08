# Enable modules to include each other's files
# TODO : remove these and prefer target include and link
include_directories(. ${Boost_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_subdirectory(common)
add_subdirectory(core)
add_subdirectory(config)
add_subdirectory(main)