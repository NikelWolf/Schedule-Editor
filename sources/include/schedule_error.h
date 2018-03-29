#pragma once

#include <iostream>

using namespace std;

namespace schedule_api {
    class ScheduleError : public runtime_error {
    public:
        explicit ScheduleError(const string &message) : runtime_error{message} {}

        explicit ScheduleError(const char *message) : runtime_error(message) {}
    };
}
