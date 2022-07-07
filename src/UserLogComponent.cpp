
#include "../lib/userLogComponent.hpp"

void printDebug2(std::unordered_map<std::string, CLMS::LogComponent::Key>& keyMap, std::vector<CLMS::LogComponent::Value> valueVect) {
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

CLMS::UserLogComponent::UserLogComponent() : LogComponent("UserLog", {"log", "user"}) {
    std::cout << "UserLogComponent\n";
    openFile(this->UserKeyIndexFile, getFilePath("User", this->dirChain, FileType::IndexKeyFile), std::ios::in);
    openFile(this->UserValueIndexFile, getFilePath("User", this->dirChain, FileType::IndexValueFile), std::ios::in);
    loadKeyValueIndexFile(this->UserKeyIndexFile, this->UserValueIndexFile, this->userKeyMap, this->userValueVect);
    std::cout << "Loaded...\n";
    printDebug2(this->userKeyMap, this->userValueVect);
    this->UserKeyIndexFile.close();
    this->UserValueIndexFile.close();
}

CLMS::UserLogComponent::~UserLogComponent() {
    openFile(this->UserKeyIndexFile, getFilePath("User", this->dirChain, FileType::IndexKeyFile), std::ios::out);
    openFile(this->UserValueIndexFile, getFilePath("User", this->dirChain, FileType::IndexValueFile), std::ios::out);
    std::cout << "Saving...\n";
    printDebug2(this->userKeyMap, this->userValueVect);
    saveKeyValueIndexFile(this->UserKeyIndexFile, this->UserValueIndexFile, this->userKeyMap, this->userValueVect);
    this->UserKeyIndexFile.close();
    this->UserValueIndexFile.close();
}

void CLMS::UserLogComponent::getComponentInput() {
    std::string Uid, state;
    uint64_t timeStamp;
    std::cout << "Enter the User Log Uid and state: ";
    std::cin >> Uid >> state;
    timeStamp = getCurrentTime();
    UserLog uLog = UserLog(
        timeStamp, Uid, state
    );
    std::string packedData = this->getPackedData(&uLog, '|');
    std::cout << "state : " << state << "\n";
    if (state == "Login") {
        if (this->userLogin(Uid)) {
            uint32_t biteOffSet = this->writeDataAndUpdateIndex(packedData, std::to_string(timeStamp), 64);
            this->updateKeyValue(this->userKeyMap, this->userValueVect, Uid, timeStamp, biteOffSet);
        }
    }else if(state == "Logout") {
        if (this->userLogout(Uid)) {
            uint32_t biteOffSet = this->writeDataAndUpdateIndex(packedData, std::to_string(timeStamp), 64);
            this->updateKeyValue(this->userKeyMap, this->userValueVect, Uid, timeStamp, biteOffSet);
        }
    }
}

std::string CLMS::UserLogComponent::getPackedData(const void* data, const char del) {
    const UserLog* uLog = (const UserLog*)data;
    return std::string() + del + std::to_string(uLog->timeStamp) + del + uLog->Uid + del + uLog->state + del;
}

std::shared_ptr<void> CLMS::UserLogComponent::unpackData(const std::string& timeStamp) {
    std::vector<std::string> logData = this->extractData(timeStamp);
    if (logData.size() == 0) {
        return std::make_shared<std::nullptr_t>(nullptr);
    }
    std::string Uid, state;
    return std::make_shared<UserLog>(new UserLog(logData));
}

std::vector<std::vector<std::string>> CLMS::UserLogComponent::getData(std::vector<std::string> ids) {
    if (ids.size() == 0) {
        return LogComponent::getData({});
    }
    std::vector<std::string> tsids = std::vector<std::string>();
    for (auto id : ids) {
        if (this->userKeyMap.find(id) != this->userKeyMap.end()) {
            int tsi = this->userKeyMap.find(id)->second.firstTimeStampIndex;
            while (tsi != -1) {
                tsids.emplace_back(std::to_string(this->userValueVect[tsi].timestamp));
                tsi = this->userValueVect[tsi].nextIndex;
            }
        }else {
            tsids.emplace_back(id);
        }
    }
    return LogComponent::getData(tsids);
}

std::vector<std::string> CLMS::UserLogComponent::getHeaders() {
    return {"timeStamp", "Uid", "state"};
}

CLMS::UserLogComponent::UserLog::UserLog(const uint64_t timeStamp, const std::string Uid, const std::string state) {
    this->timeStamp = timeStamp;
    this->Uid = Uid;
    this->state = state;
}

CLMS::UserLogComponent::UserLog::UserLog(const UserLog* uLog) {
    this->timeStamp = uLog->timeStamp;
    this->Uid = uLog->Uid;
    this->state = uLog->state;
}

CLMS::UserLogComponent::UserLog::UserLog(std::vector<std::string> data) {
    this->timeStamp = std::atoi(data[0].c_str());
    this->Uid = data[1];
    this->state = data[2];
}

std::string CLMS::UserLogComponent::UserLog::print() {
    return "{TimeStamp : " + std::to_string(this->timeStamp) + ", Uid : " + this->Uid + ", state : " + this->state + "}";
}

int CLMS::UserLogComponent::userLogin(std::string Uid) {
    auto itr = std::find(this->logedInUsers.begin(), this->logedInUsers.end(), Uid);
    if (itr == this->logedInUsers.end()) {
        this->logedInUsers.emplace_back(Uid);
        std::cout << "The User " << Uid << " has been logged in successfully\n";
        return 1;
    }else {
        std::cout << "The User " << Uid << " has been logged in allready\n";
        return 0;
    }
}

int CLMS::UserLogComponent::userLogout(std::string Uid) {
    auto itr = std::find(this->logedInUsers.begin(), this->logedInUsers.end(), Uid);
    if (itr == this->logedInUsers.end()) {
        std::cout << "The User " << Uid << " has been logged out allready\n";
        return 0;
    }else {
        this->logedInUsers.erase(itr);
        std::cout << "The User " << Uid << " has been logged out successfully\n";
        return 1;
    }
}
