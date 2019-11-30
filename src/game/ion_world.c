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

#include "game/ion_world.h"
#include "gui/drawable.h"
#include "gui/gl.h"
#include "gui/main_menu.h"
#include "gui/shader_manager.h"
#include "gui/skin_manager.h"
#include "gui/skin.h"
#include "gui/texture.h"
#include "utils/pango.h"

/**
 * Creates a new game world.
 */
IonWorld *
ion_world_new (
  GLFWwindow * window,
  int          monitor_width,
  int          monitor_height)
{
  IonWorld * self = calloc (1, sizeof (IonWorld));

  ION_WORLD = self;

  self->window = window;
  self->monitor_width = monitor_width;
  self->monitor_height = monitor_height;
  self->screen = ION_WORLD_SCREEN_MAIN_MENU;
  self->skins_dir =
    g_build_filename (
      g_get_home_dir (), ".config", "ion",
      "skins", NULL);
  self->beatmaps_dir =
    g_build_filename (
      g_get_home_dir (), ".config", "ion",
      "beatmaps", NULL);

  self->shader_manager =
    shader_manager_new ();

#define FONT "Sans Bold 18"
#define TEXT "testτεστ"
  self->test_texture =
    ion_pango_render_text_to_texture (FONT, TEXT);

  return self;
}

void
ion_world_load_skin (
  IonWorld * self)
{
  self->skin_manager =
    skin_manager_new (self->skins_dir);
}

#if 0
/**
 * To be called when the framebuffer size changes.
 */
void
ion_world_update_texture_sizes (
  IonWorld * self)
{
  int fb_width, fb_height;
  glfwGetFramebufferSize (
    self->window, &fb_width, &fb_height);

  texture_update_size (
    self->test_texture, fb_width, fb_height);
  skin_update_texture_sizes (
    self->skin_manager->current_skin, fb_width,
    fb_height);
}
#endif

/**
 * Renders the current scene.
 */
void
ion_world_render_scene (
  IonWorld * self)
{
  int fb_width, fb_height;
  glfwGetFramebufferSize (
    self->window, &fb_width, &fb_height);
  int win_width, win_height;
  glfwGetWindowSize (
    self->window, &win_width, &win_height);

  double xpos, ypos;
  glfwGetCursorPos (self->window, &xpos, &ypos);
  xpos =
    (xpos * (double) fb_width) /
    (double) win_width;
  ypos =
    (ypos * (double) fb_height) /
    (double) win_height;
  ypos = fb_height - ypos;

  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();

  self->cur_draw_time = glfwGetTime ();

  Texture * texture;
  switch (self->screen)
    {
    case ION_WORLD_SCREEN_WELCOME:
      /*texture_draw (*/
        /*self->test_texture, 0.f, 0.f, 0.f, 1.f);*/
      ion_gl_draw_test_rectangle (
        40.f, 40.f, 1000.f, 20.f);
      break;
    case ION_WORLD_SCREEN_MAIN_MENU:
      {
        /* draw bg stretched */
        drawable_draw (
          self->skin_manager->current_skin->
          menu_bg);

        drawable_draw (
          self->skin_manager->current_skin->
          logo);

        main_menu_draw (self->main_menu);

        /* draw cursor */
        cursor_draw (
          &self->skin_manager->current_skin->cursor);
      }
      break;
    default:
      break;
    }
  self->last_draw_time = glfwGetTime ();
}

void
ion_world_free (
  IonWorld * self)
{
  glDeleteTextures (1, &self->test_texture->id);
}
