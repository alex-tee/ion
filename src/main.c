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

#include <pango/pangocairo.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game/ion_world.h"
#include "gui/gl.h"
#include "gui/texture.h"
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
  ion_gl_init (window);

  ion_world_update_texture_sizes (ION_WORLD);
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
  glfwWindowHint (GLFW_SAMPLES, 4);
  glfwWindowHint (GLFW_DOUBLEBUFFER, GLFW_TRUE);
  GLFWwindow * window =
    glfwCreateWindow (
      1920, 1080,
      PROJECT_NAME, glfwGetPrimaryMonitor (), NULL);
  if (!window)
    {
      glfwTerminate ();
      g_error ("failed to create GLFW window");
    }
  /*glfwSetWindowSizeLimits (*/
    /*window, ION_GL_MIN_WINDOW_WIDTH,*/
    /*ION_GL_MIN_WINDOW_HEIGHT, GLFW_DONT_CARE,*/
    /*GLFW_DONT_CARE);*/
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

  /* hide cursor */
  glfwSetInputMode (
    window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  /* init openGL */
  ion_gl_init (window);

  GLenum err = glewInit ();
  if (GLEW_OK != err)
    {
      g_error (
        "GLEW init failed: %s",
        glewGetErrorString (err));
    }

  ION_WORLD = ion_world_new (window);

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
