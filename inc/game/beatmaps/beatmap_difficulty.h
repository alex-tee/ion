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
 * Beatmap difficulty.
 */

#ifndef __GAME_BEATMAPS_BEATMAP_DIFFICULTY_H__
#define __GAME_BEATMAPS_BEATMAP_DIFFICULTY_H__

/**
 * @addtogroup beatmaps
 *
 * @{
 */

/** The default value used for all difficulty
 * settings except slider multiplier and
 * slider tick rate. */
#define BEATMAP_DIFFICULTY_DEFAULT 5

typedef struct BeatmapDifficulty
{
  int              id;
  float            drain_rate;
  float            circle_size;
  float            overall_difficulty;
  float            approach_rate;
  double           slider_multiplier;
  double           slider_tick_rate;
}

/**
 * Maps a difficulty value [0, 10] to a two-piece
 * linar range of values.
 *
 * @param difficulty The difficulty value to be
 *   mapped.
 * @param min Minimum of the resulting range which
 *   will be achieved by a difficulty value of 0.
 * @param mid Midpoint of the resulting range which
 *   will be achieved by a difficulty value of 5.
 * @param max Maximum of the resulting range which
 *   will be achieved by a difficulty value of 10.
 *
 * @return Value to which the difficulty value maps
 *   in the specified range.
 */
double
beatmap_difficulty_range (
  double difficulty,
  double min,
  double mid,
  double max);

/**
 * @}
 */

#endif
