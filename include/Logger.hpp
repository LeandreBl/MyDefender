#pragma once

#include <iostream>
#include <chrono>
#include <string>

#include "colors.h"

static bool verbose = false;

namespace Logger {
    template <typename ...Args>
    void Log(Args&& ...args) noexcept
    {
        if (verbose == false)
            return;
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        struct tm *p = localtime(&time);
        char buffer[128];
 
        std::strftime(buffer, sizeof(buffer), "%A, %B, %d %Y", p);
        (std::cerr << YELLOW << buffer << RESET " " << ... << std::forward<Args>(args)) << std::endl;
    }

    template <typename T>
    void LogStatus(const T &object, bool status = false) noexcept
    {
        if (verbose == false)
            return;
        Log(object, " [", (status ? BOLDGREEN "OK" RESET: BOLDRED "KO" RESET), ']');
    }

    void setVerbose(bool state) noexcept
    {
        verbose = state;
    }
};