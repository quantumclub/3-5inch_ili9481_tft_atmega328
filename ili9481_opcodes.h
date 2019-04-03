/* ILI9481 Datasheet Section 8.1 Command List*/
/* See also 'MIPI Specification for Display Command Set' for parameter descriptions*/

/* 
 * File:   ili9481_opcodes.h
 * Author: root
 *
 * Created on 31 March 2019, 1:38 AM
 */

#ifndef ILI9481_OPCODES_H
#define ILI9481_OPCODES_H


/* =============================================================DEVICE */
#define DISPLAY_WIDTH   320
#define DISPLAY_HEIGHT  480


/* =============================================================ATMEGA328 PINS */
//----PINS bits         //Arduino=AVR(Pin number)
#define PIN_RST     0x10//A4=PC4(27)
#define PIN_CS      0x08//A3=PC3(26)
#define PIN_CMD     0x04//A2=PC2(25) Note: Pin is labelled RS, not CMD
#define PIN_WR      0x02//A1=PC1(24)
#define PIN_RD      0x01//A0=PC0(23)
#define PIN_00      0x01//8=PB0(14)
#define PIN_01      0x02//~9=PB1(15)
#define PIN_02      0x04//2=PD2(4)
#define PIN_03      0x08//~3=PD3(5)
#define PIN_04      0x10//4=PD4(6)
#define PIN_05      0x20//~5=PD5(11)
#define PIN_06      0x40//~6=PD6(12)
#define PIN_07      0x80//7=PD7(13)

/* =============================================================PORTS */
//PORTS
#define PORT_RST        PORTC
#define PORT_CS         PORTC
#define PORT_CMD        PORTC
#define PORT_WR         PORTC
#define PORT_RD         PORTC
#define PORT_00         PORTB
#define PORT_01         PORTB
#define PORT_02         PORTD
#define PORT_03         PORTD
#define PORT_04         PORTD
#define PORT_05         PORTD
#define PORT_06         PORTD
#define PORT_07         PORTD

/* =============================================================PIN FUNCTIONS */
//read
#define read_RST        ((PORT_RST & PIN_RST) >> 4)
#define read_CS         ((PORT_CS & PIN_CS) >> 3)
#define read_CMD        ((PORT_CMD & PIN_CMD) >> 2)
#define read_WR         ((PORT_WR & PIN_WR) >> 1)
#define read_RD         ((PORT_RD & PIN_RD) >> 0)
#define read_00         ((PORT_00 & PIN_00) >> 0)
#define read_01         ((PORT_01 & PIN_01) >> 1)
#define read_02         ((PORT_02 & PIN_02) >> 2)
#define read_03         ((PORT_03 & PIN_03) >> 3)
#define read_04         ((PORT_04 & PIN_04) >> 4)
#define read_05         ((PORT_05 & PIN_05) >> 5)
#define read_06         ((PORT_06 & PIN_06) >> 6)
#define read_07         ((PORT_07 & PIN_07) >> 7)
//idle high
#define idle_RST         (PORT_RST |= PIN_RST)
#define idle_CS          (PORT_CS |= PIN_CS)
#define idle_CMD         (PORT_CMD |= PIN_CMD)
#define idle_WR          (PORT_WR |= PIN_WR)
#define idle_RD          (PORT_RD |= PIN_RD)
//active high
#define active_00          (PORT_00 |= PIN_00)
#define active_01          (PORT_01 |= PIN_01)
#define active_02          (PORT_02 |= PIN_02)
#define active_03          (PORT_03 |= PIN_03)
#define active_04          (PORT_04 |= PIN_04)
#define active_05          (PORT_05 |= PIN_05)
#define active_06          (PORT_06 |= PIN_06)
#define active_07          (PORT_07 |= PIN_07)
//active low
#define active_RST       (PORT_RST &= ~(PIN_RST))
#define active_CS        (PORT_CS &= ~(PIN_CS))
#define active_CMD       (PORT_CMD &= ~(PIN_CMD))
#define active_WR        (PORT_WR &= ~(PIN_WR))
#define active_RD        (PORT_RD &= ~(PIN_RD))
//idle low
#define idle_00        (PORT_00 &= ~(PIN_00))
#define idle_01        (PORT_01 &= ~(PIN_01))
#define idle_02        (PORT_02 &= ~(PIN_02))
#define idle_03        (PORT_03 &= ~(PIN_03))
#define idle_04        (PORT_04 &= ~(PIN_04))
#define idle_05        (PORT_05 &= ~(PIN_05))
#define idle_06        (PORT_06 &= ~(PIN_06))
#define idle_07        (PORT_07 &= ~(PIN_07))
//high level
#define strobe_WR       {active_WR; idle_WR;}

