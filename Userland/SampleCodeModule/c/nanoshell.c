#include <nanoshell.h>
#include <standardlib.h>

#define CMD_MAX_CHARS 1000
#define CMD_NAME_MAX_CHARS 100
#define FUNCTION_NUM 8
#define PROMPT "NanoShell $> "

static char *instructions[] = {"help", "registers", "time", "eliminator", "echo", "change_font", "test_zero_division", "test_invalid_opcode"};

// @TODO: CAMBIAR COMANDO TEST_EXCEPTIONS POR COMANDOS DE INVALID OPCODE Y ZERO DIVISION
static char *help_text = "A continuacion se muestran los comandos disponibles:\n\
help --> Muestra todos los comandos disponibles a ejecutarse.\n\
registers --> Muestra el estado de los registros actualmente o cuando se los guardo por ultima vez.\n\
time --> Muestra la hora actual en formato hh:mm:ss.\n\
eliminator --> Inicia una partida de 'eliminator'! Un juego muy divertido para jugar de a 1 o 2.\n\
echo [string] --> Imprime en pantalla el string pasado como argumento.\n\
change_font --> Cambia el tamaño de la fuente actual.\n\
test_zero_division --> Testea la excepcion de division por 0.\n\
test_invalid_opcode --> Testea la excepcion de invalid opcode.";

typedef enum
{
    HELP = 0,
    REGISTERS,
    TIME,
    ELIMINATOR,
    ECHO,
    CHANGE_FONT,
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

        case CHANGE_FONT:
            changeFontSize();
            break;

        case TEST_ZERO_DIVISION:
            testZeroDivision();
            break;

        case TEST_INVALID_OPCODE:
            testInvalidOpcode();
            break;

        case -1:
            printf("No se reconoce el comando: '%s'", cmdBuff);
            break;
        }

        if (interpretation != CHANGE_FONT && interpretation != ELIMINATOR)
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