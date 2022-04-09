/*!
\file
\brief Файл с точкой входа и выводом в терминал (программа для дочернего процесса)

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "numwork.h"

/*! \brief Точка входа для дочернего процесса.
 *
 * \param argc число аргументов
 * \param argv значения аргументов
 * \return
 */
int main(int argc, char* argv[])
{
    printf("all args: %s %s %s %s ", argv[0], argv[1], argv[2], argv[3]);
    if (strcmp(argv[0], PARENT_PROGRAM) != 0)
    {
        printf("\nПрограмма запускается только из родительского процесса\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        if (strcmp(argv[2], "u") == 0)
        {
            printf(":: Режим унарной системы счисления ::\n");
            printf("Это число в десятичной системе счисления : %d", unary_to_ten(argv[2]));
        }
        else
        {
            printf("\n[] Число: %s , система счисления: %s\n", argv[2], argv[1]);
            int ten_based_number = number_to_ten_base(argv[2], argv[1]);
            printf("[] Это число в десятичной системе счисления: %d\n", ten_based_number);
            char* p_addition = get_invert_sequence(argv[2], argv[1]);
            printf("[] Инвертированная последовательность в системе счисления %s: %s \n", argv[1], p_addition);
            printf("[] Инвертированная последовательность в 10-чной системе: %d\n", number_to_ten_base(p_addition, argv[1]));
            printf("[] Дополненное число: %s\n", get_max_number(argv[2], argv[1]));
        }
        return EXIT_SUCCESS;
    }

}


