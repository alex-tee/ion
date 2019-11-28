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

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glib.h>

#include "gui/shader.h"

#define GLSL_PATH "/home/alex/Documents/git/ion/inc/gui/gsl"

Shader *
shader_new (
  const char * filename)
{
  Shader * self = calloc (1, sizeof (Shader));

  unsigned int vertex_id =
    glCreateShader (GL_VERTEX_SHADER);
  char * _filepath =
    g_build_filename (
      GLSL_PATH, filename, NULL);
  char * filepath =
    g_strdup_printf ("%s.vert", _filepath);
  char * content;
  gsize ulength;
  GError * error;
  g_file_get_contents (
    filepath, &content, &ulength, &error);
  int length = (int) ulength;
  glShaderSource (
    vertex_id, 1, &content, &length);
  glCompileShader (vertex_id);
  g_free (_filepath);
  g_free (filepath);

  int  success;
  char info[512];
  glGetShaderiv (
    vertex_id, GL_COMPILE_STATUS, &success);
  if (!success)
    {
      glGetShaderInfoLog (
        vertex_id, 512, NULL, info);
      g_critical (
        "Shader compilation failed: %s", info);
      return NULL;
    }

  unsigned int fragment_id =
    glCreateShader (GL_FRAGMENT_SHADER);
  _filepath =
    g_build_filename (
      GLSL_PATH, filename, NULL);
  filepath =
    g_strdup_printf ("%s.frag", _filepath);
  g_file_get_contents (
    filepath, &content, &ulength, &error);
  length = (int) ulength;
  glShaderSource (
    fragment_id, 1, &content, &length);
  glCompileShader (fragment_id);
  g_free (_filepath);
  g_free (filepath);

  glGetShaderiv (
    fragment_id, GL_COMPILE_STATUS, &success);
  if (!success)
    {
      glGetShaderInfoLog (
        fragment_id, 512, NULL, info);
      g_critical (
        "Shader compilation failed: %s", info);
      return NULL;
    }

  self->program_id = glCreateProgram ();
  glAttachShader (self->program_id, vertex_id);
  glAttachShader (self->program_id, fragment_id);
  glLinkProgram (self->program_id);
  glGetProgramiv (
    self->program_id, GL_LINK_STATUS, &success);
  if (!success)
    {
      glGetProgramInfoLog (
        self->program_id, 512, NULL, info);
      g_critical (
        "Shader linking failed: %s", info);
      return NULL;
    }

  glDeleteShader (vertex_id);
  glDeleteShader (fragment_id);

  return self;
}
