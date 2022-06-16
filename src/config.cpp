
#ifndef CONFIG_CPP
#define CONFIG_CPP
#include "../lib/config.hpp"

void CLMS::loadConfig () {
    std::ifstream configFile("../res/CLMS.config");
    std::string line;

    if (configFile.fail()) {
        std::ofstream defaultConfig("../res/CLMS.config");
        defaultConfig << "UesrLinesPerPage:10\n"
                    << "ChemicalLinesPerPage:15\n"
                    << "LogDir:\"../res/log\"\n"
                    << "DefaultFileOutputDir:\"../data/\"\n"
                    << "StyledOutput:\"True\"";
        defaultConfig.close();
        configFile.open("../res/CLMS.config");
    }

    if (configFile.is_open()) {
        config = std::vector<Config>();
        while (std::getline(configFile, line)) {
            std::string settingName = std::string(strtok((char*)line.c_str(), ":"));
            std::string value = std::string(strtok(NULL, ":"));
            ConfigSettings setting;

            if (settingName == "UesrLinesPerPage") {
                setting = ConfigSettings::UesrLinesPerPage;
            }else if (settingName == "ChemicalLinesPerPage") {
                setting = ConfigSettings::ChemicalLinesPerPage;
            }else if (settingName == "LogDir") {
                setting = ConfigSettings::LogDir;
            }else if (settingName == "DefaultFileOutputDir") {
                setting = ConfigSettings::DefaultFileOutputDir;
            }else if (settingName == "StyledOutput") {
                setting = ConfigSettings::StyledOutput; 
            }

            config.emplace_back(Config{
                setting,
                value
            });

        }
    }
}

void CLMS::printConfig () {
    for (Config conf : config) {
        std::cout << "setting : " << ConfigSettings(conf.setting) << ", Value : " << conf.value << "\n";
    }
}

CLMS::Config::Config(const ConfigSettings settings, const std::string& value) {
    this->setting = settings;
    this->value = value;
}

#endif
