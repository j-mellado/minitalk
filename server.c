/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 02:00:36 by jmellado          #+#    #+#             */
/*   Updated: 2025/08/06 02:02:52 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_state = 0;

void	handle_sigusr1(int sig)
{
	int	bit_count;
	int	current_char;

	(void)sig;
	bit_count = (g_state >> 8) & 0x7;
	current_char = g_state & 0xFF;
	current_char = (current_char << 1) | 1;
	bit_count++;
	ft_printf("Received SIGUSR1 (bit 1). Bits received: %d\n", bit_count);
	if (bit_count == 8)
	{
		if (current_char == '\0')
			ft_printf("\n[END OF MESSAGE]\n");
		else
			ft_printf("Character received: '%c' (ASCII: %d)\n", current_char,
				current_char);
		g_state = 0;
	}
	else
	{
		g_state = (bit_count << 8) | current_char;
	}
}

void	handle_sigusr2(int sig)
{
	int	bit_count;
	int	current_char;

	(void)sig;
	bit_count = (g_state >> 8) & 0x7;
	current_char = g_state & 0xFF;
	current_char = current_char << 1;
	bit_count++;
	ft_printf("Received SIGUSR2 (bit 0). Bits received: %d\n", bit_count);
	if (bit_count == 8)
	{
		if (current_char == '\0')
			ft_printf("\n[END OF MESSAGE]\n");
		else
			ft_printf("Character received: '%c' (ASCII: %d)\n", current_char,
				current_char);
		g_state = 0;
	}
	else
	{
		g_state = (bit_count << 8) | current_char;
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	(void)argv;
	
	if (argc != 1)
	{
		ft_printf("Error: Use ./server to execute the program\n");
		return (1);
	}
	g_state = 0;
	server_pid = getpid();
	ft_printf("Server PID: %d\n", server_pid);
	ft_printf("Server waiting for messages...\n");
	if (signal(SIGUSR1, handle_sigusr1) == SIG_ERR)
	{
		ft_printf("Error: Could not configure SIGUSR1\n");
		return (1);
	}
	if (signal(SIGUSR2, handle_sigusr2) == SIG_ERR)
	{
		ft_printf("Error: Could not configure SIGUSR2\n");
		return (1);
	}

	while (1)
	{
		pause();
	}

	return (0);
}