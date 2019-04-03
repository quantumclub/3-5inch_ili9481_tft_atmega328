/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   font1.h
 * Author: root
 *
 * Created on 03 April 2019, 2:38 PM
 */

#ifndef FONT1_H
#define FONT1_H

void print_char(char c, uint8_t size, uint16_t xpos, uint16_t ypos, uint16_t colour);
void print_str(char * c, uint8_t size, uint16_t xpos, uint16_t ypos, uint16_t colour);
void print_float(float flt, uint8_t size, uint16_t xpos, uint16_t ypos, uint16_t colour);
uint8_t * get_char(char c);
//----SPACE
const uint8_t charSPACE[] = {1,
    0, 0, 0, 0};
//----PERIOD
const uint8_t charPERIOD[] = {1,
    2, 5, 1, 1};
//----DASH/MINUS
const uint8_t charPLUS[] = {2,
    0, 3, 5, 1,
    2,1,1,5};
//----PLUS
const uint8_t charDASH[] = {1,
    0, 3, 5, 1};
//----1
const uint8_t char1[] = {4,
    0, 2, 1, 1,
    1, 1, 1, 1,
    2, 0, 1, 7,
    0, 6, 5, 1};
//----2
const uint8_t char2[] = {7,
    0, 1, 1, 1,
    1, 0, 3, 1,
    4, 1, 1, 2,
    3, 3, 1, 1,
    2, 4, 1, 1,
    1, 5, 1, 1,
    0, 6, 5, 1};
//----3
const uint8_t char3[] = {7,
    0, 1, 1, 1,
    1, 0, 3, 1,
    4, 1, 1, 2,
    2, 3, 2, 1,
    4, 4, 1, 2,
    1, 6, 3, 1,
    0, 5, 1, 1};
//----4
const uint8_t char4[] = {4,
    3, 0, 1, 7,
    2, 1, 1, 1,
    1, 2, 1, 1,
    0, 3, 5, 1};
//----5
const uint8_t char5[] = {5,
    0, 0, 5, 1,
    0, 1, 1, 2,
    0, 3, 4, 1,
    4, 4, 1, 2,
    0, 6, 4, 1};
//----6

const uint8_t char6[] = {5,
    1, 0, 4, 1,
    0, 1, 1, 5,
    1, 3, 3, 1,
    4, 4, 1, 2,
    1, 6, 3, 1};
//----7

const uint8_t char7[] = {5,
    0, 0, 5, 1,
    4, 1, 1, 1,
    3, 2, 1, 1,
    2, 3, 1, 1,
    1, 4, 1, 3};
//----8

const uint8_t char8[] = {7,
    1, 0, 3, 1,
    0, 1, 1, 2,
    4, 1, 1, 2,
    1, 3, 3, 1,
    0, 4, 1, 2,
    4, 4, 1, 2,
    1, 6, 3, 1};
//----9
const uint8_t char9[] = {5,
    1, 0, 3, 1,
    0, 1, 1, 2,
    4, 1, 1, 5,
    1, 3, 3, 1,
    0, 6, 4, 1};
//----0
const uint8_t char0[] = {7,
    1, 0, 3, 1,
    0, 1, 1, 5,
    4, 1, 1, 5,
    1, 6, 3, 1,
    3, 2, 1, 1,
    2, 3, 1, 1,
    1, 4, 1, 1};
//----*
const uint8_t charASTERISK[] = {6,
    0, 1, 1, 1,
    4, 1, 1, 1,
    0, 5, 1, 1,
    4, 5, 1, 1,
    1, 2, 3, 3,
    2, 0, 1, 7};
//----A
const uint8_t charA[] = {4,
    0, 1, 1, 6,
    4, 1, 1, 6,
    1, 0, 3, 1,
    1, 3, 3, 1};
//----B
const uint8_t charB[] = {6,
    0, 0, 1, 7,
    1, 0, 3, 1,
    1, 3, 3, 1,
    1, 6, 3, 1,
    4, 1, 1, 2,
    4, 4, 1, 2};
//----C
const uint8_t charC[] = {5,
    0, 1, 1, 5,
    1, 0, 3, 1,
    1, 6, 3, 1,
    4, 1, 1, 1,
    4, 5, 1, 1};
//----D
const uint8_t charD[] = {4,
    0, 0, 1, 7,
    1, 0, 3, 1,
    1, 6, 3, 1,
    4, 1, 1, 5};
//----E
const uint8_t charE[] = {4,
    0, 0, 1, 7,
    1, 0, 4, 1,
    1, 6, 4, 1,
    1, 3, 3, 1};
//----F
const uint8_t charF[] = {3,
    0, 0, 1, 7,
    1, 0, 4, 1,
    1, 3, 3, 1};
//----G
const uint8_t charG[] = {6,
    0, 1, 1, 6,
    1, 0, 3, 1,
    1, 6, 3, 1,
    4, 1, 1, 1,
    4, 5, 1, 1,
    3,4,2,1};
//----H
const uint8_t charH[] = {3,
    0, 0, 1, 7,
    4, 0, 1, 7,
    1, 3, 3, 1};
//----I
const uint8_t charI[] = {3,
    2, 0, 1, 7,
    0, 0, 5, 1,
    0, 6, 5, 1};
//----J
const uint8_t charJ[] = {4,
    0, 0, 5, 1,
    4, 1, 1, 5,
    1, 6, 3, 1,
    0, 5, 1, 1};
