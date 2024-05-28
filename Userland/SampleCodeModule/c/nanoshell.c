#include <nanoshell.h>
#include <standardlib.h>
#include <shellfunc.h>

#define CMD_MAX_CHARS 1000

static void readCommand();

void startNanoShell()
{
    /*
    while (1)
    {
        readCommand();
    }
    */
    for(int i =0; i < 3; i++)
        readCommand();
    getRegisters();
}

static void readCommand(){
    printf("NanoShell<33> $> ");
    char cmdBuff[CMD_MAX_CHARS];
    uint64_t length = readLine(cmdBuff);
}