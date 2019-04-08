#pragma once

#include <string>

class Config {
public:
    Config();
    ~Config() = default;

	void Reload();

private:
    void ReadJSONValues();

    std::string config_loc;
};
