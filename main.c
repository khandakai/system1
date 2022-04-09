/*!
\file
\brief Основной файл программы
 * Содержит функционал для предобработки поступаемых аргументов (валидация), родительский процесс.
*/

#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define NOT_ARGS_MODE 1
#define HELPER_MODE 2
#define NORMAL_MODE 3

#define ERROR_FORK -1
#define CHILD_FORK 0


#define MIN_NUM_BASE 2
#define MAX_NUM_BASE 20

#define DIGITS_ASCII_START 48
#define DIGITS_ASCII_END 57

#define UC_ASCII_MIN 65

#define LC_ASCII_MIN 97

#define PARENT_PROGRAM "./main"
#define CHILD_PROGRAM "./num_processing"

/*! \brief Функция удаления незначащих нулей из строки
 *
 * \param p_number указатель на строку
 * \return указатель на измененную строку
 */
char* delete_zeros(char* p_number)
{
    int length = (int)strlen(p_number);
    if (length == 1)
    {
        return p_number;
    }
    else
    {
        int i = 0;
        char first_symbol = p_number[0];
        if ((int)first_symbol == DIGITS_ASCII_START)
        {
            while ((int)first_symbol == DIGITS_ASCII_START)
            {
                i++;
                first_symbol = p_number[i];
            }
            char* p_str_without_zeros = (char*) malloc(sizeof(char) * length - i + 1);

            int j = 0;

            for (; i < length; i++)
            {
                p_str_without_zeros[j] = p_number[i];
                j++;
            }
            return p_str_without_zeros;
        }
        else
        {
            return p_number;
        }

    }
}

/*! \brief функция проверки для цифр (именно числовых)
 *
 * \param digit цифра
 * \param base основание системы
 * \return true/false
 */
bool check_numeric(char digit, int base)
{
    if (atoi(&digit) < base)
    {
        return true;
    }
    else if (atoi(&digit) == 0 && base == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*! \brief функция для проверки цифр (именно буквенных)
 *
 * \param digit_ascii код в таблице ASCII
 * \param base основание системы
 * \return true/false
 */
bool check_alphabetic(char digit_ascii, int base)
{
    int base_ascii_range = base - 11;

    if (digit_ascii >= UC_ASCII_MIN && digit_ascii <= UC_ASCII_MIN + base_ascii_range)
    {
        return true;
    }
    else if (digit_ascii >= LC_ASCII_MIN && digit_ascii <= LC_ASCII_MIN + base_ascii_range)
    {
        return true;
    }
    else
        return false;
}

/*! \brief Функция валидации аргументов
 *
 * \param argv значения аргументов
 * \return void
 */
void validate_args(char* argv[])
{
    int base;
    char* number = argv[2];
    int num_base = atoi(argv[1]);
    unsigned long digits_count = strlen(argv[2]);

    if (num_base >= MIN_NUM_BASE && num_base <= MAX_NUM_BASE)
    {
        base = num_base;
    }
    else if (strcmp(argv[1], "u") == 0)
    {
        base = 0;
    }
    else
    {
        fprintf(stderr, "Поддерживаемая система счисления (аргумент 1)  от %d до %d а так же u\n",
                MIN_NUM_BASE, MAX_NUM_BASE);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < digits_count; i++)
    {
        char current = number[i];
        int current_ascii = (int)number[i];

        if (current_ascii >= DIGITS_ASCII_START && current_ascii <= DIGITS_ASCII_END)
        {
            if (check_numeric(current, base))
            {
                continue;
            }
            else
            {
                fprintf(stderr, "Переданное число не соответствует системе счисления (аргументу 1)\n");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            if (check_alphabetic(current_ascii, base))
            {
                continue;
            }
            else
            {
                fprintf(stderr, "Переданное число не соответствует системе счисления (аргументу 1)\n");
                exit(EXIT_FAILURE);
            }

        }
    }
}
/*! \brief Точка входа в программу
 *
 * \param argc колличество аргументов
 * \param argv значения аргументов
 * \return код завершения программы
 */
int main(int argc, char* argv[])
{
    switch (argc)
    {
        case NOT_ARGS_MODE:
        {
            printf("Ошибка, не указаны дополнительные аргументы (пиши %s -h)\n", argv[0]);
            break;
        }

        case HELPER_MODE:
        {
            if (strcmp(argv[1], "-h") == 0)
            {
                printf("Использование программы:  %s {основание} {число в ней}\n", argv[0]);
            }
            else
            {
                fprintf(stderr, "[x] Чтобы вызвать справку используй %s -h\n", argv[0]);
                exit(EXIT_FAILURE);
            }
            break;
        }

        case NORMAL_MODE:
        {
            validate_args(argv);
            pid_t pid;
            int exec_status;
            switch (pid = fork()) {
                case CHILD_FORK: {
                    char *p_num = delete_zeros(argv[2]);
                    //
                    printf("MAIN OUTPUT:: %s %s %s %s", argv[0], argv[1], argv[2], p_num);
                    //
                    exec_status = execlp(CHILD_PROGRAM, PARENT_PROGRAM, argv[0], argv[1], p_num, NULL);
                    break;
                }
                case ERROR_FORK: {
                    fprintf(stderr, "Ошибка при fork!\n");
                    exit(EXIT_FAILURE);
                }

                default:
                    wait(NULL);
            };
            break;
        }

        default:
        {
            printf("Ошибка, переданное число аргументов != 2\n");
        }
    }
    return EXIT_SUCCESS;
}

