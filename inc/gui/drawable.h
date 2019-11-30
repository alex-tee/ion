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
 * Drawable object.
 */

#ifndef __GUI_DRAWABLE_H__
#define __GUI_DRAWABLE_H__

#include "gui/shader_manager.h"
#include "math/vector.h"

typedef struct Texture Texture;

/**
 * @addtogroup gui
 *
 * @{
 */

/**
 * Drawable element.
 */
typedef struct IonDrawable
{
  /** Shader to use. */
  ShaderType    shader_type;

  /** Texture to use. */
  Texture *     texture;

  /**
   * Size of the drawable, independent of the
   * texture.
   *
   * The texture will be stretched to this.
   */
  Vector2f      size;

  /** GL vertex array object. */
  unsigned int  vao;

  /** Vertices. */
  unsigned int  vbo;

  /** Texture coordinates. */
  unsigned int  tbo;

  /** Indices (elements). */
  unsigned int  ebo;

  /** How many vertices we need to draw. */
  unsigned int  draw_count;

  /** Set to 1 if the position is expected to
   * change often. */
  int           dynamic_positions;

  /** Angle to rotate by or 0. */
  float         angle;

  /** Position to start drawing at. */
  Vector2f      position;

  /** Quad. */
  Vector2f      vectors[4];

  /** Texture coordinates for each vector. */
  Vector2f      tex_coords[4];

  /** Indices. */
  unsigned int  indices[6];
} IonDrawable;

IonDrawable *
drawable_new_with_texture (
  ShaderType shader_type,
  Texture *  texture,
  Vector2f * position,
  Vector2f * size);

void
drawable_update_position (
  IonDrawable * self,
  Vector2f *    position,
  Vector2f *    size);

void
drawable_draw (
  IonDrawable * self);

void
drawable_free (
  IonDrawable * self);

/**
 * @}
 */

#endif
