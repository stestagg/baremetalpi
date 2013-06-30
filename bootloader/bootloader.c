#include "platform.h"

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


#define CR 0x0D
#define LF 0x0A

typedef unsigned long size_t;

size_t strlen(const char* string)
{
    const char*cur = string;
    while (*cur) ++ cur;
    return cur - string;
}

void puts(const char *string)
{
    const char *end = string + strlen(string);
    const char *cur = string;
    for (; cur != end; ++cur)
    {
        uart_send(*cur);
    }
    uart_send(CR);
    uart_send(LF);
}

//------------------------------------------------------------------------
unsigned char xstring[256];
//------------------------------------------------------------------------
int main ( void )
{
    unsigned int ra;
    //unsigned int rb;
    unsigned int rx;
    unsigned int addr;
    unsigned int block;
    unsigned int state;

    unsigned int crc;

    setup_for_jtag();
    uart_init();
    puts("+--------------------------------+");
    puts("| Raspberry PI Serial bootloader |");
    puts("+--------------------------------+");
    puts("");
    puts("Waiting for XMODEM transfer...");

    hexstring(0x73656e64);

    timer_init();
    while(1)
    {
        ra=timer_tick();
        if((ra-rx)>=4000000)
        {
            uart_send(0x15);
            rx+=4000000;
        }
        if((uart_lcr()&0x01)==0) continue;
        xstring[state]=uart_recv();
        rx=timer_tick();
        if(state==0)
        {
            if(xstring[state]==0x04)
            {
                uart_send(0x06);
                for(ra=0;ra<30;ra++) hexstring(ra);
                hexstring(0x11111111);
                hexstring(0x22222222);
                hexstring(0x33333333);
                uart_flush();
                BRANCHTO(ARMBASE);
                break;
            }
        }
        switch(state)
        {
            case 0:
            {
                if(xstring[state]==0x01)
                {
                    crc=xstring[state];
                    state++;
                }
                else
                {
                    //state=0;
                    uart_send(0x15);
                }
                break;
            }
            case 1:
            {
                if(xstring[state]==block)
                {
                    crc+=xstring[state];
                    state++;
                }
                else
                {
                    state=0;
                    uart_send(0x15);
                }
                break;
            }
            case 2:
            {
                if(xstring[state]==(0xFF-xstring[state-1]))
                {
                    crc+=xstring[state];
                    state++;
                }
                else
                {
                    uart_send(0x15);
                    state=0;
                }
                break;
            }
            case 131:
            {
                crc&=0xFF;
                if(xstring[state]==crc)
                {
                    for(ra=0;ra<128;ra++)
                    {
                        PUT8(addr++,xstring[ra+3]);
                    }
                    uart_send(0x06);
                    block=(block+1)&0xFF;
                }
                else
                {
                    uart_send(0x15);
                }
                state=0;
                break;
            }
            default:
            {
                crc+=xstring[state];
                state++;
                break;
            }
        }
    }
    return(0);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
//
// Copyright (c) 2012 David Welch dwelch@dwelch.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------
