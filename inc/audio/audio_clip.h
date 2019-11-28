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
 * Audio clip.
 */

#ifndef __AUDIO_AUDIO_CLIP_H__
#define __AUDIO_AUDIO_CLIP_H__

/**
 * @addtogroup audio
 *
 * @{
 */

/**
 * An audio clip to be used for small audio files.
 */
typedef struct AudioClip
{
  char *       abs_path;
  float *      frames;
  int          num_frames;
  unsigned int num_channels;
} AudioClip;

/**
 * Creates a new audio clip.
 */
AudioClip *
audio_clip_new (
  const char * abs_path);

/**
 * @}
 */

#endif

