/******************************************************************************/
/*                             PROJECT PINOUT                                 */
/******************************************************************************/
/*                             ATMega328P
 *                                ______
 *            RESET/PCINT14/PC6 =|01* 28|= PC5/PCINT13/SCL/ADC5
 *               RX/PCINT16/PD0 =|02  27|= PC4/PCINT12/SDA/ADC4
 *               TX/PCINT17/PD1 =|03  26|= PC3/PCINT11/ADC3
 *             INT0/PCINT18/PD2 =|04  25|= PC2/PCINT10/ADC2
 *                  PCINT19/PD3 =|05  24|= PC1/PCINT9/ADC1
 *                  PCINT20/PD4 =|06  23|= PC0/PCINT8/ADC0
 *                          Vcc =|07  22|= GND
 *                          GND =|08  21|= Aref
 *             XTAL1/PCINT6/PB6 =|09  20|= AVcc
 *             XTAL2/PCINT7/PB7 =|10  19|= PB5/PCINT5/SCK
 *             OC0B/PCINT21/PD5 =|11  18|= PB4/PCINT4/MISO
 *        OC0A/AIN0/PCINT22/PD6 =|12  17|= PB3/PCINT3/MOSI/OC2A/OC2
 *             AIN1/PCINT23/PD7 =|13  16|= PB2/PCINT2/SS/OC1B
 *                   PCINT0/PB0 =|14  15|= PB1/PCINT1/OC1A
 *                                ------
 * 
 *                                ______
 *                              =|01* 28|= 
 *                           RX =|02  27|= PIN_RST
 *                           TX =|03  26|= PIN_CS
 *                       PIN_02 =|04  25|= PIN_RS
 *                       PIN_03 =|05  24|= PIN_WR
 *                       PIN_04 =|06  23|= PIN_RD
 *                          Vcc =|07  22|= GND
 *                          GND =|08  21|= Aref
 *                              =|09  20|= 
 *                              =|10  19|= 
 *                       PIN_05 =|11  18|= 
 *                       PIN_06 =|12  17|= 
 *                       PIN_07 =|13  16|= DIAGNOSTIC OUTPUT PIN
 *                       PIN_00 =|14  15|= PIN_01
 *                                ------
 * 
 * 
 */



/******************************************************************************/
/*                                   DEFS                                     */
/******************************************************************************/

#define F_CPU           8000000
#define MEMSIZE         2048
#define TRUE            1
#define FALSE           0
#define ON              1
#define OFF             0
#define HIGH            1
#define LOW             0
#define NOP             asm("nop")
#define TX_BUF_LEN      8
#define RX_BUF_LEN      8

//---MACROS
#define CMD_EQ(A)           strcmp(A, rxbuf) == 0
#define CMD_EQN(A,N)        strncmp(A, rxbuf, N) == 0
#define ITOA(A)             itoa(A, txbuf, 10)
#define ITOA2(A)            itoa(A, txbuf, 2)
#define ITOA16(A)           itoa(A, txbuf, 16)

#define _readpin(a,b)       (a & b)
#define _setpin(a,b)        a |= b
#define _clearpin(a,b)      a &= ~(b)
#define _togglepin(a,b)     a ^= ba

//diagnostix
//#define PIN_DIAG    0x04
//#define PORT_DIAG   PORTB
#define PIN_POWER    0x04
#define PORT_POWER   PORTB

//
#define CHAR_COLS               0x08
#define CHAR_ROWS               0x06
#define CHAR_BIN_WITDH          0x28//40 pixels
#define CHAR_BIN_HEIGHT         0x50//80 pixels
#define CHAR_BBOX_WITDH         0x28//40 pixels
#define CHAR_BBOX_HEIGHT        0x50//80 pixels



/******************************************************************************/
/*                                 INCLUDES                                   */
/******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "math.h"
//#include <avr/eeprom.h>
//#include <avr/pgmspace.h>
#include <util/delay.h>
//#include <util/setbaud.h>
//#include <util/twi.h>
#include <stdlib.h>
//#include <string.h>
#include "ili9481_opcodes.h"
#include "font1.h"

/******************************************************************************/
/*                                VARIABLES                                   */

