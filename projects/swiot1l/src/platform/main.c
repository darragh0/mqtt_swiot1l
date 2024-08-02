#include "parameters.h"
#include "common_data.h"
#include "swiot1l_mqtt.h"

#include <stdio.h>


int main() { 

	int ret;
	struct no_os_uart_desc *uart_desc;
	
	if ((ret = no_os_uart_init(&uart_desc, &uart_ip)))
		return ret;

	no_os_uart_stdio(uart_desc);
	printf("\033[93mStarting MQTT Example Program:\033[0m\r\n\r\n");
	ret = swiot1l_mqtt();
	printf("\r\n\r\n\033[93mExit with code\033[0m -> %d\r\n", ret);

	return ret;
}
