#include "swiot1l_mqtt.h"

#include "adxl355.h"
#include "common_data.h"
#include "iio_ad74413r.h"
#include "iio_adt75.h"
#include "iio_max14906.h"
#include "lwip_adin1110.h"
#include "lwip_socket.h"
#include "mqtt_client.h"
#include "mqtt_noos_support.h"
#include "no_os_delay.h"
#include "no_os_gpio.h"
#include "no_os_print_log.h"
#include "no_os_timer.h"
#include "no_os_util.h"

#include <errno.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>


static void message_handler(struct mqtt_message_data *msg) {
    msg->message.payload[msg->message.len] = 0;
    printf("Topic:%s -- Payload: %s\n", msg->topic, msg->message.payload);
}

int swiot1l_mqtt() {
	
    uint8_t adin1110_mac_address[6] = {0x00, 0x18, 0x80, 0x03, 0x25, 0x60};
    uint8_t send_buff[1000];  // FIXME:
    uint8_t read_buff[1000];  // FIXME:
    struct ad74413r_decimal val;
    char val_buff[50];  // FIXME:
    uint32_t msg_len;
    uint32_t adt75_val;
    int ret;

    struct ad74413r_desc *ad74413r;
    struct adxl355_dev *adxl355_desc;
    struct adt75_desc *adt75;

    struct lwip_network_param lwip_ip = {
        .platform_ops = &adin1110_lwip_ops,
        .mac_param = &adin1110_ip,
    };

    struct lwip_network_desc *lwip_desc;
    struct tcp_socket_desc *tcp_socket;
    struct no_os_timer_init_param adc_demo_tip = {
        .id = 0,
        .freq_hz = 32000,
        .ticks_count = 0,
        .platform_ops = &max_timer_ops,
        .extra = NULL,
    };

    struct no_os_timer_desc *timer;
    uint32_t connect_timeout = 5000;

    struct adxl355_frac_repr x[32] = {0};
    struct adxl355_frac_repr y[32] = {0};
    struct adxl355_frac_repr z[32] = {0};
    struct adxl355_frac_repr temp;
    union adxl355_sts_reg_flags status_flags = {0};
    uint8_t fifo_entries = 0;

    struct no_os_gpio_desc *ad74413r_ldac_gpio;
    struct no_os_gpio_desc *ad74413r_reset_gpio;  // FIXME:
    struct no_os_gpio_desc *ad74413r_irq_gpio;
    struct no_os_gpio_desc *max14906_en_gpio;
    struct no_os_gpio_desc *max14906_d1_gpio;
    struct no_os_gpio_desc *max14906_d2_gpio;
    struct no_os_gpio_desc *max14906_d3_gpio;
    struct no_os_gpio_desc *max14906_d4_gpio;
    struct no_os_gpio_desc *max14906_synch_gpio;
    struct no_os_gpio_desc *adin1110_swpd_gpio;
    struct no_os_gpio_desc *adin1110_tx2p4_gpio;
    struct no_os_gpio_desc *adin1110_mssel_gpio;
    struct no_os_gpio_desc *adin1110_cfg0_gpio;
    struct no_os_gpio_desc *adin1110_cfg1_gpio;
    struct no_os_gpio_desc *adin1110_int_gpio;
    struct no_os_gpio_desc *swiot_led1_gpio;
    struct no_os_gpio_desc *swiot_led2_gpio;

    no_os_gpio_get(&swiot_led1_gpio, &swiot_led1_ip);
    no_os_gpio_get(&swiot_led2_gpio, &swiot_led2_ip);
    no_os_gpio_get(&max14906_d1_gpio, &max14906_d1_ip);
    no_os_gpio_get(&max14906_d2_gpio, &max14906_d2_ip);
    no_os_gpio_get(&max14906_d3_gpio, &max14906_d3_ip);
    no_os_gpio_get(&max14906_d4_gpio, &max14906_d4_ip);
    no_os_gpio_direction_output(max14906_d1_gpio, 0);
    no_os_gpio_direction_output(max14906_d2_gpio, 0);
    no_os_gpio_direction_output(max14906_d3_gpio, 0);
    no_os_gpio_direction_output(max14906_d4_gpio, 0);
    no_os_gpio_get(&max14906_en_gpio, &max14906_en_ip);
    no_os_gpio_direction_output(max14906_en_gpio, 0);
    no_os_gpio_get(&adin1110_cfg0_gpio, &adin1110_cfg0_ip);
    no_os_gpio_get(&ad74413r_ldac_gpio, &ad74413r_ldac_ip);
    no_os_gpio_get(&ad74413r_reset_gpio, &ad74413r_reset_ip);
    no_os_gpio_get(&ad74413r_irq_gpio, &ad74413r_irq_ip);
    no_os_gpio_get(&max14906_synch_gpio, &max14906_synch_ip);
    no_os_gpio_get(&adin1110_swpd_gpio, &adin1110_swpd_ip);
    no_os_gpio_get(&adin1110_tx2p4_gpio, &adin1110_tx2p4_ip);
    no_os_gpio_get(&adin1110_mssel_gpio, &adin1110_mssel_ip);
    no_os_gpio_get(&adin1110_cfg1_gpio, &adin1110_cfg1_ip);
    no_os_gpio_get(&adin1110_int_gpio, &adin1110_int_ip);
    no_os_gpio_direction_output(ad74413r_ldac_gpio, 0);
    no_os_gpio_direction_output(ad74413r_reset_gpio, 1);
    no_os_gpio_direction_output(max14906_synch_gpio, 1);
    no_os_gpio_direction_output(adin1110_swpd_gpio, 1);
    no_os_gpio_direction_output(adin1110_tx2p4_gpio, 0);
    no_os_gpio_direction_output(adin1110_mssel_gpio, 1);
    no_os_gpio_direction_output(adin1110_cfg1_gpio, 1);
    no_os_gpio_direction_output(adin1110_cfg0_gpio, 1);
    no_os_gpio_direction_output(swiot_led1_gpio, 1);
    no_os_gpio_direction_output(swiot_led2_gpio, 1);
    no_os_gpio_direction_input(adin1110_int_gpio);
    no_os_gpio_direction_input(ad74413r_irq_gpio);

    const mxc_gpio_cfg_t gpio_cfg = {MXC_GPIO1, (MXC_GPIO_PIN_24), MXC_GPIO_FUNC_OUT,
                                     MXC_GPIO_PAD_NONE, MXC_GPIO_VSSEL_VDDIOH, MXC_GPIO_DRVSTR_3};
    MXC_GPIO_Init(1);
    MXC_GPIO_Config(&gpio_cfg);

    printf("Sensor Hub : Dell Lab IP\r\n");
    printf("MQTT Broker Address : 192.168.0.191\r\n");

    ret = ad74413r_init(&ad74413r, &ad74413r_ip);
    if (ret) {
        printf("Failed to initialise AD74413r - %d\r\n", ret);
        goto free_gpio;
    }

    printf("AD74413r sensor initialised - %d\r\n", ret);

    ret = adt75_init(&adt75, &adt75_ip);
    if (ret) {
        printf("Failed to initialise ADT75 - %d\r\n", ret);
        return ret;
    }

    printf("ADT75 Sensor Initialised - %d\r\n", ret);

    // Setup connection to the ADXL Part
    adxl355_ip.comm_init.spi_init = adxl355_spi_ip;

    ret = adxl355_init(&adxl355_desc, adxl355_ip);
    if (ret) {
        printf("Failed to initialise ADXL355 - %d\r\n", ret);
        return ret;
    }
    ret = adxl355_soft_reset(adxl355_desc);
    if (ret) {
        printf("Failed to soft reset ADXL355 - %d\r\n", ret);
        return ret;
    }
    ret = adxl355_set_odr_lpf(adxl355_desc, ADXL355_ODR_3_906HZ);
    if (ret) {
        printf("Failed to initialise ADXL355 filter - %d\r\n", ret);
        return ret;
    }
    ret = adxl355_set_op_mode(adxl355_desc, ADXL355_MEAS_TEMP_ON_DRDY_OFF);
    if (ret) {
        printf("Failed to set mode ADXL355 - %d\r\n", ret);
        return ret;
    }

    printf("ADXL355 Sensor Initialised\r\n");

    ad74413r_set_channel_function(ad74413r, 0, AD74413R_VOLTAGE_OUT);
    ad74413r_set_channel_function(ad74413r, 1, AD74413R_VOLTAGE_IN);
    ad74413r_set_channel_function(ad74413r, 2, AD74413R_VOLTAGE_IN);
    ad74413r_set_channel_function(ad74413r, 3, AD74413R_VOLTAGE_IN);

    // ad74413r_set_adc_rejection(ad74413r, 0, AD74413R_REJECTION_NONE);
    ad74413r_set_adc_rejection(ad74413r, 1, AD74413R_REJECTION_NONE);
    ad74413r_set_adc_rejection(ad74413r, 2, AD74413R_REJECTION_NONE);
    ad74413r_set_adc_rejection(ad74413r, 3, AD74413R_REJECTION_NONE);

    uint32_t uDacCode = 0;
    ret = ad74413r_dac_voltage_to_code(5000, &uDacCode);
    if (ret) {
        printf("Failed to setup supply for ADXL1002Z - %d\r\n", ret);
        return ret;
    }

    printf("Supply voltage set to DacCode\r\n");

    // ad74413r_set_channel_dac_code(ad74413r, 1, 1000);
    // ad74413r_set_channel_dac_code(ad74413r, 3, 3000);
    ad74413r_set_channel_dac_code(ad74413r, 0, uDacCode);

    memcpy(adin1110_ip.mac_address, adin1110_mac_address, NETIF_MAX_HWADDR_LEN);
    memcpy(lwip_ip.hwaddr, adin1110_mac_address, NETIF_MAX_HWADDR_LEN);

    ret = no_os_lwip_init(&lwip_desc, &lwip_ip);
    if (ret) {
        pr_err("LWIP init error: %d (%s)\r\n", ret, strerror(-ret));
        goto free_ad74413r;
    }

    printf("Initialised LWIP\r\n");

    struct tcp_socket_init_param tcp_ip = {
        .net = &lwip_desc->no_os_net,
        .max_buff_size = 0
    };

    ret = socket_init(&tcp_socket, &tcp_ip);
    if (ret) {
        pr_err("Socket init error: %d (%s)\r\n", ret, strerror(-ret));
        goto free_ad74413r;
    }

    printf("Initialised IP socket\r\n");

    /* The default settings are 192.168.97.1:1883 */
    struct socket_address ip_addr = {
        .addr = "192.168.0.191", 
        .port = 1883
    };

    struct mqtt_desc *mqtt;
    struct mqtt_init_param mqtt_init_param = {
        .timer_init_param = &adc_demo_tip,
        .sock = tcp_socket,
        .command_timeout_ms = 20000,
        .send_buff = send_buff,
        .read_buff = read_buff,
        .send_buff_size = 700,
        .read_buff_size = 700,
        .message_handler = message_handler
    };

    ret = mqtt_init(&mqtt, &mqtt_init_param);
    if (ret) {
        pr_err("MQTT init error: %d (%s)\r\n", ret, strerror(-ret));
        goto free_socket;
    }
    
    printf("Initialised MQTT\r\n");

    struct mqtt_connect_config conn_config = {
        .version = MQTT_VERSION_3_1_1,
        .keep_alive_ms = 72000, // 1000
        .client_name = (int8_t *)"swiot_10685237",
        .username = "mod_sense",
        .password = "WaterFabProj"
    };

    ret = socket_connect(tcp_socket, &ip_addr);
    if (ret) {
        pr_err("Couldn't connect to the remote TCP socket: %d (%s)\r\n", ret,
               strerror(-ret));
        goto free_mqtt;
    }
    
    printf("Connected to remote TCP socket\r\n");

    while (connect_timeout--) {
        no_os_lwip_step(tcp_socket->net->net, NULL);
        no_os_mdelay(1);
    }

    ret = mqtt_connect(mqtt, &conn_config, NULL);
    if (ret) {
        socket_disconnect(tcp_socket);
        pr_err("Couldn't connect to the MQTT broker: %d (%s)\r\n", ret, strerror(-ret));
        goto free_mqtt;
    }
    
    printf("Connected to MQTT broker\r\n");

    struct mqtt_message test_msg = {
        .qos = 0,
        .payload = val_buff,
        .retained = false
    };

    printf("Starting MQTT Publish Loop\r\n");

    // while (1) {
    //     no_os_lwip_step(tcp_socket->net->net, NULL);

    //     ad74413r_adc_get_value(ad74413r, 2, &val);
    //     memset(val_buff, 0, sizeof(val_buff));

    //     if (val.integer == 0 && val.decimal < 0)
    //         msg_len = snprintf(val_buff, sizeof(val_buff), "-%lld mV", val.integer,
    //                            abs(val.decimal));
    //     else
    //         msg_len = snprintf(val_buff, sizeof(val_buff), "%lld mV", val.integer,
    //                            abs(val.decimal));
    //     test_msg.len = msg_len;
    //     ret = mqtt_publish(mqtt, "ad74413r/channel0", &test_msg);
    //     if (ret) {
    //         pr_err("Error publishing MQTT message: %d (%s)\r\n", ret, strerror(-ret));
    //         goto free_mqtt;
    //     }

    //     ad74413r_adc_get_value(ad74413r, 1, &val);
    //     memset(val_buff, 0, sizeof(val_buff));
    //     if (val.integer == 0 && val.decimal < 0)
    //         msg_len = snprintf(val_buff, sizeof(val_buff), "-%lld mV",
    //                            val.integer / 1000,
    //                            abs(val.decimal));
    //     else
    //         msg_len = snprintf(val_buff, sizeof(val_buff), "%lld mV", val.integer,
    //                            abs(val.decimal));
    //     test_msg.len = msg_len;
    //     ret = mqtt_publish(mqtt, "ad74413r/channel1", &test_msg);
    //     if (ret) {
    //         pr_err("Error publishing MQTT message: %d (%s)\r\n", ret, strerror(-ret));
    //         goto free_mqtt;
    //     }

    //     ad74413r_adc_get_value(ad74413r, 2, &val);
    //     memset(val_buff, 0, sizeof(val_buff));
    //     msg_len = snprintf(val_buff, sizeof(val_buff), "%lld Ω",
    //                        val.integer / 1000,
    //                        abs(val.decimal));
    //     test_msg.len = msg_len;
    //     ret = mqtt_publish(mqtt, "ad74413r/channel2", &test_msg);
    //     if (ret) {
    //         pr_err("Error publishing MQTT message: %d (%s)\r\n", ret, strerror(-ret));
    //         goto free_mqtt;
    //     }

    //     ad74413r_adc_get_value(ad74413r, 3, &val);
    //     memset(val_buff, 0, sizeof(val_buff));

    //     if (val.integer == 0 && val.decimal < 0)
    //         msg_len = snprintf(val_buff, sizeof(val_buff),
    //                            "-%lld"
    //                            ".%02lu mA",
    //                            val.integer,
    //                            abs(val.decimal / 1000000));
    //     else
    //         msg_len = snprintf(val_buff, sizeof(val_buff),
    //                            "%lld"
    //                            ".%02lu mA",
    //                            val.integer,
    //                            abs(val.decimal / 1000000));
    //     test_msg.len = msg_len;
    //     ret = mqtt_publish(mqtt, "ad74413r/channel3", &test_msg);
    //     if (ret) {
    //     }

    //     no_os_mdelay(1000);
    // }

	while (1) {
		no_os_lwip_step(tcp_socket->net->net, NULL);

		ad74413r_adc_get_value(ad74413r, 2, &val);
		memset(val_buff, 0, sizeof(val_buff));

		if (val.integer == 0 && val.decimal < 0)
			msg_len = snprintf(val_buff, sizeof(val_buff), "-%lld", val.integer, abs(val.decimal));
		else
			msg_len = snprintf(val_buff, sizeof(val_buff), "%lld", val.integer, abs(val.decimal));

		test_msg.len = msg_len;
		ret = mqtt_publish(mqtt, "ad74413r/channel0", &test_msg);
		if (ret)
			return ret;

		ad74413r_adc_get_value(ad74413r, 1, &val);
		memset(val_buff, 0, sizeof(val_buff));

		if (val.integer == 0 && val.decimal < 0)
			msg_len = snprintf(val_buff, sizeof(val_buff), "-%lld", val.integer / 1000, abs(val.decimal));
		else
			msg_len = snprintf(val_buff, sizeof(val_buff), "%lld", val.integer, abs(val.decimal));

		test_msg.len = msg_len;
		ret = mqtt_publish(mqtt, "ad74413r/channel1", &test_msg);

		// Get Temperature  
		ret = adt75_get_single_temp(adt75, &adt75_val);
		memset(val_buff, 0, sizeof(val_buff));

		if (!ret) {
			msg_len = snprintf(val_buff, sizeof(val_buff), "%.03f", ((double)adt75_val / 1000));
			printf("Temperature reading: \e[96m%.03f\e[0m degrees C\r\n\r\n", ((double) adt75_val / 1000));
		} else {
			msg_len = snprintf(val_buff, sizeof(val_buff), "Null");
			printf("No Valid Data - %d\r\n", ret);
		}

		test_msg.len = msg_len;
		ret = mqtt_publish(mqtt, "adt75/temperature", &test_msg);

		// Experiment with ADXL355 Reading 
        printf("Single read (m/s^2):  \t\t");
		ret = adxl355_get_xyz(adxl355_desc, &x[0], &y[0], &z[0]);
		memset(val_buff, 0, sizeof(val_buff)); 

		if (ret) {
			msg_len = snprintf(val_buff, sizeof(val_buff), "Null");
			printf("Failed to read - %d\r\n", ret);
		} else {
			printf("x=\e[96m%d.%05u\t\e[0m", (int)x[0].integer, (abs)(x[0].fractional));
			printf("y=\e[96m%d.%05u\t\e[0m", (int)y[0].integer, (abs)(y[0].fractional));
			printf("z=\e[96m%d.%05u\r\n\r\n\e[0m", (int)z[0].integer, (abs)(z[0].fractional));
			msg_len = snprintf(val_buff, sizeof(val_buff), "%d.%09u, %d.%09u, %d.%09u", (int)x[0].integer, (abs)(x[0].fractional), (int)y[0].integer, (abs)(y[0].fractional), (int)z[0].integer, (abs)(z[0].fractional));
		}

		ret = adxl355_get_fifo_data(adxl355_desc, &fifo_entries, &x[0], &y[0], &z[0]);

		if (ret)
			printf("Failed to read - %d\r\n", ret);
		else {
			printf("Number of read entries from the FIFO   -> \e[96m%d\e[0m\r\n", fifo_entries);
			printf("Number of read data sets from the FIFO -> \e[96m%d\e[0m\r\n\r\n", fifo_entries / 3);
            
			for (uint8_t idx = 0; idx < 32; idx++) {
				if (idx < fifo_entries / 3) {
                    printf("Reading no. \e[93m%2d\e[0m (m/s^2):\t\t", (int) idx);
					printf("x=\e[96m%d.%05u\t\e[0m", (int) x[idx].integer, (abs) (x[idx].fractional));
					printf("y=\e[96m%d.%05u\t\e[0m", (int) y[idx].integer, (abs) (y[idx].fractional));
					printf("z=\e[96m%d.%05u\e[0m\r\n", (int) z[idx].integer, (abs) (z[idx].fractional));
				}
			}

            printf("\r\n");
		}

		ret = adxl355_get_sts_reg(adxl355_desc, &status_flags);

		if (ret)
			printf("Failed to read - %d\r\n\r\n", ret);
		else {
			printf("Activity flag   -> \e[93m%d\e[0m\r\n", (uint8_t) (status_flags.fields.Activity));
			printf("DATA_RDY flag   -> \e[93m%d\e[0m\r\n", (uint8_t) (status_flags.fields.DATA_RDY));
			printf("FIFO_FULL flag  -> \e[93m%d\e[0m\r\n", (uint8_t) (status_flags.fields.FIFO_FULL));
			printf("FIFO_OVR flag   -> \e[93m%d\e[0m\r\n", (uint8_t) (status_flags.fields.FIFO_OVR));
			printf("NVM_BUSY flag   -> \e[93m%d\e[0m\r\n\r\n", (uint8_t) (status_flags.fields.NVM_BUSY));
		}

		ret = adxl355_get_temp(adxl355_desc, &temp);
		if (ret)
			printf("Failed to read - %d\r\n", ret);
		else
			printf("Temperature: \e[93m%d.%09u\e[0m millidegrees C\r\n\r\n", (int) temp.integer, (abs) (temp.fractional));
	
		test_msg.len = msg_len;
		ret = mqtt_publish(mqtt, "adxl355/accel", &test_msg);

		no_os_mdelay(5000);
        printf("\e[H\e[2J");
	}

	while(1)
		no_os_lwip_step(tcp_socket->net->net, NULL);

    return 0;

free_mqtt:
    mqtt_remove(mqtt);
free_socket:
    socket_remove(tcp_socket);
free_lwip:
    no_os_lwip_remove(lwip_desc);
free_ad74413r:
    ad74413r_remove(ad74413r);
free_gpio:
    no_os_gpio_remove(adin1110_int_gpio);
    no_os_gpio_remove(adin1110_cfg1_gpio);
    no_os_gpio_remove(adin1110_mssel_gpio);
    no_os_gpio_remove(adin1110_tx2p4_gpio);
    no_os_gpio_remove(adin1110_swpd_gpio);
    no_os_gpio_remove(max14906_synch_gpio);
    no_os_gpio_remove(ad74413r_irq_gpio);
    no_os_gpio_remove(ad74413r_reset_gpio);
    no_os_gpio_remove(ad74413r_ldac_gpio);
    no_os_gpio_remove(adin1110_cfg0_gpio);
    no_os_gpio_remove(max14906_en_gpio);
    no_os_gpio_remove(max14906_d4_gpio);
    no_os_gpio_remove(max14906_d3_gpio);
    no_os_gpio_remove(max14906_d2_gpio);
    no_os_gpio_remove(max14906_d1_gpio);
    no_os_gpio_remove(swiot_led2_gpio);
    no_os_gpio_remove(swiot_led1_gpio);

    return ret;
}
