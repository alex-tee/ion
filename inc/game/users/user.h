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
 * User.
 */

#ifndef __GAME_USERS_USER_H__
#define __GAME_USERS_USER_H__

#include <time.h>

#include "game/users/user_activity"
#include "game/users/user_status"

/**
 * @addtogroup users
 *
 * @{
 */

typedef struct Country
{
  /** The name of this country. */
  char *      full_name;

  /** Two-letter flag acronym (ISO 3166 standard). */
  char *      flag_name;
} Country;

typedef enum UserPlayStyle
{
  USER_PLAY_STYLE_KEYBOARD,
  USER_PLAY_STYLE_MOUSE,
  USER_PLAY_STYLE_TABLET,
  USER_PLAY_STYLE_TOUCH,
} UserPlayStyle;

typedef struct UserBadge
{
  time_t    awarded_at;
  char *    description;
  char *    image_url;
} UserBadge;

typedef struct UserAchievement
{
  time_t    achieved_at;

  /** Achievement ID. */
  int       id;
} UserAchievement;

typedef struct User
{
  long          id;
  time_t        join_date;
  char *        username;
  char *        previous_usernames[8];
  Country       country;
  UserStatus    status;
  UserActivity  activity;
  char *        color;
  char *        avatar_url;
  int           is_admin;
  int           is_supporter;
  int           support_level;
  int           is_gmt;
  int           is_qat;
  int           is_bng;
  int           is_bot;
  int           active;
  int           is_online;
  int           pm_friends_only;
  char *        title;
  char *        location;
  time_t        last_visit;
  UserPlayStyle play_styles[8];
  int           num_play_styles;
  char *        play_mode;
  UserStatistics statistics;
  UserBadge     badges[8];
  int           num_badges;
  UserAchievement achievements[8];
  int           num_achievements;
} User;

/**
 * Creates a user instance for displaying locally
 * created system messages.
 */
User *
user_create_system (void);

/**
 * @}
 */

#endif
