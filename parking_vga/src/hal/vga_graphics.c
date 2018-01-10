/*****************************************************************************************
*                                      vga_graphics.c
******************************************************************************************
* AUTHOR: Jon Ayerdi
*
* DESCRIPTION: Implementation of VGA graphics for the ZYBO 7000 board
*
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "hal/vga_graphics.h"

#include "io/memory.h"

/*--------------------------------------------------------------------------------------*/
/*                            		 PRIVATE FUNCTIONS                                  */
/*--------------------------------------------------------------------------------------*/

static pixel_t *_get_vbuffer(void *context);
static void _flush_vbuffer(void *context);
static void _destroy(void *context);

static pixel_t *_get_vbuffer(void *context)
{
	vga_graphics_t *vga = ((vga_graphics_t *)context);
	return vga->vbuffer;
}

static void _flush_vbuffer(void *context)
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
	output->get_vbuffer = _get_vbuffer;
	output->flush_vbuffer = _flush_vbuffer;
	output->destroy = _destroy;
	output->x = context->mode.width;
	output->y = context->mode.height;
	return status;
}

/*****************************************************************************************
*                                      vga_graphics.c
*****************************************************************************************/
