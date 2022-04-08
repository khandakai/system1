/*!
\file
\brief Файл с тестами CUnit
*/

#include <CUnit/Basic.h>
#include "numwork.h"


#define TEST_SIZE 5
/*! \brief Тест функции number_to_ten_base
 *
 */
void test_number_to_ten_base_convert(void)
{
    char* number_set[] = {"101010", "JABA", "AF12B", "1942", "176345"};

    char* base_set[] = {"2", "20", "16", "10", "8"};

    int expected_result_set[] = {42, 156230, 717099, 1942, 64741};

    for (int i = 0; i < TEST_SIZE; i++)
    {
        CU_ASSERT(number_to_ten_base(number_set[i], base_set[i]) == expected_result_set[i]);
    }
}

/*! \brief Тест функции digit_to_ten_base
 *
 */
void test_digit_to_ten_base(void)
{
    char* char_set ="5AJC9";

    int base_set[] = {6, 13, 20, 16, 10};

    int expected_result[] = {5, 10, 19, 12, 9};

    for (int i = 0; i < TEST_SIZE; i++)
    {
        CU_ASSERT(digit_to_ten_base(char_set[i], base_set[i]) == expected_result[i]);
    }
}

/*! \brief Тест функции get_invert_sequence
 *
 */
void test_get_invert_sequence(void)
{
    char* number_set[] = {"ABC", "1337", "124931", "Je23A","10101"};

    char* base_set[] = {"16", "8", "10", "20", "2"};

    char* expected_result_set[] = {"543", "6440", "875068", "05HG9", "01010"};

    for (int i = 0; i < TEST_SIZE; i++)
    {
        CU_ASSERT_STRING_EQUAL(get_invert_sequence(number_set[i], base_set[i]),
                               expected_result_set[i]);
    }
}

/*! \brief Тест функции convert_int_to_ch
 *
 */
void test_convert_int_to_ch(void)
{
    int number_set[] = {10, 5, 15, 18, 12};

    char* expected_result_set = "A5FIC";

    for (int i = 0; i < TEST_SIZE; i++)
    {
        CU_ASSERT((int)convert_int_to_ch(number_set[i]) == (int)expected_result_set[i]);
    }
}

/*! \brief Тест функции max_ch_in_base
 *
 */
void test_max_ch_in_base(void)
{
    int base_set[] = {2, 12, 16, 20, 14};

    char* expected_result_set = "1BFJD";

    for (int i = 0; i < TEST_SIZE; i++)
    {
        CU_ASSERT((int)max_ch_in_base(base_set[i]) == (int)expected_result_set[i]);
    }
}

/*! \brief Тест функции get_max_number
 *
 */
void test_get_max_number(void)
{
    char* number_set[] = {"12345", "111", "ABCDF", "123132", "2222"};

    char* base_set[] = {"10", "2", "16", "20", "8"};

    char* expected_result_set[] = {"99999", "111", "FFFFF", "JJJJJJ", "7777"};

    for (int i = 0; i < TEST_SIZE; i++)
    {
        CU_ASSERT_STRING_EQUAL(get_max_number(number_set[i], base_set[i]),
                               expected_result_set[i]);
    }
}

/*! \brief Точка входа для CUnit
 *
 * \return код завершения программы
 */
int main(void)
{
    if (CU_initialize_registry() != CUE_SUCCESS)
    {
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_pSuite suite = CU_add_suite("test_suite", 0, 0);

    if (suite == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(suite, "test_digit_to_ten_base", test_digit_to_ten_base);
    CU_add_test(suite, "test_number_to_ten_base_convert", test_number_to_ten_base_convert);
    CU_add_test(suite, "test_get_invert_sequence", test_get_invert_sequence);
    CU_add_test(suite, "test_convert_int_to_ch", test_convert_int_to_ch);
    CU_add_test(suite, "test_max_ch_in_base", test_max_ch_in_base);
    CU_add_test(suite, "test_get_max_number", test_get_max_number);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();

}