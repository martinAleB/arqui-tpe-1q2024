#include <nanoshell.h>
#include <standardlib.h>

#define CMD_MAX_CHARS 1000

static void readCommand();

void startNanoShell()
{
    while (1)
    {
        readCommand();
    }
}

static void readCommand()
{
    printf("NanoShell<33> $> ");
    char cmdBuff[CMD_MAX_CHARS];
    uint64_t length = readLine(cmdBuff);
}