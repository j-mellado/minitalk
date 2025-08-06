/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 02:00:20 by jmellado          #+#    #+#             */
/*   Updated: 2025/08/06 02:00:21 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(pid_t pid, char c)
{
	int	bit;
	int	i;

	i = 7;
	while (i >= 0)
	{
		bit = (c >> i) & 1;
		if (bit == 1)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_printf("Error: Could not send SIGUSR1\n");
				exit(1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_printf("Error: Could not send SIGUSR2\n");
				exit(1);
			}
		}
		usleep(1000);
		i--;
	}
}

void	send_message(pid_t pid, char *message)
{
	int	i;

	i = 0;
	while (message[i])
	{
		ft_printf("Sending character: '%c'\n", message[i]);
		send_char(pid, message[i]);
		i++;
	}
	ft_printf("Sending end of message...\n");
	send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	pid_t pid;

	if (argc != 3)
	{
		ft_printf("Error: Use ./client <PID> <message>\n");
		return (1);
	}

	pid = atoi(argv[1]);

	if (pid <= 0)
	{
		ft_printf("Error: Invalid PID\n");
		return (1);
	}

	ft_printf("Client sending message to PID: %d\n", pid);
	ft_printf("Message: %s\n", argv[2]);

	send_message(pid, argv[2]);
	ft_printf("Message sent successfully.\n");

	return (0);
}