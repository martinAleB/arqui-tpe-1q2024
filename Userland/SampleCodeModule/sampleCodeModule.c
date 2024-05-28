/* sampleCodeModule.c */
#include <standardlib.h>
#include <eliminator.h>
char *v = (char *)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;

extern void call_80h();



int main()
{
	// All the following code may be removed
	*v = 'X';
	*(v + 1) = 0x74;

	/* call_80h();

	printf("SOY UNA PATATA FRITA\nQUE USA PRINTF %s\t%d %u %c\n\n", "Alonsistas", -1, 50, '{');

	printf("Ingrese caracter: ");
	char c = getChar();
	// printf("a");
	printf("Caracter ingresado: %c\n", c);

	printf("% \\");

	// printf("Ingrese un string, un int, un uint y un caracter: ");
	char buff[100];
	int32_t i;
	uint32_t u;
	printf("Ingrese un caracter, un string, un uint y un int: ");
	scanf("%c %s %u %d", &c, buff, &u, &i);
	// printf("HOLA?");

	printf("Se ingreso: %s %c %u %d\n", buff, c, u, i);
	printf("Lo correcto seria: %s %c %u %d", "atata", 'p', 25, -50); */
	/* printf("MODULO DE PRUEBA DE LA LIBRERIA STANDARD DE C\nEste mensaje se esta imprimiendo con printf, deberia verse bien.\n========================\n");
	printf("A continuacion se usa printf para escribir un mensaje formateado:\n");
	printf("Soy una patata %s de %u kg, mi numero negativo favorito es %d y mi caracter favorito es %c\n", "frita", 70, -3, 'b');
	printf("Este mensaje esta\ttabeado. Ahora voy a hacer 2 saltos de linea\n\nMira ves que hay 3 saltos de linea?\n\n");
	printf("Ingresa exactamente el siguiente texto: \'patata 25 -50\'\n");
	char buff[100];
	int32_t d;
	uint32_t u;
	char c;
	scanf("%c %s %u %d", &c, buff, &u, &d);
	printf("Si scanf funciona bien, entonces el estado de las variables involucradas en el llamado deberia ser:\n");
	printf("buff = %s, c = %c, u = %u, d = %d\n", "atata", 'p', 25, -50);
	printf("Con el funcionamiento actual, scanf esta guardando en las variables:\n");
	printf("buff = %s, c = %c, u = %u, d = %d\n", buff, c, u, d);
	printf("Ingrese un caracter: ");
	c = getChar();
	printf("Se guardo con getChar y putChar imprime: ");
	putChar(c); */
	eliminator();
	printf("Ingrese un caracter: ");
	unsigned char c;
	c = getChar();
	syscall(8,0,0,0);
	syscall(10,0,0,0);

	eliminator();

	printf("Caracter: %c\n", c);
	printf("a");
	syscall(7,15,0,0);
	printf("a");
	syscall(7,15,0,0);
	printf("a");
	syscall(7,15,0,0);
	printf("a");
	syscall(7,15,0,0);
	printf("a");
	syscall(7,15,0,0);
	printf("a");
	syscall(7,15,0,0);
	printf("a");
	
	char buff[100];
	int num;
	unsigned int num2;
	char c1;
	printf("Please enter: an int (except for the cursed one), a string, an unsigned int and a character\n");
	scanf("%d %s %u %c", &num, buff, &num2, &c1);
	if (num == 33)
	{
		printf("Bala.\n");
	}
	else
	{
		printf("This was scanned:\nInt = %d\nString = %s\nUnsigned int = %u\nCharacter = %c\n", num, buff, num2, c1);
	}
	//  Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;
	return 0xDEADBEEF;
}