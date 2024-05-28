#include <nanoshell.h>
#include <standardlib.h>
#include <shellfunc.h>

#define CMD_MAX_CHARS 1000
#define PROMPT "NanoShell<33> $> "

static void readCommand();

void startNanoShell()
{
    while (1)
    {
        readCommand();
    }
}

static void readCommand(){
    fdprintf(STDMARK, PROMPT);
    char cmdBuff[CMD_MAX_CHARS];
    uint64_t length = readLine(cmdBuff);
}