#include <standardlib.h>
#include <stdarg.h>

uint64_t syscall(uint64_t rax, uint64_t rbx, uint64_t rdx, uint64_t rcx);

#define MAX_CHARS 1000
#define MAX_NUMBER_LENGTH 100

uint64_t getNextToRead(char *c)
{
    return syscall(3, 1, 1, c);
}

static void unsigned_num_to_str(uint32_t num, uint32_t start, char *buff)
{

    uint32_t i = start;
    if (num == 0)
        buff[i++] = '0';
    while (i < MAX_NUMBER_LENGTH - 1 && num > 0)
    {
        buff[i++] = (num % 10) + '0';
        num /= 10;
    }
    buff[i] = 0;
    uint32_t revit = start;
    uint32_t revend = i - 1;
    while (revit < revend)
    {
        char aux = buff[revit];
        buff[revit] = buff[revend];
        buff[revend] = aux;
        revit++;
        revend--;
    }
}

static void signed_num_to_str(int32_t num, char *buff)
{
    uint32_t i = 0;
    if (num < 0)
    {
        buff[i++] = '-';
        num = -num;
    }
    unsigned_num_to_str(num, i, buff);
}

static uint32_t unsigned_str_to_num(uint64_t *it, uint64_t buff_length, char *buff)
{
    uint32_t num = 0;
    uint64_t i = *it;
    char debug[100];
    while (i < buff_length && buff[i] != ' ' && buff[i] != '\t')
    {
        num = num * 10 + (buff[i++] - '0');
    }
    *it = i;
    return num;
}

static void unsigned_num_to_hex_str(uint32_t num, char *buff)
{
    char hexDigits[] = "0123456789ABCDEF";
    uint32_t i = 0;
    if (num == 0)
        buff[i++] = '0';
    while (i < MAX_NUMBER_LENGTH - 1 && num > 0)
    {
        buff[i++] = hexDigits[num % 16];
        num /= 16;
    }
    buff[i] = 0;
    uint32_t revit = 0;
    uint32_t revend = i - 1;
    while (revit < revend)
    {
        char aux = buff[revit];
        buff[revit] = buff[revend];
        buff[revend] = aux;
        revit++;
        revend--;
    }
}

static int32_t signed_str_to_num(uint64_t *it, uint64_t buff_length, char *buff)
{
    int32_t mult = 1;
    if (buff[*it] == '-')
    {
        mult = -1;
        (*it)++;
    }
    return mult * unsigned_str_to_num(it, buff_length, buff);
}

uint64_t readLine(char buff[], uint64_t count)
{
    uint64_t i = 0;
    uint8_t c;
    while ((c = getc()) != '\n')
    {
        if (i < count)
        {
            buff[i] = c;
        }
        if (c == '\b')
        {
            if (i > 0)
            {
                i += putChar(c);
                if (i < count)
                    buff[i] = 0;
            }
        }
        else
        {
            i += putChar(c);
        }
    }
    putChar('\n');
    uint64_t toRet;
    if (i < count)
    {
        buff[i] = 0;
        toRet = i;
    }
    else
    {
        buff[count] = 0;
        toRet = count;
    }
    return i;
}

