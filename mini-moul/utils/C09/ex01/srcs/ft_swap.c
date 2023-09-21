void ft_swap(int *a, int *b)
{
	int placeholder = *b;
	*b = *a;
	*a = placeholder;
}
