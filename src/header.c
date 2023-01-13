#include <stdint.h>

struct GBACartridge {
	uint8_t logo[156];
	char title[12];
	uint32_t id;
	uint16_t maker;
	uint8_t type;
	uint8_t unit;
	uint8_t device;
	uint8_t reserved[7];
	uint8_t version;
	uint8_t checksum;
	// And ROM data...
};

struct GBACartridge header __attribute__ ((section(".entry.header"))) = {
  .title = "Bruh",
  .id = 0x96
};