#define _IDLE           {idle_RST;idle_CS;idle_CMD;idle_WR;idle_RD;\
                        idle_00;idle_01;idle_02;idle_03;idle_04;\
                        idle_05;idle_06;idle_07;}

#define _RESET          {\
                            idle_CS; idle_RD; idle_WR;\
                            active_RST; _delay_ms(2); idle_RST;\
                            active_CS; active_CMD;\
                            put_bus_8bit_LSB(0x00);\
                            idle_CMD;\
                            put_bus_8bit_LSB(0x00);\
                            put_bus_8bit_LSB(0x00);\
                            put_bus_8bit_LSB(0x00);\
                            _IDLE;}

/* =============================================================OPCODES */
//A parameter is Host->Device when (W)rite
//and Device->Host when (R)ead
//
#define OPC_SOFT_RESET                              0x01//(C)ommand
#define OPC_GET_POWER_MODE                          0x0A//(R)ead, 1 Parameter
#define OPC_GET_ADDR_MODE                           0x0B//(R)ead, 1 Parameter, Bit[7:3]
#define OPC_GET_PIXEL_FMT                           0x0C//(R)ead, 1 Parameter
#define OPC_GET_DISPL_MODE                          0x0D//(R)ead, 1 Parameter
#define OPC_GET_SIGNAL_MODE                         0x0E//(R)ead, 1 Parameter
#define OPC_GET_DIAG_RESULT                         0x0F//(R)ead, 1 Parameter, Bit[7:6]
#define OPC_ENTER_SLEEP_MODE                        0x10//(C)ommand
#define OPC_EXIT_SLEEP_MODE                         0x11//(C)ommand
#define OPC_ENTER_PARTIAL_MODE                      0x12//(C)ommand
#define OPC_ENTER_NORMAL_MODE                       0x13//(C)ommand
#define OPC_EXIT_INVERT_MODE                        0x20//(C)ommand --> Hahaha
#define OPC_ENTER_INVERT_MODE                       0x21//(C)ommand -->lol
#define OPC_SET_DISPL_OFF                           0x28//(C)ommand
#define OPC_SET_DISPL_ON                            0x29//(C)ommand
#define OPC_WRITE_COL_ADDR                          0x2A//(W)rite, 4 Parameters
#define OPC_WRITE_PAGE_ADDR                         0x2B//(W)rite, 4 Parameters
#define OPC_WRITE_MEM_START                         0x2C//(W)rite, VAR Parameters
#define OPC_READ_MEM_START                          0x2E//(R)ead, VAR Parameters
#define OPC_WRITE_PARTIAL_AREA_ROWS                 0x30//(W)rite, 4 Parameters
#define OPC_WRITE_SCROLL_AREA                       0x33//(W)rite, 6 Parameters
#define OPC_SET_TEAR_OFF                            0x34//(C)ommand
#define OPC_WRITE_TEAR_ON                           0x35//(W)rite, 1 Parameter
#define OPC_WRITE_ADDR_MODE                         0x36//(W)rite, 1 Parameter, Bit[7:0(!2)] <--?
#define OPC_WRITE_SCROLL_START                      0x37//(W)rite, 2 Parameters
#define OPC_EXIT_IDLE_MODE                          0x38//(C)ommand
#define OPC_ENTER_IDLE_MODE                         0x39//(C)ommand
#define OPC_WRITE_PIXEL_FMT                         0x3A//(W)rite, 1 Parameter
#define OPC_WRITE_MEM_CONTINUE                      0x3C//(W)rite, VAR Parameters
#define OPC_READ_MEM_CONTINUE                       0x3E//(R)ead, VAR Parameters
#define OPC_WRITE_TEAR_SCANLINE                     0x44//(W)rite, 2 Parameters
#define OPC_READ_SCANLINE                           0x45//(R)ead, 3 Parameters
#define OPC_READ_DDB_START                          0xA1//(R)ead, 6 Parameters
//
#define OPC_FRAME_CONTROL                           0xB1//???????
#define OPC_FRAME_MEM_ACCESS_INTERFACE_SETTING      0xB3//(R/W) 4 params
#define OPC_DISP_MODE_FRAME_MEM_WRITE_MODE          0xB4//(R/W) 1 param
#define OPC_DISP_FUNCTION_CONTROL                   0xB6//(R/W) 3 params
#define OPC_ENTRY_MODE                              0xB7//??????????????????
#define OPC_DEVICE_CODE_READ                        0xBF//(R)ead 6 params
#define OPC_PANEL_DRIVING_SETTING                   0xC0//(R/W) 5 params ("power control 1")
#define OPC_DISPL_TIMING_NORMAL_MODE                0xC1//(R/W) 3 params ("power control 2")
#define OPC_DISPL_TIMING_PARTIAL_MODE               0xC2//(R/W) 3 params
#define OPC_DISPL_TIMING_IDLE_MODE                  0xC3//(R/W) 3 params
#define OPC_FRAME_RATE_INVERT_CTRL                  0xC5//(R/W) 1 param ("vcom control 1")
#define OPC_INTERFACE_CTRL                          0xC6//(R/W) 1 param
//#define OPC_VCOM_CTRL_2                             0xC7//?????????????    ("vcom control 2") 
#define OPC_GAMMA_SETTING                           0xC8//(R/W) 12 params
#define OPC_POWER_SETTING                           0xD0//(R/W) 3 params
#define OPC_VCOM_CTRL                               0xD1//(R/W) 3 params
#define OPC_POWER_SETTING_NORMAL_MODE               0xD2//(R/W) 2 params
#define OPC_POWER_SETTING_PARTIAL_MODE              0xD3//(R/W) 2 params
#define OPC_POWER_SETTING_IDLE_MODE                 0xD4//(R/W) 2 params
#define OPC_NV_MEM_WRITE                            0xE0//(R/W) 1 param
#define OPC_NV_MEM_CTRL                             0xE1//(R/W) 1 param
#define OPC_NV_MEM_STATUS                           0xE2//(R)ead 3 params
#define OPC_NV_MEM_PROTECTION                       0xE3//(R/W) 2 params



