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

#include <glib.h>

#include "game/ion_world.h"
#include "gui/drawable.h"
#include "gui/shader_manager.h"
#include "gui/skin.h"
#include "gui/texture.h"

#define LOGO_FILE "logo.png"
#define CURSOR_FILE "cursor.png"
#define CURSOR_MIDDLE_FILE "cursormiddle.png"
#define CURSOR_SMOKE_FILE "cursor-smoke.png"
#define CURSOR_TRAIL_FILE "cursortrail.png"
#define MENU_BG_FILE "menu-background.jpg"

/**
 * @param width Set to negative to use the texture's.
 * @param height Set to negative to use the texture's.
 */
static void
set_texture (
  IonDrawable ** member,
  const char *   full_path,
  ShaderType     shader,
  float          width,
  float          height)
{
  if (!(*member))
    {
      if (g_file_test (
            full_path, G_FILE_TEST_EXISTS))
        {
          Texture * texture =
            texture_new_from_file (full_path);
          Vector2f position = { 0.f, 0.f };
          Vector2f size = { width, height };
          if (size.x < 0.f)
            size.x = (float) texture->width;
          if (size.y < 0.f)
            size.y = (float) texture->height;
          *member =
            drawable_new_with_texture (
              shader, texture, &position, &size);
        }
    }
}

static void
set_all_textures (
  Skin *       self,
  const char * path)
{
  char * default_path =
    g_build_filename (
      ION_WORLD->skins_dir, "myskin", NULL);

#define SET_TEXTURE(x,file,shader,w,h) \
  { \
    char * full_path = \
      g_build_filename (path, file, NULL); \
    if (!g_file_test ( \
          full_path, G_FILE_TEST_EXISTS)) \
      { \
        g_free (full_path); \
        full_path = \
          g_build_filename ( \
            default_path, file, NULL); \
      } \
    set_texture ( \
      &self->x, full_path, SHADER_TYPE_##shader, \
      w, h); \
    g_free (full_path); \
  }

  SET_TEXTURE (
    logo, LOGO_FILE, UNCHANGED, 960.f, 960.f);
  SET_TEXTURE (
    cursor.cursor, CURSOR_FILE, UNCHANGED, -1.f, -1.f);
  SET_TEXTURE (
    cursor.cursor_middle, CURSOR_MIDDLE_FILE,
    UNCHANGED, -1.f, -1.f);
  SET_TEXTURE (
    cursor.cursor_smoke, CURSOR_SMOKE_FILE,
    UNCHANGED, -1.f, -1.f);
  SET_TEXTURE (
    cursor.cursor_trail, CURSOR_TRAIL_FILE,
    UNCHANGED, -1.f, -1.f);
  SET_TEXTURE (
    menu_bg, MENU_BG_FILE, UNCHANGED, 1920.f, 1080.f);
}

/**
 * Loads a skin matching the given name from the
 * skin directories.
 *
 * @param path The directory path of the skin.
 */
Skin *
skin_new_from_path (
  const char * path)
{
  Skin * self = calloc (1, sizeof (Skin));

  self->path = g_strdup (path);

  GKeyFile * key_file = g_key_file_new ();

  self->cursor.expand = 1;
  self->cursor.rotate = 1;

  char * ini_path =
    g_build_filename (path, "skin.ini", NULL);
  if (!g_file_test (ini_path, G_FILE_TEST_EXISTS))
    {
      g_free (ini_path);
      ini_path =
        g_build_filename (path, "Skin.ini", NULL);
    }
  GError * error = NULL;
  if (g_file_test (ini_path, G_FILE_TEST_EXISTS))
    {
      gsize key_file_content_length;
      char * key_file_content;
      g_file_get_contents (
        ini_path, &key_file_content,
        &key_file_content_length, &error);
      if (key_file_content)
        {
          /* make the key file an actual ini file */
          char **split =
            g_strsplit (key_file_content, ": ", -1);
          g_free (key_file_content);
          key_file_content = g_strjoinv("=", split);
          g_strfreev(split);

          GError * err2 = NULL;
          if (g_key_file_load_from_data (
                key_file, key_file_content,
                strlen (key_file_content),
                G_KEY_FILE_NONE,
                &err2))
            {
              int ival;

              self->name =
                g_key_file_get_string (
                  key_file, "General", "Name", NULL);
              self->creator =
                g_key_file_get_string (
                  key_file, "General", "Author", NULL);


              g_message (
                "ini file in %s parsed. "
                "Name: %s, Author: %s",
                path, self->name, self->creator);

              g_key_file_unref (key_file);
            }
          else
            {
              g_message (
                "skin.ini file parsing failed: %s",
                err2->message);
            }
          g_free (key_file_content);
        }
      else
        {
          g_message ("failed getting file contents");
        }
    }

  set_all_textures (self, path);

  return self;
}

Skin *
skin_create_default (void)
{
  Skin * self = calloc (1, sizeof (Skin));
  self->name = g_strdup ("ionv1");
  self->creator = g_strdup ("Ion team");

  return self;
}

char *
skin_get_full_name (
  Skin * self)
{
  return
    g_strdup_printf (
      "%s by %s", self->name, self->creator);
}
