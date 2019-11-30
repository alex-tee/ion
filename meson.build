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
    'warning_level=2',
    'buildtype=debug',
    'c_std=gnu11',
    ],
  )

prefix = get_option ('prefix')
bindir = join_paths (prefix, get_option('bindir'))
datadir = join_paths (prefix, get_option('datadir'))
iondatadir = join_paths (datadir, 'ion')
glsldir = join_paths (datadir, 'glsl')

cdata = configuration_data ()
cdata.set_quoted (
  'PACKAGE_VERSION',
  '@VCS_TAG@')
cdata.set_quoted (
  'COMPILER',
  meson.get_compiler('c').get_id())
cdata.set_quoted (
  'PREFIX', prefix)
cdata.set_quoted (
  'COMPILER_VERSION',
  meson.get_compiler('c').version())
cdata.set_quoted (
  'CONFIGURE_DATADIR',
  datadir)
cdata.set_quoted (
  'GLSL_DIR', glsldir)
cdata.set (
  'MESON_SOURCE_ROOT',
  meson.source_root ())
cdata.set (
  'MESON_BUILD_ROOT',
  meson.build_root ())

cc = meson.get_compiler ('c')

root_inc = include_directories ('.')
inc_inc = include_directories ('inc')

all_inc = [
  root_inc,
  inc_inc,
  ]

try_ion_cflags = [
  '-Wno-unused-parameter',
  '-Werror=implicit-function-declaration',
  ]

ion_cflags = cc.get_supported_arguments (
  try_ion_cflags)

#try_ion_ldflags = [
  #'-ldl',
  #]
#ion_ldflags = cc.get_supported_link_arguments (
  #try_ion_ldflags)

ion_deps = [
  dependency('glfw3'),
  dependency('gl'),
  dependency('pangocairo'),
  dependency('x11'),
  cc.find_library('dl', required: false),
  cc.find_library('SOIL'),
]

# create config.h
tmp_h = configure_file (
  output: 'tmp.h',
  configuration: cdata,
  )
config_h_vcs = vcs_tag (
  input: tmp_h,
  output: 'config.h',
  )
config_h_dep = declare_dependency (
  sources: config_h_vcs,
  )
ion_deps += config_h_dep

subdir ('data')
subdir ('src')

summary = [
  '',
  '------',
  'Ion @0@'.format(meson.project_version()),
  '',
  '  Build type: @0@'.format(
    get_option('buildtype')),
  '  Directories:',
  '            prefix: @0@'.format(prefix),
  '           datadir: @0@'.format(datadir),
  '------',
  ''
]
message('\n'.join(summary))
