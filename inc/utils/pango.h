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
 * Pango utils.
 */

#ifndef __UTILS_PANGO_H__
#define __UTILS_PANGO_H__

typedef struct IonGlTexture IonGlTexture;

/**
 * @addtogroup utils
 *
 * @{
 */

/**
 * Renders the given text in the given font to a
 * GL texture.
 */
IonGlTexture *
ion_pango_render_text_to_texture (
  const char * font_descr,
  const char * text);

/**
 * @}
 */

#endif
