
#include "../lib/userLogComponent.hpp";

CLMS::UserLogComponent::UserLogComponent() : LogComponent("UserLog") {}

CLMS::UserLogComponent::~UserLogComponent() {}

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
    uint32_t biteOffSet = this->writeData(this->componentIndexFile, -1,packedData, 32, '*');
    this->index.insert({std::to_string(timeStamp), biteOffSet});
    this->componentIndexFile << "%" << timeStamp << ":" << biteOffSet << "#";
}

std::string CLMS::UserLogComponent::getPackedData(const void* data, const char del) {
    const UserLog* uLog = (const UserLog*)data;
    return std::string() + del + std::to_string(uLog->timeStamp) + del + uLog->Uid + del + uLog->state + del;
}

std::shared_ptr<void> CLMS::UserLogComponent::unpackData(const std::string& timeStamp) {
    std::string logData = this->getData(timeStamp);
    if (logData.empty()) {
        return std::make_shared<std::nullptr_t>(nullptr);
    }
    std::string Uid, state;
    return std::make_shared<UserLog>(new UserLog(std::atoi(timeStamp.c_str()), Uid, state));
}

std::vector<std::string> CLMS::UserLogComponent::getHeaders() {
    return {"timeStamp", "Uid", "state"};
}

std::string CLMS::UserLogComponent::getData(const std::string& timeStamp) {
    auto val = this->index.find(timeStamp);
    if (val != this->index.end()) {
        this->componentFile.seekg(val->second);
        std::string line;
        this->componentFile >> line;
        return line;
    }
    return "";
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

std::string CLMS::UserLogComponent::UserLog::print() {
    return "{TimeStamp : " + std::to_string(this->timeStamp) + ", Uid : " + this->Uid + ", state : " + this->state + "}";
}
