#include <syscallDispatcher.h>
#include <naiveConsole.h>
#include <stdarg.h>
#include <keyboardDriver.h>
#include <videoDriver.h>

uint64_t syscallDispatcher(uint64_t id, ...)
{
    va_list args;
    va_start(args, id);
    uint64_t ret;
    switch (id)
    {
    case 3:;
    case 4:;
        FileDescriptor fd = va_arg(args, FileDescriptor);
        char *buffer = va_arg(args, char *);
        uint64_t count = va_arg(args, uint64_t);
        if (id == 3)
            ret = read(fd, buffer, count);
        else
            ret = write(fd, buffer, count);
        break;
    }
    va_end(args);
    return ret;
}

uint64_t read(FileDescriptor fd, char *buffer, uint64_t count)
{
    // @TODO: ver que onda stderr
    return readBuffer(buffer, count);
}
uint64_t write(FileDescriptor fd, const char *buffer, uint64_t count)
{
    uint32_t styleByFileDescriptor[] = {0, 0x00FFFFFF, 0x00FF0000};
    return vdNPrintStyled(buffer, styleByFileDescriptor[fd], 0, count);
}