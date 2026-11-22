/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macheuk- <macheuk-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 17:04:38 by macheuk-          #+#    #+#             */
/*   Updated: 2026/11/22 11:23:07 by macheuk-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

# include <stdint.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <ifaddrs.h>
# include <net/if.h>
# include <net/ethernet.h>
# include <netinet/if_ether.h>
# include <netpacket/packet.h>

# include "libft.h"

# pragma pack(push, 1)
struct s_arp_packet
{
	struct ether_header	eth;
	struct ether_arp	arp;
};
# pragma pack(pop)

/* utils.c */
int		parse_mac(const char *str, uint8_t mac[6]);
int		parse_ip(const char *str, uint32_t *ip_be);
int		find_interface(char *ifname, size_t len, int *ifindex, uint32_t tgt_ip);

/* net.c */
int		open_raw_socket(void);
int		recv_arp_request(int sockfd, int ifindex, const uint8_t tgt_mac[6],
			uint32_t tgt_ip, uint32_t src_ip,
			uint8_t req_mac[6], uint32_t *req_ip);
int		send_arp_reply(int sockfd, int ifindex, const uint8_t dst_mac[6],
			const uint8_t src_mac[6], uint32_t src_ip, uint32_t dst_ip);

#endif
