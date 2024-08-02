#include "common_data.h"


struct no_os_uart_init_param uart_ip = {
	.device_id = UART_DEVICE_ID,
	.irq_id = UART_IRQ_ID,
	.asynchronous_rx = true,
	.baud_rate = UART_BAUDRATE,
	.size = NO_OS_UART_CS_8,
	.parity = NO_OS_UART_PAR_NO,
	.platform_ops = &max_uart_ops,
	.stop = NO_OS_UART_STOP_1_BIT,
	.extra = UART_EXTRA,
};

const struct no_os_spi_init_param adin1110_spi_ip = {
	.device_id = 2,
	.max_speed_hz = 15000000,
	.bit_order = NO_OS_SPI_BIT_ORDER_MSB_FIRST,
	.mode = NO_OS_SPI_MODE_0,
	.platform_ops = &max_spi_ops,
	.chip_select = 0,
	.extra = SPI_EXTRA,
};

const struct no_os_i2c_init_param adt75_comm_param = {
	.device_id = 1,
	.max_speed_hz = 400000,
	.slave_address = ADT75_ADDR(0),
	.platform_ops = &max_i2c_ops,
	.extra = I2C_EXTRA,
};

struct adt75_init_param adt75_ip = {
	.comm_param = adt75_comm_param,
};

