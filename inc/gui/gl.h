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
 * OpenGL utils.
 */

#ifndef __GUI_GL_H__
#define __GUI_GL_H__

/* see https://www.rapidtables.com/web/dev/screen-resolution-statistics.html */
#define ION_GL_WINDOW_WIDTH 1366
#define ION_GL_WINDOW_HEIGHT 768
#define ION_GL_MIN_WINDOW_WIDTH 1280
#define ION_GL_MIN_WINDOW_HEIGHT 720

/**
 * Texture info.
 */
typedef struct IonGlTexture
{
  /** OpenGL texture ID. */
  unsigned int    id;
  unsigned int    width;
  unsigned int    height;
  unsigned char * pixels;
} IonGlTexture;

/**
 * Initialization during startup.
 */
void
ion_gl_init ();

/**
 * Draws a test triangle.
 */
void
ion_gl_draw_test_triangle (
  float x,
  float y,
  float width,
  float height);

/**
 * Generate a texture with an ID for the given data
 * of the given dimensions.
 */
IonGlTexture *
ion_gl_create_texture (
  unsigned int    width,
  unsigned int    height,
  unsigned char * pixels);

/**
 * Draws the texture in the given rectangle.
 */
void
ion_gl_draw_texture (
  IonGlTexture * texture,
  float          x,
  float          y);

#endif
