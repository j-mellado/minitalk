#include "minitalk.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

void send_char(pid_t pid, char c)
{
    int bit;
    int i;

    i = 7;  // Empezar desde el bit más significativo
    while (i >= 0)
    {
        bit = (c >> i) & 1;  // Extraer el bit en posición i
        
        if (bit == 1)
            kill(pid, SIGUSR1);  // Enviar SIGUSR1 para bit 1
        else
            kill(pid, SIGUSR2);  // Enviar SIGUSR2 para bit 0
            
        usleep(1000);  // Pausa de 1ms entre señales
        i--;
    }
}

void send_message(pid_t pid, char *message)
{
    int i;

    i = 0;
    while (message[i])
    {
        ft_printf("Enviando carácter: '%c'\n", message[i]);
        send_char(pid, message[i]);
        i++;
    }
    
    // Enviar carácter nulo para marcar fin del mensaje
    ft_printf("Enviando fin de mensaje...\n");
    send_char(pid, '\0');
}

int main(int argc, char** argv)
{
    pid_t pid;
    
    if (argc != 3)
    {
        ft_printf("Error: Use ./client <PID> <mensaje>\n");
        return 1;
    }

    pid = atoi(argv[1]);
    ft_printf("Cliente enviando mensaje al PID: %d\n", pid);
    ft_printf("Mensaje: %s\n", argv[2]);
    
    send_message(pid, argv[2]);
    ft_printf("Mensaje enviado completamente.\n");
    
    return 0;
}