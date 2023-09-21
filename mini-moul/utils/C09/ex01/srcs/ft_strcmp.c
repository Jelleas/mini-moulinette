int ft_strcmp(char *s1, char *s2)
{
	int s1_minus_s2 = 0;
	int i = 0;
	while ((s1_minus_s2 == 0) && ((s1[i] != '\0') || (s2[i] != '\0')))
	{
		s1_minus_s2 = s1[i] - s2[i];
		i++;
	}
	return (s1_minus_s2);
}