/* ============================================================= PARAMETERS */
//------6.17 get_power_mode returns 1 parameter
//bits[6:2] 
#define POWER_MODE_IDLE_ON                          0x40//bit 6
#define POWER_MODE_PARTIAL_ON                       0x20//bit 5
#define POWER_MODE_SLEEP_ON                         0x10//bit 4
#define POWER_MODE_NORMAL_ON                        0x08//bit 3
#define POWER_MODE_DISPLAY_ON                       0x04//bit 2

//------6.17 get_address_mode returns 1 parameter
//bits[7:3] only
#define ADDR_MODE_PAGE_ADDR_ORDER_TOP               0x80//bit 7
#define ADDR_MODE_COL_ADDR_ORDER_R_TO_L             0x40//bit 6
#define ADDR_MODE_PAGE_COL_ORDER_REVERSED           0x20//bit 5
#define ADDR_MODE_LINE_ADDR_ORDER_B_TO_TOP          0x10//bit 4
#define ADDR_MODE_RGB_ORDER_BGR                     0x08//bit 3

//------6.27 idle_address_mode requires various parameters
//This command sets the data order for transfers from the host processor to
//display module’s frame memory, bits B[7:5], and from the display module’s
//frame memory to the display device, bits B[4:0].
//i.e. Host->FrameMem [7:5], FrameMem->Display[4:0]
//
//bit 7 - Page Address Order
//0 - Top -> Bot, StartPage -> EndPage (default))
//1 - Bot -> Top, EndPage -> StartPage
#define ADDR_MODE_PAGE_B_TO_T_EP_TO_SP              0x80//upside down
//
//bit 6 - Column Address Order
//0 - Left -> Right, StartCol -> EndCol (default))
//1 - Right -> Left, EndCol -> StartCol
#define ADDR_MODE_COL_R_TO_L_EC_TO_SC               0x40//back-to-front
//
//bit 5 - Page/Col Addressing Order
//0 - Normal (default)
//1 - Reversed
#define ADDR_MODE_PAGECOL_REVERSED                  0x20//rows-as-cols
//
//bit 4 - Display Device Line Refresh Order
//0 - top to bottom (default)
//1 - bottom to top
#define ADDR_MODE_LINE_REFRESH_B_TO_T               0x10//
//
//bit 3 - RGB/BGR order
//0 - RGB (default)
//1 - BGR
#define ADDR_MODE_BGR                               0x08//
//
//bit 2
//
//bit 1 Flip Horizontal
//0 - normal (default)
//1 - flipped
#define ADDR_MODE_FLIP_HORIZ                        0x02//
//
//bit 0 Flip Vertical
//0 - normal (default)
//1 - flipped
#define ADDR_MODE_FLIP_VERT                         0x01//


