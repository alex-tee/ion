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
 * Skin.
 */

#ifndef __GAME_SKINNING_SKIN_H__
#define __GAME_SKINNING_SKIN_H__

#include "gui/cursor.h"
#include "gui/rgba.h"

typedef struct AudioClip AudioClip;
typedef struct Texture Texture;
typedef struct IonDrawable IonDrawable;

/**
 * @addtogroup skinning
 *
 * @{
 */

typedef enum SkinFormatVersion
{
  SKIN_FORMAT_VERSION_1_0,
  SKIN_FORMAT_VERSION_LATEST,
} SkinFormatVersion;

typedef struct Skin
{
  int             id;

  /** Absolute path to the skin folder. */
  char *          path;

  char *          name;
  char *          hash;
  char *          creator;

  /** Skin format version (not skin version). */
  SkinFormatVersion version;

  IonRGBA         combo_colors[16];
  int             num_combo_colors;

  IonCursor          cursor;

  IonDrawable *      logo;
  IonDrawable *      menu_bg;
  Texture *       selection_mod_autoplay;
  Texture *       selection_mod_cinema;
  Texture *       selection_mod_doubletime;
  Texture *       selection_mod_flashlight;
  Texture *       selection_mod_hardrock;
  Texture *       selection_mod_hidden;
  Texture *       selection_mod_nightcore;
  Texture *       selection_mod_nofail;
  Texture *       selection_mod_perfect;
  Texture *       selection_mod_relax;
  Texture *       selection_mod_autopilot;
  Texture *       selection_mod_spunout;

  /** Note: animation names: play-skip-{n}.png. */
  Texture *       play_skip;

  Texture *       play_unranked;
  Texture *       play_warning_arrow;
  Texture *       arrow_pause;
  Texture *       arrow_warning;
  Texture *       multi_skipped;
  Texture *       section_fail_texture;
  Texture *       section_pass_texture;
  Texture *       count1;
  Texture *       count2;
  Texture *       count3;
  Texture *       go;
  Texture *       ready;

  /* note: these can be animated */
  Texture *       hit0;
  Texture *       hit50;
  Texture *       hit100;
  Texture *       hit100k;
  Texture *       hit300;
  Texture *       hit300g;
  Texture *       hit300k;

  Texture *       pause_overlay;
  Texture *       fail_bg;
  Texture *       pause_back;
  Texture *       pause_continue;
  Texture *       pause_replay;
  Texture *       pause_retry;
  Texture *       scorebar_bg;
  Texture *       scorebar_color;
  Texture *       scorebar_ki;
  Texture *       scorebar_kidanger;
  Texture *       scorebar_kidanger2;
  Texture *       scorebar_marker;
  Texture *       score0;
  Texture *       score1;
  Texture *       score2;
  Texture *       score3;
  Texture *       score4;
  Texture *       score5;
  Texture *       score6;
  Texture *       score7;
  Texture *       score8;
  Texture *       score9;
  Texture *       score_comma;
  Texture *       score_dot;
  Texture *       score_percent;
  Texture *       score_x;
  Texture *       ranking_xh;
  Texture *       ranking_xh_small;
  Texture *       ranking_x;
  Texture *       ranking_x_small;
  Texture *       ranking_sh;
  Texture *       ranking_sh_small;
  Texture *       ranking_s;
  Texture *       ranking_s_small;
  Texture *       ranking_a;
  Texture *       ranking_a_small;
  Texture *       ranking_b;
  Texture *       ranking_b_small;
  Texture *       ranking_c;
  Texture *       ranking_c_small;
  Texture *       ranking_d;
  Texture *       ranking_d_small;
  Texture *       ranking_accuracy;
  Texture *       ranking_graph;
  Texture *       ranking_maxcombo;
  Texture *       ranking_panel;
  Texture *       ranking_perfect;
  Texture *       ranking_title;
  Texture *       ranking_replay;
  Texture *       ranking_retry;
  Texture *       ranking_winner;
  Texture *       score_entry0;
  Texture *       score_entry1;
  Texture *       score_entry2;
  Texture *       score_entry3;
  Texture *       score_entry4;
  Texture *       score_entry5;
  Texture *       score_entry6;
  Texture *       score_entry7;
  Texture *       score_entry8;
  Texture *       score_entry9;
  Texture *       score_entry_comma;
  Texture *       score_entry_dot;
  Texture *       score_entry_percent;
  Texture *       score_entry_x;
  Texture *       menu_back_texture;
  Texture *       menu_button_bg;
  Texture *       selection_mode;
  Texture *       selection_mode_over;
  Texture *       selection_mods;
  Texture *       selection_mods_over;
  Texture *       selection_random;
  Texture *       selection_random_over;
  Texture *       selection_options;
  Texture *       selection_options_over;
  Texture *       selection_tab;
  Texture *       star;
  Texture *       star2;
  Texture *       mode_osu;
  Texture *       mode_taiko;
  Texture *       mode_fruits;
  Texture *       mode_mania;
  Texture *       mode_osu_med;
  Texture *       mode_taiko_med;
  Texture *       mode_fruits_med;
  Texture *       mode_mania_med;
  Texture *       mode_osu_small;
  Texture *       mode_taiko_small;
  Texture *       mode_fruits_small;
  Texture *       mode_mania_small;
  Texture *       comboburst;
  Texture *       default0;
  Texture *       default1;
  Texture *       default2;
  Texture *       default3;
  Texture *       default4;
  Texture *       default5;
  Texture *       default6;
  Texture *       default7;
  Texture *       default8;
  Texture *       default9;
  Texture *       approach_circle;
  Texture *       hit_circle;
  Texture *       hit_circle_overlay;
  Texture *       hit_circle_select;
  Texture *       follow_points[16];
  int             num_follow_points;
  Texture *       lighting;
  Texture *       slider_start_circle;
  Texture *       slider_start_overlay;
  Texture *       slider_end_circle;
  Texture *       slider_end_overlay;
  Texture *       reverse_arrow;
  Texture *       slider_follow_circle;
  Texture *       slider_ball_flips[16];
  int             num_slider_ball_flips;
  Texture *       sliderb_nd;
  Texture *       sliderb_spec;
  Texture *       slider_point_10;
  Texture *       slider_point_30;
  Texture *       slider_score_point;
  Texture *       spinner_approach_circle;
  Texture *       spinner_rpm;
  Texture *       spinner_clear;
  Texture *       spinner_spin_texture;
  Texture *       spinner_glow;
  Texture *       spinner_bottom;
  Texture *       spinner_top;
  Texture *       spinner_middle;
  Texture *       spinner_middle2;
  Texture *       particle_50;
  Texture *       particle_100;
  Texture *       particle_300;

  AudioClip *     heartbeat;
  AudioClip *     seeya;
  AudioClip *     welcome;
  AudioClip *     key_confirm;
  AudioClip *     key_delete;
  AudioClip *     key_movement;
  AudioClip *     key_press1;
  AudioClip *     key_press2;
  AudioClip *     key_press3;
  AudioClip *     key_press4;
  AudioClip *     back_button_click;
  AudioClip *     check_on;
  AudioClip *     check_off;
  AudioClip *     click_close;
  AudioClip *     click_short_confirm;
  AudioClip *     menu_back_clip;
  AudioClip *     menu_hit;
  AudioClip *     menu_back_click;
  AudioClip *     menu_charts_click;
  AudioClip *     menu_direct_click;
  AudioClip *     menu_edit_click;
  AudioClip *     menu_exit_click;
  AudioClip *     menu_freeplay_click;
  AudioClip *     menu_multiplayer_click;
  AudioClip *     menu_options_click;
  AudioClip *     menu_play_click;
  AudioClip *     pause_back_click;
  AudioClip *     select_expand;
  AudioClip *     select_difficulty;
  AudioClip *     shutter;
  AudioClip *     button_hover;
  AudioClip *     click_short;
  AudioClip *     menu_click;
  AudioClip *     menu_back_hover;
  AudioClip *     menu_charts_hover;
  AudioClip *     pause_hover;
  AudioClip *     slider_bar;

  /** This can either be 1 or 3. */
  AudioClip *     counts[3];
  int             num_counts;

  AudioClip *     gos;
  AudioClip *     readys;
  AudioClip *     combo_burst;
  AudioClip *     combo_break;
  AudioClip *     fail_sound;
  AudioClip *     section_pass_clip;
  AudioClip *     section_fail_clip;
  AudioClip *     applause;
  AudioClip *     pause_loop;
  AudioClip *     drum_hit_normal;
  AudioClip *     drum_hit_clap;
  AudioClip *     drum_hit_finish;
  AudioClip *     drum_hit_whistle;
  AudioClip *     drum_slider_tick;
  AudioClip *     drum_slider_slide;
  AudioClip *     drum_slider_whistle;
  AudioClip *     normal_hit_normal;
  AudioClip *     normal_hit_clap;
  AudioClip *     normal_hit_finish;
  AudioClip *     normal_hit_whistle;
  AudioClip *     normal_slider_tick;
  AudioClip *     normal_slider_slide;
  AudioClip *     normal_slider_whistle;
  AudioClip *     soft_hit_soft;
  AudioClip *     soft_hit_clap;
  AudioClip *     soft_hit_finish;
  AudioClip *     soft_hit_whistle;
  AudioClip *     soft_slider_tick;
  AudioClip *     soft_slider_slide;
  AudioClip *     soft_slider_whistle;
  AudioClip *     spinner_spin_clip;
  AudioClip *     spinner_bonus;

  /* TODO */
} Skin;

/**
 * Loads a skin matching the given name from the
 * skin directories.
 *
 * @param path The directory path of the skin.
 */
Skin *
skin_new_from_path (
  const char * path);

Skin *
skin_create_default (void);

/**
 * Returns a texture for the given name.
 *
 * The name must be a base name, such as
 * "menu-background".
 */
Texture *
skin_get_texture (
  Skin *       self,
  const char * lookup_name);

char *
skin_get_full_name (
  Skin * self);

void
skin_update_texture_sizes (
  Skin * self,
  int    fb_width,
  int    fb_height);

/**
 * @}
 */

#endif
