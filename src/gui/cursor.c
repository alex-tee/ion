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

#include <GLFW/glfw3.h>
#include <glib.h>

#include "game/ion_world.h"
#include "gui/cursor.h"
#include "gui/texture.h"
#include "math/matrix.h"

void
cursor_draw (
  Cursor * self)
{
  int fb_width, fb_height;
  glfwGetFramebufferSize (
    ION_WORLD->window, &fb_width, &fb_height);
  int win_width, win_height;
  glfwGetWindowSize (
    ION_WORLD->window, &win_width, &win_height);

  double xpos, ypos;
  glfwGetCursorPos (ION_WORLD->window, &xpos, &ypos);
  xpos =
    (xpos * (double) fb_width) / (double) win_width;
  ypos =
    (ypos * (double) fb_height) / (double) win_height;

  Texture * texture = self->cursor;
  float start_xpos =
    (float) xpos - (float) texture->width / 2.f;
  float start_ypos =
    (float) ypos - (float) texture->height / 2.f;

  if (self->rotate)
    {
      self->last_angle =
        self->last_angle +
        CURSOR_RPM * 2.f * G_PI *
        (ION_WORLD->cur_draw_time -
           ION_WORLD->last_draw_time);

      /* wrap */
      if (self->last_angle > 360.f)
        self->last_angle -= 360.f;
      /*g_message ("current rotation %f", rotation.w);*/
    }

  texture_draw (
    texture, start_xpos, start_ypos,
    self->last_angle, 1.f);
}
