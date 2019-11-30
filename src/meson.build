# Copyright (C) 2019 Alexandros Theodotou <alex at zrythm dot org>
#
# This file is part of Ion
#
# Ion is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Ion is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with Ion.  If not, see <https://www.gnu.org/licenses/>.

ion_main = files ('main.c')
ion_srcs = files ([
  'glad.c',
  'glad_glx.c',
  ])

subdir ('game')
subdir ('gui')
subdir ('math')
subdir ('utils')

ion_exe = executable(
  'ion',
  sources: [
    ion_main,
    ion_srcs,
    ],
  dependencies: ion_deps,
  include_directories: all_inc,
  c_args: ion_cflags,
  #link_args: ion_ldflags,
  install: true,
  )

test('basic', ion_exe)
