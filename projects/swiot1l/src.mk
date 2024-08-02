
LIBRARIES += lwip mqtt
TINYIIOD=y
IIOD=y

INCS += $(PLATFORM_DRIVERS)/maxim_gpio.h                                                    \
        $(PLATFORM_DRIVERS)/maxim_spi.h                                                     \
        $(PLATFORM_DRIVERS)/maxim_gpio_irq.h                                                \
        $(PLATFORM_DRIVERS)/maxim_irq.h                                                     \
        $(PLATFORM_DRIVERS)/maxim_i2c.h                                                     \
		$(PLATFORM_DRIVERS)/maxim_trng.h													\
        $(PLATFORM_DRIVERS)/maxim_timer.h                                                   \
        $(PLATFORM_DRIVERS)/maxim_uart.h                                                    \
        $(PLATFORM_DRIVERS)/maxim_uart_stdio.h                                              \
        $(PLATFORM_DRIVERS)/../common/maxim_dma.h 

SRCS += $(PLATFORM_DRIVERS)/maxim_delay.c                                                   \
        $(PLATFORM_DRIVERS)/maxim_gpio.c                                                    \
        $(PLATFORM_DRIVERS)/maxim_spi.c                                                     \
        $(PLATFORM_DRIVERS)/maxim_init.c                                                    \
		$(PLATFORM_DRIVERS)/maxim_trng.c 													\
        $(PLATFORM_DRIVERS)/maxim_i2c.c                                                     \
        $(PLATFORM_DRIVERS)/maxim_timer.c                                                   \
        $(PLATFORM_DRIVERS)/maxim_gpio_irq.c                                                \
        $(PLATFORM_DRIVERS)/maxim_irq.c                                                     \
        $(PLATFORM_DRIVERS)/maxim_uart.c                                                    \
        $(PLATFORM_DRIVERS)/maxim_uart_stdio.c                                              \
        $(PLATFORM_DRIVERS)/../common/maxim_dma.c                                           
	
INCS += $(INCLUDE)/no_os_delay.h      					                                    \
		$(INCLUDE)/no_os_error.h      				                                        \
		$(INCLUDE)/no_os_gpio.h       					                                    \
		$(INCLUDE)/no_os_print_log.h  					                                    \
		$(INCLUDE)/no_os_spi.h        					                                    \
		$(INCLUDE)/no_os_irq.h        					                                    \
		$(INCLUDE)/no_os_init.h       					                                    \
		$(INCLUDE)/no_os_trng.h																\
		$(INCLUDE)/no_os_list.h       				                                        \
		$(INCLUDE)/no_os_mutex.h                                                            \
		$(INCLUDE)/no_os_crc8.h       					                                    \
		$(INCLUDE)/no_os_uart.h       					                                    \
		$(INCLUDE)/no_os_mutex.h      				                                        \
		$(INCLUDE)/no_os_i2c.h        					                                    \
		$(INCLUDE)/no_os_mdio.h      					                                    \
		$(INCLUDE)/no_os_timer.h      				                                        \
		$(INCLUDE)/no_os_lf256fifo.h  				                                        \
		$(INCLUDE)/no_os_util.h                                                             \
		$(INCLUDE)/no_os_units.h      				                                    	\
		$(INCLUDE)/no_os_alloc.h															\
		$(INCLUDE)/no_os_dma.h

SRCS += $(DRIVERS)/api/no_os_gpio.c                                                         \
		$(NO-OS)/util/no_os_lf256fifo.c                                                     \
		$(DRIVERS)/api/no_os_irq.c                                                          \
		$(DRIVERS)/api/no_os_spi.c                                                          \
		$(DRIVERS)/api/no_os_uart.c                                                         \
		$(DRIVERS)/api/no_os_i2c.c                                                          \
		$(DRIVERS)/api/no_os_timer.c                                                        \
		$(DRIVERS)/api/no_os_mdio.c                                                         \
		$(DRIVERS)/api/no_os_dma.c                                                          \
		$(NO-OS)/util/no_os_list.c                                                          \
		$(NO-OS)/util/no_os_crc8.c                                                          \
		$(NO-OS)/util/no_os_util.c                                                          \
		$(NO-OS)/util/no_os_mutex.c                                                         \
		$(NO-OS)/util/no_os_alloc.c                                                         

INCS += $(DRIVERS)/digital-io/max149x6/max149x6-base.h	                                    \
		$(DRIVERS)/digital-io/max149x6/max14906.h                                           \
		$(DRIVERS)/digital-io/max149x6/iio_max14906.h                                       \
		$(DRIVERS)/adc-dac/ad74413r/ad74413r.h                                              \
		$(DRIVERS)/adc-dac/ad74413r/iio_ad74413r.h                                          \
		$(DRIVERS)/temperature/adt75/adt75.h                                                \
		$(DRIVERS)/temperature/adt75/iio_adt75.h                                            \
		$(DRIVERS)/accel/adxl355/adxl355.h                                                  \
		$(DRIVERS)/net/adin1110/adin1110.h

SRCS += $(DRIVERS)/digital-io/max149x6/max149x6-base.c	                                    \
		$(DRIVERS)/digital-io/max149x6/max14906.c                                           \
		$(DRIVERS)/digital-io/max149x6/iio_max14906.c                                       \
		$(DRIVERS)/adc-dac/ad74413r/ad74413r.c                                              \
		$(DRIVERS)/adc-dac/ad74413r/iio_ad74413r.c                                          \
		$(DRIVERS)/temperature/adt75/adt75.c                                                \
		$(DRIVERS)/temperature/adt75/iio_adt75.c                                            \
		$(DRIVERS)/accel/adxl355/adxl355.c                                                  \
		$(DRIVERS)/net/adin1110/adin1110.c

INCS += $(PROJECT)/src/platform/parameters.h                                                \
		$(PROJECT)/src/common/common_data.h                                                 \
		$(PROJECT)/src/swiot1l_mqtt.h                                                       \
		$(PROJECT)/src/common/swiot.h
 
SRCS += $(PROJECT)/src/platform/parameters.c                                                \
		$(PROJECT)/src/platform/main.c                                                      \
		$(PROJECT)/src/common/common_data.c                                                 \
		$(PROJECT)/src/swiot1l_mqtt.c                                                       \
		$(PROJECT)/src/common/swiot.c                                                    

INCS += $(NO-OS)/network/tcp_socket.h                                                       \
		$(NO-OS)/network/noos_mbedtls_config.h                                              \
		$(NO-OS)/network/network_interface.h                                                \
		$(NO-OS)/network/lwip_raw_socket/netdevs/adin1110/lwip_adin1110.h                   \

INCS += $(PLATFORM_DRIVERS)/maxim_gpio.h                                                    \
		$(NO-OS)/iio/iio_trigger.h														\

SRCS += $(NO-OS)/network/tcp_socket.c                                                       \
		$(NO-OS)/network/lwip_raw_socket/netdevs/adin1110/lwip_adin1110.c                   \
		$(NO-OS)/iio/iio_trigger.c

SRC_DIRS +=	$(NO-OS)/iio/iio_app
