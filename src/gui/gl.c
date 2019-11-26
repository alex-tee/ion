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

#include <stdlib.h>

#include <GLFW/glfw3.h>
#include <glib.h>

#include "gui/gl.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

/**
 * Initialization during startup.
 */
void
ion_gl_init ()
{
  glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
  glDisable (GL_DEPTH_TEST);
  glEnable (GL_BLEND);

  /* enable multisampling (for antialiasing) */
  glEnable(GL_MULTISAMPLE);

  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable (GL_TEXTURE_2D);
  glViewport (0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glOrtho (0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
}

/**
 * Generate a texture with an ID for the given data
 * of the given dimensions.
 */
IonGlTexture *
ion_gl_create_texture (
  unsigned int    width,
  unsigned int    height,
  unsigned char * pixels)
{
  IonGlTexture * texture =
    calloc (1, sizeof (IonGlTexture));

  glGenTextures (1, &texture->id);
  glBindTexture (GL_TEXTURE_2D, texture->id);
  glTexParameteri (
    GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
    GL_LINEAR);
  glTexParameteri (
    GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D (
    GL_TEXTURE_2D, 0, GL_RGBA, width, height,
    0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);

  texture->width = width;
  texture->height = height;

  return texture;
}

/**
 * Draws the texture in the given rectangle.
 */
void
ion_gl_draw_texture (
  IonGlTexture * texture,
  float          x,
  float          y)
{
  /* Render a texture in immediate mode. */
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  glClear (GL_COLOR_BUFFER_BIT);
  glPushMatrix ();
  glBindTexture (GL_TEXTURE_2D, texture->id);
  glColor3f (1.f, 1.0f, 1.0f);

  glBegin (GL_QUADS);
  glTexCoord2f (0.0f, 0.0f);
  glVertex2f (x, y);
  glTexCoord2f (1.0f, 0.0f);
  glVertex2f (x + texture->width, y);
  glTexCoord2f (1.0f, 1.0f);
  glVertex2f (
    x + texture->width, y + texture->height);
  glTexCoord2f (0.0f, 1.0f);
  glVertex2f (x, y + texture->height);
  glEnd ();

  glPopMatrix ();
}
