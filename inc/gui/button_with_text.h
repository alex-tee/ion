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
 * Themable button with text.
 */

#ifndef __GUI_BUTTON_WITH_TEXT_H__
#define __GUI_BUTTON_WITH_TEXT_H__

#include "gui/cursor.h"
#include "gui/rgba.h"

typedef struct Texture Texture;
typedef struct IonDrawable IonDrawable;

/**
 * @addtogroup gui
 *
 * @{
 */

typedef struct ButtonWithText
{
  /** Text to show. */
  char *          text;

  /** If themable, the button will use the button
   * background of the skin. */
  int             themable;

  /** These are used if themable. */
  IonDrawable *   left_drawable;
  IonDrawable *   middle_drawable;
  IonDrawable *   right_drawable;

  /** The text rendered as a texture. */
  IonDrawable *   text_drawable;
} ButtonWithText;

ButtonWithText *
button_with_text_new (
  const char * text,
  int          themable);

/**
 * Updates the position.
 *
 * Must be called at least once before drawing.
 */
void
button_with_text_update_position (
  ButtonWithText * self,
  float            x,
  float            y);

void
button_with_text_draw (
  ButtonWithText * self);

/**
 * @}
 */

#endif
