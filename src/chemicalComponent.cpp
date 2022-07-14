
#include "../lib/chemicalComponent.hpp"

CLMS::ChemicalComponent::ChemicalComponent() : Component("ChemicalComponent", ComponentType::DataComponent, {"component", "Chemical"}) {
    loadIndex();
}

CLMS::ChemicalComponent::~ChemicalComponent(){}

void CLMS::ChemicalComponent::getComponentInput() {
    std::string Cid, Chemical_Name, Quantity;
    std::cout << "Enter Chemical Information Cid, Chemical_Name, Quantity: ";
    std::cin >> Cid >> Chemical_Name >> Quantity;
    Chemical chemical = Chemical(
        Cid, Chemical_Name, Quantity
    );
    this->writeDataAndUpdateIndex(this->getPackedData(&chemical, '|'), Cid, 36);
}

std::string CLMS::ChemicalComponent::getPackedData(const void* data, const char del) {
    const Chemical* chemicalData = (const Chemical*)data;
    return std::string() + del + chemicalData->Cid + del + chemicalData->Chemical_Name + del + chemicalData->Quantity + del;
}

std::shared_ptr<void> CLMS::ChemicalComponent::unpackData(const std::string& componentId) {
    std::vector<std::string> compData = this->extractData(componentId);
    if (compData.size() == 0) {
        return std::make_shared<std::nullptr_t>(nullptr);
    }
    return std::make_shared<Chemical>(new Chemical(compData));
}

std::vector<std::string> CLMS::ChemicalComponent::getHeaders() {
    return {"Cid", "Chemical_Name", "Quantity"};
}

CLMS::ChemicalComponent::Chemical::Chemical(const std::string Cid, const std::string Chemical_Name, const std::string Quantity) {
    this->Cid = Cid;
    this->Chemical_Name = Chemical_Name;
    this->Quantity = Quantity;
}

CLMS::ChemicalComponent::Chemical::Chemical(const CLMS::ChemicalComponent::Chemical* chemical) {
    this->Cid = chemical->Cid;
    this->Chemical_Name = chemical->Chemical_Name;
    this->Quantity = chemical->Quantity;
}

CLMS::ChemicalComponent::Chemical::Chemical(std::vector<std::string> data) {
    this->Cid = data[0];
    this->Chemical_Name = data[1];
    this->Quantity = data[2];
}

std::string CLMS::ChemicalComponent::Chemical::print() {
    return "{Cid : " + this->Cid + ", Chemical_Name : " + this->Chemical_Name + ", Quantity : " + this->Quantity + "}";
}
