/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef EXFLASH_H
#define EXFLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct {

	enum {
		UNKNOWN_EXFLASH = 0,

		W25Q128,
		MX25L25645G,
	} type;

	struct {
		uint32_t page;
		uint32_t sector;    // or subsector
		uint32_t block;     // or sector
		uint32_t total;
	} size;

} exflash_info_t;

extern exflash_info_t exflash_info;

uint8_t exflash_init(void);

#ifdef __cplusplus
}
#endif

#endif /* EXFLASH_H */
