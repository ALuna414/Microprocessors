#ifndef VT100_H
#define VT100_H

/*
 * VT100.h
 * revision date: 15 August 2021
 * Written by: William Stapleton
 * The purpose of this header file is to provide functions for
 * sending common VT100 command codes to the default display (STDOUT)
 * 
 * This is NOT an exhaustive list of available VT100 codes!
 * The codes illustrated are the ones likely to be useful for
 * EE3420 at Texas State University
 */

#include "ASCII.h"

char vt100_temp_string[80];

char* vt100_home()
{
    sprintf(vt100_temp_string, vt100_temp_string, "\x1b[H");
    return(vt100_temp_string);
}

char* vt100_move_cursor(int row, int column)
{
    sprintf(vt100_temp_string, "\x1b[%i;%iH\0",row,column);
    return(vt100_temp_string);
}

char* vt100_save_cursor()
{
    sprintf(vt100_temp_string, "\x1b[s");
    return(vt100_temp_string);
}

char* vt100_unsave_cursor()
{
    sprintf(vt100_temp_string, "\x1b[u");
    return(vt100_temp_string);
}

char* vt100_up()
{
    sprintf(vt100_temp_string, "\x1b[A");
    return(vt100_temp_string);
}

char* vt100_up_by(int count)
{
    sprintf(vt100_temp_string, "\x1b[%iA",count);
    return(vt100_temp_string);
}

char* vt100_down()
{
    sprintf(vt100_temp_string, "\x1b[B");
    return(vt100_temp_string);
}

char* vt100_down_by(int count)
{
    sprintf(vt100_temp_string, "\x1b[%iB",count);
    return(vt100_temp_string);
}

char* vt100_right()
{
    sprintf(vt100_temp_string, "\x1b[C");
    return(vt100_temp_string);
}

char* vt100_right_by(int count)
{
    sprintf(vt100_temp_string, "\x1b[%iC",count);
    return(vt100_temp_string);
}

char* vt100_left()
{
    sprintf(vt100_temp_string, "\x1b[D");
    return(vt100_temp_string);
}

char* vt100_left_by(int count)
{
    sprintf(vt100_temp_string, "\x1b[%iD",count);
    return(vt100_temp_string);
}

char* vt100_erase_right()
{
    sprintf(vt100_temp_string, "\x1b[K");
    return(vt100_temp_string);
}

char* vt100_erase_left()
{
    sprintf(vt100_temp_string, "\x1b[1K");
    return(vt100_temp_string);
}

char* vt100_erase_line()
{
    sprintf(vt100_temp_string, "\x1b[2K");
    return(vt100_temp_string);
}

char* vt100_erase_above()
{
    sprintf(vt100_temp_string, "\x1b[J");
    return(vt100_temp_string);
}

char* vt100_erase_below()
{
    sprintf(vt100_temp_string, "\x1b[1J");
    return(vt100_temp_string);
}

char* vt100_erase_screen()
{
    sprintf(vt100_temp_string, "\x1b[2J");
    return(vt100_temp_string);
}

char* vt100_set_attribute(int attrib)
{
    sprintf(vt100_temp_string, "\x1b[%xm\0",attrib);
    return(vt100_temp_string);
}

enum vt100_colors
{
    black=0,
    red=1,
    green=2,
    yellow=3,
    blue=4,
    magenta=5,
    cyan=6,
    white=7
};

char* vt100_text_default()
{
    //vt100_set_attribute(0);
    sprintf(vt100_temp_string, "\x1b[0m");
    return(vt100_temp_string);
}

char* vt100_text_bright()
{
    //vt100_set_attribute(1);
    sprintf(vt100_temp_string, "\x1b[1m");
    return(vt100_temp_string);
}

char* vt100_text_dim()
{
    //vt100_set_attribute(2);
    sprintf(vt100_temp_string, "\x1b[2m");
    return(vt100_temp_string);
}

char* vt100_text_underscore()
{
    //vt100_set_attribute(4);
    sprintf(vt100_temp_string, "\x1b[4m");
    return(vt100_temp_string);
}

char* vt100_text_blink()
{
    vt100_set_attribute(5);
    return(vt100_temp_string);
}

char* vt100_text_reverse()
{
    vt100_set_attribute(7);
    return(vt100_temp_string);
}

char* vt100_text_hidden()
{
    vt100_set_attribute(8);
    return(vt100_temp_string);
}

char* vt100_set_foreground(int color)
{
    if(color<0 || color > 7)
    {
        sprintf(vt100_temp_string, "\nforeground color must be in the range 0-7\n");
        return(vt100_temp_string);
    }
    vt100_set_attribute(0x30+color);
}

char* vt100_set_background(int color)
{
    if(color<0 || color > 7)
    {
        sprintf(vt100_temp_string, "\nbackground color must be in the range 0-7\n");
        return(vt100_temp_string);
    }
    vt100_set_attribute(0x40+color);
}

#endif //VT100_H
