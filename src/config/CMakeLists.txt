add_library(config STATIC
	config.h
	config.cpp
	settings.h
	settings.cpp
)

target_link_libraries(config PUBLIC common core nlohmann_json::nlohmann_json)