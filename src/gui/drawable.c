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

#include <glad/glad_glx.h>
#include <GLFW/glfw3.h>
#include <glib.h>

#include "game/ion_world.h"
#include "gui/drawable.h"
#include "gui/shader.h"
#include "gui/texture.h"

IonDrawable *
drawable_new_with_texture (
  ShaderType shader_type,
  Texture *  texture,
  Vector2f * position,
  Vector2f * size)
{
  g_return_val_if_fail (texture && position, NULL);

  IonDrawable * self =
    calloc (1, sizeof (IonDrawable));

  self->shader_type = shader_type;
  self->texture = texture;

  drawable_update_position (self, position, size);

  glGenVertexArrays (1, &self->vao);
  glGenBuffers (1, &self->vbo);
  glGenBuffers (1, &self->tbo);
  glGenBuffers (1, &self->ebo);
  glBindVertexArray (self->vao);

  /* vertices */
  glBindBuffer (
    GL_ARRAY_BUFFER, self->vbo);
  glBufferData (
    GL_ARRAY_BUFFER, sizeof (self->vectors),
    self->vectors, GL_DYNAMIC_DRAW);
  glVertexAttribPointer (
    0, 2, GL_FLOAT, GL_FALSE,
    sizeof (Vector2f), 0);
  glEnableVertexAttribArray (0);

  /* texture coords */
  glBindBuffer (
    GL_ARRAY_BUFFER, self->tbo);
  glBufferData (
    GL_ARRAY_BUFFER, sizeof (self->tex_coords),
    self->tex_coords, GL_STATIC_DRAW);
  glVertexAttribPointer (
    1, 2, GL_FLOAT, GL_FALSE,
    sizeof (Vector2f), 0);
  glEnableVertexAttribArray (1);

  /* indices */
  glBindBuffer (
    GL_ELEMENT_ARRAY_BUFFER, self->ebo);
  glBufferData (
    GL_ELEMENT_ARRAY_BUFFER, sizeof (self->indices),
    self->indices, GL_STATIC_DRAW);

  /* unbind */
  glBindBuffer (GL_ARRAY_BUFFER, 0);
  glBindVertexArray (0);

  return self;
}

void
drawable_update_position (
  IonDrawable * self,
  Vector2f *    position,
  Vector2f *    size)
{
  self->position = *position;
  self->size = *size;

  /* bottom left */
  self->vectors[0].x =
    position->x;
  self->vectors[0].y =
    position->y;
  self->tex_coords[0].x = 0.f;
  self->tex_coords[0].y = 1.f;

  /* bottom right */
  self->vectors[1].x =
    position->x + size->x;
  self->vectors[1].y =
    position->y;
  self->tex_coords[1].x = 1.f;
  self->tex_coords[1].y = 1.f;

  /* top right */
  self->vectors[2].x =
    position->x + size->x;
  self->vectors[2].y =
    position->y + size->y;
  self->tex_coords[2].x = 1.f;
  self->tex_coords[2].y = 0.f;

  /* top left */
  self->vectors[3].x =
    position->x;
  self->vectors[3].y =
    position->y + size->y;
  self->tex_coords[3].x = 0.f;
  self->tex_coords[3].y = 0.f;

  /* draw 2 triangles (rectangle) */
  self->indices[0] = 0;
  self->indices[1] = 1;
  self->indices[2] = 3;
  self->indices[3] = 1;
  self->indices[4] = 2;
  self->indices[5] = 3;

  /* rebind the vectors */
  glBindVertexArray (self->vao);
  glBindBuffer (
    GL_ARRAY_BUFFER, self->vbo);
  glBufferData (
    GL_ARRAY_BUFFER, sizeof (self->vectors),
    self->vectors, GL_DYNAMIC_DRAW);
  glBindVertexArray (0);
}

void
drawable_draw (
  IonDrawable * self)
{
  shader_bind (
    ION_WORLD->shader_manager->shaders[
      self->shader_type]);
  if (self->texture)
    {
      texture_bind (self->texture);
    }
  glUniform2f (
    0, (float) ION_WORLD->viewport_width,
    (float) ION_WORLD->viewport_height);
  glUniform1f (
    1, self->angle);

  glBindVertexArray (self->vao);
  glDrawElements (
    GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray (0);
}

void
drawable_free (
  IonDrawable * self)
{
  /*glDeleteBuffers (1, self->vab);*/
  /*glDeleteVertexArrays (1, self->vao);*/
}
