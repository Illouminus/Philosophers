/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:51:13 by edouard           #+#    #+#             */
/*   Updated: 2024/08/22 11:59:46 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

bool is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
const char *check_sign(const char *str, int *error)
{
	if (*str == '+')
		return str + 1;
	else if (*str == '-')
	{
		*error = 1;
		return NULL;
	}
	return str;
}

const char *skip_spaces(const char *str)
{
	while (is_space(*str))
		str++;
	return str;
}
const char *check_digits(const char *str, int *error)
{
	int len = 0;
	const char *nmb = str;

	while (is_digit(*str))
	{
		len++;
		str++;
	}
	if (len == 0 || len > 10)
	{
		*error = 1;
		return NULL;
	}
	return nmb;
}

const char *valid_input(const char *str, int *error)
{
	str = skip_spaces(str);
	str = check_sign(str, error);
	if (*error)
		return NULL;
	return check_digits(str, error);
}