/******************************************************************************/

uint32_t timer_counter;
uint8_t status_byte = 0xff;

/******************************************************************************/
/*                             STRUCTS AND ENUMS                              */

/******************************************************************************/


/******************************************************************************/
/*                            FUNCTION DECLARATIONS                           */
/******************************************************************************/

int main(void);
static void init(void);
void mainloop(void);
//
void init_tftlcd(void);
void write_command(uint8_t cmd);
void write_command(uint8_t cmd, uint8_t dat);
void write_command(uint8_t cmd, uint8_t dat[], uint8_t size);
void write_data(uint8_t dat[], uint8_t size);
void put_bus_8bit_LSB(uint8_t byte);
void put_bus_8bit_MSB(uint8_t byte);
uint8_t get_bus_byte(void);
uint16_t rgb_to_565(uint8_t r, uint8_t g, uint8_t b);
//general 
void clear_screen(void);
void fill_rect(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t colour);
void draw_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t colour);
void plot_pixel(uint16_t x, uint16_t y, uint16_t colour);
void plot_2D_graph(void);
void draw_v_line(uint16_t x, uint16_t y, uint16_t len, uint16_t colour);
void draw_h_line(uint16_t x, uint16_t y, uint16_t len, uint16_t colour);
//usart
//i2c
//ADC
//eeprom
//timer
ISR(TIMER0_OVF_vect);
//util
uint8_t reverse_bits(uint8_t b);
void delay_n_us(uint16_t n);
void delay_n_ms(uint16_t n);
int available_sram(void);

/******************************************************************************
 *                                FUNCTIONS                                   *
 ******************************************************************************/

int main(void)
{
    init();
    _clearpin(PORT_POWER, PIN_POWER);
    _delay_ms(1000);
    _setpin(PORT_POWER, PIN_POWER);
    _delay_ms(500);
    init_tftlcd();
    mainloop();
    return 0;
}

/*******************************************************************************
 *                                                                        INIT*/

static void init(void)
{

    //=======================================================================I/O
    //Direction registers port c 1=output 0=input
    /*If DDxn is written logic one, Pxn is configured as an output pin. 
     * If DDxn is written logic zero, Pxn is configured as an input pin.
     * If PORTxn is written logic one AND the pin is configured as an input pin (0), 
     * the pull-up resistor is activated.
     */
    DDRB |= PIN_00 | PIN_01 | PIN_POWER;
    PORTB |= 0xff;

    DDRC |= PIN_RST | PIN_CS | PIN_CMD | PIN_WR | PIN_RD;
    PORTC |= 0xff;

    DDRD |= PIN_02 | PIN_03 | PIN_04 | PIN_05 | PIN_06 | PIN_07;
    PORTD |= 0xff;

    //=======================================================================ADC

    //======================================================================UART

    //====================================================================TIMER0
    TCNT0 = 0x00;
    TCCR0B |= _BV(CS00); // | (1 << CS02);//prescaler
    TIMSK0 |= _BV(TOV0); //timer 0 overflow interrupt enable

    //=======================================================================I2C

    //================================================================INTERRUPTS
    sei();
}

/******************************************************************************
 *                                                                    MAINLOOP*/
void mainloop(void)
{
    uint16_t colr = rgb_to_565(12, 63, 0);
    uint16_t black = rgb_to_565(0, 0, 0);
    uint16_t size = 3;
    uint16_t xoffset=25, yoffset = 65, step=70;

    print_str("ROOIVALK",size,xoffset,yoffset,colr);
    yoffset+=step;
    print_str("COCKPIT",size,xoffset,yoffset,colr);
    yoffset+=step;
    print_str("SIMULATOR+",size,xoffset,yoffset,colr);
    yoffset+=step;
    print_str("133.0000",size,xoffset,yoffset,colr);
    yoffset+=step;
    print_str("00-00311",size,xoffset,yoffset,colr);
    yoffset+=step;
    print_str("132.2000",size,xoffset,yoffset,colr);
    

    while (TRUE)
    {
    }
    return;
}

