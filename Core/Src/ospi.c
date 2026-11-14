/* Includes ------------------------------------------------------------------*/
#include "ospi.h"
#include "exflash.h"

/* Private constants --------------------------------------------------------*/
#define VOID_CMD_PARAM                     UINT32_MAX

/*!<nCS stay high for at least N clock cycle between commands, N is ChipSelectHighTime*/
#define HAL_OSPI_CS_HIGH_TIME_N_CYCLE(N)   (((N) - 1) << OCTOSPI_DCR1_CSHT_Pos)

/* Exported variables --------------------------------------------------------*/
extern OSPI_HandleTypeDef hospi1;

/* Private variables ---------------------------------------------------------*/
static OSPI_HandleTypeDef hospi_tmp;

/* Private functions ---------------------------------------------------------*/
static OSPI_Status OSPI_WriteEnable(void);

static OSPI_Status OSPI_AutoPolling(OSPI_AutoPollingTypeDef *sConfig, uint32_t Timeout);
static OSPI_Status OSPI_AutoPollingMemReady(uint32_t Timeout);
static OSPI_Status OSPI_AutoPollingWriteEnable(uint32_t Timeout);

#if 0
static OSPI_Status OSPI_DummyCyclesCfg(void);
#endif

static inline void OSPI_SetCommand(OSPI_RegularCmdTypeDef *sCommand,
	uint32_t InstructionMode, uint32_t Instruction, uint32_t InstructionSize,
	uint32_t AddressMode, uint32_t Address, uint32_t AddressSize,
	uint32_t AlternateBytesMode, uint32_t AlternateBytes, uint32_t AlternateBytesSize,
	uint32_t DataMode, uint32_t NbData,
	uint32_t DummyCycles);
static inline void OSPI_SetCommand_Instruction   (OSPI_RegularCmdTypeDef *sCommand, uint32_t Instruction);
static inline void OSPI_SetCommand_Address       (OSPI_RegularCmdTypeDef *sCommand, uint32_t Address);
static inline void OSPI_SetCommand_AlternateBytes(OSPI_RegularCmdTypeDef *sCommand, uint32_t AlternateBytes);
static inline void OSPI_SetCommand_NbData        (OSPI_RegularCmdTypeDef *sCommand, uint32_t NbData);

/* Exported functions --------------------------------------------------------*/
/**
  * @brief  Initializes the OSPI interface.
  * @param  None
  * @retval Result status
  */
