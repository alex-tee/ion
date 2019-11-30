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

#include <glad/glad_glx.h>
#include <GLFW/glfw3.h>
#include <glib.h>
#include <SOIL/SOIL.h>

#include "game/ion_world.h"
#include "gui/shader.h"
#include "gui/shader_manager.h"
#include "gui/texture.h"
#include "math/matrix.h"

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
  int          fb_height)
{
  self->width =
    (unsigned int)
    (((float) self->orig_width *
      (float) fb_width) / 1920.f);
  self->height =
    (unsigned int)
    (((float) self->orig_height *
      (float) fb_height) / 1080.f);

  /*g_message ("updated texture size to %d, %d",*/
    /*self->width, self->height);*/
}

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
  unsigned char * pixels)
{
  Texture * texture =
    calloc (1, sizeof (Texture));

  glGenTextures (1, &texture->id);
  glBindTexture (GL_TEXTURE_2D, texture->id);
  glTexParameteri (
    GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
    GL_LINEAR);
  glTexParameteri (
    GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D (
    GL_TEXTURE_2D, 0, GL_RGBA, width, height,
    0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

  texture->orig_width = width;
  texture->orig_height = height;
  texture->width = width;
  texture->height = height;

  /*g_message (*/
    /*"created texture %d with width %u and height %u",*/
    /*texture->id, width, height);*/

  return texture;
}

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
  const char * full_path)
{
  Texture * texture =
    calloc (1, sizeof (Texture));

  glGenTextures (1, &texture->id);
  glBindTexture (GL_TEXTURE_2D, texture->id);
  glTexParameteri (
    GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
    GL_LINEAR);
  glTexParameteri (
    GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height;
  unsigned char * pixels =
    SOIL_load_image (
      full_path, &width, &height, 0,
      SOIL_LOAD_RGBA);
  glTexImage2D (
    GL_TEXTURE_2D, 0, GL_RGBA, width, height,
    0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
  SOIL_free_image_data (pixels);

  texture->orig_width = width;
  texture->orig_height = height;
  texture->width = width;
  texture->height = height;

  /* FIXME free image data */

  return texture;
}

/**
 * Binds the texture to be used.
 */
void
texture_bind (
  Texture * self)
{
  glActiveTexture (GL_TEXTURE0);
  glBindTexture (GL_TEXTURE_2D, self->id);
}

#if 0
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
  float     scale)
{
  /* Render a texture in immediate mode. */
  glPushMatrix ();
  texture_bind (self);
  glColor3f (1.f, 1.0f, 1.0f);
  /*unsigned int program =*/
    /*ION_WORLD->shader_manager->rotate_2d_shader->*/
      /*program_id;*/
  /*glUseProgram (program);*/
  /*GLint loc =*/
    /*glGetUniformLocation (program, "_angle");*/
  /*glUniform1f (loc, rotation_angle);*/

  /* translate to the middle of the texture to
   * rotate it. */
  glTranslatef (
    x + (float) self->width / 2.f,
    y + (float) self->height / 2.f, 0.f);

  /* rotate around z axis */
  glRotatef (
    rotation_angle, 0.f, 0.f, 1.f);

  /* translate back */
  glTranslatef (
    - (x + (float) self->width / 2.f),
    - (y + (float) self->height / 2.f), 0.f);

  glBegin (GL_QUADS);
  glTexCoord2f (0.0f, 0.0f);
  glVertex2f (x, y);
  glTexCoord2f (1.0f, 0.0f);
  glVertex2f (x + self->width, y);
  glTexCoord2f (1.0f, 1.0f);
  glVertex2f (
    x + self->width, y + self->height);
  glTexCoord2f (0.0f, 1.0f);
  glVertex2f (x, y + self->height);
  glEnd ();

  /*glUseProgram (*/
    /*ION_WORLD->shader_manager->unchanged_shader->*/
      /*program_id);*/
  glPopMatrix ();
}
#endif
