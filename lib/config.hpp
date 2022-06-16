
#pragma once

#include "main.hpp"
#include "util.hpp"

namespace CLMS {

    enum ConfigSettings {
        UesrLinesPerPage = 0,
        ChemicalLinesPerPage = 2,
        LogDir = 3,
        DefaultFileOutputDir = 5,
        StyledOutput = 7
    };

    class Config {
        private:
            
        
        public:
            ConfigSettings setting;
            std::string value;

            Config(const ConfigSettings setting, const std::string& value);

    };

    std::vector<Config> config;
    std::string configStr;
    void loadConfig();
    void printConfig();

}
