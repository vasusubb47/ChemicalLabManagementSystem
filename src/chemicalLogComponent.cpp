
#include "../lib/chemicalLogComponent.hpp"

CLMS::ChemicalLogComponent::ChemicalLogComponent() : LogComponent("ChemicalLog", {"log", "chemical"}) {
    std::cout << "ChemicalLogComponent\n";
    openFile(this->UserKeyIndexFile, getFilePath("User", this->dirChain, FileType::IndexKeyFile), std::ios::in);
    openFile(this->UserValueIndexFile, getFilePath("User", this->dirChain, FileType::IndexValueFile), std::ios::in);
    loadKeyValueIndexFile(this->UserKeyIndexFile, this->UserValueIndexFile, this->userKeyMap, this->userValueVect);
    this->UserKeyIndexFile.close();
    this->UserValueIndexFile.close();
    openFile(this->ChemicalKeyIndexFile, getFilePath("Chemical", this->dirChain, FileType::IndexKeyFile), std::ios::in);
    openFile(this->ChemicalValueIndexFile, getFilePath("Chemical", this->dirChain, FileType::IndexValueFile), std::ios::in);
    loadKeyValueIndexFile(this->ChemicalKeyIndexFile, this->ChemicalValueIndexFile, this->chemicalKeyMap, this->chemicalValueVect);
    this->ChemicalKeyIndexFile.close();
    this->ChemicalValueIndexFile.close();
}

CLMS::ChemicalLogComponent::~ChemicalLogComponent() {
    openFile(this->UserKeyIndexFile, getFilePath("User", this->dirChain, FileType::IndexKeyFile), std::ios::out);
    openFile(this->UserValueIndexFile, getFilePath("User", this->dirChain, FileType::IndexValueFile), std::ios::out);
    saveKeyValueIndexFile(this->UserKeyIndexFile, this->UserValueIndexFile, this->userKeyMap, this->userValueVect);
    this->UserKeyIndexFile.close();
    this->UserValueIndexFile.close();
    openFile(this->ChemicalKeyIndexFile, getFilePath("Chemical", this->dirChain, FileType::IndexKeyFile), std::ios::out);
    openFile(this->ChemicalValueIndexFile, getFilePath("Chemical", this->dirChain, FileType::IndexValueFile), std::ios::out);
    saveKeyValueIndexFile(this->ChemicalKeyIndexFile, this->ChemicalValueIndexFile, this->chemicalKeyMap, this->chemicalValueVect);
    this->ChemicalKeyIndexFile.close();
    this->ChemicalValueIndexFile.close();
}

void CLMS::ChemicalLogComponent::getComponentInput() {
    std::string Uid, Cid, Quantity, Action;
    uint64_t timeStamp;
    std::cout << "Enter the Chemical Log Uid, Chemical Log Cid, Quantity and action: ";
    std::cin >> Uid >> Cid >> Quantity >> Action;
    timeStamp = getCurrentTime();
    ChemicalLog cLog = ChemicalLog(
        timeStamp, Uid, Cid, Quantity, Action
    );
    std::string packedData = this->getPackedData(&cLog, '|');
    uint32_t biteOffSet = this->writeDataAndUpdateIndex(packedData, std::to_string(timeStamp), 64);
    this->updateKeyValue(this->userKeyMap, this->userValueVect, Uid, timeStamp, biteOffSet);
    this->updateKeyValue(this->chemicalKeyMap, this->chemicalValueVect, Cid, timeStamp, biteOffSet);
}

std::string CLMS::ChemicalLogComponent::getPackedData(const void* data, const char del) {
    const ChemicalLog* cLog = (const ChemicalLog*)data;
    return std::string() + del + std::to_string(cLog->timeStamp) + del + cLog->Uid + del + cLog->Cid + del + cLog->Quantity + del + cLog->Action + del;
}

std::shared_ptr<void> CLMS::ChemicalLogComponent::unpackData(const std::string& timeStamp) {
    std::vector<std::string> logData = this->extractData(timeStamp);
    if (logData.size() == 0) {
        return std::make_shared<std::nullptr_t>(nullptr);
    }
    std::string Uid, Cid, Quantity, Action;
    return std::make_shared<ChemicalLog>(new ChemicalLog(logData));
}

std::vector<std::vector<std::string>> CLMS::ChemicalLogComponent::getData(std::vector<std::string> ids) {
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
        }else if (this->chemicalKeyMap.find(id) != this->chemicalKeyMap.end()) {
            int tsi = this->chemicalKeyMap.find(id)->second.firstTimeStampIndex;
            while (tsi != -1) {
                tsids.emplace_back(std::to_string(this->chemicalValueVect[tsi].timestamp));
                tsi = this->chemicalValueVect[tsi].nextIndex;
            }
        } else {
            tsids.emplace_back(id);
        }
    }
    return LogComponent::getData(tsids);
}

std::vector<std::string> CLMS::ChemicalLogComponent::getHeaders() {
    return {"timeStamp", "Uid", "Cid", "Quantity", "Action"};
}

CLMS::ChemicalLogComponent::ChemicalLog::ChemicalLog(const uint64_t timeStamp, const std::string Uid, const std::string Cid, const std::string Quantity,  const std::string Action) {
    this->timeStamp = timeStamp;
    this->Uid = Uid;
    this->Cid = Cid;
    this->Quantity = Quantity;
    this->Action = Action;
}

CLMS::ChemicalLogComponent::ChemicalLog::ChemicalLog(const ChemicalLog* cLog) {
    this->timeStamp = cLog->timeStamp;
    this->Uid = cLog->Uid;
    this->Cid = cLog->Cid;
    this->Quantity = cLog->Quantity;
    this->Action = cLog->Action;
}

CLMS::ChemicalLogComponent::ChemicalLog::ChemicalLog(std::vector<std::string> data) {
    this->timeStamp = std::atoi(data[0].c_str());
    this->Uid = data[1];
    this->Cid = data[2];
    this->Quantity = data[3];
    this->Action = data[4];
}

std::string CLMS::ChemicalLogComponent::ChemicalLog::print() {
    return "{TimeStamp : " + std::to_string(this->timeStamp) + ", Uid : " + this->Uid + ", Cid : " + this->Cid + ", Quantity : " + this->Quantity + ", Quantity : " + this->Quantity + "}";
}
