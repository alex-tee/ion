/*
 * Copyright (C) 2019 Alexandros Theodotou <alex at zrythm dot org>
 *
 * This file is part of Ion
 *
 * Ion is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Ion is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU General Affero Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * \file
 *
 * Texture.
 */

#ifndef __GUI_TEXTURE_H__
#define __GUI_TEXTURE_H__

typedef struct Matrix Matrix;

/**
 * @addtogroup gui
 *
 * @{
 */

/**
 * Texture info.
 */
typedef struct Texture
{
  /** OpenGL texture ID. */
  unsigned int    id;

  /** The dimensions in 1920 x 1080. */
  unsigned int    orig_width;
  unsigned int    orig_height;

  /**
   * The dimensions for the current resolution.
   *
   * This is used when drawing to draw the
   * texture in a smaller or larger rectangle.
   */
  unsigned int    width;
  unsigned int    height;

  unsigned char * pixels;
} Texture;

/**
 * Updates the current texture size.
 *
 * @param fb_width Framebuffer width.
 * @param fb_height Framebuffer height.
 */
void
texture_update_size (
  Texture *    self,
  int          fb_width,
  int          fb_height);

/**
 * Generate a texture in the backend for the given data
 * using the given dimensions.
 *
 * The texture will be scaled based on the current
 * resolution. The default resolution is assumed to
 * be 1920x1080.
 */
Texture *
texture_new_from_raw_data (
  unsigned int    width,
  unsigned int    height,
  unsigned char * pixels);

/**
 * Binds the texture to be used.
 */
void
texture_bind (
  Texture * self);

/**
 * Generate a texture in the backend for the given
 * file.
 *
 * The texture will be scaled based on the current
 * resolution. The default resolution is assumed to
 * be 1920x1080.
 */
Texture *
texture_new_from_file (
  const char * full_path);

/**
 * Draws the texture at the given global coordinates,
 * optionally applying any of the given matrices, if
 * non-NULL.
 */
void
texture_draw (
  Texture * self,
  float     x,
  float     y,
  float     rotation_angle,
  float     scale);

/**
 * @}
 */

#endif
