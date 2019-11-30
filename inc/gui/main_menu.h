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

#ifndef __GUI_MAIN_MENU_H__
#define __GUI_MAIN_MENU_H__

typedef struct Texture Texture;

/**
 * @addtogroup gui
 *
 * @{
 */

/**
 * A drawable logo, as part of a Skin.
 */
typedef struct MainMenu
{
} MainMenu;

void
main_menu_draw (
  MainMenu * self);

/**
 * @}
 */

#endif
