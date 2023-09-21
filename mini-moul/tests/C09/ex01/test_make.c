#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    char *command;
    char **expectations;
    int n;
} t_test;

int run_test(t_test test, int test_num);
char *modify_string(const char *str);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "Makefile supports make all",
            .command = "make all",
            .expectations = (char *[]){
                "test -f srcs/ft_putchar.o",
                "test -f srcs/ft_putstr.o",
                "test -f srcs/ft_strcmp.o",
                "test -f srcs/ft_strlen.o",
                "test -f srcs/ft_swap.o",
                "test -f libft.a"
            },
            .n = 6
        },
        {
            .desc = "Makefile supports make clean",
            .command = "(make all && make clean)",
            .expectations = (char *[]){
                "! test -f srcs/*.o",
                "test -f libft.a"
            },
            .n = 2
        },
        {
            .desc = "Makefile supports make fclean",
            .command = "(make all && make fclean)",
            .expectations = (char *[]){
                "! test -f srcs/*.0",
                "! test -f libft.a"
            },
            .n = 2
        },
        {
            .desc = "Makefile supports make re",
            .command = "make re",
            .expectations = (char *[]){
                "test -f srcs/ft_putchar.o",
                "test -f srcs/ft_putstr.o",
                "test -f srcs/ft_strcmp.o",
                "test -f srcs/ft_strlen.o",
                "test -f srcs/ft_swap.o",
                "test -f libft.a"
            },
            .n = 6
        },
        {
            .desc = "Makefile supports make libft.a",
            .command = "(make fclean && make libft.a)",
            .expectations = (char *[]){
                "test -f srcs/ft_putchar.o",
                "test -f srcs/ft_putstr.o",
                "test -f srcs/ft_strcmp.o",
                "test -f srcs/ft_strlen.o",
                "test -f srcs/ft_swap.o",
                "test -f libft.a"
            },
            .n = 6
        }
    };

    int num_tests = sizeof(tests) / sizeof(t_test);

    int overall_result = 0;

    for (int i = 0; i < num_tests; i++)
    {
        int result = run_test(tests[i], i + 1);

        if (result != 0)
        {
            overall_result = -1;
        }
    }

    return overall_result;
}

int run_test(t_test test, int test_num)
{
    fflush(stdout);
    char buf[1024];
    memset(buf, 0, sizeof(buf));

    system("cp -R utils/C09/ex01/* .");
    system("cp ../ex01/Makefile .");

    char *make_command;
    asprintf(&make_command, "%s 1>/dev/null", test.command);
    system(make_command);
    free(make_command);

    for (int i = 0; i < test.n; i++)
    {
        int test_result = system(test.expectations[i]);
        if (test_result != 0)
        {
            printf("    " RED "[%d] %s Expected \"%s\" to return 0.\n" DEFAULT, test_num, test.desc, test.expectations[i]);
            return -1;
        }
    }

    printf("  " GREEN CHECKMARK GREY " [%d] %s\n" DEFAULT, test_num, test.desc);
    return (0);
}

char *modify_string(const char *str)
{
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        char *new_str = (char *)malloc(len);
        strncpy(new_str, str, len - 1);
        new_str[len - 1] = '$';
        return new_str;
    }
    else
    {
        return strdup(str);
    }
}