/******************************************************************************
 *                                                                ili interface*/

void init_tftlcd()
{
    //init lcd
    _RESET;
    //---power setting 0xD0,3
    uint8_t pwr[] = {0x07, 0x42, 0x18};
    write_command(OPC_POWER_SETTING, pwr, 3);
    //---vcom 0xD1,3
    uint8_t vcom[] = {0x00, 0x07, 0x10};
    write_command(OPC_VCOM_CTRL, vcom, 3);
    //---power mode 0xD2,2
    uint8_t pwrset[] = {0x01, 0x02};
    write_command(OPC_POWER_SETTING_NORMAL_MODE, pwrset, 2);
    //---panel driving 0xC0,5
    uint8_t pnldrv[] = {0x10, 0x3B, 0x00, 0x02, 0x11};
    write_command(OPC_PANEL_DRIVING_SETTING, pnldrv, 5);
    //---frame rate 0xC5,1
    write_command(OPC_FRAME_RATE_INVERT_CTRL, 0x03);
    //---gamma 0xC8,12
    uint8_t gamma[] = {0x00, 0x32, 0x36, 0x45, 0x06, 0x16, 0x37, 0x75, 0x77, 0x54, 0x0C, 0x00};
    write_command(OPC_GAMMA_SETTING, gamma, 12);
    //---addr mode 0x36,1
    write_command(OPC_WRITE_ADDR_MODE, 0x0A);
    //---pixel format 0x3A,1
    write_command(OPC_WRITE_PIXEL_FMT, PIXEL_FMT_16BITS);
    //--------------------------------------------new start
    //---func ctrl 0xB6,3
    uint8_t dispfunc[] = {0x00, 0x42, 0x3B};
    //write_command(OPC_DISP_FUNCTION_CONTROL, dispfunc, 3);
    //---scoll area 0x33,6
    uint8_t scrlar[] = {0x00, 0x00, 0x01, 0x0E1, 0x00, 0x00};
    //write_command(OPC_WRITE_SCROLL_AREA, scrlar, 6);
    //--------------------------------------------new end
    //---normal mode 0x13
    write_command(OPC_ENTER_NORMAL_MODE); /**/
    //---wake up 0x11
    write_command(OPC_EXIT_SLEEP_MODE);
    _delay_ms(120);
    //---display ON 0x29
    write_command(OPC_SET_DISPL_ON);
    _delay_ms(120);
    //---exit invert mode 0x20
    write_command(OPC_ENTER_INVERT_MODE);
    clear_screen();
    return;
}

void write_command(uint8_t cmd)
{
    active_CS;
    active_CMD;
    put_bus_8bit_LSB(cmd);
    _IDLE;
    return;
}

void write_command(uint8_t cmd, uint8_t dat)
{
    active_CS;
    active_CMD;
    put_bus_8bit_LSB(cmd);
    idle_CMD;
    put_bus_8bit_LSB(dat);
    _IDLE;
    return;
}

void write_command(uint8_t cmd, uint8_t dat[], uint8_t size)
{
    active_CS;
    active_CMD;
    put_bus_8bit_LSB(cmd);
    idle_CMD;
    for (uint8_t i = 0; i < size; i++)
    {
        put_bus_8bit_LSB(dat[i]);
    }
    _IDLE;
    return;
}

void write_data(uint8_t dat[], uint8_t size)
{
    active_CS;
    for (uint16_t len = 0; len < size; len++)
    {
        put_bus_8bit_LSB(dat[len]);
    }
    _IDLE;
    return;
}

