
#pragma once

#include "component.hpp"
#include "util.hpp"

namespace CLMS {
    class LogComponent : public Component {
        public:

            LogComponent(const std::string& componentFileName);
            ~LogComponent();

    };
}
