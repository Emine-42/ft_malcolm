/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macheuk- <macheuk-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:11:29 by macheuk-          #+#    #+#             */
/*   Updated: 2026/11/20 16:00:00 by macheuk-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"

volatile sig_atomic_t	g_stop = 0;

static void	sigint_handler(int sig)
{
	(void)sig;
	g_stop = 1;
}

static void	print_mac(const uint8_t mac[6])
{
	printf("%02x:%02x:%02x:%02x:%02x:%02x",
		mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

static int	validate_args(int argc, char **argv, uint8_t src_mac[6],
				uint8_t tgt_mac[6], uint32_t *src_ip, uint32_t *tgt_ip)
{
	if (argc != 5)
	{
		fprintf(stderr, "Usage: ft_malcolm <src_ip> <src_mac> <tgt_ip> <tgt_mac>\n");
		return (-1);
	}
	if (parse_ip(argv[1], src_ip) < 0)
	{
		fprintf(stderr, "ft_malcolm: unknown host or invalid IP address: (%s).\n", argv[1]);
		return (-1);
	}
	if (parse_mac(argv[2], src_mac) < 0)
	{
		fprintf(stderr, "ft_malcolm: invalid mac address: (%s)\n", argv[2]);
		return (-1);
	}
	if (parse_ip(argv[3], tgt_ip) < 0)
	{
		fprintf(stderr, "ft_malcolm: unknown host or invalid IP address: (%s).\n", argv[3]);
		return (-1);
	}
	if (parse_mac(argv[4], tgt_mac) < 0)
	{
		fprintf(stderr, "ft_malcolm: invalid mac address: (%s)\n", argv[4]);
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	uint8_t				src_mac[6];
	uint8_t				tgt_mac[6];
	uint32_t			src_ip;
	uint32_t			tgt_ip;
	uint8_t				req_mac[6];
	uint32_t			req_ip;
	char				ifname[IF_NAMESIZE];
	int					ifindex;
	int					sock;
	int					ret;
	struct sigaction	sa;
	char				ipbuf[INET_ADDRSTRLEN];
	struct in_addr		in;

	if (getuid() != 0)
	{
		fprintf(stderr, "ft_malcolm: must be run with \"sudo\"\n");
		return (1);
	}
	if (validate_args(argc, argv, src_mac, tgt_mac, &src_ip, &tgt_ip) < 0)
		return (1);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);
	ifindex = 0;
	if (find_interface(ifname, sizeof(ifname), &ifindex, tgt_ip) < 0)
	{
		fprintf(stderr, "ft_malcolm: no suitable interface found\n");
		return (1);
	}
	printf("Found available interface: %s\n", ifname);
	sock = open_raw_socket();
	if (sock < 0)
	{
		fprintf(stderr, "ft_malcolm: socket: %s\n", strerror(errno));
		return (1);
	}
	ret = recv_arp_request(sock, ifindex, tgt_mac, tgt_ip, src_ip, req_mac, &req_ip);
	if (ret <= 0)
	{
		close(sock);
		printf("Exiting program...\n");
		return (0);
	}
	printf("An ARP request has been broadcast.\n");
	printf("mac address of request: ");
	print_mac(req_mac);
	printf("\n");
	in.s_addr = req_ip;
	if (inet_ntop(AF_INET, &in, ipbuf, sizeof(ipbuf)) == NULL)
		ft_strlcpy(ipbuf, "unknown", sizeof(ipbuf));
	printf("IP address of request: %s\n", ipbuf);
	printf("Now sending an ARP reply to the target address with spoofed source, please wait...\n");
	if (send_arp_reply(sock, ifindex, tgt_mac, src_mac, src_ip, tgt_ip) < 0)
	{
		fprintf(stderr, "ft_malcolm: sendto: %s\n", strerror(errno));
		close(sock);
		return (1);
	}
	printf("Sent an ARP reply packet, you may now check the arp table on the target.\n");
	close(sock);
	printf("Exiting program...\n");
	return (0);
}
