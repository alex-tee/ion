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

#include <glib.h>

#include "gui/skin_manager.h"
#include "gui/skin.h"

/**
 * Creates and initializes the skin manager.
 */
SkinManager *
skin_manager_new (
  const char * skins_dir)
{
  SkinManager * self =
    calloc (1, sizeof (SkinManager));

  /* collect all available skins */
  GError *error;
  GDir * dir = g_dir_open (skins_dir, 0, &error);
  const char * filename;
  while ((filename = g_dir_read_name (dir)))
    {
      char * full_path =
        g_build_filename (skins_dir, filename, NULL);
      if (g_file_test (
            full_path, G_FILE_TEST_IS_DIR))
        {
          self->available_skins[
            self->num_available_skins++] =
              skin_new_from_path (full_path);
        }
    }

  self->current_skin =
    self->available_skins[2];

  return self;
}
