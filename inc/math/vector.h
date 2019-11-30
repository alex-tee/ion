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
 * Vectors.
 */

#ifndef __MATH_VECTOR_H__
#define __MATH_VECTOR_H__

/**
 * @addtogroup math
 *
 * @{
 */

/**
 * Vector.
 */
typedef struct Vector2f
{
  float x;
  float y;
} Vector2f;

typedef struct Vector3f
{
  float x;
  float y;
  float z;
} Vector3f;

/**
 * @}
 */

#endif
