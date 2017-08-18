turn_on:
ldr r1,0x20200004
ldr r2,0x20200028
ldr r3,0x2020001C
ldr r4,0xFFF
ldr r5,0xFFF
orr r1,r1,0x40000 
and r1,r1,0xFFF9FFFF
orr r2,r2,0x10000
orr r3,r3,0x10000
str r1,0x20200004
str r2,0x20200028
str r3,0x2020001C
wait:
sub r4,r4,#1
cmp r4,#0
bne wait          
turn_off:
and r1,r1,0xFFFEFFFF
str r1,0x20200004
wait2:
sub r5,r5,#1
cmp r5,#0
bne wait
b turn_on