OSPI_Status OSPI_Init(void)
{
	OSPI_Status status;

	if ((status = OSPI_DeInit()) != OSPI_OK)
	{
		return status;
	}

	hospi1.Instance = hospi_tmp.Instance;
	hospi1.Init = hospi_tmp.Init;

	if (HAL_OSPI_Init(&hospi1) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	OSPIM_CfgTypeDef sOspiManagerCfg = { 0 };

	sOspiManagerCfg.ClkPort = 1;
	sOspiManagerCfg.NCSPort = 1;
	sOspiManagerCfg.IOLowPort = HAL_OSPIM_IOPORT_1_LOW;

	if (HAL_OSPIM_Config(&hospi1, &sOspiManagerCfg, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	HAL_OSPI_DLYB_CfgTypeDef HAL_OSPI_DLYB_Cfg_Struct = {0};

	HAL_OSPI_DLYB_Cfg_Struct.Units = 0;
	HAL_OSPI_DLYB_Cfg_Struct.PhaseSel = 0;

	if (HAL_OSPI_DLYB_SetConfig(&hospi1, &HAL_OSPI_DLYB_Cfg_Struct) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	return OSPI_OK;
}

/**
  * @brief  De-Initializes the OSPI interface.
  * @param  None
  * @retval Result status
  */
OSPI_Status OSPI_DeInit(void)
{
	hospi_tmp = hospi1;

	if (HAL_OSPI_DeInit(&hospi1) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	return OSPI_OK;
}

/**
  * @brief  Reads an amount of data from the OSPI memory.
  * @param  pData: Pointer to data to be read
  * @param  ReadAddr: Read start address
  * @param  Size: Size of data to read
  * @retval Result status
  */
OSPI_Status OSPI_FastRead(uint8_t *pData, uint32_t ReadAddr, uint32_t Size)
{
	OSPI_RegularCmdTypeDef sCommand;

	switch (exflash_info.type)
	{
	case W25Q128:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_1_LINE, 0x6B, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_1_LINE, ReadAddr, HAL_OSPI_ADDRESS_24_BITS,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_4_LINES, Size,
			8
		);

		break;

	case MX25L25645G:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_4_LINES, 0xEB, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_4_LINES, ReadAddr, HAL_OSPI_ADDRESS_32_BITS,
			HAL_OSPI_ALTERNATE_BYTES_4_LINES, 0x00, HAL_OSPI_ALTERNATE_BYTES_8_BITS,
			HAL_OSPI_DATA_4_LINES, Size,
			4
		);

		break;

	default:
		return OSPI_UNKNOWN_EXFLASH;
	}

	/* Configure the command */
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	/* Set S# timing for read command */
	MODIFY_REG(hospi1.Instance->DCR1, OCTOSPI_DCR1_CSHT, HAL_OSPI_CS_HIGH_TIME_N_CYCLE(3));

	/* Reception of the data */
	if (HAL_OSPI_Receive(&hospi1, pData, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	/* Restore S# timing for nonRead commands */
	MODIFY_REG(hospi1.Instance->DCR1, OCTOSPI_DCR1_CSHT, HAL_OSPI_CS_HIGH_TIME_N_CYCLE(6));

	return OSPI_OK;
}

/**
  * @brief  Writes an amount of data to the OSPI memory.
  * @param  pData: Pointer to data to be written
  * @param  WriteAddr: Write start address
  * @param  Size: Size of data to write
  * @retval Result status
  */
OSPI_Status OSPI_Write(uint8_t *pData, uint32_t WriteAddr, uint32_t Size)
{
	OSPI_Status status;
	OSPI_RegularCmdTypeDef sCommand;
	uint32_t current_size,
			 current_addr,
			 end_addr;

	/* Calculation of the size between the write address and the end of the page */
	current_size = exflash_info.size.page - (WriteAddr % exflash_info.size.page);

	/* Check if the size of the data is less than the remaining place in the page */
	if (Size < current_size)
	{
		current_size = Size;
	}

	/* Initialize the address variables */
	current_addr = WriteAddr;
	end_addr = WriteAddr + Size;

	switch (exflash_info.type)
	{
	case W25Q128:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_1_LINE, 0x32, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_1_LINE, VOID_CMD_PARAM, HAL_OSPI_ADDRESS_24_BITS,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_4_LINES, VOID_CMD_PARAM,
			0
		);

		break;

	case MX25L25645G:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_4_LINES, 0x02, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_4_LINES, VOID_CMD_PARAM, HAL_OSPI_ADDRESS_32_BITS,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_4_LINES, VOID_CMD_PARAM,
			0
		);

		break;

	default:
		return OSPI_UNKNOWN_EXFLASH;
	}

	/* Perform the write page by page */
	do
	{
		OSPI_SetCommand_Address(&sCommand, current_addr);
		OSPI_SetCommand_NbData(&sCommand, current_size);

		/* Enable write operations */
		if ((status = OSPI_WriteEnable()) != OSPI_OK)
		{
			return status;
		}

		/* Configure the command */
		if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		{
			return OSPI_ERROR;
		}

		/* Transmission of the data */
		if (HAL_OSPI_Transmit(&hospi1, pData, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		{
			return OSPI_ERROR;
		}

		/* Configure automatic polling mode to wait for end of program */
		if ((status = OSPI_AutoPollingMemReady(HAL_OSPI_TIMEOUT_DEFAULT_VALUE)) != OSPI_OK)
		{
			return status;
		}

		/* Update the address and size variables for next page programming */
		current_addr += current_size;
		pData += current_size;
		current_size = ((current_addr + exflash_info.size.page) > end_addr)
					   ? (end_addr - current_addr)
					   : exflash_info.size.page;
	} while (current_addr < end_addr);

  return OSPI_OK;
}

/**
  * @brief  Erases the specified sector of the OSPI memory.
  * @param  EraseAddr: Erase start address (based on Sector)
  * @retval Result status
  */
OSPI_Status OSPI_EraseSector(uint32_t EraseAddr)
{
	OSPI_Status status;
	OSPI_RegularCmdTypeDef sCommand;
	uint32_t timeout;

	switch (exflash_info.type)
	{
	case W25Q128:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_1_LINE, 0x20, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_1_LINE, EraseAddr, HAL_OSPI_ADDRESS_24_BITS,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_NONE, VOID_CMD_PARAM,
			0
		);

		timeout  =  400;

		break;

	case MX25L25645G:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_4_LINES, 0x21, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_4_LINES, EraseAddr, HAL_OSPI_ADDRESS_32_BITS,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_NONE, VOID_CMD_PARAM,
			0
		);

		timeout  =  400;

		break;

	default:
		return OSPI_UNKNOWN_EXFLASH;
	}

	/* Enable write operations */
	if ((status = OSPI_WriteEnable()) != OSPI_OK)
	{
		return status;
	}

	/* Configure the command */
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	/* Configure automatic polling mode to wait for end of erase */
	if ((status = OSPI_AutoPollingMemReady(timeout)) != OSPI_OK)
	{
		return status;
	}

	return OSPI_OK;
}

/**
  * @brief  Erases the specified block of the OSPI memory.
  * @param  EraseAddr: Erase start address (based on Block)
  * @retval Result status
  */
OSPI_Status OSPI_EraseBlock(uint32_t EraseAddr)
{
	OSPI_Status status;
	OSPI_RegularCmdTypeDef sCommand;
	uint32_t timeout;

	switch (exflash_info.type)
	{
	case W25Q128:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_1_LINE, 0xD8, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_1_LINE, EraseAddr, HAL_OSPI_ADDRESS_24_BITS,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_NONE, VOID_CMD_PARAM,
			0
		);

		timeout  =  3000;

		break;

	case MX25L25645G:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_4_LINES, 0xDC, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_4_LINES, EraseAddr, HAL_OSPI_ADDRESS_32_BITS,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_NONE, VOID_CMD_PARAM,
			0
		);

		timeout  =  2000;

		break;

	default:
		return OSPI_UNKNOWN_EXFLASH;
	}

	/* Enable write operations */
	if ((status = OSPI_WriteEnable()) != OSPI_OK)
	{
		return status;
	}

	/* Configure the command */
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	/* Configure automatic polling mode to wait for end of erase */
	if ((status = OSPI_AutoPollingMemReady(timeout)) != OSPI_OK)
	{
		return status;
	}

	return OSPI_OK;
}

/**
  * @brief  Erases the entire OSPI memory.
  * @param  None
  * @retval Result status
  */
OSPI_Status OSPI_EraseChip(void)
{
	OSPI_Status status;
	OSPI_RegularCmdTypeDef sCommand;
	uint32_t timeout;

	switch (exflash_info.type)
	{
	case W25Q128:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_1_LINE, 0xC7, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_NONE, VOID_CMD_PARAM,
			0
		);

		timeout  =  250000;

		break;

	case MX25L25645G:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_4_LINES, 0xC7, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_NONE, VOID_CMD_PARAM,
			0
		);

		timeout  =  220000;

		break;

	default:
		return OSPI_UNKNOWN_EXFLASH;
	}

	/* Enable write operations */
	if ((status = OSPI_WriteEnable()) != OSPI_OK)
	{
		return status;
	}

	/* Configure the command */
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	/* Configure automatic polling mode to wait for end of erase */
	if ((status = OSPI_AutoPollingMemReady(timeout)) != OSPI_OK)
	{
		return status;
	}

	return OSPI_OK;
}

