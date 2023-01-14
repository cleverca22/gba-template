#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "log.h"
#include "xprintf.h"

volatile uint16_t * const vram = (uint16_t*)0x06000000;

#define REG16(addr) (*(volatile uint16_t*)(addr))
#define REG32(addr) (*(volatile uint32_t*)(addr))

#define BASE 0x04000000
#define DISPCNT REG16(BASE + 0x0)
#define DISPSTAT REG16(BASE + 0x4)

#define KEYINPUT REG16(BASE + 0x130)
#define KEYCNT REG16(BASE + 0x132)

#define IE REG16(BASE + 0x200)
#define IF REG16(BASE + 0x202)
#define IME REG32(BASE + 0x208)

#define IRQ_ENTRY REG32(0x3007FFC)

volatile bool vsync_happened;

void irq_on();

__attribute__((target("arm"))) void irq_handler() {
  uint16_t code = IF;
  uint16_t ack = 0;
  if (code & 1) {
    // vsync
    ack |= 1;
    vsync_happened = true;
  }
  if (code & (1<<12)) {
    // keypad
    ack |= (1<<12);
    printf("key hit\n");
  }
  code &= ~ack;
  IF = ack;
  if (code) {
    printf("irq code %d\n", code);
  }
}

void draw() {
  IRQ_ENTRY = (uint32_t)&irq_handler;
  IE = 1; // | (1<<12);
  DISPSTAT = 1<<3;
  //KEYCNT = (1 << 6) | (1<<14);
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

void mainloop() {
  while (true) {
    if (vsync_happened) {
      vsync_happened = false;
      uint16_t keys = ~KEYINPUT;
      if (keys & 1) printf("a\n");
      if (keys & 2) printf("b\n");
      if (keys & 4) printf("select\n");
      if (keys & 8) printf("start\n");
      if (keys & 16) printf("right\n");
      if (keys & 32) printf("left\n");
      if (keys & 64) printf("up\n");
      if (keys & 128) printf("down\n");
      if (keys & 256) printf("R\n");
      if (keys & 512) printf("L\n");
    }
  }
}