void put_bus_8bit_LSB(uint8_t byte)
{
    status_byte = byte;
    if (((byte >> 0)&0x01) == 0x01)
    {
        active_00;
    }
    else
    {
        idle_00;
    }
    if (((byte >> 1)&0x01) == 0x01)
    {
        active_01;
    }
    else
    {
        idle_01;
    }
    if (((byte >> 2)&0x01) == 0x01)
    {
        active_02;
    }
    else
    {
        idle_02;
    }
    if (((byte >> 3)&0x01) == 0x01)
    {
        active_03;
    }
    else
    {
        idle_03;
    }
    if (((byte >> 4)&0x01) == 0x01)
    {
        active_04;
    }
    else
    {
        idle_04;
    }
    if (((byte >> 5)&0x01) == 0x01)
    {
        active_05;
    }
    else
    {
        idle_05;
    }
    if (((byte >> 6)&0x01) == 0x01)
    {
        active_06;
    }
    else
    {
        idle_06;
    }
    if (((byte >> 7)&0x01) == 0x01)
    {
        active_07;
    }
    else
    {
        idle_07;
    }
    strobe_WR;
    return;
}

void put_bus_8bit_MSB(uint8_t byte)
{
    put_bus_8bit_LSB(reverse_bits(byte));
    return;
}

uint8_t get_bus_byte(void)
{
    uint8_t ret = 0x00;
    ret |= (read_00 << 0) | (read_01 << 1) | (read_02 << 2) | (read_03 << 3) | (read_04 << 4) | (read_05 << 5) | (read_06 << 6) | (read_07 << 7);
    return ret;
}

uint16_t rgb_to_565(uint8_t r, uint8_t g, uint8_t b)
{
    //truncate
    r &= 0x1F; //0-31
    g &= 0x3F; //0-63
    b &= 0x1F; //0-31
    return ((0xFFFF & (r << 11)) | (g << 5)) | b;
}

/******************************************************************************
 *                                                           GENERAL FUNCTIONS*/
void clear_screen(void)
{
    uint8_t coladdr[] = {0x00, 0x00, 0x01, 0x3F};
    uint8_t pageaddr[] = {0x00, 0x00, 0x01, 0xDF};
    write_command(OPC_WRITE_COL_ADDR, coladdr, 4);
    write_command(OPC_WRITE_PAGE_ADDR, pageaddr, 4);
    uint8_t black[] = {0x00, 0x00};
    write_command(OPC_WRITE_MEM_START, black, 2);
    write_command(OPC_WRITE_MEM_CONTINUE, black, 2);
    active_CS;
    put_bus_8bit_LSB(black[0]);
    put_bus_8bit_LSB(black[1]);
    for (uint32_t i = 0; i < 153600; i++)
    {
        strobe_WR;
        strobe_WR;
    }
    idle_CS;
    _IDLE;
    return;
}

void fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t colour)
{

    uint32_t area = w*h;
    w += (x - 1);
    h += (y - 1);
    uint8_t caddr[] = {0xFF & (x >> 8), 0xFF & x, 0xFF & (w >> 8), 0xFF & w};
    uint8_t paddr[] = {0xFF & (y >> 8), 0xFF & y, 0xFF & (h >> 8), 0xFF & h};
    write_command(OPC_WRITE_COL_ADDR, caddr, 4);
    write_command(OPC_WRITE_PAGE_ADDR, paddr, 4);
    uint8_t col[] = {0xFF & (colour >> 8), 0xFF & colour};
    write_command(OPC_WRITE_MEM_START, col, 2);
    write_command(OPC_WRITE_MEM_CONTINUE, col, 2);
    active_CS;
    for (uint32_t i = 1; i < area; i++)
    {
        put_bus_8bit_LSB(col[0]);
        put_bus_8bit_LSB(col[1]);
    }
    idle_CS;
    _IDLE;
    return;
}

void plot_pixel(uint16_t x, uint16_t y, uint16_t colour)
{
    fill_rect(x, y, 1, 1, colour);
    return;
}

void draw_h_line(uint16_t x, uint16_t y, uint16_t len, uint16_t colour)
{
    fill_rect(x, y, len, 1, colour);
    return;
}

