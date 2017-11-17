/*
 * vga_textmode.c
 *
 *  Created on: 6 Nov 2017
 *      Author: Jon Ayerdi
 */

#include "vga_textmode.h"

#include "vga/vga_modes.h"
#include "vga/display_ctrl.h"
#include "vga/font8x8.h"
#include <string.h>

static DisplayCtrl display;
static u32 vgaFrames[DISPLAY_NUM_FRAMES][VGA_RESOLUTION_X*VGA_RESOLUTION_Y];
static u32 vgaTempFrame[VGA_RESOLUTION_X*VGA_RESOLUTION_Y];
static u8 currentFrame = 0;

static u32 _cursorX = 0;
static u32 _cursorY = 0;

static u32 _color = 0x00DDDDDD;
static u32 _background = 0x00000066;

int vga_textmode_init()
{
	u32 *vgaPtr[DISPLAY_NUM_FRAMES];
	for (int i = 0; i < DISPLAY_NUM_FRAMES; i++)
		vgaPtr[i] = vgaFrames[i];
	int status = DisplayInitialize(&display, VGA_VDMA_ID, VGA_BASEADDR, DISPLAY_NOT_HDMI, vgaPtr, VGA_STRIDE * sizeof(u32));
	if(status != 0)
		return status;
	status = DisplaySetMode(&display, VGA_MODE);
	if(status != 0)
		return status;
	status = DisplayStart(&display);
	return status;
}

void inline vga_textmode_set_color(u32 background, u32 color)
{
	_background = background;
	_color = color;
}

void vga_textmode_putchar(char c, u32 posX, u32 posY)
{
	posX = (posX % VGA_TEXT_LINE_CHARS) * 8;
	posY = (posY % VGA_TEXT_LINE_COUNT) * 8;

	for (unsigned char y = 0 ; y < 8 ; y++)
		for(unsigned char x = 0 ; x < 8; x++)
			vgaTempFrame[(posX + x) +  ((posY + y) * VGA_STRIDE )] = (font8x8_basic[(unsigned  char)c][y] & (1 << x)) ? _color : _background;
}

void inline vga_textmode_clear(void)
{
	for(size_t x = 0 ; x < VGA_TEXT_LINE_CHARS ; x++)
		for(size_t y = 0 ; y < VGA_TEXT_LINE_COUNT ; y++)
			vga_textmode_putchar(0, x, y);
}

void vga_textmode_write(const char *str, size_t size)
{
	while(size--)
	{
		if(*str == '\n')
		{
			_cursorX = 0;
			if(_cursorY == (VGA_TEXT_LINE_COUNT - 1))
				vga_textmode_scroll();
			else
				_cursorY++;
			vga_textmode_flush();
		}
		else
		{
			vga_textmode_putchar(*str, _cursorX, _cursorY);
			_cursorX = (_cursorX + 1) % VGA_TEXT_LINE_CHARS;
		}
		str++;
	}
}

void vga_textmode_scroll(void)
{
	memmove(&vgaTempFrame[0], &vgaTempFrame[VGA_RESOLUTION_X*8], sizeof(u32)*(VGA_RESOLUTION_X-1)*VGA_RESOLUTION_Y);
	for(unsigned char x = 0 ; x < VGA_TEXT_LINE_CHARS ; x++)
		vga_textmode_putchar('\0', x, VGA_TEXT_LINE_COUNT-1);
}

void vga_textmode_flush(void)
{
	memcpy(vgaFrames[currentFrame], vgaTempFrame, sizeof(u32) * VGA_RESOLUTION_X * VGA_RESOLUTION_Y);
	//for(size_t i = 0 ; i < VGA_RESOLUTION_X * VGA_RESOLUTION_Y ; i++)
	//	vgaFrames[currentFrame][i] = vgaTempFrame[i];
	DisplayChangeFrame(&display, currentFrame);
	currentFrame = (currentFrame + 1) % DISPLAY_NUM_FRAMES;
}
