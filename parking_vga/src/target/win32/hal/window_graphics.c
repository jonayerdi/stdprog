/*************************************************************************************//**
* @file window_graphics.c
* @brief Implementation of graphics with SDL windows
* @author Jon Ayerdi
*****************************************************************************************/

/*--------------------------------------------------------------------------------------*/
/*                                       INCLUDES                                       */
/*--------------------------------------------------------------------------------------*/

#include "hal/window_graphics.h"

#include "io/memory.h"

/*--------------------------------------------------------------------------------------*/
/*                            		 PRIVATE FUNCTIONS                                  */
/*--------------------------------------------------------------------------------------*/

static int _get_surface(void *context, image_t *surface, size_t x1, size_t y1, size_t x2, size_t y2);
static void _render(void *context);
static void _destroy(void *context);

static int _get_surface(void *context, image_t *surface, size_t x1, size_t y1, size_t x2, size_t y2)
{
    window_graphics_t *window_graphics = ((window_graphics_t *)context);
	if(x1>x2 || y1>y2 || x2>=window_graphics->config.x || y2>=vga->window_graphics->config.y)
		return GRAPHICS_ERROR_OUT_OF_BOUNDS;
	surface->pixels = &window_graphics->vbuffer[(y1 * window_graphics->config.x) + x1];
	surface->x = x2 - x1;
	surface->y = y2 - y1;
	surface->stride = window_graphics->config.x;
	return GRAPHICS_OK;
}

static void _render(void *context)
{
    window_graphics_t *window_graphics = ((window_graphics_t *)context);
    SDL_Surface *vbuffer_surface = SDL_CreateRGBSurfaceFrom(window_graphics->vbuffer,
                                      window_graphics->config.x,
                                      window_graphics->config.y,
                                      32,
                                      window_graphics->config.x * sizeof(pixel_t),
                                      (Uint32)PIXEL_RED,
                                      (Uint32)PIXEL_GREEN,
                                      (Uint32)PIXEL_BLUE,
                                      (Uint32)0);
    SDL_Surface *window_surface = SDL_GetWindowSurface(SDL_Window* window);
    if(vbuffer_surface != NULL && window_surface != NULL)
    {
        SDL_BlitSurface(vbuffer_surface, NULL, window_surface, NULL);
        SDL_FreeSurface(vbuffer_surface);
        SDL_UpdateWindowSurface(window);
    }
}

static void _destroy(void *context)
{
    window_graphics_t *window_graphics = (window_graphics_t *)context;
    SDL_DestroyRenderer(window_graphics->renderer);
    SDL_DestroyWindow(window_graphics->window);
    memory_free(window_graphics->vbuffer);
    memory_free(window_graphics);
}

/*--------------------------------------------------------------------------------------*/
/*                             PUBLIC FUNCTION DEFINITIONS                              */
/*--------------------------------------------------------------------------------------*/

int window_graphics_init(graphics_t *output, window_graphics_config_t config)
{
    //Init SDL if needed
    int status = sdl_init_if_needed();
	if(status)
        return status;
    //Allocate window_graphics_t instance
    window_graphics_t *window_graphics = (window_graphics_t *)memory_allocate(sizeof(window_graphics_t));
	if(window_graphics == NULL)
		return MEMORY_ERROR;
    window_graphics->vbuffer = (pixel_t *)memory_allocate(sizeof(pixel_t) * config.x * config.y);
    if(window_graphics->vbuffer == NULL)
    {
        memory_free(window_graphics);
        return MEMORY_ERROR;
    }
    //Init window_graphics
    window_graphics->config = config;
    window_graphics->window = SDL_CreateWindow(config.title, 100, 100, config.x, config.y, SDL_WINDOW_SHOWN);
    if(window_graphics->window == NULL)
	{
        memory_free(window_graphics->vbuffer);
        memory_free(window_graphics);
        return (int)SDL_GetError());
    }
    /* Implement output interface */
	output->context = window_graphics;
	output->get_surface = _get_surface;
	output->render = _render;
	output->destroy = _destroy;
	output->x = config.x;
	output->y = config.y;
	return status;
}

/*****************************************************************************************
*                                    window_graphics.c
*****************************************************************************************/