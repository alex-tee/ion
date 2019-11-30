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
#include "gui/main_menu.h"
#include "gui/shader.h"
#include "gui/shader_manager.h"
#include "gui/skin_manager.h"
#include "gui/skin.h"
#include "gui/texture.h"

void
main_menu_draw (
  MainMenu * self)
{
  int fb_width, fb_height;
  glfwGetFramebufferSize (
    ION_WORLD->window, &fb_width, &fb_height);

#if 0

  /* ---- draw logo ----- */
  unsigned int program =
    ION_WORLD->shader_manager->unchanged_shader->
      program_id;
  Texture * texture =
    ION_WORLD->skin_manager->current_skin->logo;
  GLint baseImageLoc =
    glGetUniformLocation (program, "baseImage");
  GLint normalMapLoc =
    glGetUniformLocation(program, "normalMap");
  GLint shadowMapLoc =
    glGetUniformLocation(program, "shadowMap");

  glUseProgram (program);
  glUniform1i(baseImageLoc, 0); // Texture unit 0 is for base images.
  glUniform1i(normalMapLoc, 2); // Texture unit 2 is for normal maps.
  glUniform1i(shadowMapLoc, 4); // Texture unit 4 is for shadow maps.

  // When rendering an objectwith this program.
  glActiveTexture(GL_TEXTURE0 + 0);
  glBindTexture(GL_TEXTURE_2D, texture->id);

  glPushMatrix ();
  glTranslatef (
    400.f, 20.f, 0.f);
  texture_draw (
    texture,
    (float) fb_width / 2.f -
      (float) texture->width / 2.f,
    (float) fb_height / 2.f -
      (float) texture->height / 2.f,
    0.f, 1.f);
  glPopMatrix ();
#endif
}
