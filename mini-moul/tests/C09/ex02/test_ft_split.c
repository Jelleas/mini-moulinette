#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../../../../ex02/ft_split.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    char *str;
    char *charset;
    char **expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "ft_split(\"hello world\", \" \") works as expected\n",
            .str = "hello world",
            .charset = " ",
            .expected = (char *[]){"hello", "world", "\0"},
        },
        {
            .desc = "ft_split(\"hello world\", \" l\") works as expected\n",
            .str = "hello world",
            .charset = " l",
            .expected = (char *[]){"he", "o", "wor", "d", "\0"},
        },
        {
            .desc = "ft_split(\"hello world\", \"\") works as expected\n",
            .str = "hello world",
            .charset = "",
            .expected = (char *[]){"hello world", "\0"},
        },
        {
            .desc = "ft_split(\"hello world\", \"hello world\") works as expected\n",
            .str = "hello world",
            .charset = "hello world",
            .expected = (char *[]){"\0"},
        },
    };
    int count = sizeof(tests) / sizeof(tests[0]);

    return run_tests(tests, count);
}

int run_test(t_test test, int i_test)
{
    char **result = ft_split(test.str, test.charset);

    for (int i = 0; test.expected[i][0]; i++)
    {
        if (strcmp(test.expected[i], result[i]) != 0)
        {
            printf("    " RED "[%d] %s Expected %s, got %s\n", i_test + 1, test.desc, test.expected[i], result[i]);
            return -1;
        }
    }

    printf("  " GREEN CHECKMARK GREY " [%d] %s " DEFAULT, i_test + 1, test.desc);
    return 0;
}

int run_tests(t_test *tests, int count)
{
    int error = 0;

    for (int i = 0; i < count; i++)
    {
        int result = run_test(tests[i], i);
        error = error || result;
    }

    return error;
}