#include <stdbool.h>
#include <stdint.h>

#define REG_MGBA_ENABLE         (*(volatile uint16_t*)0x04FFF780)
#define REG_MGBA_FLAGS          (*(volatile uint16_t*)0x04FFF700)
#define MGBA_LOG_OUT            ((char*)0x04FFF600)

#if 0
bool logInitMgba(void) {
  REG_MGBA_ENABLE = 0xC0DE;

  return REG_MGBA_ENABLE == 0x1DEA;
}
#endif

void logOutputMgba(uint8_t level, const char *message) {
  for (int i = 0; message[i] && i < 256; i++) {
    MGBA_LOG_OUT[i] = message[i];
  }

  // FIXME: What if invalid level? Reject? Default to TRACE?
  REG_MGBA_FLAGS = (level - 1) | 0x100;
}

int puts(const char *s) {
  logOutputMgba(3, s);
}

static char buffer[101];
static int buffer_used = 0;

int putchar(int c) {
  buffer[buffer_used++] = c;
  if ((buffer_used == 100) || (c == '\n')) {
    buffer[buffer_used++] = 0;
    logOutputMgba(3, buffer);
    buffer_used = 0;
  }
}
