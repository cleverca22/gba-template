#include <stdbool.h>
#include <stdint.h>

#define REG_MGBA_ENABLE         (*(volatile uint16_t*)0x04FFF780)
#define REG_MGBA_FLAGS          (*(volatile uint16_t*)0x04FFF700)
#define MGBA_LOG_OUT            ((char*)0x04FFF600)

bool logInitMgba(void) {
  REG_MGBA_ENABLE = 0xC0DE;

  return REG_MGBA_ENABLE == 0x1DEA;
}

void logOutputMgba(uint8_t level, const char *message) {
  for (int i = 0; message[i] && i < 256; i++) {
    MGBA_LOG_OUT[i] = message[i];
  }

  // FIXME: What if invalid level? Reject? Default to TRACE?
  REG_MGBA_FLAGS = (level - 1) | 0x100;
}

