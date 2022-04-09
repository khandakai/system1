/*!
\file
\brief Заголовочный файл для numwork.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef NUMWORK_H
#define NUMWORK_H

#define PARENT_PROGRAM "./main"
#define CHILD_PROGRAM "./num_processing"

/**
 * @brief Преобразовывает цифру
 * (char) в десятичную систему счисления (int)
 * @param digit цифра
 * @param base основание системы счисления (шестнадцатеричная = 16 и т.д.)
 * @return (int) число (преобразованная цифра в десятичную систему счисления)
 */
int digit_to_ten_base(char digit, int base);

int number_to_ten_base(char* number, char* number_base);

char convert_int_to_ch(int number);

char* get_invert_sequence(char* number, char* number_base);

char max_ch_in_base(int number_base);

char* get_max_number(char* number, char* number_base);

int unary_to_ten(char* number);
#endif /*NUMWORK_H*/