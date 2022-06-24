
#pragma once

#include "component.hpp"
#include "util.hpp"

namespace CLMS {
    class LogComponent : public Component {
        public:

            LogComponent(std::string logName, std::vector<std::string> dirChain);
            ~LogComponent();

            struct Value {
                uint64_t timestamp;
                uint32_t biteOffSet;
            };

            struct Key {
                std::string key;
                uint32_t biteOffSet;
                uint16_t firstTimeStampIndex;
            };

    };
}
