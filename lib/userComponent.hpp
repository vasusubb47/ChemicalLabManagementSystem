
#pragma once

#include "component.hpp"
#include "util.hpp"

namespace CLMS {
    class UserComponent : public Component {
        private:

        public:

            UserComponent(const std::string& componentFileName);
            ~UserComponent();

            virtual std::string getPackedData(const std::string& componentId, char del);
            virtual void unpackData(const std::string& data);
            // virtual void writeData(const std::string& packedData, uint16_t width, char fill);
            virtual void getComponentInput();
            virtual std::vector<std::string> getHeaders();
            virtual std::vector<std::string> getData(const std::string& componentId);

            struct User {
                std::string Id, Name, Contact;

                // User();
                User(const std::string Id, const std::string name, const std::string contact);
            };

    };
}
