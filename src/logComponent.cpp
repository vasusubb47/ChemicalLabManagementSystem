
#include "../lib/logComponent.hpp"

CLMS::LogComponent::LogComponent(std::string logName, std::vector<std::string> dirChain) : Component(logName, ComponentType::LogComponent, dirChain) {
    std::cout << "Log Component\n";
    loadIndex();
}

CLMS::LogComponent::~LogComponent() {}


void printDebug1(std::unordered_map<std::string, CLMS::LogComponent::Key>& keyMap, std::vector<CLMS::LogComponent::Value> valueVect) {
    std::cout << "printDebug1\n";
    for (auto key : keyMap) {
        std::cout << std::setw(45) << std::setfill('%') << "" << std::endl;
        int i = key.second.firstTimeStampIndex;
        CLMS::LogComponent::Value value = valueVect[i];
        while (1) {
            std::cout << "Uid : " << key.first << ", timestamp : " << value.timestamp << ", ts biteOffset : " << value.biteOffSet << ", index : " << i << std::endl;
            i = value.nextIndex;
            if (i != -1) {
                value = valueVect[i];
            }else {
                break;
            }
        }
    }
}


void CLMS::LogComponent::loadKeyValueIndexFile(std::fstream& KeyStream, std::fstream& ValueStream, std::unordered_map<std::string, Key>& KeyMap, std::vector<Value>& valueVect) {
    std::cout << "loadKeyValueIndexFile\n";
    if (!KeyStream.eof()) {
        std::cout << "loading KeyStream...\n";
        KeyMap = std::unordered_map<std::string, Key>();
        char temp[2], key[7], biteOffSet[16];
        KeyStream.seekg(KeyStream.tellg());
        while (!KeyStream.eof()) {
            std::cout << "Reading\n";
            KeyStream.seekg(((int)KeyStream.tellg()) + 1);
            KeyStream.getline(key, 8, ':');
            std::cout << "Key : " << key << "\n";
            if (key[0] == '\0') {
                break;
            }
            KeyStream.getline(biteOffSet, 16, '#');
            if (key[0] != '\0') {
                int bfs = std::atoi(biteOffSet);
                Key k = Key(std::string(key), bfs, bfs / 32);
                KeyMap.insert({
                    k.key,
                    k
                });
            }
        }
    }else {
        KeyMap = std::unordered_map<std::string, Key>();
    }
    if (KeyMap.size() != 0) {
        if (!ValueStream.eof()) {
            std::cout << "loading ValueStream...\n";
            valueVect = std::vector<Value>();
            char timestamp[20], biteOffSet[16], dummy[30];
            int32_t bfs;
            while (!ValueStream.eof()) {
                bfs = ValueStream.tellg();
                ValueStream.seekg(bfs + 1);
                ValueStream.getline(timestamp, 22, ':');
                ValueStream.getline(biteOffSet, 16, '#');
                ValueStream.getline(dummy, 30, '\n');
                if (timestamp[0] != '\0') {
                    char* temp;
                    Value v = Value(std::strtoull(timestamp, &temp, 10), bfs, std::atoi(biteOffSet) / 32);
                    valueVect.emplace_back(v);
                }
            }
        }else {
            valueVect = std::vector<Value>();
        }
    }else {
        valueVect = std::vector<Value>();
    }
    printDebug1(KeyMap, valueVect);
}

void CLMS::LogComponent::saveKeyValueIndexFile(std::fstream& KeyStream, std::fstream& ValueStream, std::unordered_map<std::string, Key>& KeyMap, std::vector<Value>& valueVect) {
    std::cout << "saveKeyValueIndexFile\n";
    for (auto value : valueVect) {
        std::string pd = "%" + std::to_string(value.timestamp) + ":";
        if (value.nextIndex == -1) {
            pd += "-1#";
        }else {
            pd += std::to_string(value.nextIndex * 32) + "#";
        }
        value.biteOffSet = ValueStream.tellg();
        ValueStream << std::setw(32) << std::setfill('*') << std::setiosflags(std::ios::left) << pd << "\n";
    }
    std::vector<std::string> keys(KeyMap.size());
    for (auto idKeyPair : KeyMap) {
        keys.emplace_back(idKeyPair.first);
    }
    for (auto idKeyPair : KeyMap) {
        KeyStream << "%" << idKeyPair.second.key << ":" << idKeyPair.second.firstTimeStampIndex * 32 << "#";
    }
    for (auto key : KeyMap) {
        std::cout << std::setw(45) << std::setfill('%') << "" << std::endl;
        int i = key.second.firstTimeStampIndex;
        Value value = valueVect[i];
        while (1) {
            std::cout << "Uid : " << key.first << ", timestamp : " << value.timestamp << ", ts biteOffset : " << value.biteOffSet << ", index : " << i << std::endl;
            i = value.nextIndex;
            if (i != -1) {
                value = valueVect[i];
            }else {
                break;
            }
        }
    }
}

void CLMS::LogComponent::updateKeyValue(std::unordered_map<std::string, Key>& KeyMap, std::vector<Value>& valueVect, std::string& key, uint64_t timeStamp, int32_t biteOffSet) {
    std::cout << std::setw(45) << std::setfill('#') << "" << std::endl;
    auto keyCond = KeyMap.find(key);
    if (keyCond == KeyMap.end()) {
        std::cout << "Creating key : " << key << std::endl;
        valueVect.emplace_back(
            Value{timeStamp, biteOffSet, -1}
        );
        Key k = Key(key, timeStamp, valueVect.size() -1);
        KeyMap.emplace(key, k);
    }else {
        std::cout << "Key : " << key << std::endl;
        Key k = keyCond->second;
        Value v = valueVect[k.firstTimeStampIndex];
        int valueIndex = k.firstTimeStampIndex;
        while (v.nextIndex != -1) {
            std::cout << "timeStamp : " << v.timestamp << std::endl;
            valueIndex = v.nextIndex;
            v = valueVect[v.nextIndex];
        }
        valueVect.emplace_back(
            Value{timeStamp, biteOffSet, -1}
        );
        valueVect[valueIndex].nextIndex = valueVect.size() - 1;
    }
    std::cout << "key : " << key << ", timeStamp : " << timeStamp << ", biteOffSet : " << biteOffSet << std::endl;
}

std::vector<std::vector<std::string>> CLMS::LogComponent::getData(std::vector<std::string> ids) {
    return Component::getData(ids);
}

CLMS::LogComponent::Key::Key(std::string key, int32_t firstValueBiteOffset, int32_t firstTimeStampIndex) {
    this->key = key;
    this->firstValueBiteOffset = firstValueBiteOffset;
    this->firstTimeStampIndex = firstTimeStampIndex;
}

CLMS::LogComponent::Key::Key(Key* key) {
    this->key = key->key;
    this->firstValueBiteOffset = key->firstValueBiteOffset;
    this->firstTimeStampIndex = key->firstTimeStampIndex;
}

CLMS::LogComponent::Value::Value(uint64_t timestamp, int32_t biteOffSet, int32_t nextIndex){
    this->timestamp = timestamp;
    this->biteOffSet = biteOffSet;
    if (nextIndex == 0) {
        this->nextIndex = -1;
    }else {
        this->nextIndex = nextIndex;
    }
}

CLMS::LogComponent::Value::Value(Value* value){
    this->timestamp = value->timestamp;
    this->biteOffSet = value->biteOffSet;
    this->nextIndex = value->nextIndex;
}
