
#pragma once

#include "main.hpp"
#include "util.hpp"
#include "component.hpp"
#include "logComponent.hpp"

namespace CLMS {
    class UserLogComponent : public LogComponent {
        public:

            UserLogComponent();
            ~UserLogComponent();

            virtual std::string getPackedData(const void* data, const char del);
            virtual std::shared_ptr<void> unpackData(const std::string& data);
            virtual void getComponentInput();
            virtual std::vector<std::string> getHeaders();
            virtual std::string getData(const std::string& componentId);

            struct UserLog {
                uint64_t timeStamp;
                std::string Uid, state;

                UserLog(const uint64_t timeStamp, const std::string Uid, const std::string state);
                UserLog(const UserLog* uLog);
                std::string print();
            };

    };
}
