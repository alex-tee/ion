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

/**
 * \file
 *
 * Skin manager.
 */

#ifndef __GAME_SKINNING_SKIN_MANAGER_H__
#define __GAME_SKINNING_SKIN_MANAGER_H__

typedef struct Skin Skin;
typedef struct IonWorld IonWorld;

/**
 * @addtogroup skinning
 *
 * @{
 */

typedef struct SkinManager
{
  Skin *       current_skin;
  Skin *       available_skins[200];
  int          num_available_skins;

  /* TODO */
} SkinManager;

/**
 * Creates and initializes the skin manager.
 */
SkinManager *
skin_manager_new (
  const char * skins_dir);

/**
 * @}
 */

#endif
