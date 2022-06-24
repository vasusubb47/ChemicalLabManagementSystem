
#include "../lib/logComponent.hpp"

CLMS::LogComponent::LogComponent(std::string logName, std::vector<std::string> dirChain) : Component(logName, ComponentType::LogComponent, dirChain) {
    std::cout << "Log Component\n";
    loadIndex();
}

CLMS::LogComponent::~LogComponent() {}
