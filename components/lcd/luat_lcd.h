
#ifndef LUAT_LCD
#define LUAT_LCD

#include "luat_base.h"
#include "luat_spi.h"
#include "u8g2.h"

#define LCD_WHITE            0xFFFF
#define LCD_BLACK            0x0000

#ifndef LUAT_LCD_COLOR_DEPTH
#define LUAT_LCD_COLOR_DEPTH 16
#endif

#if (LUAT_LCD_COLOR_DEPTH == 32)
#define luat_color_t uint32_t
#elif (LUAT_LCD_COLOR_DEPTH == 16)
#define luat_color_t uint16_t
#elif (LUAT_LCD_COLOR_DEPTH == 8)
#define luat_color_t uint8_t
#else
#error "no supprt color depth"
#endif

#define LUAT_LCD_SPI_DEVICE 255

struct luat_lcd_opts;

typedef struct luat_lcd_conf {
    uint8_t port;
    uint8_t pin_dc;
    uint8_t pin_pwr;
    uint8_t pin_rst;

    int16_t w;
    int16_t h;
    uint32_t buffer_size;
    uint32_t dc_delay_us;
    uint8_t xoffset;//偏移
    uint8_t yoffset;//偏移
    uint8_t auto_flush;
    uint8_t direction;//方向
    u8g2_t luat_lcd_u8g2 ;
    const struct luat_lcd_opts* opts;
    luat_spi_device_t* lcd_spi_device;
    int lcd_spi_ref;
    void* userdata;

    // buff 相关
    luat_color_t* buff;
    int buff_ref;
    int16_t flush_y_min;
    int16_t flush_y_max;
    uint8_t is_init_done;
} luat_lcd_conf_t;

typedef struct luat_lcd_opts {
    const char* name;
    int (*init)(luat_lcd_conf_t* conf);
    int (*write_cmd)(luat_lcd_conf_t* conf,const uint8_t cmd);
    int (*write_data)(luat_lcd_conf_t* conf,const uint8_t data);
} luat_lcd_opts_t;

int lcd_write_cmd(luat_lcd_conf_t* conf,const uint8_t cmd);
int lcd_write_data(luat_lcd_conf_t* conf,const uint8_t data);

luat_lcd_conf_t* luat_lcd_get_default(void);
const char* luat_lcd_name(luat_lcd_conf_t* conf);
int luat_lcd_init(luat_lcd_conf_t* conf);
int luat_lcd_close(luat_lcd_conf_t* conf);
int luat_lcd_display_on(luat_lcd_conf_t* conf);
int luat_lcd_display_off(luat_lcd_conf_t* conf);
int luat_lcd_sleep(luat_lcd_conf_t* conf);
int luat_lcd_wakeup(luat_lcd_conf_t* conf);
int luat_lcd_inv_off(luat_lcd_conf_t* conf);
int luat_lcd_inv_on(luat_lcd_conf_t* conf);
int luat_lcd_set_address(luat_lcd_conf_t* conf, int16_t x1, int16_t y1, int16_t x2, int16_t y2);
int luat_lcd_set_color(luat_color_t back, luat_color_t fore);
luat_color_t color_swap(luat_color_t color);
int luat_lcd_draw(luat_lcd_conf_t* conf, int16_t x1, int16_t y1, int16_t x2, int16_t y2, luat_color_t* color);
int luat_lcd_flush(luat_lcd_conf_t* conf);
int luat_lcd_draw_no_block(luat_lcd_conf_t* conf, int16_t x1, int16_t y1, int16_t x2, int16_t y2, luat_color_t* color, uint8_t last_flush);
int luat_lcd_clear(luat_lcd_conf_t* conf, luat_color_t color);
int luat_lcd_draw_fill(luat_lcd_conf_t* conf, int16_t x1,int16_t y1,int16_t x2,int16_t y2,luat_color_t color);
int luat_lcd_draw_point(luat_lcd_conf_t* conf, int16_t x, int16_t y, luat_color_t color);
int luat_lcd_draw_line(luat_lcd_conf_t* conf, int16_t x1, int16_t y1, int16_t x2, int16_t y2, luat_color_t color);
int luat_lcd_draw_vline(luat_lcd_conf_t* conf, int16_t x, int16_t y,int16_t h, luat_color_t color);
int luat_lcd_draw_hline(luat_lcd_conf_t* conf, int16_t x, int16_t y,int16_t h, luat_color_t color);
int luat_lcd_draw_rectangle(luat_lcd_conf_t* conf, int16_t x1, int16_t y1, int16_t x2, int16_t y2, luat_color_t color);
int luat_lcd_draw_circle(luat_lcd_conf_t* conf, int16_t x0, int16_t y0, uint8_t r, luat_color_t color);

void luat_lcd_execute_cmds(luat_lcd_conf_t* conf, uint32_t* cmds, uint32_t count);

typedef struct luat_lcd_custom {
    size_t init_cmd_count;
    uint32_t *initcmd; // 实际命令长度与init_cmd_count相同
}luat_lcd_custom_t;

void luat_lcd_service_init(uint32_t pro);
void luat_lcd_service_run(void *CB, void *data, uint32_t param, uint32_t timeout);
void luat_lcd_service_draw(void *data);
uint32_t luat_lcd_service_cache_len(void);
#endif

