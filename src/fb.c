#include <stdint.h>
#include <stdio.h>
#include "log.h"

volatile uint16_t * vram = (uint16_t*)0x06000000;

#define REG16(addr) (*(volatile uint16_t*)(addr))
#define REG32(addr) (*(volatile uint32_t*)(addr))

#define BASE 0x04000000
#define DISPCNT REG16(BASE + 0x0)
#define DISPSTAT REG16(BASE + 0x4)

#define KEYCNT REG16(BASE + 0x132)

#define IE REG16(BASE + 0x200)
#define IF REG16(BASE + 0x202)
#define IME REG32(BASE + 0x208)

#define IRQ_ENTRY REG32(0x3007FFC)

void irq_on();

__attribute__((target("arm"))) void irq_handler() {
  uint16_t code = IF;
  char msg[15];
  for (int i=0; i<14; i++) {
    if (code & (1<<i)) msg[i] = '_';
    else msg[i] = 'X';
  }
  msg[14] = 0;
  logOutputMgba(4, msg);
}

void draw() {
  IRQ_ENTRY = (uint32_t)&irq_handler;
  IE = 1 || (1<<12);
  //DISPSTAT = 1<<3;
  KEYCNT = (1 << 6) || (1<<14);
  IME = 1;
  irq_on();
  // https://problemkaputt.de/gbatek.htm#lcdiodisplaycontrol
  DISPCNT = 0x403; // 4= Layer 2 on / 3= ScreenMode 3
  for (int i=0; i<100; i++) {
    int x = i;
    int y = i;
    vram[x + (y*240)] = 0xffff;
  }
}
