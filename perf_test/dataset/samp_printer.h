#ifndef __perf_printer_h
#define __perf_printer_h

#include <iostream>
#include <atomic>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

class SampPrinter {
public:
    SampPrinter(boost::asio::io_context& io, int interval_sec,
            std::atomic<int> *file_number_readed, std::atomic<uint64_t> *file_size_readed,
            std::ostream &out)
        : timer_(io, boost::asio::chrono::seconds(interval_sec)), interval_sec_(interval_sec), stop_flag_(false),
        file_number_readed_(file_number_readed), file_size_readed_(file_size_readed), out_(out)
    {
        timer_.async_wait(boost::bind(&SampPrinter::print, this));
    }

    ~SampPrinter()
    {
        std::cout << "~SampPrinter" << std::endl;
    }

    void print();

    void stop();

private:
    boost::asio::steady_timer timer_;
    int interval_sec_;
    std::atomic<bool> stop_flag_;

    std::atomic<int> *file_number_readed_;
    std::atomic<uint64_t> *file_size_readed_;

    int last_file_number_readed_ = 0;
    uint64_t last_file_size_readed_ = 0;

    int curr_file_number_readed_ = 0;
    uint64_t curr_file_size_readed_ = 0;

    std::ostream &out_;
};

#endif
