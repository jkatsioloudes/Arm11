turn_on:
  ldr r1,0x20200004 ; Set register 1 to the address of the 10-19 pins.
  ldr r2,0x20200028 ; Set register 2 to the address of the clearing pins.
  ldr r3,0x2020001C ; Set register 3 to the address of the setting pins.
  ldr r4,0xFFF      ; Set register 4 to 4095.
  ldr r5,0xFFF      ; Set register 5 to 4095.
  orr r1,0x40000    ; 
  and r1,0xFFF9FFFF ; Set pin 16 as output.
  orr r2,0x10000    ; Clear pin 16.
  orr r3,0x10000    ; Set pin 16.
  str r1,0x20200004 ; Store result of r1 into memory.
  str r2,0x20200028 ; Store result of r2 into memory.
  str r3,0x2020001C ; Store result of r3 into memory.
wait:
  sub r4,r4,#1      ; Decrease r4 by 1.
  cmp r4,#0         ; Compare r4 to 0.
  bne wait          ; If r4 != 0, go back to label wait.
turn_off:
  and r1,0xFFFEFFFF ; Disable pin 16;
  str r1,0x20200004 ; Store result of r1 into memory.
wait2:
  sub r5,r5,#1      ; Decrease r5 by 1.
  cmp r5,#0         ; Compare r5 to 0.
  bne wait          ; If r5 != 0, go back to label wait.
  b turn_on         ;
