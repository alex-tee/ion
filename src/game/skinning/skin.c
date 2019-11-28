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

#include "game/skinning/skin.h"
#include "game/ion_world.h"
#include "gui/texture.h"

#define LOGO_FILE "logo.png"
#define CURSOR_FILE "cursor.png"
#define CURSOR_MIDDLE_FILE "cursormiddle.png"
#define CURSOR_SMOKE_FILE "cursor-smoke.png"
#define CURSOR_TRAIL_FILE "cursortrail.png"
#define MENU_BG_FILE "menu-background.jpg"

/**
 * Fills unset values from the default skin.
 */
static void
fill_values_from_default (
  Skin * self)
{
#define SET_TEXTURE(member,filename) \
  if (!self->member) \
    { \
      char * full_path = \
        g_build_filename ( \
          ION_WORLD->skins_dir, "myskin", \
          filename, NULL); \
      self->member = \
        texture_new_from_file (full_path); \
      g_free (full_path); \
    }

  SET_TEXTURE (logo, LOGO_FILE);
  SET_TEXTURE (cursor.cursor, CURSOR_FILE);
  SET_TEXTURE (
    cursor.cursor_middle, CURSOR_MIDDLE_FILE);
  SET_TEXTURE (
    cursor.cursor_smoke, CURSOR_SMOKE_FILE);
  SET_TEXTURE (
    cursor.cursor_trail, CURSOR_TRAIL_FILE);
  SET_TEXTURE (menu_bg, MENU_BG_FILE);

#undef SET_TEXTURE
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

#define SET_TEXTURE(member,filename) \
      full_resource_path = \
        g_build_filename ( \
          path, filename, NULL); \
      if (g_file_test ( \
            full_resource_path, G_FILE_TEST_EXISTS)) \
        { \
          self->member = \
            texture_new_from_file (full_resource_path); \
        } \
      g_free (full_resource_path)

  char * full_resource_path;
  SET_TEXTURE (logo, LOGO_FILE);
  SET_TEXTURE (cursor.cursor, CURSOR_FILE);
  SET_TEXTURE (
    cursor.cursor_middle, CURSOR_MIDDLE_FILE);
  SET_TEXTURE (
    cursor.cursor_smoke, CURSOR_SMOKE_FILE);
  SET_TEXTURE (
    cursor.cursor_trail, CURSOR_TRAIL_FILE);
  SET_TEXTURE (
    menu_bg, MENU_BG_FILE);

  fill_values_from_default (self);

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

void
skin_update_texture_sizes (
  Skin * self,
  int    fb_width,
  int    fb_height)
{
#define UPDATE_TEXTURE_SIZE(member) \
  if (self->member) \
    { \
      texture_update_size ( \
        self->member, fb_width, fb_height); \
      g_message ("height %u", self->member->height); \
    }

  UPDATE_TEXTURE_SIZE (logo);
}

char *
skin_get_full_name (
  Skin * self)
{
  return
    g_strdup_printf (
      "%s by %s", self->name, self->creator);
}
