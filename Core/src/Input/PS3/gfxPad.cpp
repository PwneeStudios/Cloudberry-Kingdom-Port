/* SCE CONFIDENTIAL
 * PlayStation(R)3 Programmer Tool Runtime Library 430.001
 *                Copyright (C) 2010 Sony Computer Entertainment Inc.
 *                                               All Rights Reserved.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/process.h>
#include <sys/spu_initialize.h>
#include <sys/paths.h>

//#include <PSGL/psgl.h>
//#include <PSGL/psglu.h>
#include <cell/pad/libpad.h>      /* USB Gamepad Library */
#include <cell/pad/error.h>

#define CELL_USBPAD_AUTO_PARSE


static CellPadInfo2 PadInfo;/* connection PadInformation buffer */
static CellPadData  PadData[CELL_PAD_MAX_PORT_NUM];/*Gamapad data buffer */
static CellPadData  PadData2;

uint8_t old_status[CELL_PAD_MAX_PORT_NUM];

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void gfxInitPad(void)
{
	int ret = cellPadInit (CELL_PAD_MAX_PORT_NUM);
	if(ret != CELL_OK && ret != CELL_PAD_ERROR_ALREADY_INITIALIZED) 
		{
        printf ("Initialize error %d\n", ret);
        while (1);
		}

    for (int i = 0; i < CELL_PAD_MAX_PORT_NUM; i++) 
	{
        old_status[i] = 0;
    }

}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void gfxPadRead(void)
{
	int32_t ret = 0;

	ret = cellPadGetInfo2 (&PadInfo);
	if(ret)
	{
		printf ("Error%d : cellPadGetPadInfo\n", ret);
	}

	for (int i = 0; i < CELL_PAD_MAX_PORT_NUM; i++) 
	{
		//detect new pad connection
		if(PadInfo.port_status[i] != 0) 
		{
			if(old_status[i]==0) 
			{
            printf ("New gamepad %d is connected\n",i);

			}
		}

	#ifdef CELL_USBPAD_AUTO_PARSE
		ret = cellPadGetData(i, &PadData2);
		
		//if (ret == CELL_USBPAD_UNSUPPORT)
		//	ret = cellPadGetRawData (i, &PadData2);
	    #else
		ret = cellPadGetData(i, &PadData2);
		#endif

		if (PadData2.len!=0)
		{
			memcpy(&PadData[i],&PadData2,sizeof(CellPadData));

//			printf ("Pad[%d] data =", i);
//			for (int j = 0; j < 8; j++)
//			{    
//				printf (" %2.2x", PadData[i].button[j]);
//			}
//			printf ("\n");
		}

	old_status[i] = PadInfo.port_status[i];
	}

}
//-----------------------------------------------------------------------------

void gfxPadEnd(void)
{
	cellPadEnd();
}

bool gfxPadConnected(int pad)
{
	if(PadInfo.port_status[pad] & CELL_PAD_STATUS_CONNECTED)
		return true;

	return false;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool gfxStartDown(int pad)
{

	if(PadData[pad].button[2]&CELL_PAD_CTRL_START)
		{
		return true;
		}

	return false;
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool gfxSelectDown(int pad)
{

	if(PadData[pad].button[2]&CELL_PAD_CTRL_SELECT)
		{
		return true;
		}

	return false;
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool gfxL1Down(int pad)
{

	if(PadData[pad].button[3]&0x04)
		{
		return true;
		}

	return false;
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool gfxL2Down(int pad)
{

	if(PadData[pad].button[3]&0x01)
		{
		return true;
		}

	return false;
}

bool gfxL3Down(int pad)
{

	if(PadData[pad].button[CELL_PAD_BTN_OFFSET_DIGITAL1] & CELL_PAD_CTRL_L3)
		return true;

	return false;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool gfxR1Down(int pad)
{

	if(PadData[pad].button[3]&0x08)
		{
		return true;
		}

	return false;
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool gfxR2Down(int pad)
{

	if(PadData[pad].button[3]&0x02)
		{
		return true;
		}

	return false;
}

bool gfxR3Down(int pad)
{

	if(PadData[pad].button[CELL_PAD_BTN_OFFSET_DIGITAL1] & CELL_PAD_CTRL_R3)
		return true;

	return false;
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool gfxDpadUp(int pad)
{

	if(PadData[pad].button[2]&0x10)
		{
		return true;
		}

	return false;
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool gfxDpadDown(int pad)
{

	if(PadData[pad].button[2]&0x40)
		{
		return true;
		}

	return false;
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool gfxDpadLeft(int pad)
{

	if(PadData[pad].button[2]&0x80)
		{
		return true;
		}

	return false;
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool gfxDpadRight(int pad)
{

	if(PadData[pad].button[2]&0x20)
		{
		return true;
		}

	return false;
}

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool gfxDpadTri(int pad)
{
	if(PadData[pad].button[3]&0x10)
		{
		return true;
		}

	return false;

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool gfxDpadCross(int pad)
{
	if(PadData[pad].button[3]&0x40)
		{
		return true;
		}

	return false;
}
//-----------------------------------------------------------------------------
bool gfxDpadSquare(int pad)
{
	if(PadData[pad].button[3]&0x80)
		{
		return true;
		}

	return false;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool gfxDpadCircle(int pad)
{
	if(PadData[pad].button[3]&0x20)
		{
		return true;
		}

	return false;
}
//-----------------------------------------------------------------------------

float gfxL2Pressure(int pad)
{
	return static_cast< float >( PadData[ pad ].button[ CELL_PAD_BTN_OFFSET_PRESS_L2 ] ) / 255.f;
}

float gfxR2Pressure(int pad)
{
	return static_cast< float >( PadData[ pad ].button[ CELL_PAD_BTN_OFFSET_PRESS_R2 ] ) / 255.f;
}

void gfxLeftStick(int pad, float &x, float &y)
{
	int xVal = PadData[ pad ].button[ CELL_PAD_BTN_OFFSET_ANALOG_LEFT_X ];
	int yVal = PadData[ pad ].button[ CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y ];

	x = ( static_cast< float >( xVal ) - 127.5f ) / 127.5f;
	y = ( 127.5f - static_cast< float >( yVal ) ) / 127.5f;
}

void gfxRightStick(int pad, float &x, float &y)
{
	int xVal = PadData[ pad ].button[ CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_X ];
	int yVal = PadData[ pad ].button[ CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_Y ];

	x = ( static_cast< float >( xVal ) - 127.5f ) / 127.5f;
	y = ( 127.5f - static_cast< float >( yVal ) ) / 127.5f;
}
