#include <rt/rt.h>
#include <cstdio>
#include <constants/colors.hpp>
#include <log/log.h>
RT::RT(const std::string &msg) : _msg{msg}
{
    _start = std::chrono::high_resolution_clock::now();
};
RT::~RT()
{
    _end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elaped_time{_end - _start};
    auto formated_string=std::format("Time taken by {} {:.2f}s\n", _msg.c_str(), elaped_time.count());
    Log::log(formated_string,Type::E_DISPLAY);
};