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
#include "gui/button_with_text.h"
#include "gui/drawable.h"
#include "gui/main_menu.h"
#include "gui/shader.h"
#include "gui/shader_manager.h"
#include "gui/skin_manager.h"
#include "gui/skin.h"
#include "gui/texture.h"

/**
 * Updates the main menu before drawing.
 */
void
main_menu_update (
  MainMenu * self)
{
  double xpos, ypos;
  glfwGetCursorPos (
    ION_WORLD->window, &xpos, &ypos);

  int state =
    glfwGetMouseButton (
      ION_WORLD->window, GLFW_MOUSE_BUTTON_LEFT);
  if (state == GLFW_PRESS &&
      drawable_hit (CURRENT_LOGO, xpos, ypos))
    {
      self->showing_options = 1;
    }

  float logo_transition = 24.f;
  if (self->showing_options)
    {
      /* move logo */
      Vector2f new_pos = CURRENT_LOGO->position;
      new_pos.x =
        MAX (40.f, new_pos.x - logo_transition);
      drawable_update_position (
        CURRENT_LOGO, &new_pos,
        &CURRENT_LOGO->size);

      /* move options positions */
      int y_pad = 4.f;
      button_with_text_update_position (
        self->play,
        CURRENT_LOGO->position.x +
          CURRENT_LOGO->size.x,
        (CURRENT_LOGO->position.y +
          CURRENT_LOGO->size.y / 2.f) +
          (self->play->left_drawable->size.y +
             y_pad) * 3.f);
      button_with_text_update_position (
        self->options,
        CURRENT_LOGO->position.x +
          CURRENT_LOGO->size.x,
        (CURRENT_LOGO->position.y +
          CURRENT_LOGO->size.y / 2.f) +
          (self->play->left_drawable->size.y +
             y_pad) * 2.f);
      button_with_text_update_position (
        self->exit,
        CURRENT_LOGO->position.x +
          CURRENT_LOGO->size.x,
        (CURRENT_LOGO->position.y +
          CURRENT_LOGO->size.y / 2.f) +
          (self->play->left_drawable->size.y +
             y_pad) * 1.f);
    }
  else
    {
      /* move logo */
      Vector2f new_pos = CURRENT_LOGO->position;
      new_pos.x =
        MIN (
          CURRENT_LOGO->size.x / 2.f,
          new_pos.x + logo_transition);
      drawable_update_position (
        CURRENT_LOGO, &new_pos,
        &CURRENT_LOGO->size);
    }
}

static void
draw_options (
  MainMenu * self)
{
  button_with_text_draw (self->play);
  button_with_text_draw (self->options);
  button_with_text_draw (self->exit);
}

void
main_menu_draw (
  MainMenu * self)
{
  /* draw bg stretched */
  drawable_draw (CURRENT_SKIN->menu_bg);

  /* draw options */
  if (self->showing_options)
    {
      draw_options (self);
    }

  /* draw logo */
  drawable_draw (CURRENT_LOGO);
}

/**
 * Creates the main menu.
 */
MainMenu *
main_menu_new (void)
{
  MainMenu * self = calloc (1, sizeof (MainMenu));

  self->play =
    button_with_text_new (
      "Play", 1);
  self->options =
    button_with_text_new (
      "Options", 1);
  self->exit =
    button_with_text_new (
      "Exit", 1);

  return self;
}