//----K
const uint8_t charK[] = {6,
    0, 0, 1, 7,
    1, 3, 2, 1,
    3, 2, 1, 1,
    3, 4, 1, 1,
    4, 0, 1, 2,
    4, 5, 1, 2};
//----L
const uint8_t charL[] = {2,
    0, 0, 1, 7,
    1, 6, 4, 1};
//----M
const uint8_t charM[] = {5,
    0, 0, 1, 7,
    4, 0, 1, 7,
    1, 1, 1, 1,
    2, 2, 1, 1,
    3, 1, 1, 1};
//----N
const uint8_t charN[] = {5,
    0, 0, 1, 7,
    4, 0, 1, 7,
    1, 2, 1, 1,
    2, 3, 1, 1,
    3, 4, 1, 1};
//----O
const uint8_t charO[] = {4,
    0, 1, 1, 5,
    4, 1, 1, 5,
    1, 0, 3, 1,
    1, 6, 3, 1};
//----P
const uint8_t charP[] = {4,
    0, 0, 1, 7,
    1, 0, 3, 1,
    1, 3, 3, 1,
    4, 1, 1, 2};
//----Q
const uint8_t charQ[] = {7,
    0, 1, 1, 5,
    4, 1, 1, 4,
    1, 0, 3, 1,
    2, 4, 1, 1,
    3, 5, 1, 1,
    4, 6, 1, 1,
    1, 6, 2, 1};
//----R
const uint8_t charR[] = {5,
    0, 0, 1, 7,
    1, 0, 3, 1,
    1, 3, 3, 1,
    4, 1, 1, 2,
    4, 4, 1, 3};
//----S
const uint8_t charS[] = {5,
    1, 0, 4, 1,
    0, 1, 1, 2,
    1, 3, 3, 1,
    4, 4, 1, 2,
    0, 6, 4, 1};
//----T
const uint8_t charT[] = {2,
    0, 0, 5, 1,
    2, 1, 1, 6};
//----U
const uint8_t charU[] = {3,
    0, 0, 1, 6,
    4, 0, 1, 6,
    1, 6, 3, 1};
//----V
const uint8_t charV[] = {5,
    0, 0, 1, 5,
    4, 0, 1, 5,
    1, 5, 1, 1,
    2, 6, 1, 1,
    3, 5, 1, 1};
//----W
const uint8_t charW[] = {5,
    0, 0, 1, 7,
    4, 0, 1, 7,
    1, 5, 1, 1,
    2, 4, 1, 1,
    3, 5, 1, 1};
//----X
const uint8_t charX[] = {9,
    0, 0, 1, 2,
    4, 0, 1, 2,
    0, 5, 1, 2,
    4, 5, 1, 2,
    1, 2, 1, 1,
    3, 2, 1, 1,
    2, 3, 1, 1,
    1, 4, 1, 1,
    3, 4, 1, 1};
//----Y
const uint8_t charY[] = {5,
    0, 0, 1, 2,
    4, 0, 1, 2,
    2, 3, 1, 4,
    1, 2, 1, 1,
    3, 2, 1, 1};
//----Z
const uint8_t charZ[] = {7,
    0, 0, 5, 1,
    0, 6, 5, 1,
    4, 1, 1, 1,
    3, 2, 1, 1,
    2, 3, 1, 1,
    1, 4, 1, 1,
    0, 5, 1, 1};


//==============================================================

uint8_t * get_char(char c) {
    switch (c) {
        case '1':
            return (uint8_t *) char1;
        case '2':
            return (uint8_t *) char2;
        case '3':
            return (uint8_t *) char3;
        case '4':
            return (uint8_t *) char4;
        case '5':
            return (uint8_t *) char5;
        case '6':
            return (uint8_t *) char6;
        case '7':
            return (uint8_t *) char7;
        case '8':
            return (uint8_t *) char8;
        case '9':
            return (uint8_t *) char9;
        case '0':
            return (uint8_t *) char0;
        case '*':
            return (uint8_t *) charASTERISK;
        case '.':
            return (uint8_t *) charPERIOD;
        case '-':
            return (uint8_t *) charDASH;
        case '+':
            return (uint8_t *) charPLUS;
        case 'A':
            return (uint8_t *) charA;
        case 'B':
            return (uint8_t *) charB;
        case 'C':
            return (uint8_t *) charC;
        case 'D':
            return (uint8_t *) charD;
        case 'E':
            return (uint8_t *) charE;
        case 'F':
            return (uint8_t *) charF;
        case 'G':
            return (uint8_t *) charG;
        case 'H':
            return (uint8_t *) charH;
        case 'I':
            return (uint8_t *) charI;
        case 'J':
            return (uint8_t *) charJ;
        case 'K':
            return (uint8_t *) charK;
        case 'L':
            return (uint8_t *) charL;
        case 'M':
            return (uint8_t *) charM;
        case 'N':
            return (uint8_t *) charN;
        case 'O':
            return (uint8_t *) charO;
        case 'P':
            return (uint8_t *) charP;
        case 'Q':
            return (uint8_t *) charQ;
        case 'R':
            return (uint8_t *) charR;
        case 'S':
            return (uint8_t *) charS;
        case 'T':
            return (uint8_t *) charT;
        case 'U':
            return (uint8_t *) charU;
        case 'V':
            return (uint8_t *) charV;
        case 'W':
            return (uint8_t *) charW;
        case 'X':
            return (uint8_t *) charX;
        case 'Y':
            return (uint8_t *) charY;
        case 'Z':
            return (uint8_t *) charZ;

        default:
            return (uint8_t *) charSPACE;
    }
}

#endif /* FONT1_H */

