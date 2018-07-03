#include "perf_printer.h"

void PerfPrinter::print()
{
    if (*stop_flag_)
    {
        return;
    }

    std::cout << "xxxx" << std::endl;

    timer_.expires_at(timer_.expiry() + boost::asio::chrono::seconds(interval_sec_));
    timer_.async_wait(boost::bind(&PerfPrinter::print, this));
}

