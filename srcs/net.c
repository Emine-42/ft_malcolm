/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macheuk- <macheuk-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:11:31 by macheuk-          #+#    #+#             */
/*   Updated: 2026/11/20 16:00:00 by macheuk-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"

extern volatile sig_atomic_t	g_stop;

int	open_raw_socket(void)
{
	int	sock;

	sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	if (sock < 0)
		return (-1);
	return (sock);
}

static int	is_matching_request(const struct s_arp_packet *pkt,
				const uint8_t tgt_mac[6], uint32_t tgt_ip, uint32_t src_ip)
{
	const uint8_t	bcast[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	uint32_t		req_tgt_ip;
	uint32_t		req_src_ip;

	if (ntohs(pkt->eth.ether_type) != ETHERTYPE_ARP)
		return (0);
	if (ft_memcmp(pkt->eth.ether_dhost, bcast, 6) != 0)
		return (0);
	if (ntohs(pkt->arp.ea_hdr.ar_hrd) != ARPHRD_ETHER)
		return (0);
	if (ntohs(pkt->arp.ea_hdr.ar_pro) != ETHERTYPE_IP)
		return (0);
	if (pkt->arp.ea_hdr.ar_hln != 6 || pkt->arp.ea_hdr.ar_pln != 4)
		return (0);
	if (ntohs(pkt->arp.ea_hdr.ar_op) != ARPOP_REQUEST)
		return (0);
	ft_memcpy(&req_tgt_ip, pkt->arp.arp_tpa, 4);
	if (req_tgt_ip != src_ip)
		return (0);
	ft_memcpy(&req_src_ip, pkt->arp.arp_spa, 4);
	if (ft_memcmp(pkt->arp.arp_sha, tgt_mac, 6) != 0 && req_src_ip != tgt_ip)
		return (0);
	return (1);
}

int	recv_arp_request(int sockfd, int ifindex, const uint8_t tgt_mac[6],
		uint32_t tgt_ip, uint32_t src_ip,
		uint8_t req_mac[6], uint32_t *req_ip)
{
	uint8_t				buf[4096];
	struct sockaddr_ll	addr;
	socklen_t			addrlen;
	ssize_t				r;
	struct s_arp_packet	*pkt;

	while (!g_stop)
	{
		addrlen = sizeof(addr);
		r = recvfrom(sockfd, buf, sizeof(buf), 0,
				(struct sockaddr *)&addr, &addrlen);
		if (r < 0)
		{
			if (errno == EINTR)
				continue ;
			return (-1);
		}
		if (r < (ssize_t)sizeof(struct s_arp_packet))
			continue ;
		if (ifindex != 0 && addr.sll_ifindex != ifindex)
			continue ;
		pkt = (struct s_arp_packet *)buf;
		if (is_matching_request(pkt, tgt_mac, tgt_ip, src_ip))
		{
			ft_memcpy(req_mac, pkt->arp.arp_sha, 6);
			ft_memcpy(req_ip, pkt->arp.arp_spa, 4);
			return (1);
		}
	}
	return (0);
}

int	send_arp_reply(int sockfd, int ifindex, const uint8_t dst_mac[6],
		const uint8_t src_mac[6], uint32_t src_ip, uint32_t dst_ip)
{
	struct s_arp_packet	pkt;
	struct sockaddr_ll	saddr;
	ssize_t				sent;

	ft_memset(&pkt, 0, sizeof(pkt));
	ft_memcpy(pkt.eth.ether_dhost, dst_mac, 6);
	ft_memcpy(pkt.eth.ether_shost, src_mac, 6);
	pkt.eth.ether_type = htons(ETHERTYPE_ARP);
	pkt.arp.ea_hdr.ar_hrd = htons(ARPHRD_ETHER);
	pkt.arp.ea_hdr.ar_pro = htons(ETHERTYPE_IP);
	pkt.arp.ea_hdr.ar_hln = 6;
	pkt.arp.ea_hdr.ar_pln = 4;
	pkt.arp.ea_hdr.ar_op = htons(ARPOP_REPLY);
	ft_memcpy(pkt.arp.arp_sha, src_mac, 6);
	ft_memcpy(pkt.arp.arp_spa, &src_ip, 4);
	ft_memcpy(pkt.arp.arp_tha, dst_mac, 6);
	ft_memcpy(pkt.arp.arp_tpa, &dst_ip, 4);
	ft_memset(&saddr, 0, sizeof(saddr));
	saddr.sll_family = AF_PACKET;
	saddr.sll_ifindex = ifindex;
	saddr.sll_halen = 6;
	ft_memcpy(saddr.sll_addr, dst_mac, 6);
	sent = sendto(sockfd, &pkt, sizeof(pkt), 0,
			(struct sockaddr *)&saddr, sizeof(saddr));
	if (sent != (ssize_t)sizeof(pkt))
		return (-1);
	return (0);
}
