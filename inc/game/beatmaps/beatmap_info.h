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
 * Beatmap info.
 */

#ifndef __GAME_BEATMAPS_BEATMAP_INFO_H__
#define __GAME_BEATMAPS_BEATMAP_INFO_H__

#include "game/beatmaps/beatmap_difficulty.h"

/**
 * @addtogroup beatmaps
 *
 * @{
 */

typedef enum BeatmapSetOnlineStatus
{
  BEATMAP_SET_ONLINE_STATUS_NONE = -3,
  BEATMAP_SET_ONLINE_STATUS_GRAVEYARD = -2;
  BEATMAP_SET_ONLINE_STATUS_WIP = -1;
  BEATMAP_SET_ONLINE_STATUS_PENDING = 0;
  BEATMAP_SET_ONLINE_STATUS_RANKED = 1;
  BEATMAP_SET_ONLINE_STATUS_APPROVED = 2;
  BEATMAP_SET_ONLINE_STATUS_QUALIFIED = 3;
  BEATMAP_SET_ONLINE_STATUS_LOVED = 4;
} BeatmapSetOnlineStatus;

typedef struct BeatmapMetadata
{
  int              id;

  /** Romanized title. */
  char *           title;

  /** Unicode title. */
  char *           title_unicode;

  /** Romanized artist. */
  char *           artist;

  /** Unicode artist. */
  char *           artist_unicode;

  BeatmapInfo *    beatmaps[16];
  int              num_beatmaps;

  BeatmapSetInfo * beatmap_sets[16];
  int              num_beatmap_sets;

  /** Author user. */
  User             author;

  char *           source;
  char *           tags;
  int              preview_time;
  char *           audio_file;
  char *           background_file;
  char *           video_file;
}

typedef struct BeatmapSetInfo
{
  int              id;
  int              online_id;
  time_t           date_added;
  BeatmapSetOnlineStatus status;

  BeatmapMetadata  metadata;

  BeatmapInfo *    beatmaps;
  int              num_beatmaps;

  BeatmapSetOnlineInfo online_info;

  BeatmapSetMetrics metrics;

  /** The maximum star difficulty of all beatmaps
   * in this set. */
  double           max_star_difficulty;

  /** The maximum playable length in ms of all
   * beatmaps in this set. */
  double           max_length;

  /** The maximum BPM of all beatmaps in this set. */
  double           max_bpm;

  int              delete_pending;
  char *           hash;
  char *           storyboard_file;

  BeatmapSetFileInfo * files[16];
  int              num_files;

  int              is_protected;
} BeatmapSetInfo;

typedef struct BeatmapSetOnlineGenre
{
  int      id;
  char *   name;
} BeatmapSetOnlineGenre;

typedef struct BeatmapSetOnlineLanguage
{
  int      id;
  char *   name;
} BeatmapSetOnlineLanguage;

typedef struct BeatmapSetOnlineCovers
{
  char *        cover_low_res;
  char *        cover;
  char *        card_low_res;
  char *        card;
  char *        list_low_res;
  char *        list;
} BeatmapSetOnlineCovers;

typedef struct BeatmapSetOnlineAvailability
{
  int           download_disabled;
  char *        external_link;
} BeatmapSetOnlineAvailability;

/**
 * Beatmap set info retrieved for previewing locally
 * without having the set downloaded.
 */
typedef struct BeatmapSetOnlineInfo
{
  /** The date this bneatmap was submitted to the
   * online listing. */
  time_t           submitted;

  /** The date this beatmap set was ranked. */
  time_t           ranked;

  /** The date this beatmap set was last updated. */
  time_t           last_updated;

  /** The status of this beatmap set. */
  BeatmapSetOnlineStatus status;

  /** Whether this beatmap set has a background
   * video. */
  int              has_video;

  int              has_storyboard;

  /** The different sizes of cover art for this
   * beatmap set. */
  BeatmapSetOnlineCovers covers;

  /** A small sample clip of this beatmap set's
   * song. */
  char *           preview;

  /** BPM of this beatmap set's song. */
  double           bpm;

  /** The amount of plays this beatmap set has. */
  int              playcount;

  /** The amount of people who have favorited this
   * beatmap set. */
  int              favorite_count;

  /** Whether this beatmap set has been favorited
   * by the current user. */
  int              has_favorited;

  /** The availability of this beatmap set. */
  BeatmapSetOnlineAvailability availability;

  /** The song genre of this beatmap set. */
  BeatmapSetOnlineGenre genre;

  /** The song language of this beatmap set. */
  BeatmapSetOnlineLanguage language;
} BeatmapSetOnlineInfo;

typedef struct BeatmapSetFileInfo
{
  int       id;
  int       beatmap_set_info_id;
  int       file_info_id;
  FileInfo  file_info;
  char *    filename;
} BeatmapSetFileInfo;

/**
 * Beatmap metrics based on accumulated online data
 * from community plays.
 */
typedef struct BeatmapMetrics
{
  /** Points of failure on a relative time scale
   * (usually 0-100). */
  int      fails[16];

  /** Points of retry on a relative time scale
   * (usually 0-100). */
  int      retries[16];
} BeatmapMetrics;

/**
 * BeatmapSetMetrics is the same struct as
 * BeatmapMetrics.
 */
typedef struct BeatmapMetrics BeatmapSetMetrics;

/**
 * Beatmap info retrieved for previewing locally
 * without having the beatmap downloaded.
 */
typedef struct BeatmapOnlineInfo
{
  /** The amount of circles in this beatmap. */
  int         circle_count;

  /** The amount of sliders in this beatmap. */
  int         slider_count;

  /** The amount of plays this beatmap has. */
  int         play_count;

  /** The amount of passes this beatmap has. */
  int         pass_count;
} BeatmapOnlineInfo;

typedef struct BeatmapInfo
{
  int              id;
  int              version;
  int              online_id;
  int              set_info_id;

  BeatmapSetOnlineStatus status;
  BeatmapSetInfo   beatmap_set;
  BeatmapMetadata  metadata;
  int              base_difficulty_id;
  BeatmapDifficulty base_difficulty;
  BeatmapMetrics   metrics;

  BeatmapOnlineInfo online_info;

  /** The playable length in ms of this
   * beatmap. */
  double           length;

  /** The most common BPM in this beatmap. */
  double           bpm;

  char *           path;

  /** SHA2 hash. */
  char *           hash;

  int              hidden;

  /** MD5 hash. */
  char *           md5_hash;

  /* --------------- GENERAL ---------------- */

  double           audio_lead_in;

  /** Boolean. */
  int              countdown;

  float            stack_leniency;
  int              special_style;

  int              ruleset_id;
  RulesetInfo      ruleset;
  /* TODO */

} BeatmapInfo;

/**
 * @}
 */

#endif
