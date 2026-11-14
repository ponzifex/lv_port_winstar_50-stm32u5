#include "exFlash.h"
#include "ospi.h"
#include <string.h>

#define  K(N)     ((N) * 1024)
#define  M(N)     (K(N) * K(1))

exflash_info_t exflash_info = { 0 };

uint8_t exflash_init(void)
{
	uint8_t ID[3] = { 0 };

//	if (OSPI_Init() != OSPI_OK)
//	{
//		goto exflash_init_fail;
//	}

	if (OSPI_ReadID(ID) != OSPI_OK)
	{
		goto exflash_init_fail;
	}

	if (memcmp(ID, "\xEF\x40\x18", 3) == 0)
	{
		exflash_info.type         =  W25Q128;
		exflash_info.size.page    =  256;
		exflash_info.size.sector  =  K(4);
		exflash_info.size.block   =  K(64);
		exflash_info.size.total   =  M(16);

		if (OSPI_Reset() != OSPI_OK)
		{
			goto exflash_init_fail;
		}

		if (OSPI_CheckStatusRegister() != OSPI_OK)
		{
			goto exflash_init_fail;
		}

		if (OSPI_EnableMemoryMappedMode() != OSPI_OK)
		{
			goto exflash_init_fail;
		}
	}
	else if (memcmp(ID, "\xC2\x20\x19", 3) == 0)
	{
		exflash_info.type         =  MX25L25645G;
		exflash_info.size.page    =  256;
		exflash_info.size.sector  =  K(4);
		exflash_info.size.block   =  K(64);
		exflash_info.size.total   =  M(32);

		if (OSPI_Reset() != OSPI_OK)
		{
			goto exflash_init_fail;
		}

		if (OSPI_EnterQPIMode() != OSPI_OK)
		{
			goto exflash_init_fail;
		}

		if (OSPI_IsEnterByteMode() != OSPI_OK)
		{
			goto exflash_init_fail;
		}

		if (OSPI_EnableMemoryMappedMode() != OSPI_OK)
		{
			goto exflash_init_fail;
		}
	}
	else
	{
		exflash_info.type         =  UNKNOWN_EXFLASH;
	}

	return 1;

exflash_init_fail:

	return 0;
}
