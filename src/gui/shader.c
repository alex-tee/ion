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

#include "config.h"

#include <stdlib.h>

#include <glad/glad_glx.h>
#include <GLFW/glfw3.h>
#include <glib.h>

#include "gui/shader.h"

Shader *
shader_new (
  const char * filename)
{
  Shader * self = calloc (1, sizeof (Shader));

  self->program_id = glCreateProgram ();

  unsigned int vertex_id =
    glCreateShader (GL_VERTEX_SHADER);
  char * _filepath =
    g_build_filename (
      GLSL_DIR, filename, NULL);
  char * filepath =
    g_strdup_printf ("%s.vert", _filepath);
  char * content;
  gsize ulength;
  GError * error = NULL;
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
        "Shader %s compilation failed: %s",
        filename, info);
      return NULL;
    }

  unsigned int fragment_id =
    glCreateShader (GL_FRAGMENT_SHADER);
  _filepath =
    g_build_filename (
      GLSL_DIR, filename, NULL);
  filepath =
    g_strdup_printf ("%s.frag", _filepath);
  error = NULL;
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
        "Shader %s compilation failed: %s",
        filename, info);
      return NULL;
    }

  self->vertex_shader_id = vertex_id;
  self->fragment_shader_id = fragment_id;

  glAttachShader (self->program_id, vertex_id);
  glAttachShader (self->program_id, fragment_id);

  glBindAttribLocation (
    self->program_id, 0, "position");
  glBindAttribLocation (
    self->program_id, 1, "tex_coord");

  glLinkProgram (self->program_id);
  glGetProgramiv (
    self->program_id, GL_LINK_STATUS, &success);
  if (!success)
    {
      glGetProgramInfoLog (
        self->program_id, 512, NULL, info);
      g_critical (
        "Shader %s linking failed: %s",
        filename, info);
      return NULL;
    }

  glValidateProgram (self->program_id);
  glGetProgramiv (
    self->program_id, GL_VALIDATE_STATUS, &success);
  if (!success)
    {
      glGetProgramInfoLog (
        self->program_id, 512, NULL, info);
      g_critical (
        "Shader %s program validation failed: %s",
        filename, info);
      return NULL;
    }

  g_message ("Shader program %s ready.", filename);

  return self;
}

void
shader_bind (
  Shader * self)
{
  glUseProgram (self->program_id);
}

void
shader_free (
  Shader * self)
{
  /*glDetachShader (self->vertex_shader_id);*/
  /*glDetachShader (self->fragment_shader_id);*/
  glDeleteShader (self->vertex_shader_id);
  glDeleteShader (self->fragment_shader_id);

  glDeleteProgram (self->program_id);
}
