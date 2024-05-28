#ifndef LIBASM_H
#define LIBASM_H

#include <stdint.h>

uint64_t syscall(uint64_t rax, uint64_t rbx, uint64_t rdx, uint64_t rcx);

#endif