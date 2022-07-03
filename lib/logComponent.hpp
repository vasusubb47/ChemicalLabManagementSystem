
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
                int32_t biteOffSet;
                int32_t nextIndex;

                Value(uint64_t timestamp, int32_t biteOffSet, int32_t nextIndex);
                Value(Value* value);
            };

            struct Key {
                std::string key;
                int32_t firstValueBiteOffset;
                int32_t firstTimeStampIndex, lastTimeStampIndex;

                Key(std::string key, int32_t firstValueBiteOffset, int32_t firstTimeStampIndex);
                Key(Key* key);
            };

            void loadKeyValueIndexFile(std::fstream& KeyStream, std::fstream& ValueStream, std::unordered_map<std::string, Key>& KeyMap, std::vector<Value>& valueVect);
            void saveKeyValueIndexFile(std::fstream& KeyStream, std::fstream& ValueStream, std::unordered_map<std::string, Key>& KeyMap, std::vector<Value>& valueVect);
            void updateKeyValue(std::unordered_map<std::string, Key>& KeyMap, std::vector<Value>& valueVect, std::string& key, uint64_t timestamp, int32_t biteOffSet);

    };
}
