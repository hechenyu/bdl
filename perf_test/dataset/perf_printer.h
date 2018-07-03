#ifndef __perf_printer_h
#define __perf_printer_h

#include <iostream>
#include <atomic>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

class PerfPrinter {
public:
    PerfPrinter(boost::asio::io_context& io, int interval_sec, std::atomic<bool> *stop_flag)
        : timer_(io, boost::asio::chrono::seconds(interval_sec)), interval_sec_(interval_sec), stop_flag_(stop_flag)
    {
        timer_.async_wait(boost::bind(&PerfPrinter::print, this));
    }

    ~PerfPrinter()
    {
        std::cout << "~PerfPrinter" << std::endl;
    }

    void print();

private:
    boost::asio::steady_timer timer_;
    int interval_sec_;
    std::atomic<bool> *stop_flag_;
};

#endif
