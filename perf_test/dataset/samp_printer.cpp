#include <chrono>
#include "boost/format.hpp"
#include "samp_printer.h"
#include "utc_to_string.h"

void SampPrinter::stop()
{
    stop_flag_ = true;
}

void SampPrinter::print()
{
    if (stop_flag_)
    {
        return;
    }

    curr_file_number_readed_ = file_number_readed_->load();
    curr_file_size_readed_ = file_size_readed_->load();

    int iops = (curr_file_number_readed_ - last_file_number_readed_) / interval_sec_;
    double io_rate = (double) (curr_file_size_readed_ - last_file_size_readed_) / interval_sec_ / 1000000;

    const std::string fmt_str = R"({"now": %s, "io_rate MB/s": %.2f, "iops file/s": %d})";
    boost::format fmt(fmt_str);
    out_ << fmt % utc_to_string(std::chrono::system_clock::now()) % io_rate % iops << std::endl;

    last_file_number_readed_ = curr_file_number_readed_;
    last_file_size_readed_ = curr_file_size_readed_;

    timer_.expires_at(timer_.expiry() + boost::asio::chrono::seconds(interval_sec_));
    timer_.async_wait(boost::bind(&SampPrinter::print, this));
}