//------6.16 get_pixel_format returns 1 parameter
//bits[6:4],[2:0]
#define PIXEL_FMT_3BITS                             0x11//
#define PIXEL_FMT_8BITS                             0x22//
#define PIXEL_FMT_12BITS                            0x33//
#define PIXEL_FMT_16BITS                            0x55//
#define PIXEL_FMT_18BITS                            0x66//
#define PIXEL_FMT_24BITS                            0x77//

//------6.14 get_display_mode returns 1 parameter
//bits[7],[5],[2:0]
#define DISPL_MODE_VERT_SCROLL_ON                   0x80//bit 7
#define DISPL_MODE_INVERTED                         0x20//bit 5
#define DISPL_MODE_GAMMA_CURVE_1                    0x00//
#define DISPL_MODE_GAMMA_CURVE_2                    0x01//
#define DISPL_MODE_GAMMA_CURVE_3                    0x02//
#define DISPL_MODE_GAMMA_CURVE_4                    0x03//

//------6.20 get_signal_mode returns 1 parameter
//bits[7:6]
#define SIGNAL_MODE_TEARING_EFFECT_ON               0x80//bit 7
#define SIGNAL_MODE_TEAR_EFFECT_LINE_OUTP_MODE1     0x40//bit 6

//------6.13 get_diagnostic_result returns 1 parameter
//bits[7:6]
#define DIAG_RESULT_REGISTER_LOADING_DETECTION      0x80//bit 7
#define DIAG_RESULT_FUNCTIONALITY_DETECTION         0x40//bit 6

//------6.28 idle_column_address requires 4 parameters
//This command defines the column extent of the frame memory accessed by the
//host processor with the read_memory_continue and write_memory_continue
//commands. No status bits are changed.
typedef struct {
    uint16_t START_COLUMN;
    uint16_t END_COLUMN;
} COLUMN_ADDRESS;

//------6.32 idle_page_address requires 4 parameters
//"page" refers to a row in the frame memory
//This command defines the page (active row) extent of the frame memory accessed by the
//host processor with the read_memory_continue and write_memory_continue
//commands. No status bits are changed.

typedef struct {
    uint16_t START_PAGE;
    uint16_t END_PAGE;
} PAGE_ADDRESS;

//------6.44 write_memory_continue various parameters
//This command transfers image data from the host processor to the display
//module’s frame memory continuing from the pixel location following the
//previous write_memory_continue or write_memory_start command.

//------6.45 write_memory_start various parameters
//This command transfers image data from the host processor to the display
//module’s frame memory starting at the pixel location specified by preceding
//idle_column_address and idle_page_address commands

typedef struct {//2 pixels!!!
uint8_t:
    0;
    uint8_t R1 : 1;
    uint8_t G1 : 1;
    uint8_t B1 : 1;
    uint8_t R2 : 1;
    uint8_t G2 : 1;
    uint8_t B2 : 1;
} PIXEL_3BIT;

