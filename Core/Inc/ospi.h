/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OSPI_H
#define OSPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/* Type define ------------------------------------------------------------------*/
typedef uint8_t                           OSPI_Status;

/* Exported constants --------------------------------------------------------*/
/* OSPI Error codes */
#define OSPI_OK                           ((OSPI_Status)0x00)
#define OSPI_ERROR                        ((OSPI_Status)0x01)
#define OSPI_BUSY                         ((OSPI_Status)0x02)
#define OSPI_NOT_SUPPORTED                ((OSPI_Status)0x04)
#define OSPI_SUSPENDED                    ((OSPI_Status)0x08)
#define OSPI_UNKNOWN_EXFLASH              ((OSPI_Status)0x10)

/* Exported types ------------------------------------------------------------*/
typedef struct {
  uint32_t FlashSize;
  uint32_t EraseSectorSize;
  uint32_t EraseSectorsNumber;
  uint32_t ProgPageSize;
  uint32_t ProgPagesNumber;
} OSPI_Info;

/* Exported functions --------------------------------------------------------*/
OSPI_Status OSPI_Init(void);
OSPI_Status OSPI_DeInit(void);

OSPI_Status OSPI_FastRead(uint8_t *pData, uint32_t ReadAddr, uint32_t Size);
OSPI_Status OSPI_Write(uint8_t *pData, uint32_t WriteAddr, uint32_t Size);

OSPI_Status OSPI_EraseSector(uint32_t EraseAddr);
OSPI_Status OSPI_EraseBlock(uint32_t EraseAddr);
OSPI_Status OSPI_EraseChip(void);

OSPI_Status OSPI_EnableMemoryMappedMode(void);

OSPI_Status OSPI_Reset(void);

OSPI_Status OSPI_GetStatus(void);                                               // (no check)
OSPI_Status OSPI_GetInfo(OSPI_Info *pInfo);
OSPI_Status OSPI_ReadID(uint8_t *pID);

OSPI_Status OSPI_IsEnterByteMode(void);                                         // (no check)

OSPI_Status OSPI_EnterQPIMode(void);                                            // (no check)
OSPI_Status OSPI_ExitQPIMode(void);                                             // (no check)

OSPI_Status OSPI_ReadStatusRegister(uint8_t *pReg);
OSPI_Status OSPI_WriteStatusRegister(uint8_t *pReg);                            // (no check)
OSPI_Status OSPI_CheckStatusRegister(void);

#ifdef __cplusplus
}
#endif

#endif /* OSPI_H */