/**
  * @brief  Configure the OSPI in memory-mapped mode.
  * @param  None
  * @retval Result status
  */
OSPI_Status OSPI_EnableMemoryMappedMode(void)
{
	OSPI_RegularCmdTypeDef sCommand;

	switch (exflash_info.type)
	{
	case W25Q128:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_1_LINE, 0x6B, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_1_LINE, VOID_CMD_PARAM, HAL_OSPI_ADDRESS_24_BITS,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_4_LINES, VOID_CMD_PARAM,
			8
		);

		break;

	case MX25L25645G:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_4_LINES, 0xEB, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_4_LINES, VOID_CMD_PARAM, HAL_OSPI_ADDRESS_32_BITS,
			HAL_OSPI_ALTERNATE_BYTES_4_LINES, 0x00, HAL_OSPI_ALTERNATE_BYTES_8_BITS,
			HAL_OSPI_DATA_4_LINES, VOID_CMD_PARAM,
			4
		);

		break;

	default:
		return OSPI_UNKNOWN_EXFLASH;
	}

	/* Configure the command */
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	OSPI_MemoryMappedTypeDef sMemMappedCfg;

	/* Configure the memory mapped mode */
	sMemMappedCfg.TimeOutActivation  =  HAL_OSPI_TIMEOUT_COUNTER_DISABLE;
	sMemMappedCfg.TimeOutPeriod      =  0;

	if (HAL_OSPI_MemoryMapped(&hospi1, &sMemMappedCfg) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	return OSPI_OK;
}

