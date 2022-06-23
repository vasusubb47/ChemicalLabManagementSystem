
#pragma once

#include "component.hpp"
#include "util.hpp"

namespace CLMS {
    class UserComponent : public Component {
        private:

        public:

            UserComponent();
            ~UserComponent();

            virtual std::string getPackedData(const void* data, const char del);
            virtual std::shared_ptr<void> unpackData(const std::string id);
            virtual void getComponentInput();
            virtual std::vector<std::string> getHeaders();

            struct User {
                std::string Id, Name, Contact;

                User(const User* user);
                User(const std::string Id, const std::string name, const std::string contact);
                User(std::vector<std::string> data);
                std::string print();
            };

    };
}
