#ifndef _UTIL_H_
#define _UTIL_H_

/*
 * util.h - Utility Functions for SDL-based Graphics Operations
 *
 * This header file contains a collection of inline utility functions for
 * various graphics operations using SDL (Simple DirectMedia Layer).
 * These functions provide convenient methods for image manipulation,
 * texture rendering, and debug drawing.
 *
 * Key features:
 * - Image flipping
 * - Texture rendering (with and without camera)
 * - Partial texture rendering (cutting and drawing)
 * - Debug line drawing
 * - Image sketching effect
 *
 * These utilities are designed to simplify common graphics tasks in
 * SDL-based applications, particularly for 2D game development.
 */

#include "camera.h"
#include "vector2.h"

#include <SDL.h>

// Function to flip an image horizontally
inline void flip_image(SDL_Surface *src, SDL_Surface *dst)
{
	// Get the width and height of the source surface
	int w = src->w;
	int h = src->h;

	// Free the existing destination surface and create a new one
	SDL_FreeSurface(dst);
	dst = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

	// Lock the surfaces to directly access pixel data
	SDL_LockSurface(src);
	SDL_LockSurface(dst);

	// Get pointers to the pixel data of both surfaces
	Uint32 *src_pixels = (Uint32 *)src->pixels;
	Uint32 *dst_pixels = (Uint32 *)dst->pixels;

	// Iterate through each pixel and copy it to its mirrored position
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			// Calculate the source and destination indices
			int idx_src = y * w + x;
			int idx_dst = y * w + (w - x - 1);
			// Copy the pixel from source to destination
			dst_pixels[idx_dst] = src_pixels[idx_src];
		}
	}

	// Unlock the surfaces after manipulation
	SDL_UnlockSurface(src);
	SDL_UnlockSurface(dst);
}

// draw image without camera
inline void render_texture(SDL_Renderer *renderer, SDL_Texture *texture, int dst_x, int dst_y)
{
	SDL_Rect dst_rect = {dst_x, dst_y, 0, 0};
	SDL_QueryTexture(texture, NULL, NULL, &dst_rect.w, &dst_rect.h);
	SDL_RenderCopy(renderer, texture, NULL, &dst_rect);
}

// draw image with camera
inline void render_texture(SDL_Renderer *renderer, SDL_Texture *texture, const Camera &camera, int dst_x, int dst_y)
{
	const Vector2 &pos_camera = camera.get_position();
	SDL_Rect dst_rect = {(int)(dst_x - pos_camera.x), (int)(dst_y - pos_camera.y), 0, 0};
	SDL_QueryTexture(texture, NULL, NULL, &dst_rect.w, &dst_rect.h);
	SDL_RenderCopy(renderer, texture, NULL, &dst_rect);
}

// cut and draw image
inline void render_texture(SDL_Renderer *renderer, SDL_Texture *texture, int dst_x, int dst_y, int width, int height, int src_x, int src_y)
{
	SDL_Rect src_rect = {src_x, src_y, width, height};
	SDL_Rect dst_rect = {dst_x, dst_y, width, height};
	SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
}

// draw debug line
inline void draw_line(SDL_Renderer *renderer, const Camera &camera, int x1, int y1, int x2, int y2)
{
	const Vector2 &pos_camera = camera.get_position();
	SDL_RenderDrawLine(renderer,
					   (int)(x1 - pos_camera.x), (int)(y1 - pos_camera.y),
					   (int)(x2 - pos_camera.x), (int)(y2 - pos_camera.y));
}

// sketch image
inline void sketch_texture(SDL_Texture *src, SDL_Texture *dst)
{
	// Get the dimensions of the source texture
	int w, h;
	SDL_QueryTexture(src, NULL, NULL, &w, &h);

	// Create a new surface for the destination texture
	SDL_Surface *dst_surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

	// Lock the surfaces for pixel manipulation
	SDL_Surface *src_surface = SDL_CreateRGBSurfaceFrom(NULL, w, h, 32, 0, 0, 0, 0, 0);
	SDL_LockTexture(src, NULL, &src_surface->pixels, &src_surface->pitch);
	SDL_LockSurface(dst_surface);

	// Get pixel data
	Uint32 *src_pixels = (Uint32 *)src_surface->pixels;
	Uint32 *dst_pixels = (Uint32 *)dst_surface->pixels;

	// Fill the destination surface with white
	SDL_FillRect(dst_surface, NULL, SDL_MapRGBA(dst_surface->format, 255, 255, 255, 255));

	// Copy pixels from source to destination
	for (int i = 0; i < w * h; ++i)
	{
		Uint8 r, g, b, a;
		SDL_GetRGBA(src_pixels[i], src_surface->format, &r, &g, &b, &a);
		dst_pixels[i] = SDL_MapRGBA(dst_surface->format, r, g, b, a);
	}

	// Unlock surfaces
	SDL_UnlockTexture(src);
	SDL_UnlockSurface(dst_surface);

	// Update the destination texture
	SDL_UpdateTexture(dst, NULL, dst_surface->pixels, dst_surface->pitch);

	// Free the temporary surface
	SDL_FreeSurface(dst_surface);
	SDL_FreeSurface(src_surface);
}

#endif // !_UTIL_H_