/**
  * @brief  This function reset the OSPI memory.
  * @param  None
  * @retval Result status
  */
OSPI_Status OSPI_Reset(void)
{
	OSPI_Status status;
	OSPI_RegularCmdTypeDef sCommand;

	switch (exflash_info.type)
	{
	case W25Q128:
	case MX25L25645G:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_1_LINE, 0x66, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_NONE, VOID_CMD_PARAM,
			0
		);

		break;

	default:
		return OSPI_UNKNOWN_EXFLASH;
	}

	/* Configure the command */
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	switch (exflash_info.type)
	{
	case W25Q128:
	case MX25L25645G:

		OSPI_SetCommand_Instruction(&sCommand, 0x99);

		break;

	default:
		return OSPI_UNKNOWN_EXFLASH;
	}

	/* Configure the command */
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	/* Configure automatic polling mode to wait for end of program */
	if ((status = OSPI_AutoPollingMemReady(HAL_OSPI_TIMEOUT_DEFAULT_VALUE)) != OSPI_OK)
	{
		return status;
	}

	return OSPI_OK;
}

/**
  * @brief  Reads current status of the OSPI memory.
  * @param  None
  * @retval OSPI memory status
  */
OSPI_Status OSPI_GetStatus(void)
{
	OSPI_RegularCmdTypeDef sCommand;
	uint8_t reg;

	/* Initialize the read flag status register command */
	switch (exflash_info.type)
	{
	case W25Q128:
	case MX25L25645G:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_1_LINE, 0x70, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_1_LINE, 1,
			0
		);

		break;

	default:
		return OSPI_UNKNOWN_EXFLASH;
	}

	/* Configure the command */
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	/* Reception of the data */
	if (HAL_OSPI_Receive(&hospi1, &reg, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	/* Check the value of the register */
	if ((reg & (0x02 | 0x08 | 0x10 | 0x20)) != 0)
	{
		return OSPI_ERROR;
	}
	else if ((reg & (0x04 | 0x40)) != 0)
	{
		return OSPI_SUSPENDED;
	}
	else if ((reg & 0x80) != 0)
	{
		return OSPI_OK;
	}
	else
	{
		return OSPI_BUSY;
	}
}

/**
  * @brief  Return the configuration of the OSPI memory.
  * @param  pInfo: Pointer on the configuration structure
  * @retval Result status
  */
OSPI_Status OSPI_GetInfo(OSPI_Info *pInfo)
{
	/* Configure the structure with the memory configuration */
	pInfo->FlashSize           =  exflash_info.size.total;
	pInfo->EraseSectorSize     =  exflash_info.size.sector;
	pInfo->EraseSectorsNumber  =  (exflash_info.size.total / exflash_info.size.sector);
	pInfo->ProgPageSize        =  exflash_info.size.page;
	pInfo->ProgPagesNumber     =  (exflash_info.size.total / exflash_info.size.page);

	return OSPI_OK;
}

/**
  * @brief  Return the ID of the OSPI memory.
  * @param  pInfo: Pointer to ID to be read
  * @retval Result status
  */
OSPI_Status OSPI_ReadID(uint8_t *pID)
{
	OSPI_RegularCmdTypeDef sCommand;

	OSPI_SetCommand(&sCommand,
		HAL_OSPI_INSTRUCTION_1_LINE, 0x9F, HAL_OSPI_INSTRUCTION_8_BITS,
		HAL_OSPI_ADDRESS_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
		HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
		HAL_OSPI_DATA_1_LINE, 3,
		0
	);

	/* Configure the command */
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	/* Reception of the data */
	if (HAL_OSPI_Receive(&hospi1, pID, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	return OSPI_OK;
}

OSPI_Status OSPI_IsEnterByteMode(void)
{
	OSPI_RegularCmdTypeDef sCommand;

	switch (exflash_info.type)
	{
	case W25Q128:
		return OSPI_NOT_SUPPORTED;

	case MX25L25645G:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_4_LINES, 0xB7, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_NONE, VOID_CMD_PARAM,
			0
		);

		break;

	default:
		return OSPI_UNKNOWN_EXFLASH;
	}

	/* Configure the command */
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	return OSPI_OK;
}

OSPI_Status OSPI_EnterQPIMode(void)
{
	OSPI_RegularCmdTypeDef sCommand;

	switch (exflash_info.type)
	{
	case W25Q128:
		return OSPI_NOT_SUPPORTED;

	case MX25L25645G:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_1_LINE, 0x35, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_NONE, VOID_CMD_PARAM,
			0
		);

		break;

	default:
		return OSPI_UNKNOWN_EXFLASH;
	}

	/* Configure the command */
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	return OSPI_OK;
}

OSPI_Status OSPI_ExitQPIMode(void)
{
	OSPI_RegularCmdTypeDef sCommand;

	switch (exflash_info.type)
	{
	case W25Q128:
		return OSPI_NOT_SUPPORTED;

	case MX25L25645G:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_4_LINES, 0xF5, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_NONE, VOID_CMD_PARAM,
			0
		);

		break;

	default:
		return OSPI_UNKNOWN_EXFLASH;
	}

	/* Configure the command */
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	return OSPI_OK;
}