void draw_v_line(uint16_t x, uint16_t y, uint16_t len, uint16_t colour)
{
    fill_rect(x, y, 1, len, colour);
    return;
}

void draw_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t colour)
{
    draw_h_line(x, y, w, colour);
    draw_h_line(x, y + h, w, colour);
    draw_v_line(x, y, h, colour);
    draw_v_line(x + w, y, h, colour);
    return;
}

void plot_2D_graph(void)
{

    for (uint16_t y = 0; y < DISPLAY_HEIGHT; y++)
    {
        uint16_t ress = (DISPLAY_WIDTH / 2) - sin((y / 60.0))*100.0;
        plot_pixel(ress, y, rgb_to_565(31, 0, 0));
        uint16_t resc = (DISPLAY_WIDTH / 2) - cos((y / timer_counter / 100))*100.0;
        plot_pixel(resc, y, rgb_to_565(0, 63, 0));
        uint16_t rest = (DISPLAY_WIDTH / 2) - tan((y / 60.0))*100.0;
        plot_pixel(rest, y, rgb_to_565(0, 0, 31));
    }
    return;
}

void print_char(char c, uint8_t size, uint16_t xpos, uint16_t ypos, uint16_t colour)
{
    uint8_t * chararr = get_char(c);
    for (uint8_t i = 0; i < chararr[0]; i++)
    {
        fill_rect(xpos + (size * chararr[1 + (i * 4)]), ypos + (size * chararr[2 + (i * 4)]), size * chararr[3 + (i * 4)], size * chararr[4 + (i * 4)], colour);
    }
    return;
}

void print_str(char * c, uint8_t size, uint16_t xpos, uint16_t ypos, uint16_t colour)
{
    uint8_t offset = 0, step = size * 7;
    while (*c - '\0')
    {
        print_char(*c, size, offset + xpos, ypos, colour);
        offset += step;
        c++;
    }
    return;
}

void print_float(float flt, uint8_t size, uint16_t xpos, uint16_t ypos, uint16_t colour)
{
    char str[6];
    print_str(dtostrf(flt, 3, 3, str), size, xpos, ypos, colour);
    return;
}

/******************************************************************************
 *                                                                       USART*/


/*****************************************************************************
 *                                                                     I2C LCD*/

/******************************************************************************
 *                                                                        ADC*/

/******************************************************************************
 *                                                                      TIMER0*/
ISR(TIMER0_OVF_vect)
{
    timer_counter++;
    if (timer_counter > 0x1a12)
    {
        timer_counter = 0;
    }
    /* timer_counter++;
     if (timer_counter > 0x7a12)
     {
         timer_counter = 0;
         _setpin(PORT_DIAG, PIN_DIAG);
         _delay_us(16);
         _clearpin(PORT_DIAG, PIN_DIAG);
         _delay_us(4);
         for (uint8_t i = 0; i < 8; i++)
         {
             if (((status_byte >> (7 - i))&0x01) == 0x01)
             {
                 _setpin(PORT_DIAG, PIN_DIAG);
                 _delay_us(8);
             }
             else
             {
                 _setpin(PORT_DIAG, PIN_DIAG);
                 _delay_us(4);
             }
             _clearpin(PORT_DIAG, PIN_DIAG);
             _delay_us(4);
         }
         _clearpin(PORT_DIAG, PIN_DIAG);
     }*/
}

/*****************************************************************************
 *                                                                      EEPROM*/

/*****************************************************************************
 *                                                                        UTIL*/

uint8_t reverse_bits(uint8_t b)
{
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

void delay_n_us(uint16_t n)
{
    while (n--)
    {
        _delay_us(1);
    }
    return;
}

void delay_n_ms(uint16_t n)
{
    while (n--)
    {
        _delay_ms(1);
    }
    return;
}

int available_sram(void)
{
    extern int __heap_start, *__brkval;
    int v;
    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}