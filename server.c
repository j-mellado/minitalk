#include "minitalk.h"

// Variable global para contar bits recibidos
int bit_count = 0;
char current_char = 0;

// Manejador para SIGUSR1 (representa bit 1)
void handle_sigusr1(int sig)
{
    (void)sig;  // Evitar warning de parámetro no usado
    
    current_char = (current_char << 1) | 1;  // Desplazar y agregar bit 1
    bit_count++;
    
    ft_printf("Recibido SIGUSR1 (bit 1). Bits recibidos: %d\n", bit_count);
    
    // Si completamos 8 bits, mostramos el carácter
    if (bit_count == 8)
    {
        if (current_char == '\0')
            ft_printf("\n[FIN DEL MENSAJE]\n");
        else
            ft_printf("Carácter recibido: '%c' (ASCII: %d)\n", current_char, current_char);
        
        // Reiniciar para el siguiente carácter
        bit_count = 0;
        current_char = 0;
    }
}

// Manejador para SIGUSR2 (representa bit 0)
void handle_sigusr2(int sig)
{
    (void)sig;  // Evitar warning de parámetro no usado
    
    current_char = current_char << 1;  // Desplazar y agregar bit 0
    bit_count++;
    
    ft_printf("Recibido SIGUSR2 (bit 0). Bits recibidos: %d\n", bit_count);
    
    // Si completamos 8 bits, mostramos el carácter
    if (bit_count == 8)
    {
        if (current_char == '\0')
            ft_printf("\n[FIN DEL MENSAJE]\n");
        else
            ft_printf("Carácter recibido: '%c' (ASCII: %d)\n", current_char, current_char);
        
        // Reiniciar para el siguiente carácter
        bit_count = 0;
        current_char = 0;
    }
}

int main (int argc, char** argv)
{
    (void)argv;
    
    if (argc != 1)
    {
        ft_printf("Error: Use ./server para ejecutar el programa\n");
        return (1);
    }

    pid_t server_pid;

    server_pid = getpid();
    ft_printf("El PID de este servidor es: %d\n", server_pid);
    ft_printf("Servidor esperando mensajes...\n");
    
    // Configurar los manejadores de señales
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGUSR2, handle_sigusr2);

    while (1)
    {
        pause(); 
    }

    return (0);
}