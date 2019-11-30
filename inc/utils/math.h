/*
 * Copyright (C) 2018-2019 Alexandros Theodotou <alex at zrythm dot org>
 *
 * This file is part of Zrythm
 *
 * Zrythm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zrythm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Zrythm.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __UTILS_MATH_H__
#define __UTILS_MATH_H__

#include <float.h>
#include <math.h>
#include <stdint.h>

#define MATH_FLOATS_EQUAL(a,b,epsilon) \
  (fabsf (a - b) < epsilon)

/**
 * Checks if 2 floating points are equal.
 *
 * @param epsilon The allowed differene.
 */
static inline int
math_floats_equal (
  const float a,
  const float b,
  const float epsilon)
{
  return fabsf (a - b) < epsilon;
}

/**
 * Checks if 2 doubles are equal.
 *
 * @param epsilon The allowed differene.
 */
static inline int
math_doubles_equal (
  const double a,
  const double b,
  const double epsilon)
{
  return fabs (a - b) < epsilon;
}

#endif
