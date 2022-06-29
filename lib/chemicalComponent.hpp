#pragma once

#include "component.hpp"
#include "util.hpp"

namespace CLMS {
    class ChemicalComponent : public Component {
        private:

        public:

            ChemicalComponent();
            ~ChemicalComponent();

            virtual std::string getPackedData(const void* data, const char del);
            virtual std::shared_ptr<void> unpackData(const std::string& data);
            virtual void getComponentInput();
            virtual std::vector<std::string> getHeaders();

            struct Chemical {
                std::string Cid, Chemical_Name, Quantity;

                Chemical(const Chemical* chemical);
                Chemical(const std::string Cid, const std::string Chemical_Name, const std::string Quantity);
                Chemical(std::vector<std::string> data);
                std::string print();
            };

    };
}