OSPI_Status OSPI_ReadStatusRegister(uint8_t *pReg)
{
	OSPI_RegularCmdTypeDef sCommand;

	uint32_t read_status_reg_instruction[3];
	uint8_t  read_status_reg_instruction_n;
	uint8_t  read_status_reg_i;

	switch (exflash_info.type)
	{
	case W25Q128:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_1_LINE, VOID_CMD_PARAM, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_1_LINE, 1,
			0
		);

		read_status_reg_instruction_n = 3;

		read_status_reg_instruction[0] = 0x05;
		read_status_reg_instruction[1] = 0x35;
		read_status_reg_instruction[2] = 0x15;

		break;

	case MX25L25645G:  /* Instruction: 05h */
		return OSPI_NOT_SUPPORTED;

	default:
		return OSPI_UNKNOWN_EXFLASH;
	}

	for (read_status_reg_i = 0;
		 read_status_reg_i < read_status_reg_instruction_n;
		 read_status_reg_i ++)
	{
		OSPI_SetCommand_Instruction(&sCommand, read_status_reg_instruction[read_status_reg_i]);

		/* Configure the command */
		if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		{
			return OSPI_ERROR;
		}

		/* Reception of the data */
		if (HAL_OSPI_Receive(&hospi1, &pReg[read_status_reg_i], 100) != HAL_OK)
		{
			return OSPI_ERROR;
		}
	}

	return OSPI_OK;
}

