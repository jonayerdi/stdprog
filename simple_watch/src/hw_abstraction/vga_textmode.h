/*
 * vga_textmode.h
 *
 *  Created on: 6 Nov 2017
 *      Author: Jon Ayerdi
 */

#ifndef SRC_HW_ABSTRACTION_VGA_TEXTMODE_H_
#define SRC_HW_ABSTRACTION_VGA_TEXTMODE_H_

#include <xil_types.h>

#define VGA_VDMA_ID XPAR_AXIVDMA_0_DEVICE_ID
#define VGA_BASEADDR XPAR_AXI_DISPCTRL_0_S_AXI_BASEADDR

#define VGA_RESOLUTION_X 800
#define VGA_RESOLUTION_Y 600
#define VGA_MODE &VMODE_800x600
#define VGA_STRIDE (VGA_RESOLUTION_X)

#define VGA_TEXT_LINE_CHARS (VGA_RESOLUTION_X / 8)
#define VGA_TEXT_LINE_COUNT (VGA_RESOLUTION_Y / 8)

int vga_textmode_init();
void vga_textmode_set_color(u32 background, u32 color);
void vga_textmode_putchar(char c, u32 x, u32 y);
void vga_textmode_clear(void);
void vga_textmode_write(const char *str, size_t size);
void vga_textmode_scroll(void);
void vga_textmode_flush(void);

#define hw_abstraction_vga_textmode { vga_textmode_write, vga_textmode_flush }

#endif /* SRC_HW_ABSTRACTION_VGA_TEXTMODE_H_ */
