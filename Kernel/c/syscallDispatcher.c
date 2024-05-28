#include <syscallDispatcher.h>
#include <naiveConsole.h>
#include <stdarg.h>
#include <keyboardDriver.h>
#include <videoDriver.h>
#include <interrupts.h>
#include <time.h>

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
    case 5:;
        // sys_draw_rectangle

        Rectangle *r = va_arg(args, Rectangle *);
        drawRectangle(r->color, r->up_l_x, r->up_l_y, r->lo_r_x, r->lo_r_y);
        break;
    case 6:;
        // sys_rtc
        break;
    case 7:;
        // sys_sleep
        _sti();
        uint32_t ticks = va_arg(args, uint32_t);
        sleep(ticks);
        _cli();
        break;
    case 8:;
        // sys_clear
        vdClear();
        break;
    case 9:;
        // sys_play_sound
        
        uint64_t sound_ticks = va_arg(args, uint64_t);
        uint64_t hz = va_arg(args, uint64_t); //hacer que no devuelva cero
        _sti();
        beep(hz, sound_ticks);
        _cli();
        break;
    case 10:;
        // sys_change_font
        vdChangeFontSize();
        break;
    }
    va_end(args);
    return ret;
}

uint64_t read(FileDescriptor fd, char *buffer, uint64_t count)
{
    // @TODO: ver si volar el file descriptor
    unsigned char character;
    uint64_t i = 0;
    while (i < count && (character = nextFromBuffer()) != 0)
    {
        buffer[i++] = character;
    }
    return i;
}
uint64_t write(FileDescriptor fd, const char *buffer, uint64_t count)
{
    uint32_t styleByFileDescriptor[] = {0, 0x00FFFFFF, 0x00FF0000, 0x0000FF00};
    return vdNPrintStyled(buffer, styleByFileDescriptor[fd], 0, count);
}