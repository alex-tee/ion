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

#include <nanovg.h>

#include "gui/gl.h"
#include "gui/texture.h"

/**
 * Initialization during startup.
 */
void
ion_gl_init (
  GLFWwindow * window)
{
  glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
  glDisable (GL_DEPTH_TEST);
  glEnable (GL_BLEND);

  /* enable multisampling (for antialiasing) */
  glEnable(GL_MULTISAMPLE);

  int width, height;
  glfwGetFramebufferSize (window, &width, &height);
  glViewport (0, 0, width, height);

  glBlendFunc (
    GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable (GL_TEXTURE_2D);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glOrtho (0, width, height, 0, -1, 1);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
}

/**
 * Draws a test triangle.
 */
void
ion_gl_draw_test_rectangle (
  float x,
  float y,
  float width,
  float height)
{
  glPushMatrix ();
  glBindTexture (GL_TEXTURE_2D, 0);

  glColor3f (0.f, 1.0f, 1.0f);
  glBegin (GL_QUADS);
  glVertex2f (x, y);
  glVertex2f (x + width, y);
  glVertex2f (
    x + width, y + height);
  glVertex2f (x, y + height);
  glEnd ();

  glPopMatrix ();
}