OSPI_Status OSPI_WriteStatusRegister(uint8_t *pReg)
{
	OSPI_Status status;
	OSPI_RegularCmdTypeDef sCommand;

	uint32_t write_status_reg_instruction[3];
	uint8_t  write_status_reg_instruction_n;
	uint8_t  write_status_reg_i;

	switch (exflash_info.type)
	{
	case W25Q128:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_1_LINE, VOID_CMD_PARAM, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_1_LINE, 1,
			0
		);

		write_status_reg_instruction_n = 3;

		write_status_reg_instruction[0] = 0x01;
		write_status_reg_instruction[1] = 0x31;
		write_status_reg_instruction[2] = 0x11;

		break;

	case MX25L25645G:  /* Instruction: 01h */
		return OSPI_NOT_SUPPORTED;

	default:
		return OSPI_UNKNOWN_EXFLASH;
	}

	for (write_status_reg_i = 0;
		 write_status_reg_i < write_status_reg_instruction_n;
		 write_status_reg_i ++)
	{
		/* Enable write operations */
		if ((status = OSPI_WriteEnable()) != OSPI_OK)
		{
			return status;
		}

		OSPI_SetCommand_Instruction(&sCommand, write_status_reg_instruction[write_status_reg_i]);

		/* Configure the command */
		if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		{
			return OSPI_ERROR;
		}

		/* Transmission of the data */
		if (HAL_OSPI_Transmit(&hospi1, &pReg[write_status_reg_i], 100) != HAL_OK)
		{
			return OSPI_ERROR;
		}

		/* Configure automatic polling mode to wait for end of program */
		if ((status = OSPI_AutoPollingMemReady(HAL_OSPI_TIMEOUT_DEFAULT_VALUE)) != OSPI_OK)
		{
			return status;
		}
	}

	return OSPI_OK;
}

OSPI_Status OSPI_CheckStatusRegister(void)
{
	OSPI_Status status;

	union {

		uint8_t buffer[3];

		struct {
			// Bit 0 ~ 7
			uint8_t BUSY :1;
			uint8_t WEL  :1;
			uint8_t BP0  :1;
			uint8_t BP1  :1;
			uint8_t BP2  :1;
			uint8_t TB   :1;
			uint8_t SEC  :1;
			uint8_t SRP  :1;

			// Bit 8 ~ 15
			uint8_t SRL  :1;
			uint8_t QE   :1;
			uint8_t      :1;
			uint8_t LB1  :1;
			uint8_t LB2  :1;
			uint8_t LB3  :1;
			uint8_t CMP  :1;
			uint8_t SUS  :1;

			// Bit 16 ~ 23
			uint8_t      :1;
			uint8_t      :1;
			uint8_t WPS  :1;
			uint8_t      :1;
			uint8_t      :1;
			uint8_t DR2  :1;
			uint8_t DR1  :1;
			uint8_t      :1;
		} status;

	} Register;

	if ((status = OSPI_ReadStatusRegister(Register.buffer)) != OSPI_OK)
	{
		return status;
	}

	if (Register.status.CMP == 1 ||
		Register.status.BP0 == 1 ||
		Register.status.BP1 == 1 ||
		Register.status.BP2 == 1)
	{
		Register.status.CMP = 0;
		Register.status.BP0 = 0;
		Register.status.BP1 = 0;
		Register.status.BP2 = 0;

		if ((status = OSPI_WriteStatusRegister(Register.buffer)) != OSPI_OK)
		{
			return status;
		}
	}

	if ((status = OSPI_ReadStatusRegister(Register.buffer)) != OSPI_OK)
	{
		return status;
	}

	return OSPI_OK;
}

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  This function send a write enable and wait it is effective.
  * @param  None
  * @retval Result status
  */
static OSPI_Status OSPI_WriteEnable(void)
{
	OSPI_Status status;
	OSPI_RegularCmdTypeDef sCommand;

	switch (exflash_info.type)
	{
	case W25Q128:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_1_LINE, 0x06, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_NONE, VOID_CMD_PARAM,
			0
		);

		break;

	case MX25L25645G:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_4_LINES, 0x06, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_NONE, VOID_CMD_PARAM,
			0
		);

		break;

	default:
		return OSPI_UNKNOWN_EXFLASH;
	}

	/* Configure the command */
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	if ((status = OSPI_AutoPollingWriteEnable(HAL_OSPI_TIMEOUT_DEFAULT_VALUE)) != OSPI_OK)
	{
		return status;
	}

	return OSPI_OK;
}

