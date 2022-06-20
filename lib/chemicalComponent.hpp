#pragma once

#include "component.hpp"
#include "util.hpp"

namespace CLMS {
    class chemicalComponent : public Component {
        private:

        public:

            ChemicalComponent();
            ~ChemicalComponent();

            virtual std::string getPackedData(const void* data, const char del);
            virtual std::shared_ptr<void> unpackData(const std::string& data);
            virtual void getComponentInput();
            virtual std::vector<std::string> getHeaders();
            virtual std::string getData(const std::string& componentId);

            struct Chemical {
                std::string CId, Chemical_Name, Quantity;

                Chemical(const User* user);
                Chemival(const std::string CId, const std::string Chemical_Name, const std::string Quantity);
                std::string print();
            };

    };
}
