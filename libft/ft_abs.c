/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 08:17:06 by pcarles           #+#    #+#             */
/*   Updated: 2018/11/30 08:17:18 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_abs(int x)
{
	int	neg;

	neg = x >> ((sizeof(int) * 8) - 1);
	return ((neg ^ x) - neg);
}
