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

/*
 * Copyright (c) 2019 ppy Pty Ltd <contact@ppy.sh>.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**
 * \file
 *
 * FontAwesome IconUsage.
 */

#ifndef __FRAMEWORK_GRAPHICS_SPRITES_FONT_AWESOME_H__
#define __FRAMEWORK_GRAPHICS_SPRITES_FONT_AWESOME_H__

typedef struct IconUsage IconUsage;

/**
 * @addtogroup framework
 *
 * @{
 */

typedef enum FontAwesomeWeight
{
  FONT_AWESOME_WEIGHT_REGULAR,
  FONT_AWESOME_WEIGHT_SOLID,
} FontAwesomeWeight;

typedef enum FontAwesomeIconType
{
  FONT_AWESOME_ICON_TYPE_QUESTION,
} FontAwesomeIconType;

/**
 * Returns a new IconUsage for a FontAwesome icon.
 */
IconUsage *
font_awesome_new_icon_usage (
  FontAwesomeWeight   weight,
  FontAwesomeIconType icon);

/**
 * @}
 */

#endif
