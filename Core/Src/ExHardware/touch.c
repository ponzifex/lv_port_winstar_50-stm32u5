#include "touch.h"
#include "ltdc.h"

typedef enum {
	ILI2130,

	UNKNOWN_CTP,
} CTP_Driver;

static Touch_Type touch_type = NTP;
static CTP_Driver ctp_driver = UNKNOWN_CTP;

void CTP_reset(void);
void CTPDriver_detect(void);

void touch_init(void)
{
	touch_type = TOUCH_TYPE;
	CTP_reset();
	CTPDriver_detect();
}

bool touch_detect(int32_t *x, int32_t *y)
{
	switch (touch_type)
	{
	//====================================================================//
	case RTP:
		break;
	//====================================================================//
	case CTP:

		if (ctp_driver == UNKNOWN_CTP)
		{
			CTPDriver_detect();
		}

		if (ctp_driver == ILI2130)
		{
			uint8_t Buf[64];
			uint32_t sx, sy;

			if (HAL_I2C_Mem_Read(&hi2c3, 0x82, 0x10, I2C_MEMADD_SIZE_8BIT, &Buf[0], 64, 10) == HAL_OK)
			{
				if ( (Buf[0] == 0x48)  &&
					 (Buf[1] &  0x40)  &&   // Tip switch
					!(Buf[1] &  0x3F))      // Point ID = 0
				{
					sx = (Buf[3] << 8) | Buf[2];
					sy = (Buf[5] << 8) | Buf[4];

					*x = (sx * DISPLAY_WIDTH)  / 0x4000;
					*y = (sy * DISPLAY_HEIGHT) / 0x4000;

					return true;
				}
			}
			else
			{
//					HAL_I2C_Mem_Read(&hi2c3, 0x82, 0x31, I2C_MEMADD_SIZE_8BIT, &Buf[0], 10, 10);

				HAL_I2C_DeInit(&hi2c3);
				HAL_I2C_Init(&hi2c3);

				CTP_reset();
				HAL_Delay(980);
			}
		}

		break;
	//====================================================================//
	default:
		break;
	//====================================================================//
	}

	return false;
}

void CTP_reset(void)
{
	HAL_GPIO_WritePin(CTP_RST_GPIO_PORT, CTP_RST_GPIO_PIN, GPIO_PIN_RESET);   // CTP reset pin set low (active)
	HAL_Delay(20);
	HAL_GPIO_WritePin(CTP_RST_GPIO_PORT, CTP_RST_GPIO_PIN, GPIO_PIN_SET);     // CTP reset pin set high (inactive)
	HAL_Delay(20);
}

void CTPDriver_detect(void)
{
	uint8_t Buf[64];

	if (HAL_I2C_Mem_Read(&hi2c3, 0x82, 0x10, I2C_MEMADD_SIZE_8BIT, &Buf[0], 64, 10) == HAL_OK)
	{
		ctp_driver = ILI2130;
	}
}
