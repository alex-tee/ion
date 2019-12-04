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

#include <glib.h>

#include "game/ion_world.h"
#include "gui/button_with_text.h"
#include "gui/drawable.h"
#include "gui/shader.h"
#include "gui/skin.h"
#include "gui/skin_manager.h"
#include "gui/texture.h"
#include "math/vector.h"
#include "utils/pango.h"

ButtonWithText *
button_with_text_new (
  const char * text,
  int          themable)
{
  ButtonWithText * self =
    calloc (1, sizeof (ButtonWithText));

  self->themable = themable;
  self->text = g_strdup (text);

  Vector2f pos = { 0.f, 0.f };
  Vector2f size;
  if (themable)
    {
      size.x =
        (float) CURRENT_SKIN->button_left->width;
      size.y =
        (float) CURRENT_SKIN->button_left->height;
      self->left_drawable =
        drawable_new_with_texture (
          SHADER_TYPE_UNCHANGED,
          CURRENT_SKIN->button_left,
          &pos, &size);
      size.x =
        (float) CURRENT_SKIN->button_middle->width;
      size.y =
        (float) CURRENT_SKIN->button_middle->height;
      self->middle_drawable =
        drawable_new_with_texture (
          SHADER_TYPE_UNCHANGED,
          CURRENT_SKIN->button_middle,
          &pos, &size);
      size.x =
        (float) CURRENT_SKIN->button_right->width;
      size.y =
        (float) CURRENT_SKIN->button_right->height;
      self->right_drawable =
        drawable_new_with_texture (
          SHADER_TYPE_UNCHANGED,
          CURRENT_SKIN->button_right,
          &pos, &size);
    }

  Texture * text_texture =
    ion_pango_render_text_to_texture (
      "Sans 24", text);
  size.x =
    (float) text_texture->width;
  size.y =
    (float) text_texture->height;
  self->text_drawable =
    drawable_new_with_texture (
      SHADER_TYPE_UNCHANGED, text_texture,
      &pos, &size);

  return self;
}

/**
 * Updates the position.
 *
 * Must be called at least once before drawing.
 */
void
button_with_text_update_position (
  ButtonWithText * self,
  float            x,
  float            y)
{
  Vector2f pos = { x, y };
  Vector2f size = { 0.f, 0.f };

  /* left */
  drawable_update_position (
    self->left_drawable, &pos,
    &self->left_drawable->size);

  /* middle */
  pos.x = x + self->left_drawable->size.x;
  pos.y = y;
  size.x = self->text_drawable->size.x + 4.f;
  size.y = self->middle_drawable->size.y;
  drawable_update_position (
    self->middle_drawable, &pos, &size);

  /* right */
  pos.x =
    x + self->left_drawable->size.x +
    self->middle_drawable->size.x;
  pos.y = y;
  drawable_update_position (
    self->right_drawable, &pos,
    &self->right_drawable->size);

  /* text */
  pos.x = x + self->left_drawable->size.x + 2.f;
  pos.y = y;
  size.x = self->text_drawable->size.x;
  size.y = self->text_drawable->size.y;
  drawable_update_position (
    self->text_drawable, &pos,
    &self->text_drawable->size);
}

void
button_with_text_draw (
  ButtonWithText * self)
{
  drawable_draw (self->left_drawable);
  drawable_draw (self->middle_drawable);
  drawable_draw (self->right_drawable);
  drawable_draw (self->text_drawable);
}
