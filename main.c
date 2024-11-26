#include "stdio.h"
#include "./lib/conio.h"
#include "./lib/keyboard.c"
#include <sys/ioctl.h>
#include "./lib/common.c"

#define MAX_LINE_LEN 64

void panic(char message[])
{
    gotoxy(0, wherey() + 1);
    printf("Error %s                                         ", message);
    exit(1);
}

void injectAt(char array[], int size, int index, char value)
{
    if (index < 0 || index > size)
    {
        printf("Access out of bounds, trying to access index %d at size %d", index, size);
        exit(3);
    }
    for (int i = size; i > index; i--)
    {
        array[i] = array[i - 1];
    }
    array[index] = value;
}

void deleteAt(char array[], int size, int index)
{
    if (index < 0 || index > size)
    {
        printf("Access out of bounds, trying to access index %d at size %d", index, size);
        exit(3);
    }
    for (int i = index; i < size - 1; i++)
    {
        array[i] = array[i + 1];
    }
    array[size - 1] = '\0';
}

int main()
{

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    char buffer[MAX_LINE_LEN] = {0};
    int len = 0;
    int current = 0;
    char insertmode = 0;
    setCursor(IBeam);
    printf("%s", buffer);
    while (1)
    {
        int input = captureKeyboardInput();
        switch (input)
        {
        case Insert:
            insertmode = !insertmode;
            setCursor(insertmode ? Underline : IBeam);
            break;
        case Home:
            current = 0;
            gotox(0);
            break;
        /*TODO: handle word deletion*/
        /* case AltBackSpace:
         *     while (buffer[current] != ' ' && len > 0 && current > 0)
         *     {
         *         printf("d(%d, %d)\n\n\n%s", buffer[current], current, buffer);
         *         deleteAt(buffer, len, current);
         *         current--;
         *         len--;
         *     }
         *     break;
         */
        case End:
            current = len;
            gotox(current);
            break;
        case Enter:
            system("clear");
            printf("Your message: `%s`\n", buffer);
            exit(0);
        //TODO: add delete function
        // case Delete:
        //     if(current < len && current >= 0 && len > 0){
        //         deleteAt(buffer, len, current);
        //         len--;
        //         system("clear");
        //         printf("%s", buffer);
        //         gotox(current);
        //     }
        //     break;

        case Backspace:
            if (current > 0 && len > 0)
            {
                deleteAt(buffer, len, insertmode ? current : current - 1);
                len--;
                current--;
                system("clear");
                printf("%s", buffer);
                gotox(current + 1);
            }
            if (current == 0 && insertmode && len)
            {
                deleteAt(buffer, len, 0);
                len--;
                system("clear");
                printf("%s", buffer);
                gotox(current + 1);
            }
            break;
        case ArrowLeft:
            if (current > 0)
            {
                gotox(wherex() - 1);
                current--;
            }
            break;
        case ArrowRight:
            if (current < len)
            {
                gotox(wherex() + 1);
                current++;
            }
            break;
        case KeySpace ... KeyTilde:
        {
            if (insertmode)
            {
                if (current == len)
                { /*@end*/
                    if (len == MAX_LINE_LEN)
                    { /* max len */
                        /* replace only */
                        buffer[current] = input;
                        printf("%c", input);
                        gotox(wherex() - 1);
                    }
                    else
                    {
                        buffer[current] = input; /* replace */
                        printf("%c", input);
                        len++;     /* expand */
                        current++; /* increase */
                    }
                }
                else
                {                            /* not at the end */
                    buffer[current] = input; /* replace */
                    printf("%c", input);
                    current++; /* increase */
                }
            }
            else
            {
                if (current == len)
                { /*@end*/
                    if (len != MAX_LINE_LEN)
                    {
                        buffer[current] = input;
                        printf("%c", input);
                        current++;
                        len++;
                    }
                }
                else
                {
                    if (len + 1 < MAX_LINE_LEN)
                    {
                        injectAt(buffer, len + 1, current, input);
                        system("clear");
                        printf("%s", buffer);
                        current += 1;
                        len++;
                        gotox(current + 1);
                    }
                }
            }
        }
        break;

        default:
            // printf("BADACTx %d", input);
            break;
        }

        /* int lasty = wherey();
         * int lastx = wherex();
         * gotoxy(0, lasty + 1);
         * printf("[DEBUG]: current = %d, insert_mode = %d, len = %d                 ", current, insertmode, len);
         * gotoxy(lastx, lasty);
         */
    }
}