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
    char *program;
    char *expected;
} t_test;

int run_test(t_test test, int test_num);
char *modify_string(const char *str);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "libft.a has ft_putchar",
            .program = "putchar.c",
            .expected = "c"
        },
        {
            .desc = "libft.a has ft_putstr",
            .program = "putstr.c",
            .expected = "hello world"
        },
        {
            .desc = "libft.a has ft_strlen",
            .program = "strlen.c",
            .expected = "11"
        },
        {
            .desc = "libft.a has ft_swap",
            .program = "swap.c",
            .expected = "42"
        },
        {
            .desc = "libft.a has ft_strcmp",
            .program = "strcmp.c",
            .expected = "0"
        },
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
    int result;

    char *copy_command;
    asprintf(&copy_command, "cp utils/C09/ex00/%s foo.c", test.program);
    system(copy_command);
    free(copy_command);

    system("mkdir -p ex00");
    system("cp ../ex00/*.c ex00");
    system("cp ../ex00/*.sh ex00");
    system("(cd ex00; sh libft_creator.sh)");
    system("cc -c -g -Wall -Werror -Wextra foo.c");
    system("cc -o foo foo.o ex00/libft.a");

    char *run_command = "./foo";

    // Run the program and capture its output
    FILE *fp = popen(run_command, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to run command '%s': %s\n", run_command, strerror(errno));
        exit(EXIT_FAILURE);
    }

    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        if (strcmp(buf, test.expected) != 0)
        {
            printf("    " RED "[%d] %s Expected \"%s\", got \"%s\"\n" DEFAULT, test_num, test.desc, test.expected, modify_string(buf));
            result = -1;
        }
        else
        {
            printf("  " GREEN CHECKMARK GREY " [%d] %s output \"%s\" as expected\n" DEFAULT, test_num, test.desc, modify_string(buf));
            result = 0;
        }
    }

    if (pclose(fp) == -1)
    {
        fprintf(stderr, "Failed to close command stream: %s\n", strerror(errno));
        exit(EXIT_FAILURE); // Remove the program executable
        if (remove("foo") != 0)
        {
            fprintf(stderr, "Failed to remove program '%s': %s\n", "foo", strerror(errno));
            exit(EXIT_FAILURE);
        }

        remove("foo.c");

        return (result);
    }

    // Remove the program executable
    if (remove("foo") != 0)
    {
        fprintf(stderr, "Failed to remove program '%s': %s\n", "foo", strerror(errno));
        exit(EXIT_FAILURE);
    }

    remove("foo.c");

    return (result);
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