typedef struct {
    uint8_t Rb2 : 1;
    uint8_t Rb1 : 1;
    uint8_t Rb0 : 1;
    uint8_t Gb2 : 1;
    uint8_t Gb1 : 1;
    uint8_t Gb0 : 1;
    uint8_t Bb1 : 1;
    uint8_t Bb0 : 1;
} PIXEL_8BIT;

typedef struct {
    uint16_t Rb4 : 1;
    uint16_t Rb3 : 1;
    uint16_t Rb2 : 1;
    uint16_t Rb1 : 1;
    uint16_t Rb0 : 1;
    uint16_t Gb5 : 1;
    uint16_t Gb4 : 1;
    uint16_t Gb3 : 1;
    uint16_t Gb2 : 1;
    uint16_t Gb1 : 1;
    uint16_t Gb0 : 1;
    uint16_t Bb4 : 1;
    uint16_t Bb3 : 1;
    uint16_t Bb2 : 1;
    uint16_t Bb1 : 1;
    uint16_t Bb0 : 1;
} PIXEL_16BIT;

//------6.33 idle_partial_cols requires 4 parameters
//This command defines the Partial Display mode’s display width. There are two
//parameters associated with this command, the first defines the Start Col (SC)
//and the second the End Col (EC).
//SC and EC refer to the Frame Memory Column Pointer.

typedef struct {
    uint16_t START_PART_COL;
    uint16_t END_PART_COL;
} PARTIAL_COLS;

//------6.34 idle_partial_rows requires 4 parameters
//This command defines the Partial Display mode’s display height. There are two
//parameters associated with this command, the first defines the Start Row (SR)
//and the second the End Row (ER).
//SR and ER refer to the Frame Memory Line Pointer.

typedef struct {
    uint16_t START_PART_ROW;
    uint16_t END_PART_ROW;
} PARTIAL_ROWS;


//------6.36 idle_scroll area requires 6 parameters
//This command defines the display module’s Vertical Scrolling Area.
//If idle_address_mode B4 = 0: (the reverse is true for =1)
//param 1,2: 
//Top Fixed Area (TFA) in number of lines from the top of the frame memory.
//The top of the frame memory and top of the display device are aligned.
//param 3,4: 
//Vertical Scrolling Area in number of lines of frame memory from
//the Vertical Scrolling Start Address.
//The first line of the VSA starts immediately after the bottom most line of
//the TFA. 
//The last line of the VSA ends immediately before the top most line of the BFA
//param 5,6:Bottom Fixed Area in number of lines from the bottom of the frame
//memory. The bottom of the frame memory and bottom of the display device are aligned.
//

typedef struct {
    uint16_t TOP_FIXED_AREA;
    uint16_t VERTICAL_SCROLLING_AREA;
    uint16_t BOTTOM_FIXED_AREA;
} SCROLL_AREA;

//------6.39 idle_tear_on requires 1 parameter
//bit[0] only
#define TEAR_EFFECT_V_AND_H_BLANK                   0x80//bit 0

//------6.40 idle_tear_scanline requires 2 params

typedef struct {
    uint16_t FROM_DEVICE;
    uint16_t TO_DEVICE;
} TEAR_SCANLINE;

//------6.23 read_DDB_start 6 params
//This command reads identifying and descriptive information from the 
//peripheral. This information is organized in the Device Descriptor Block (DDB)
//stored on the peripheral. The response to this command returns a sequence of 
//bytes that may be any length up to 64K bytes. Note that the returned sequence
//of bytes does not necessarily correspond to the entire DDB; it may be a
//portion of a larger block of data.
//Escape codes:
//0xFF - No more data in Descr Block
//0x00 - Supplier proprietary data in DB
//0x01-0xFE - there is DDB data in DB

typedef struct {
    uint16_t SUPPLIER_ID;
    uint8_t SUPPLIER_ELECTIVE_DATA;
    uint8_t ESCAPE_CODE;
} DEVICE_DESCRIPTOR_BLOCK;

#endif /* ILI9481_OPCODES_H */

