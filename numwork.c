/*!
\file
\brief Файл содержит функционал необходимый, для работы программы

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

/*! \brief Преобразовывает число из унарной системы счисления в десятичную
 *
 * @param number число в унарной системе
 * @return число в десятичной
 */
int unary_to_ten(char* number)
{
    unsigned long digits_count = strlen(number);
    printf("%d\n",digits_count);
    int count = 0;
    for (int i = 0; i < strlen(number); i++)
    {
        count++;
    }
    return count;
}
/*! \brief Преобразовывает цифру в десятичную систему счисления
 *
 *
 * \param digit цифра
 * \param base основание системы счисления (шестнадцатеричная = 16 и т.д.)
 * \return (int) число (преобразованная цифра в десятичную систему счисления)
 */
int digit_to_ten_base(char digit, int base)

{
    int base_ascii_range = 0;
    if (base > 10)
    {
        base_ascii_range = base - 11;
    }
    int digit_ascii = (int)digit;
    if (digit_ascii >= DIGITS_ASCII_START && digit_ascii <= DIGITS_ASCII_END)
    {
        return atoi(&digit);
    }
    else if (digit_ascii >= UC_ASCII_MIN && digit_ascii <= UC_ASCII_MIN + base_ascii_range)
    {
        int ten_based = 10;
        int i = UC_ASCII_MIN;

        while(i < digit_ascii)
        {
            ten_based++;
            i++;
        }
        return ten_based;
    }
    else if (digit_ascii >= LC_ASCII_MIN && digit_ascii <= LC_ASCII_MIN + base_ascii_range)
    {
        int ten_based = 10;
        int i = LC_ASCII_MIN;
        while(i < digit_ascii)
        {
            ten_based++;
            i++;
        }
        return ten_based;
    }
    else
    {
        fprintf(stderr, "[x] Некорректное число!\n");
        exit(EXIT_FAILURE);
    }

}


 /*! \brief Преобразовавывает число (строка char*) в системе счисления
 * (char*) в число (int) в десятичной системе счисления
 * системе счисления
 * \param number число системы счисления  1 < number <= 20
 * \param number_base система счисления 1 < number_base <= 20
 * \return (int) преобразованное число в системе счисления 10
 */
int number_to_ten_base(char* number, char* number_base)
{
    unsigned long digits_count = strlen(number);
    int base = atoi(number_base);
    int ten_based = 0;
    int power = 0;
    int current;
    for (int i = (int)digits_count - 1; i >= 0; i--)
    {
        current = digit_to_ten_base(number[i], base);
        ten_based += (int)(current * pow(base, power));
        power++;
    }
    return ten_based;
}

/*! \brief Переводит цифру из целочисленного в
 * в char с сохранением значения
 *
 * \param number цифра
 * \return (char) цифра но в символьном виде
 */
char convert_int_to_ch(int number)
{
    if (number < 10)
    {
        return (char)(DIGITS_ASCII_START + number);
    }
    else
    {
        int invert_int = UC_ASCII_MIN;
        int need  = number - 10;
        for (int i = 0; i < need; i++)
        {
            invert_int++;
        }
        return (char)invert_int;
    }
}


/*! \brief Находит и возвращает для числа (number) в системе счисления (number_base)
 * инвертированную последовательность (складывая её и число - получим максимальную
 * цифру для этой системы счисления в каждом разряде)
 *
 * \param number число
 * \param number_base система счисления
 * \return (char*) возвращает указатель на строку (инвертированную последовательность)
 */
char* get_invert_sequence(char* number, char* number_base)
{
    int base = atoi(number_base);
    unsigned long digits_count = strlen(number);
    int invert[digits_count];
    for (int i = 0; i < digits_count; i++)
    {
        int current = digit_to_ten_base(number[i], base);
        invert[i] = base - 1 - current;
    }
    char* p_result = (char*) malloc(sizeof(char) * digits_count + 1);

    for (int i = 0; i < digits_count; i++)
    {
        p_result[i] = convert_int_to_ch(invert[i]);
    }
    return p_result;
}

/*! \brief Функция возвращает максимальную цифру в системе счисления (number_base)
 *
 * \param number_base основание системы счисления
 * \return (char) Максимальная цифра в данной системе
 */
char max_ch_in_base(int number_base)
{
    if (number_base <= 10)
    {
        return (char)(DIGITS_ASCII_START + number_base - 1);
    }
    else
    {
        int max_ch = UC_ASCII_MIN;
        int need = number_base - 11;
        for (int i = 0; i < need; i++)
        {
            max_ch++;
        }
        return (char)max_ch;
    }
}

/*! \brief Функция генерирует строку из максимальных цифр в каждом разряде (максимальных в этой
 * системе счисления)
 *
 * \param number число
 * \param number_base система счисления
 * \return (char*) возвращает указатель на строку (строка из максимальных цифр в данной системе)
 */
char* get_max_number(char* number, char* number_base)
{
    unsigned long digits_count = strlen(number);
    char* p_result = (char*) malloc(sizeof(char) * digits_count + 1);

    char max_digit = max_ch_in_base(atoi(number_base));
    for (int i = 0; i < digits_count; i++)
    {
        p_result[i] = max_digit;
    }
    return p_result;
}
