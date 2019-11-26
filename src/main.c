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

#include <GLFW/glfw3.h>

#define PROJECT_NAME "Ion"

int main (
  int argc, char **argv)
{
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit ())
    {
      return -1;
    }

  /* Create a windowed mode window and its OpenGL context */
  window =
    glfwCreateWindow (
      640, 480, PROJECT_NAME, NULL, NULL);
  if (!window)
    {
      glfwTerminate ();
      return -1;
    }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
    {
      /* Render here */
      glClear(GL_COLOR_BUFFER_BIT);

      /* Swap front and back buffers */
      glfwSwapBuffers(window);

      /* Poll for and process events */
      glfwPollEvents();
    }

  glfwTerminate();

  return 0;
}
