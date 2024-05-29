#ifndef SYSCALLS_DISPATCHER_H
#define SYSCALLS_DISPATCHER_H

#include <stdint.h>
#include <rtc.h>

typedef enum
{
    STDOUT = 1,
    STDERR,
    STDMARK,
} FileDescriptor;

uint64_t syscallDispatcher(uint64_t id, ...);
uint64_t read(FileDescriptor fd, char *buffer, uint64_t count);
uint64_t write(FileDescriptor fd, const char *buffer, uint64_t count);
uint64_t getRegBackup(uint64_t* arr);

#endif