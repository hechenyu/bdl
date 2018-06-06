#include "error.h"
#include "calculate_crc32.h"
#include <boost/crc.hpp>

using namespace boost;

uint32_t calculate_crc32(const uint8_t *data, int size)
{
    crc_32_type crc32;
    crc32.process_bytes(data, size);
    return crc32.checksum();
}
