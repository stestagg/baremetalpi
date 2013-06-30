#define BASE 0x200000
#define COPY_SIZE 0x050000
#define WORD 4
#define STACK_LOCATION 0x08000000

_start:
    mov r1, pc        // PC will be the address of the next instruction, so
                      // No matter where we're loaded, we can use that to 
                      // work out what ranges to copy.  -8 seems to be the
                      // magic number here(?)
    sub r1, #8 // Not entirely sure I understand why this is needed...

    ldr r4, =mem_size // Load the end of file marker address
    add r4, r4, r1 // Offset it from the start of file (in memory)
    mov r2, #BASE // R2 holds the destination address
loop:
    ldr r3, [r1, #0] // Read the word
    str r3, [r2, #0] // Write it
    add r1, r1, #WORD // Increment both pointers
    add r2, r2, #WORD
    cmp r1, r4 // Are we at the end?
    ble loop // No? do the loop..

    mov r3, #BASE // Yes? load the new base address
    add r3, r3, #(cmain) // Offset to the cmain func...
    mov pc, r3 // Jump

cmain:
    mov sp, #STACK_LOCATION
    bl main

hang: b hang


.globl PUT32
PUT32:
    str r1,[r0]
    bx lr

.globl PUT16
PUT16:
    strh r1,[r0]
    bx lr

.globl PUT8
PUT8:
    strb r1,[r0]
    bx lr

.globl GET32
GET32:
    ldr r0,[r0]
    bx lr

.globl GETPC
GETPC:
    mov r0,lr
    bx lr

.globl BRANCHTO
BRANCHTO:
    bx r0

.globl dummy
dummy:
    bx lr


;@-------------------------------------------------------------------------
;@
;@ Copyright (c) 2012 David Welch dwelch@dwelch.com
;@
;@ Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
;@
;@ The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
;@
;@ THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
;@
;@-------------------------------------------------------------------------
