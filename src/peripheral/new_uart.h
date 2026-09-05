typedef struct {
    uart_channel_t channel;
    uart_parity_t parity;
    uart_datalength_t data_length;
    uint32_t clk_freq;
    uint32_t baud_rate;
} uart_config_t;