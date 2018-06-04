#ifndef __print_section_h
#define __print_section_h

#include "section_memory_cache.h"
#include <string>

void print_section_header(const SectionMemoryCache &section, const std::string &title);

void print(const SectionMemoryCache &section, const std::string &title);

#endif