static OSPI_Status OSPI_AutoPolling(OSPI_AutoPollingTypeDef *sConfig, uint32_t Timeout)
{
	OSPI_RegularCmdTypeDef sCommand;

	switch (exflash_info.type)
	{
	case W25Q128:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_1_LINE, 0x05, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_1_LINE, 1,
			0
		);

		break;

	case MX25L25645G:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_4_LINES, 0x05, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_4_LINES, 1,
			0
		);

		break;

	default:
		return OSPI_UNKNOWN_EXFLASH;
	}

	/* Configure the command */
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	if (HAL_OSPI_AutoPolling(&hospi1, sConfig, Timeout) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	return OSPI_OK;
}

/**
  * @brief  This function read the SR of the memory and wait the EOP.
  * @param  Timeout
  * @retval Result status
  */
static OSPI_Status OSPI_AutoPollingMemReady(uint32_t Timeout)
{
	OSPI_Status status;
	OSPI_AutoPollingTypeDef sConfig;

	/* Configure automatic polling mode to wait for memory ready */
	sConfig.Match          =  0x00;
	sConfig.Mask           =  0x01;
	sConfig.MatchMode      =  HAL_OSPI_MATCH_MODE_AND;
	sConfig.AutomaticStop  =  HAL_OSPI_AUTOMATIC_STOP_ENABLE;
	sConfig.Interval       =  0x10;

	if ((status = OSPI_AutoPolling(&sConfig, Timeout)) != OSPI_OK)
	{
		return status;
	}

	return OSPI_OK;
}

static OSPI_Status OSPI_AutoPollingWriteEnable(uint32_t Timeout)
{
	OSPI_Status status;
	OSPI_AutoPollingTypeDef sConfig;

	/* Configure automatic polling mode to wait for write enabling */
	sConfig.Match          =  0x02;
	sConfig.Mask           =  0x02;
	sConfig.MatchMode      =  HAL_OSPI_MATCH_MODE_AND;
	sConfig.AutomaticStop  =  HAL_OSPI_AUTOMATIC_STOP_ENABLE;
	sConfig.Interval       =  0x10;

	if ((status = OSPI_AutoPolling(&sConfig, Timeout)) != OSPI_OK)
	{
		return status;
	}

	return OSPI_OK;
}

#if 0
/**
  * @brief  This function configure the dummy cycles on memory side.
  * @param  None
  * @retval Result status
  */
