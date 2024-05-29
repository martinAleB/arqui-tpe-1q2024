#include <nanoshell.h>
#include <standardlib.h>

#define CMD_MAX_CHARS 1000
#define FUNCTION_NUM 8
#define PROMPT "NanoShell<33> $> "

static char * instructions[] = {"help", "registers", "time", "eliminator", "echo", "change_font", "vim", "test_exceptions"};

static char * help_text = "A continuación se muestran los comandos disponibles:\n\
                        help --> muestra todos los comandos disponibles a ejecutarse\n\
                        registers --> muestra el estado de los registros actualmente o cuando se los guardó por última vez\n\
                        time --> muestra la hora actual en formato hh:mm:ss\n\
                        eliminator --> inicia una partida de 'eliminator'! Un juego muy divertido para jugar contra la compu\n\
                        \t\t\t\to contra un amigo! El objetivo es sobrevivir más que tu oponente, mové tu serpiente con\n\
                        \t\t\t\twasd (jugador 1) o con ijkl (jugador 2), y no te choques con nada! Buena suerte!\n\
                        echo [string] --> imprime en pantalla el string pasado como argumento\n\
                        change_font --> cambia el tamaño de la fuente actual\n\
                        vim --> abre un editor de texto\n\
                        test_exceptions --> testea las excepciones manejadas\n";

typedef enum {
	HELP=0,
	REGISTERS,
	TIME,
	ELIMINATOR,
	ECHO,
    CHANGE_FONT,
	VIM,
	TEST_EXCEPTIONS
} INSTRUCTION;

static uint64_t readCommand(char * buff);
static int interpret(char * command);

void startNanoShell()
{
    char cmdBuff[CMD_MAX_CHARS] = {0};
    int exit = 0;
    while (!exit)
    {
        fdprintf(STDMARK, PROMPT);
        int command_length = readLine(cmdBuff);

        int interpretation = interpret(cmdBuff);

        char toPrint[100];
        int i=0;

        switch(interpretation) 
		{
			case HELP:
				printf(help_text);
				break;
			
			case REGISTERS:
                getRegisters();
				break;
			
			case TIME:
                printf("Coming soon...");
				//showTime();
				break;
			
			case ELIMINATOR:
				eliminator();
				break;
				
			case ECHO:
                while (cmdBuff[i] && cmdBuff[i]!=' ' && cmdBuff != '\t') {
                    i++;
                }
                i++;
                for (int j=0;cmdBuff[i];i++, j++) {
                    toPrint[j] = cmdBuff[i];
                }
				printf(toPrint);
				break;
				
			case CHANGE_FONT:
                changeFontSize();
                break;
			
			case VIM:
				printf("Coming soon...");
                //vim();
				break;
				
			case TEST_EXCEPTIONS:
                printf("Coming soon...");
                //test_exceptions();
                break;

			case -1:
				printf("No se reconoce el comando: '%s'", cmdBuff);
				break;
		}
        printf("\n");

    }
}

//Hace falta?
static uint64_t readCommand(char * buff)
{
    return readLine(buff);
}

static int interpret(char * command) {
	char actualCommand[100] = {0};
    for (int i=0; command[i]!= 0 && command[i]!= ' ' && command[i] != '\t'; i++){
        actualCommand[i] = command[i];
        toMinus(actualCommand);
    }
	for (int i=0; i<FUNCTION_NUM; i++) {
		if (strcmp(actualCommand, instructions[i])==0)
			return i;
	}
	return -1;
}