#include "platform.h"

    
void main()
{
    uart_init();
    puts_unsafe("+---------------------+");
    puts_unsafe("|     Hello World     |");
    puts_unsafe("+---------------------+");
}