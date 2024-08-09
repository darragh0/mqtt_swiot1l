#include "parameters.h"
#include "common_data.h"
#include "swiot1l_mqtt.h"

#include <stdio.h>


int main() { 

	int ret;
	struct no_os_uart_desc *uart_desc;
	
	// Initialisation of UART required for successful `printf` calls 
	if ((ret = no_os_uart_init(&uart_desc, &uart_ip)))
		return ret;

	// Redirect stdio
	no_os_uart_stdio(uart_desc);

	printf("\e[H\e[2J\e[93mStarting MQTT Example Program:\e[0m\r\n\r\n");
	ret = swiot1l_mqtt();
	printf("\r\n\r\n\e[93mExit with code\e[0m -> %d\r\n", ret);

	return ret;
}
