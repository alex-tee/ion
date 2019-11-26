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

#include <glad/glad.h>
#include <pango/pangocairo.h>
#include <GLFW/glfw3.h>

#include "gui/gl.h"
#include "utils/pango.h"

#define PROJECT_NAME "Ion"
#define FONT "Sans Bold 18"
#define TEXT "testτεστ"

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
  glViewport (0, 0, width, height);
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


int main (
  int argc, char **argv)
{
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit ())
    {
      return -1;
    }
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint (
    GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint (GLFW_SAMPLES, 4);

  /* Create a windowed mode window and its OpenGL
   * context */
  window =
    glfwCreateWindow (
      640, 480, PROJECT_NAME, NULL, NULL);
  if (!window)
    {
      glfwTerminate ();
      g_error ("failed to create window");
    }

  /* Make the window's context current */
  glfwMakeContextCurrent (window);

  /* set callbacks */
  glfwSetFramebufferSizeCallback (
    window, framebuffer_size_cb);
  glfwSetCursorPosCallback (window, mouse_cb);
  glfwSetScrollCallback (window, scroll_cb);

  /* init GLAD */
  if (!gladLoadGLLoader (
        (GLADloadproc) glfwGetProcAddress))
    {
      g_error ("Failed to initialize GLAD");
    }

  /* init openGL */
  ion_gl_init ();

  IonGlTexture * texture =
    ion_pango_render_text_to_texture (FONT, TEXT);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
    {
      /* frame logic */
      float current_frame = glfwGetTime ();
      (void) current_frame;

      /* process user input */
      /*process_input (window);*/

      /* Render */
      glClear(GL_COLOR_BUFFER_BIT);
      ion_gl_draw_texture (texture, 0.f, 0.f);

      /* Swap front and back buffers */
      glfwSwapBuffers (window);

      /* Poll for and process events */
      glfwPollEvents ();
    }

  /* Clean up */
  glDeleteTextures (1, &texture->id);

  glfwTerminate();

  return 0;
}
