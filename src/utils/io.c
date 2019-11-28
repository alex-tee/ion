/*
 * Copyright (C) 2018-2019 Alexandros Theodotou
 *
 * This file is part of Zrythm
 *
 * Zrythm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zrythm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Zrythm.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * \file
 *
 * IO utils.
 */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "utils/io.h"

#include <glib.h>

/**
 * Gets directory part of filename. MUST be freed.
 */
char *
io_get_dir (const char * filename) ///< filename containing directory
{
  return g_path_get_dirname (filename);
}

/**
 * Makes directory if doesn't exist.
 */
void
io_mkdir (const char * dir)
{
  struct stat st = {0};
  if (stat(dir, &st) == -1)
    {
      g_mkdir_with_parents (dir, 0700);
    }
}

/**
 * Returns file extension or NULL.
 */
char *
io_file_get_ext (const char * file)
{
  char ** parts = g_strsplit (file, ".", 2);
  char * file_part = parts[0];
  char * ext_part = parts[1];

  g_free (file_part);

  return ext_part;
}

/**
 * Gets home dir. MUST be freed.
 */
const char *
io_get_home_dir ()
{
  return g_get_home_dir ();
}

/**
 * Creates the file if doesn't exist
 */
FILE *
io_touch_file (const char * filename)
{
  return fopen(filename, "ab+");
}

/**
 * Strips extensions from given filename.
 *
 * MUST be freed.
 */
char *
io_file_strip_ext (const char * filename)
{
  char ** parts = g_strsplit (filename, ".", 2);
  char * file_part =
    g_strdup (parts[0]);
  g_strfreev (parts);
  return file_part;
}

/**
 * Strips path from given filename.
 *
 * MUST be freed.
 */
char *
io_path_get_basename (const char * filename)
{
  return g_path_get_basename (filename);
}

char *
io_path_get_parent_dir (const char * path)
{
  char ** parts = g_strsplit (path, G_DIR_SEPARATOR_S, -1);
  char * new_str = NULL;
  char * prev_str = NULL;
  int num_parts = 0;
  while (parts[num_parts])
    {
      num_parts++;
    }

  /* root */
  if (num_parts < 2)
    new_str = g_strdup (G_DIR_SEPARATOR_S);
  else
    {
      for (int i = 0; i < num_parts - 1; i++)
        {
          prev_str = new_str;

          if (i == 1)
            new_str = g_strconcat (new_str,
                                   parts[i],
                                   NULL);
          else if (i == 0)
            new_str = g_strconcat (G_DIR_SEPARATOR_S,
                                   parts[i],
                                   NULL);
          else
            new_str = g_strconcat (new_str,
                                   G_DIR_SEPARATOR_S,
                                   parts[i],
                                   NULL);

          if (prev_str)
            g_free (prev_str);
        }
    }

  g_strfreev (parts);

  g_message ("parent dir for %s is %s",
             path,
             new_str);
  return new_str;
}

char *
io_file_get_creation_datetime (const char * filename)
{
  /* TODO */
  return NULL;
}

char *
io_file_get_last_modified_datetime (
  const char * filename)
{
  struct stat result;
  struct tm *nowtm;
  char tmbuf[64];
  if (stat (filename, &result)==0)
    {
      nowtm = localtime (&result.st_mtime);
      strftime(tmbuf, sizeof (tmbuf), "%Y-%m-%d %H:%M:%S", nowtm);
      char * mod = g_strdup (tmbuf);
      return mod;
    }
  g_message ("Failed to get last modified for %s",
             filename);
  return NULL;
}

/**
 * Removes the given file.
 */
int
io_remove (
  const char * path)
{

  return 0;
}

/**
 * Removes a dir, optionally forcing deletion.
 */
int
io_rmdir (
  const char * path,
  int          force)
{
  /* TODO */
  g_message ("Removing %s", path);

  return 0;
}

/**
 * Appends files to the given array from the given
 * dir if they end in the given string.
 *
 * @param end_string If empty, appends all files.
 */
static void
append_files_from_dir_ending_in (
  char ***     files,
  int *        num_files,
  const int    recursive,
  const char * _dir,
  const char * end_string)
{
  GDir *dir;
  GError *error;
  const gchar *filename;
  char * full_path;

  dir = g_dir_open (_dir, 0, &error);
  while ((filename = g_dir_read_name (dir)))
    {
      full_path =
        g_build_filename (
          _dir, filename, NULL);

      /* recurse if necessary */
      if (recursive &&
          g_file_test (
            full_path, G_FILE_TEST_IS_DIR))
        {
          append_files_from_dir_ending_in (
            files, num_files, recursive, full_path,
            end_string);
        }

      if (!end_string ||
          (end_string &&
             g_str_has_suffix (
               full_path, end_string)))
        {
          *files =
            realloc (
              *files,
              sizeof (char *) *
                (size_t) (*num_files + 2));
          (*files)[(*num_files)] =
            g_strdup (full_path);
          (*num_files)++;
        }

      g_free (full_path);
    }

  /* NULL terminate */
  (*files)[*num_files] = NULL;
}

/**
 * Returns a list of the files in the given
 * directory.
 *
 * @param dir The directory to look for.
 *
 * @return a NULL terminated array of strings that
 *   must be free'd with g_strfreev().
 */
char **
io_get_files_in_dir_ending_in (
  const char * _dir,
  const int    recursive,
  const char * end_string)
{
  char ** arr =
    calloc (1, sizeof (char *));
  int count = 0;

  append_files_from_dir_ending_in (
    &arr, &count, recursive, _dir, end_string);

  return arr;
}

/**
 * Returns a newly allocated path that is either
 * a copy of the original path if the path does
 * not exist, or the original path appended with
 * (n), where n is a number.
 *
 * Example: "myfile" -> "myfile (1)"
 */
char *
io_get_next_available_filepath (
  const char * filepath)
{
  int i = 1;
  char * file_without_ext =
    io_file_strip_ext (filepath);
  char * file_ext =
    io_file_get_ext (filepath);
  char * new_path = g_strdup (filepath);
  while (io_file_exists (new_path))
    {
      if (g_file_test (
            new_path, G_FILE_TEST_IS_DIR))
        {
          g_free (new_path);
          new_path =
            g_strdup_printf (
              "%s (%d)", filepath, i++);
        }
      else
        {
          g_free (new_path);
          new_path =
            g_strdup_printf (
              "%s (%d).%s",
              file_without_ext, i++,
              file_ext);
        }
    }
  g_free (file_without_ext);
  g_free (file_ext);

  return new_path;
}

/**
 * Opens the given directory using the default
 * program.
 */
void
io_open_directory (
  const char * path)
{
  g_return_if_fail (
    g_file_test (path, G_FILE_TEST_IS_DIR));
  char * command =
    g_strdup_printf (
      "xdg-open \"%s\"",
      path);
  FILE* file = popen (command, "r");
  pclose(file);
  g_free (command);
}
