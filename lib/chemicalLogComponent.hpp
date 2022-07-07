
#pragma once

#include "main.hpp"
#include "util.hpp"
#include "component.hpp"
#include "logComponent.hpp"

namespace CLMS {
    class ChemicalLogComponent : public LogComponent {
        protected:

            std::unordered_map<std::string, Key> userKeyMap, chemicalKeyMap;
            std::vector<Value> userValueVect, chemicalValueVect;
            std::fstream UserKeyIndexFile, UserValueIndexFile, ChemicalKeyIndexFile, ChemicalValueIndexFile;
        public:

            ChemicalLogComponent();
            ~ChemicalLogComponent();

            virtual std::string getPackedData(const void* data, const char del);
            virtual std::shared_ptr<void> unpackData(const std::string& data);
            virtual void getComponentInput();
            virtual std::vector<std::string> getHeaders();
            virtual std::vector<std::vector<std::string>> getData(std::vector<std::string> ids = {});

            struct ChemicalLog {
                uint64_t timeStamp;
                std::string Uid, Cid, Quantity, Action;

                ChemicalLog(const uint64_t timeStamp, const std::string Uid, const std::string Cid, const std::string Quantity, const std::string Action);
                ChemicalLog(const ChemicalLog* cLog);
                ChemicalLog(std::vector<std::string> data);
                std::string print();
            };

    };
}
