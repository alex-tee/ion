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

project(
  'ion', 'c',
  version : '0.1',
  license: 'AGPLv3+',
  default_options: [
    'warning_level=3',
    'buildtype=debug',
    'c_std=gnu11',
    ],
  )

cc = meson.get_compiler ('c')

root_inc = include_directories ('.')
inc_inc = include_directories ('inc')

all_inc = [
  root_inc,
  inc_inc,
  ]

try_ion_cflags = [
  '-Wno-unused-parameter',
  ]

ion_cflags = []
foreach f : try_ion_cflags
  if cc.has_argument (f)
    ion_cflags += f
  endif
endforeach

ion_deps = [
  dependency('glfw3'),
  dependency('gl'),
]

subdir ('src')