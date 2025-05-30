#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

void    test_with_str_and_int(void) {
    int ret1, ret2;

    ft_printf("------TEST WITH STR AND INT------\n");
    ret1 = printf("Hello %s %d\n", "world", 42);
    ret2 = ft_printf("Hello %s %d\n", "world", 42);

    if (ret1 != ret2)
        printf("Mismatch return: printf=%d ft_printf=%d\n", ret1, ret2);
    else
        printf("Match return values (%d)\n", ret1);
}

void    test_with_hex(void) {
    int ret1, ret2;

    ft_printf("------TEST WITH HEX------\n");
    ret1 = printf("Hex: %x %X\n", 42, 42);
    ret2 = ft_printf("Hex: %x %X\n", 42, 42);

    if (ret1 != ret2)
        printf("Mismatch return: printf=%d ft_printf=%d\n", ret1, ret2);
    else
        printf("Match return values (%d)\n", ret1);
}

void    test_with_address(void) {
    int ret1, ret2;
    int a = 42;

    ft_printf("------TEST WITH ADDRESS------\n");
    ret1 = printf("Address: %p\n", (void *)&a);
    ret2 = ft_printf("Address: %p\n", (void *)&a);

    if (ret1 != ret2)
        printf("Mismatch return: printf=%d ft_printf=%d\n", ret1, ret2);
    else
        printf("Match return values (%d)\n", ret1);
}

void    test_with_unsigned(void) {
    int ret1, ret2;

    ft_printf("------TEST WITH UNSIGNED------\n");
    ret1 = printf("Unsigned: %u\n", 42);
    ret2 = ft_printf("Unsigned: %u\n", 42);

    if (ret1 != ret2)
        printf("Mismatch return: printf=%d ft_printf=%d\n", ret1, ret2);
    else
        printf("Match return values (%d)\n", ret1);
}

void    test_with_char(void) {
    int ret1, ret2;

    ft_printf("------TEST WITH CHAR------\n");
    ret1 = printf("Char: %c\n", 'A');
    ret2 = ft_printf("Char: %c\n", 'A');

    if (ret1 != ret2)
        printf("Mismatch return: printf=%d ft_printf=%d\n", ret1, ret2);
    else
        printf("Match return values (%d)\n", ret1);
}

//edges cases
void    test_with_empty_string(void) {
    int ret1, ret2;

    ft_printf("------TEST WITH EMPTY STRING------\n");
    ret1 = printf("Empty string: %s\n", "");
    ret2 = ft_printf("Empty string: %s\n", "");

    if (ret1 != ret2)
        printf("Mismatch return: printf=%d ft_printf=%d\n", ret1, ret2);
    else
        printf("Match return values (%d)\n", ret1);
}

void    test_with_null(void) {
    int ret1, ret2;
    char *str = NULL;

    ft_printf("------TEST WITH NULL------\n");
    ret1 = printf("Null: %s\n", str);
    ret2 = ft_printf("Null: %s\n", str);

    if (ret1 != ret2)
        printf("Mismatch return: printf=%d ft_printf=%d\n", ret1, ret2);
    else
        printf("Match return values (%d)\n", ret1);
}

void    test_with_negative(void) {
    int ret1, ret2;

    ft_printf("------TEST WITH NEGATIVE------\n");
    ret1 = printf("Negative: %d\n", -42);
    ret2 = ft_printf("Negative: %d\n", -42);

    if (ret1 != ret2)
        printf("Mismatch return: printf=%d ft_printf=%d\n", ret1, ret2);
    else
        printf("Match return values (%d)\n", ret1);
}

void    test_with_large_number(void) {
    int ret1, ret2;

    ft_printf("------TEST WITH LARGE NUMBER------\n");
    ret1 = printf("Large number: %d\n", 2147483647);
    ret2 = ft_printf("Large number: %d\n", 2147483647);

    if (ret1 != ret2)
        printf("Mismatch return: printf=%d ft_printf=%d\n", ret1, ret2);
    else
        printf("Match return values (%d)\n", ret1);
}

void    test_with_negative_large_number(void) {
    int ret1, ret2;

    ft_printf("------TEST WITH NEGATIVE LARGE NUMBER------\n");
    ret1 = printf("Negative large number: %d\n", INT_MIN);
    ret2 = ft_printf("Negative large number: %d\n", INT_MIN);

    if (ret1 != ret2)
        printf("Mismatch return: printf=%d ft_printf=%d\n", ret1, ret2);
    else
        printf("Match return values (%d)\n", ret1);
}

void    test_with_dif_zero_formats(void) {
    int ret1, ret2;

    ft_printf("------TEST WITH DIFFERENT ZERO FORMATS------\n");
    ret1 = printf("%d %u %x %X %p\n", 0, 0u, 0, 0, NULL);
    ret2 = ft_printf("%d %u %x %X %p\n", 0, 0u, 0, 0, NULL);

    if (ret1 != ret2)
        printf("Mismatch return: printf=%d ft_printf=%d\n", ret1, ret2);
    else
        printf("Match return values (%d)\n", ret1);
}

void    test_with_negatives_unsigned(void) {
    int ret1, ret2;

    ft_printf("------TEST WITH NEGATIVE UNSIGNED------\n");
    ret1 = printf("Negative unsigned: %u\n", -42);
    ret2 = ft_printf("Negative unsigned: %u\n", -42);

    if (ret1 != ret2)
        printf("Mismatch return: printf=%d ft_printf=%d\n", ret1, ret2);
    else
        printf("Match return values (%d)\n", ret1);
}

void    test_with_percentages(void) {
    int ret1, ret2;

    ft_printf("------TEST WITH PERCENTAGES------\n");
    ret1 = printf("This is 100%% done\n");
    ret2 = ft_printf("This is 100%% done\n");

    if (ret1 != ret2)
        printf("Mismatch return: printf=%d ft_printf=%d\n", ret1, ret2);
    else
        printf("Match return values (%d)\n", ret1);
}

void    test_with_non_formatted_specifier(void) {

    ft_printf("------TEST WITH NON FORMATTED SPECIFIER------\n");
    printf("The real printf gives and error\n");
    ft_printf("Non formatted specifier: %q lets see what happens");
}

int main(void) {
    test_with_str_and_int();
    test_with_hex();
    test_with_address();
    test_with_unsigned();
    test_with_char();
    test_with_empty_string();
    test_with_null();
    test_with_negative();
    test_with_large_number();
    test_with_negative_large_number();
    test_with_dif_zero_formats();
    test_with_negatives_unsigned();
    test_with_percentages();
    test_with_non_formatted_specifier();
    return (0);
}