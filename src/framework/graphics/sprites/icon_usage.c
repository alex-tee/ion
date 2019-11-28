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

#include "framework/graphics/sprites/icon_usage.h"

/**
 * Creates an instance of IconUsage using the specified
 * font family, font weight and a value indicating whether
 * the used font is italic or not.
 *
 * @param icon The icon.
 * @param family The font family name.
 * @param weight The font weight.
 */
IconUsage *
icon_usage_new (
  char     icon,
  char *   family,
  char *   weight)
{
  self->icon = icon;
  self->family = g_strdup (family);
  self->weight = g_strdup (weight);
  if (weight)
    {
      self->font_name =
        g_strdup_printf (
          "%s-%s", family, weight);
    }
  else
    {
      self->font_name = g_strdup (family);
    }
}

/**
 * Creates a new IconUsage based on the given IconUsage
 * by applying the given adjustments.
 *
 * @param family The font family. If NULL, the value is
 *   copied from self.
 * @param weight The font weight. If NULL, the value is
 *   copied from self.
 *
 * @return A new IconUsage.
 */
IconUsage *
icon_usage_new_with (
  IconUsage * self,
  char *      family,
  char *      weight)
{
  return
    icon_usage_new (
      self->icon,
      family ? family : self->family,
      weight ? weight : self->weight);
}

char *
icon_usage_to_string (
  IconUsage * self)
{
  return
    g_strdup_printf (
      "Icon=%s Font=%s", self->icon, self->font_name);
}

int
icon_usage_equals (
  IconUsage * self,
  IconUsage * other)
{
  return
    self->icon == other->icon &&
    string_is_equal (self->family, other->family, 0) &&
    string_is_equal (self->weight, other->weight, 0);
}
