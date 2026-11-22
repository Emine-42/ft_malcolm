/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macheuk- <macheuk-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 11:38:24 by macheuk-          #+#    #+#             */
/*   Updated: 2026/11/22 11:26:51 by macheuk-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"

static int	hex_char_val(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

int	parse_mac(const char *str, uint8_t mac[6])
{
	int	i;
	int	hi;
	int	lo;

	if (!str || ft_strlen(str) != 17)
		return (-1);
	i = 0;
	while (i < 6)
	{
		hi = hex_char_val(str[i * 3]);
		lo = hex_char_val(str[i * 3 + 1]);
		if (hi < 0 || lo < 0)
			return (-1);
		mac[i] = (uint8_t)((hi << 4) | lo);
		if (i < 5 && str[i * 3 + 2] != ':')
			return (-1);
		i++;
	}
	return (0);
}

int	parse_ip(const char *str, uint32_t *ip_be)
{
	struct in_addr	addr;

	if (!str || !ip_be)
		return (-1);
	if (inet_pton(AF_INET, str, &addr) != 1)
		return (-1);
	*ip_be = addr.s_addr;
	return (0);
}

int	find_interface(char *ifname, size_t len, int *ifindex, uint32_t tgt_ip)
{
	struct ifaddrs		*ifaddr;
	struct ifaddrs		*ifa;
	struct sockaddr_in	*sa;
	struct sockaddr_in	*netmask;
	char				fallback[IF_NAMESIZE];

	fallback[0] = '\0';
	if (getifaddrs(&ifaddr) == -1)
		return (-1);
	ifa = ifaddr;
	while (ifa)
	{
		if (ifa->ifa_name && (ifa->ifa_flags & IFF_UP)
			&& !(ifa->ifa_flags & IFF_LOOPBACK)
			&& ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET)
		{
			sa = (struct sockaddr_in *)ifa->ifa_addr;
			netmask = (struct sockaddr_in *)ifa->ifa_netmask;
			if (netmask && (tgt_ip & netmask->sin_addr.s_addr)
				== (sa->sin_addr.s_addr & netmask->sin_addr.s_addr))
			{
				ft_strlcpy(ifname, ifa->ifa_name, len);
				*ifindex = if_nametoindex(ifa->ifa_name);
				freeifaddrs(ifaddr);
				return (0);
			}
			if (fallback[0] == '\0')
				ft_strlcpy(fallback, ifa->ifa_name, sizeof(fallback));
		}
		ifa = ifa->ifa_next;
	}
	freeifaddrs(ifaddr);
	if (fallback[0] != '\0')
	{
		ft_strlcpy(ifname, fallback, len);
		*ifindex = if_nametoindex(fallback);
		return (0);
	}
	return (-1);
}
