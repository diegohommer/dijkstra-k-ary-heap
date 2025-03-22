#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include <cstdio>   // For FILE, fopen, fscanf, fclose
#include <unistd.h> // For getpagesize() on Linux
#include <cstddef>  // For size_t

size_t memory_used(bool resident = false);

#endif // MEMORY_UTILS_H
