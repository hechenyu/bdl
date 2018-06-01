#ifndef __ceil_to_align_at_h
#define __ceil_to_align_at_h

#include <type_traits>

template <typename T, typename = typename
    std::enable_if<std::is_integral<T>::value>::type>
T ceil_to_align_at(T val, int align)
{
    T q = val / align;
    T r = val % align;
    T align_val = q * align + (r == 0 ? 0 : align);
    return align_val;
}

#endif