const struct no_os_gpio_init_param adin1110_int_ip = {
	.port = 2,
	.number = 6,
	.pull = NO_OS_PULL_UP,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

const struct no_os_gpio_init_param adin1110_rst_gpio_ip = {
	.port = 2,
	.number = 1,
	.pull = NO_OS_PULL_UP,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

const struct no_os_gpio_init_param tx_perf_gpio_ip = {
	.port = 2,
	.number = 16,
	.pull = NO_OS_PULL_UP,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

struct no_os_gpio_init_param ad74413r_reset_ip = {
	.port = 0,
	.number = 26,
	.pull = NO_OS_PULL_UP,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

const struct no_os_gpio_init_param ad74413r_ldac_ip = {
	.port = 0,
	.number = 27,
	.pull = NO_OS_PULL_NONE,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

const struct no_os_gpio_init_param ad74413r_irq_ip = {
	.port = 1,
	.number = 22,
	.pull = NO_OS_PULL_UP,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

const struct no_os_gpio_init_param max14906_en_ip = {
	.port = 1,
	.number = 25,
	.pull = NO_OS_PULL_NONE,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

const struct no_os_gpio_init_param max14906_d1_ip = {
	.port = 3,
	.number = 7,
	.pull = NO_OS_PULL_NONE,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

const struct no_os_gpio_init_param max14906_d2_ip = {
	.port = 3,
	.number = 4,
	.pull = NO_OS_PULL_NONE,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

const struct no_os_gpio_init_param max14906_d3_ip = {
	.port = 3,
	.number = 8,
	.pull = NO_OS_PULL_NONE,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

const struct no_os_gpio_init_param max14906_d4_ip = {
	.port = 3,
	.number = 5,
	.pull = NO_OS_PULL_NONE,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

const struct no_os_gpio_init_param max14906_synch_ip = {
	.port = 3,
	.number = 6,
	.pull = NO_OS_PULL_NONE,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

const struct no_os_gpio_init_param adin1110_swpd_ip = {
	.port = 2,
	.number = 25,
	.pull = NO_OS_PULL_UP,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

const struct no_os_gpio_init_param adin1110_tx2p4_ip = {
	.port = 2,
	.number = 10,
	.pull = NO_OS_PULL_DOWN,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

const struct no_os_gpio_init_param adin1110_mssel_ip = {
	.port = 2,
	.number = 9,
	.pull = NO_OS_PULL_NONE,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

const struct no_os_gpio_init_param adin1110_cfg0_ip = {
	.port = 2,
	.number = 3,
	.pull = NO_OS_PULL_NONE,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

const struct no_os_gpio_init_param adin1110_cfg1_ip = {
	.port = 2,
	.number = 0,
	.pull = NO_OS_PULL_UP,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

const struct no_os_gpio_init_param swiot_led1_ip = {
	.port = 2,
	.number = 15,
	.pull = NO_OS_PULL_UP,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

const struct no_os_gpio_init_param swiot_led2_ip = {
	.port = 2,
	.number = 14,
	.pull = NO_OS_PULL_UP,
	.platform_ops = &max_gpio_ops,
	.extra = GPIO_EXTRA,
};

struct adin1110_init_param adin1110_ip = {
	.chip_type = ADIN1110,
	.comm_param = adin1110_spi_ip,
	.reset_param = adin1110_rst_gpio_ip,
	.append_crc = false,
};

const struct no_os_platform_spi_delays ad74413r_spi_delays = {
	.cs_delay_first = 1000,
	.cs_delay_last = 0,
};

const struct no_os_spi_init_param ad74413r_spi_ip = {
	.device_id = 3,
	.max_speed_hz = 1000000,
	.bit_order = NO_OS_SPI_BIT_ORDER_MSB_FIRST,
	.mode = NO_OS_SPI_MODE_2,
	.platform_ops = &max_spi_ops,
	.chip_select = 3,
	.platform_delays = ad74413r_spi_delays,
	.extra = SPI_EXTRA,
};

struct no_os_spi_init_param max14906_spi_ip = {
	.device_id = 1,
	.max_speed_hz = 10000000,
	.bit_order = NO_OS_SPI_BIT_ORDER_MSB_FIRST,
	.mode = NO_OS_SPI_MODE_0,
	.platform_ops = &max_spi_ops,
	.chip_select = 3,
	.extra = SPI_EXTRA,
};

const struct no_os_spi_init_param pmod_spi_ip = {
	.device_id = 1,
	.max_speed_hz = 10000000,
	.bit_order = NO_OS_SPI_BIT_ORDER_MSB_FIRST,
	.mode = NO_OS_SPI_MODE_0,
	.platform_ops = &max_spi_ops,
	.chip_select = 2,
	.extra = SPI_EXTRA,
};

const struct no_os_gpio_init_param psu_gpio_ip = {
	.port = 3,
	.number = 9,
	.platform_ops = &max_gpio_ops,
	.pull = NO_OS_PULL_UP,
	.extra = GPIO_EXTRA
};

struct max149x6_init_param max14906_ip = {
	.chip_address = 0,
	.comm_param = &max14906_spi_ip,
	.crc_en = true,
};

const struct no_os_irq_init_param ad74413r_nvic_ip = {
	.irq_ctrl_id = 0,
	.platform_ops = &max_irq_ops,
	.extra = NULL,
};

struct ad74413r_init_param ad74413r_ip = {
	.chip_id = AD74413R,
	.comm_param = ad74413r_spi_ip,
};

// Adding in ADXL355 Support 

struct no_os_uart_init_param adxl355_uart_ip = {
	.device_id = UART_DEVICE_ID,
	.irq_id = UART_IRQ_ID,
	.asynchronous_rx = true,
	.baud_rate = UART_BAUDRATE,
	.size = NO_OS_UART_CS_8,
	.parity = NO_OS_UART_PAR_NO,
	.stop = NO_OS_UART_STOP_1_BIT,
	.extra = UART_EXTRA,
	.platform_ops = UART_OPS,
};

struct no_os_spi_init_param adxl355_spi_ip = {
	.device_id = SPI1_DEVICE_ID,
	.max_speed_hz = SPI1_BAUDRATE,
	.bit_order = NO_OS_SPI_BIT_ORDER_MSB_FIRST,
	.mode = NO_OS_SPI_MODE_0,
	.platform_ops = SPI1_OPS,
	.chip_select = SPI1_CS,
	.extra = SPI1_EXTRA,
};

struct adxl355_init_param adxl355_ip = {
	.comm_type = ADXL355_SPI_COMM,
	.dev_type = ID_ADXL355,
};
