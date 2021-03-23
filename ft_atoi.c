/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kxayavon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 11:44:30 by kxayavon          #+#    #+#             */
/*   Updated: 2021/03/23 14:26:54 by kxayavon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	skip_n_mixed_charset(int start_pos, char *str, char *charset)
{
	int	found;
	int i;

	while (*(str + start_pos))
	{
		found = 0;
		i = 0;
		while (charset[i])
		{
			if (*(str + start_pos) == charset[i])
			{
				found = 1;
				break ;
			}
			i++;
		}
		start_pos++;
		if (!found)
			break ;
	}
	return (--start_pos);
}

int	get_sign(int start_pos, char *str, char *sign)
{
	if (*(str + start_pos) == '+' || *(str + start_pos) == '-')
	{
		*sign = *(str + start_pos);
		return (skip_n_mixed_charset(start_pos, str, "+-"));
	}
	else if (*(str + start_pos) >= '0' && *(str + start_pos) <= '9')
		*sign = '+';
	return (start_pos);
}

int	get_numbers(int start_pos, char *str, char *dest, int *n)
{
	int i;

	i = 0;
	if (!(*str >= '0' && *str <= '9') && *(str - 1) == '0')
		*(dest + i++) = '0';
	while (*(str + start_pos) >= '0' && *(str + start_pos) <= '9')
		*(dest + i++) = *(str + start_pos++);
	*n = i;
	*(dest + i) = '\0';
	return (start_pos);
}

int	power(int base, unsigned int xpn)
{
	if (xpn == 0)
		return (1);
	return (base * power(base, xpn - 1));
}

int	ft_atoi(char *str)
{
	int		result;
	int		i;
	int		n;
	char	sign;
	char	buffer[11];

	result = 0;
	i = 0;
	i = skip_n_mixed_charset(i, str, "\t\v\r\n\f ");
	i = get_sign(i, str, &sign);
	i = skip_n_mixed_charset(i, str, "0");
	i = get_numbers(i, str, buffer, &n);
	i = 0;
	while (buffer[i])
	{
		result += ((buffer[i] - '0') * power(10, n - 1));
		i++;
		n--;
	}
	if (sign == '-')
		return ((result *= -1));
	return (result);
}
