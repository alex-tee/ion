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

#include <stdio.h>

#include <glad/glad_glx.h>
#include <pango/pangocairo.h>
#include <GLFW/glfw3.h>

#include "game/ion_world.h"
#include "gui/gl.h"
#include "gui/drawable.h"
#include "gui/shader.h"
#include "gui/shader_manager.h"
#include "gui/skin.h"
#include "gui/skin_manager.h"
#include "gui/texture.h"
#include "math/vector.h"
#include "utils/pango.h"

#define PROJECT_NAME "Ion"

/**
 * Called whenever the window size changed (by OS
 * or user resize).
 */
void framebuffer_size_cb (
  GLFWwindow * window,
  int          width,
  int          height)
{
  /* make sure the viewport matches the new window
   * dimensions */
  g_message (
    "changing viewport to (%d, %d)",
    width, height);
  if (ION_WORLD)
    {
      ION_WORLD->viewport_width = width;;
      ION_WORLD->viewport_height = height;;
      ion_gl_init (window);
    }

  /*ion_world_update_texture_sizes (ION_WORLD);*/
}

static void
mouse_cb (
  GLFWwindow* window,
  double xpos,
  double ypos)
{
}

static void scroll_cb (
  GLFWwindow* window,
  double xoffset,
  double yoffset)
{
}

static void
error_cb (
  int          error,
  const char * description)
{
  g_critical (
    "A GLFW error occurred (%d): %s",
    error, description);
}

static void
window_close_cb (
  GLFWwindow* window)
{
  g_message ("closing window");
  /*if (!time_to_close)*/
    /*glfwSetWindowShouldClose(window, GLFW_FALSE);*/
}

int main (
  int argc, char **argv)
{
  ION_WORLD = NULL;

  g_message (
    "GLFW version %s",
    glfwGetVersionString ());

  glfwSetErrorCallback (error_cb);

  /* Initialize the library */
  if (!glfwInit ())
    {
      return -1;
    }

  /* Create a windowed mode window and its OpenGL
   * context */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint (
    GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint (GLFW_SAMPLES, 4);
  glfwWindowHint (GLFW_DOUBLEBUFFER, GLFW_TRUE);
  GLFWmonitor * monitor = glfwGetPrimaryMonitor ();
  g_return_val_if_fail (monitor, -1);
  const GLFWvidmode* mode =
    glfwGetVideoMode (monitor);
  g_return_val_if_fail (mode, -1);
  GLFWwindow * window =
    glfwCreateWindow (
      mode->width, mode->height,
      PROJECT_NAME, monitor, NULL);
  if (!window)
    {
      glfwTerminate ();
      g_error ("failed to create GLFW window");
    }
  glfwSetWindowSizeLimits (
    window, mode->width,
    mode->height, mode->width,
    mode->height);
  /*glfwSetWindowAspectRatio (window, 16, 9);*/

  /* set window icon */
  /*GLFWimage images[2];*/
  /*images[0] = load_icon ("my_icon.png");*/
  /*images[1] = load_icon ("my_icon_small.png");*/
  /*glfwSetWindowIcon (window, 2, images);*/

  /* Make the window's context current */
  glfwMakeContextCurrent (window);

  /* set callbacks */
  glfwSetFramebufferSizeCallback (
    window, framebuffer_size_cb);
  glfwSetCursorPosCallback (window, mouse_cb);
  glfwSetScrollCallback (window, scroll_cb);
  glfwSetWindowCloseCallback (
    window, window_close_cb);

  if (!gladLoadGLLoader (
        (GLADloadproc) glfwGetProcAddress))
    {
      g_error ("failed to load glad");
    }
  g_message (
    "OpenGL %d.%d",
    GLVersion.major, GLVersion.minor);

  /* hide cursor */
  glfwSetInputMode (
    window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  /* init openGL */
  ion_gl_init (window);

  ION_WORLD =
    ion_world_new (
      window, mode->width, mode->height);

  /* loop a couple of times to let the frame
   * buffer size stabilize */
  for (int i = 0; i < 10; i++)
    {
      glClear (GL_COLOR_BUFFER_BIT);
      glfwSwapBuffers (window);
      glfwPollEvents ();
    }

  /* load skin with textures used for the game */
  ion_world_load_skin (ION_WORLD);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose (window))
    {
      /* Render */
      ion_world_render_scene (ION_WORLD);

      /* Swap front and back buffers */
      glfwSwapBuffers (window);

      /* Poll for and process events */
      glfwPollEvents ();
    }

  /* Clean up */
  ion_world_free (ION_WORLD);

  glfwTerminate();

  return 0;
}
