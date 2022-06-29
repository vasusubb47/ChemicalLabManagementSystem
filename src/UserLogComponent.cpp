
#include "../lib/userLogComponent.hpp"

CLMS::UserLogComponent::UserLogComponent() : LogComponent("UserLog", {"log", "user"}) {
    std::cout << "UserLogComponent\n";
    openFile(this->componentKeyIndexFile, getFilePath(this->componentName, this->dirChain, FileType::IndexKeyFile), std::ios::in);
    openFile(this->componentValueIndexFile, getFilePath(this->componentName, this->dirChain, FileType::IndexValueFile), std::ios::in);
}

CLMS::UserLogComponent::~UserLogComponent() {
    this->componentKeyIndexFile.close();
    this->componentValueIndexFile.close();
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
    this->writeDataAndUpdateIndex(packedData, std::to_string(timeStamp), 64);
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