static OSPI_Status OSPI_DummyCyclesCfg(void)
{
	OSPI_Status status;
	OSPI_RegularCmdTypeDef sCommand;
	uint8_t reg;

	/* Initialize the read volatile configuration register command */
	switch (exflash_info.type)
	{
	case W25Q128:
	case MX25L25645G:

		OSPI_SetCommand(&sCommand,
			HAL_OSPI_INSTRUCTION_1_LINE, 0x85, HAL_OSPI_INSTRUCTION_8_BITS,
			HAL_OSPI_ADDRESS_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_ALTERNATE_BYTES_NONE, VOID_CMD_PARAM, VOID_CMD_PARAM,
			HAL_OSPI_DATA_1_LINE, 1,
			0
		);

		break;

	default:
		return OSPI_UNKNOWN_EXFLASH;
	}

	/* Configure the command */
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	/* Reception of the data */
	if (HAL_OSPI_Receive(&hospi1, &reg, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	/* Enable write operations */
	if ((status = OSPI_WriteEnable()) != OSPI_OK)
	{
		return status;
	}

	/* Initialize the write volatile configuration register command */
	switch (exflash_info.type)
	{
	case W25Q128:
	case MX25L25645G:

		OSPI_SetCommand_Instruction(&sCommand, 0x81);

		break;

	default:
		return OSPI_UNKNOWN_EXFLASH;
	}

	/* Update volatile configuration register (with new dummy cycles) */
	MODIFY_REG(reg, 0xF0, (10 << POSITION_VAL(0xF0)));

	/* Configure the command */
	if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	/* Transmission of the data */
	if (HAL_OSPI_Transmit(&hospi1, &reg, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return OSPI_ERROR;
	}

	return OSPI_OK;
}
#endif

static inline void OSPI_SetCommand(OSPI_RegularCmdTypeDef *sCommand,
	uint32_t InstructionMode, uint32_t Instruction, uint32_t InstructionSize,
	uint32_t AddressMode, uint32_t Address, uint32_t AddressSize,
	uint32_t AlternateBytesMode, uint32_t AlternateBytes, uint32_t AlternateBytesSize,
	uint32_t DataMode, uint32_t NbData,
	uint32_t DummyCycles)
{
	sCommand->InstructionMode          =  InstructionMode;
	if (sCommand->InstructionMode     !=  HAL_OSPI_INSTRUCTION_NONE)
	{
		sCommand->Instruction          =  Instruction;
		sCommand->InstructionSize      =  InstructionSize;
	}

	sCommand->AddressMode              =  AddressMode;
	if (sCommand->AddressMode         !=  HAL_OSPI_ADDRESS_NONE)
	{
		sCommand->Address              =  Address;
		sCommand->AddressSize          =  AddressSize;
	}

	sCommand->AlternateBytesMode       =  AlternateBytesMode;
	if (sCommand->AlternateBytesMode  !=  HAL_OSPI_ALTERNATE_BYTES_NONE)
	{
		sCommand->AlternateBytes       =  AlternateBytes;
		sCommand->AlternateBytesSize   =  AlternateBytesSize;
	}

	sCommand->DataMode                 =  DataMode;
	if (sCommand->DataMode            !=  HAL_OSPI_DATA_NONE)
	{
		sCommand->NbData               =  NbData;
	}

	sCommand->DummyCycles              =  DummyCycles;

	sCommand->OperationType            =  HAL_OSPI_OPTYPE_COMMON_CFG;
	sCommand->FlashId                  =  HAL_OSPI_FLASH_ID_1;
	sCommand->SIOOMode                 =  HAL_OSPI_SIOO_INST_EVERY_CMD;

	sCommand->InstructionDtrMode       =  HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	sCommand->AddressDtrMode           =  HAL_OSPI_ADDRESS_DTR_DISABLE;
	sCommand->AlternateBytesDtrMode    =  HAL_OSPI_ALTERNATE_BYTES_DTR_DISABLE;
	sCommand->DataDtrMode              =  HAL_OSPI_DATA_DTR_DISABLE;
	sCommand->DQSMode                  =  HAL_OSPI_DQS_DISABLE;
}

static inline void OSPI_SetCommand_Instruction(OSPI_RegularCmdTypeDef *sCommand, uint32_t Instruction)
{
	if (sCommand->InstructionMode     !=  HAL_OSPI_INSTRUCTION_NONE)
	{
		sCommand->Instruction          =  Instruction;
	}
}

static inline void OSPI_SetCommand_Address(OSPI_RegularCmdTypeDef *sCommand, uint32_t Address)
{
	if (sCommand->AddressMode         !=  HAL_OSPI_ADDRESS_NONE)
	{
		sCommand->Address              =  Address;
	}
}

static inline void OSPI_SetCommand_AlternateBytes(OSPI_RegularCmdTypeDef *sCommand, uint32_t AlternateBytes)
{
	if (sCommand->AlternateBytesMode  !=  HAL_OSPI_ALTERNATE_BYTES_NONE)
	{
		sCommand->AlternateBytes       =  AlternateBytes;
	}
}

static inline void OSPI_SetCommand_NbData(OSPI_RegularCmdTypeDef *sCommand, uint32_t NbData)
{
	if (sCommand->DataMode            !=  HAL_OSPI_DATA_NONE)
	{
		sCommand->NbData               =  NbData;
	}
}






