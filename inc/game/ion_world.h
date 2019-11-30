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
 * Ion world.
 */

#ifndef __GAME_ION_WORLD_H__
#define __GAME_ION_WORLD_H__

typedef struct GLFWwindow GLFWwindow;
typedef struct SkinManager SkinManager;
typedef struct Texture Texture;
typedef struct ShaderManager ShaderManager;
typedef struct MainMenu MainMenu;

/**
 * @addtogroup game
 *
 * @{
 */

#define ION_WORLD ion_world

#define ION_WORLD_DEFAULT_WIDTH 1920
#define ION_WORLD_DEFAULT_HEIGHT 1080

/**
 * The screen to be displayed.
 */
typedef enum IonWorldScreen
{
  /** Welcome splash. */
  ION_WORLD_SCREEN_WELCOME,

  /** Main menu screen (where player selects to play,
   * view options, etc. */
  ION_WORLD_SCREEN_MAIN_MENU,

  /** Main screen where beatmaps are shown. */
  ION_WORLD_SCREEN_MAIN,

  /** Song screen during gameplay. */
  ION_WORLD_SCREEN_SONG,

  /** Ranking view. */
  ION_WORLD_SCREEN_RANKING,
} IonWorldScreen;

/**
 * The global game struct.
 */
typedef struct IonWorld
{
  IonWorldScreen   screen;
  SkinManager *    skin_manager;

  /** The game GLFW window. */
  GLFWwindow *     window;

  int              viewport_width;
  int              viewport_height;

  int              monitor_width;
  int              monitor_height;

  char *           skins_dir;
  char *           beatmaps_dir;

  /** Last draw time in seconds. */
  double           last_draw_time;

  /** Current draw time. */
  double           cur_draw_time;

  /* FIXME delete */
  Texture *        test_texture;

  MainMenu *       main_menu;

  ShaderManager *  shader_manager;
} IonWorld;

extern IonWorld * ion_world;
IonWorld * ion_world;

/**
 * Creates a new game world.
 */
IonWorld *
ion_world_new (
  GLFWwindow * window,
  int          monitor_width,
  int          monitor_height);

void
ion_world_load_skin (
  IonWorld * self);

/**
 * To be called when the framebuffer size changes.
 */
void
ion_world_update_texture_sizes (
  IonWorld * self);

/**
 * Renders the current scene.
 */
void
ion_world_render_scene (
  IonWorld * self);

void
ion_world_free (
  IonWorld * self);

/**
 * @}
 */

#endif
