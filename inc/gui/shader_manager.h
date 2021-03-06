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
 * GLSL shader manager.
 */

#ifndef __GUI_SHADER_MANAGER_H__
#define __GUI_SHADER_MANAGER_H__

typedef struct Shader Shader;

/**
 * @addtogroup gui
 *
 * @{
 */

typedef enum ShaderType
{
  SHADER_TYPE_UNCHANGED,
  NUM_SHADER_TYPES,
} ShaderType;

typedef struct ShaderManager
{
  Shader *      shaders[NUM_SHADER_TYPES];
} ShaderManager;

ShaderManager *
shader_manager_new (void);

/**
 * @}
 */

#endif