static uint64_t fdprintfargs(FileDescriptor fd, const char *fmt, va_list args)
{
    char buffer[MAX_CHARS] = {0};

    char numstr[MAX_NUMBER_LENGTH] = {0};
    uint64_t i, j, k;
    for (i = 0, j = 0; j < MAX_CHARS && fmt[i] != 0; i++)
    {
        if (fmt[i + 1] != 0)
        {
            if (fmt[i] == '%')
            {
                switch (fmt[i + 1])
                {
                case 's':;
                    // Tengo que poner un string
                    const char *s = va_arg(args, const char *);
                    k = 0;
                    while (j < MAX_CHARS && s[k] != 0)
                        buffer[j++] = s[k++];
                    i++; // salteo la s
                    break;
                case 'd':;
                    // Tengo que poner un valor entero con signo
                    int32_t d = va_arg(args, int32_t);
                    signed_num_to_str(d, numstr);
                    k = 0;
                    while (j < MAX_CHARS && numstr[k] != 0)
                        buffer[j++] = numstr[k++];
                    i++; // salteo la d
                    break;
                case 'u':;
                    // Tengo que poner un valor entero sin signo
                    uint32_t u = va_arg(args, uint32_t);
                    unsigned_num_to_str(u, 0, numstr);
                    k = 0;
                    while (j < MAX_CHARS && numstr[k] != 0)
                        buffer[j++] = numstr[k++];
                    i++; // salteo la u
                    break;
                case 'c':;
                    // Tengo que poner un caracter
                    int8_t c = va_arg(args, int);
                    buffer[j++] = c;
                    i++; // salteo la c
                    break;
                case 'x':;
                    // Tengo que poner un valor entero en hexadecimal
                    uint32_t x = va_arg(args, uint32_t);
                    unsigned_num_to_hex_str(x, numstr);
                    k = 0;
                    while (j < MAX_CHARS && numstr[k] != 0)
                        buffer[j++] = numstr[k++];
                    i++; // salteo la x
                    break;
                default:
                    // Si no es ninguno pongo el porcentaje
                    buffer[j++] = '%';
                    break;
                }
            }
            else if (fmt[i] == '\\')
            {
                switch (fmt[i + 1])
                {
                case 'n':
                    buffer[j++] = '\n';
                    i++;
                    break;
                case 't':
                    buffer[j++] = '\t';
                    i++;
                    break;
                default:
                    buffer[j++] = '\\';
                    i++;
                    break;
                }
            }
            else
            {
                buffer[j++] = fmt[i];
            }
        }
        else
        {
            buffer[j++] = fmt[i];
        }
    }
    buffer[j++] = 0;

    return syscall(4, fd, j, buffer);
}

uint64_t fdprintf(FileDescriptor fd, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    uint64_t toRet = fdprintfargs(fd, fmt, args);
    va_end(args);
    return toRet;
}

uint64_t printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    uint64_t toRet = fdprintfargs(STDOUT, fmt, args);
    va_end(args);
    return toRet;
}

uint64_t scanf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char buffer[MAX_CHARS + 1] = {0};
    char auxBuffer[100] = {0};
    uint64_t i, j, count_read;
    uint8_t *char_dir;
    int32_t *int_dir;

    uint64_t buffSize = 0;

    for (i = 0, j = 0, count_read = 0; fmt[i] != 0;)
    {
        if (j == buffSize)
        {
            buffSize = readLine(buffer, MAX_CHARS);
            j = 0;
        }
        if (buffer[j] == ' ')
        {
            j++;
        }
        else
        {
            if (fmt[i + 1] != 0 && fmt[i] == '%')
            {
                switch (fmt[i + 1])
                {
                case 's':;
                    char_dir = va_arg(args, char *);
                    while (j < buffSize && buffer[j] != ' ' && buffer[j] != '\t')
                        *char_dir++ = buffer[j++];
                    *char_dir = 0;
                    i++;
                    count_read++;
                    break;
                case 'd':;
                    int_dir = va_arg(args, int32_t *);
                    *int_dir = signed_str_to_num(&j, buffSize, buffer);
                    i++;
                    count_read++;
                    break;
                case 'u':;
                    int_dir = va_arg(args, uint32_t *);
                    *int_dir = unsigned_str_to_num(&j, buffSize, buffer);
                    i++;
                    count_read++;
                    break;
                case 'c':;
                    char_dir = va_arg(args, char *);
                    *char_dir = buffer[j++];
                    count_read++;
                    i++;
                    break;    
                }
            }
            i++;
        }
    }
    return count_read;
}

uint64_t
putChar(uint64_t character)
{
    uint8_t buffer[] = {character};
    return syscall(4, 1, 1, buffer);
}

uint8_t getc()
{
    uint8_t c;
    uint64_t l;
    while ((l = getNextToRead(&c)) < 1)
        ;
    return c;
}

uint8_t getChar()
{
    uint8_t buff[MAX_CHARS + 1];
    readLine(buff, MAX_CHARS);
    return buff[0];
}

int strcmp(char *s1, char *s2)
{
    int i, toReturn = 0, checked = 0;
    for (i = 0; s1[i] && s2[i]; i++)
    {
        if (!checked)
        {
            toReturn += (s1[i] - s2[i]);
            checked = toReturn == 0 ? 0 : 1;
        }
    }
    if (s1[i])
    {
        toReturn = s1[i];
    }
    else if (s2[i])
    {
        toReturn = s2[i];
    }
    return toReturn;
}

void toMinus(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += ('a' - 'A');
    }
}

void wait(uint32_t ticks)
{
    syscall(7, ticks, 0, 0);
}

void beep(uint32_t hz, uint32_t ticks)
{
    syscall(9, ticks, 0, hz);
}