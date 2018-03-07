/*************************************************************************************//**
* @file vga_graphics.c
* @brief Implementation of VGA graphics for the ZYBO 7000 board
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "hal/vga_graphics.h"

#include "io/memory.h"

/*--------------------------------------------------------------------------------------*/
/*                            		 PRIVATE FUNCTIONS                                  */
/*--------------------------------------------------------------------------------------*/

static int _get_surface(void *context, image_t *surface, size_t x1, size_t y1, size_t x2, size_t y2);
static void _render(void *context);
static void _destroy(void *context);

static int _get_surface(void *context, image_t *surface, size_t x1, size_t y1, size_t x2, size_t y2)
{
	vga_graphics_t *vga = ((vga_graphics_t *)context);
	if(x1>x2 || y1>y2 || x2>=vga->mode.width || y2>=vga->mode.height)
		return GRAPHICS_ERROR_OUT_OF_BOUNDS;
	surface->pixels = &vga->vbuffer[(y1 * vga->mode.width) + x1];
	surface->x = x2 - x1;
	surface->y = y2 - y1;
	surface->stride = vga->mode.width;
	return GRAPHICS_OK;
}

static void _render(void *context)
{
	vga_graphics_t *vga = ((vga_graphics_t *)context);
	memcpy(vga->framebuffers[(size_t)vga->current_frame], vga->vbuffer, sizeof(pixel_t) * vga->mode.width * vga->mode.height);
	DisplayChangeFrame(&vga->driver, vga->current_frame);
	vga->current_frame = (vga->current_frame + 1) % DISPLAY_NUM_FRAMES;
}

static void _destroy(void *context)
{
	vga_graphics_t *vga = ((vga_graphics_t *)context);
	for(size_t i = 0 ; i < DISPLAY_NUM_FRAMES ; i++)
		memory_free(vga->framebuffers[i]);
	memory_free(vga->vbuffer);
	memory_free(vga);
}

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

int vga_graphics_init(graphics_t *output, vga_graphics_config_t config)
{
	/* Initialize vga_graphics_t struct */
	vga_graphics_t *context = (vga_graphics_t *)memory_allocate(sizeof(vga_graphics_t));
	if(context == NULL)
		return MEMORY_ERROR;
	context->current_frame = 0;
	context->mode = config.mode;
	context->vbuffer = (pixel_t *)memory_allocate(sizeof(pixel_t) * context->mode.height * context->mode.width);
	if(context->vbuffer == NULL)
	{
		memory_free(context);
		return MEMORY_ERROR;
	}
	context->framebuffers = (pixel_t **)memory_allocate(sizeof(pixel_t*) * DISPLAY_NUM_FRAMES);
	for(size_t i = 0 ; i < DISPLAY_NUM_FRAMES ; i++)
	{
		context->framebuffers[i] = (pixel_t *)memory_allocate(sizeof(pixel_t) * context->mode.height * context->mode.width);
		if(context->framebuffers[i] == NULL)
		{
			for(size_t j = 0 ; j < i ; j++)
				memory_free(context->framebuffers[i]);
			memory_free(context->vbuffer);
			memory_free(context);
			return MEMORY_ERROR;
		}
	}
	/* Initialize display driver */
	u32 *vgaPtr[DISPLAY_NUM_FRAMES];
	for (int i = 0; i < DISPLAY_NUM_FRAMES; i++)
		vgaPtr[i] = context->framebuffers[i];
	int status = DisplayInitialize(&context->driver, config.vdma_id, config.display_ctrl_address, config.hdmi, vgaPtr, context->mode.width * sizeof(u32));
	if(status != 0)
	{
		_destroy((void *)context);
		return status;
	}
	/* Set video mode */
	status = DisplaySetMode(&context->driver, &context->mode);
	if(status != 0)
	{
		_destroy((void *)context);
		return status;
	}
	/* Start display driver */
	status = DisplayStart(&context->driver);
	/* Implement output interface */
	output->context = context;
	output->get_surface = _get_surface;
	output->render = _render;
	output->destroy = _destroy;
	output->x = context->mode.width;
	output->y = context->mode.height;
	return status;
}

/*****************************************************************************************
*                                      vga_graphics.c
*****************************************************************************************/
