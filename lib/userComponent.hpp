
#pragma once

#include "component.hpp"
#include "util.hpp"

namespace CLMS {
    class UserComponent : public Component {
        private:

            std::string Id, Name, Contact;

        public:

            UserComponent(const std::string& componentFileName);
            ~UserComponent();
    };
}
