#include <nanoshell.h>
#include <standardlib.h>
#include <videolib.h>

#define CMD_MAX_CHARS 1000
#define CMD_NAME_MAX_CHARS 100
#define FUNCTION_NUM 8
#define PROMPT "NanoShell $> "

static char *instructions[] = {"help", "registers", "time", "eliminator", "echo", "clear", "change_font", "nano_song", "test_zero_division", "test_invalid_opcode"};

static char *help_text = "Here's a list of all available commands:\n\
- help --> Help display with all commands\n\
- registers --> Displays the lastest backup of registers\n\
- time --> Displays time and date\n\
- eliminator --> Starts the eliminator game\n\
- echo [string] --> Prints the [string] argument in the display\n\
- clear --> clears the display\n\
- change_font --> Changes the current font\n\
- nano_song --> Use command for a surprise\n\
- test_zero_division --> Test for the Zero Division exception\n\
- test_invalid_opcode --> Test for the Invalid Opcode exception";

typedef enum
{
    HELP = 0,
    REGISTERS,
    TIME,
    ELIMINATOR,
    ECHO,
    CLEAR,
    CHANGE_FONT,
    NANO_SONG,
    TEST_ZERO_DIVISION,
    TEST_INVALID_OPCODE,
} INSTRUCTION;

static uint64_t readCommand(char *buff);
static int interpret(char *command);

void startNanoShell()
{
    char cmdBuff[CMD_MAX_CHARS + 1] = {0};
    int exit = 0;
    while (!exit)
    {
        fdprintf(STDMARK, PROMPT);
        int command_length = readLine(cmdBuff, CMD_MAX_CHARS);

        int interpretation = interpret(cmdBuff);

        char toPrint[100];
        int i = 0;

        switch (interpretation)
        {
        case HELP:
            printf(help_text);
            break;

        case REGISTERS:
            getRegisters();
            break;

        case TIME:
            printCurrentTime();
            break;

        case ELIMINATOR:
            eliminator();
            break;

        case ECHO:
            while (cmdBuff[i] && cmdBuff[i] != ' ' && cmdBuff != '\t')
            {
                i++;
            }
            i++;
            int j;
            for (j = 0; cmdBuff[i]; i++, j++)
            {
                toPrint[j] = cmdBuff[i];
            }
            toPrint[j] = 0;
            printf(toPrint);
            break;
            
        case CLEAR:
            clearScreen();
            break;

        case CHANGE_FONT:
            changeFontSize();
            break;

        case NANO_SONG:
            nanoAnthem();
            break;

        case TEST_ZERO_DIVISION:
            testZeroDivision();
            break;

        case TEST_INVALID_OPCODE:
            testInvalidOpcode();
            break;

        case -1:
            printf("Command not found: '%s'", cmdBuff);
            break;
        }

        if (interpretation != CHANGE_FONT && interpretation != ELIMINATOR && interpretation != CLEAR)
        {
            printf("\n");
        }
    }
}

static int interpret(char *command)
{
    char actualCommand[CMD_MAX_CHARS] = {0};
    int i;
    for (i = 0; i < CMD_MAX_CHARS && command[i] != 0 && command[i] != ' ' && command[i] != '\t'; i++)
    {
        actualCommand[i] = command[i];
        toMinus(actualCommand);
    }
    if (i == CMD_MAX_CHARS && command[i] != 0)
        return -1;
    for (i = 0; i < FUNCTION_NUM; i++)
    {
        if (strcmp(actualCommand, instructions[i]) == 0)
            return i;
    }
    return -1;
}