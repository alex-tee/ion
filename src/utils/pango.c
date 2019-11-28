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

#include <pango/pangocairo.h>

#include "gui/gl.h"
#include "gui/texture.h"
#include "utils/pango.h"

/**
 * Renders the given text in the given font to a
 * GL texture.
 */
Texture *
ion_pango_render_text_to_texture (
  const char * font_descr,
  const char * text)
{
  /*
   * Create a cairo context for PangoLayout objects.
   *
   * The pango layout needs a context in order to
   * function. We use cairo_image_surface_create()
   * with dimensions of 0 x 0 because we won’t
   * actually be rendering to this surface.
   * Instead, we will layout our text
   * and use create_cairo_context to build a context
   * with a surface that is the size of the rendered
   * text.
   *
   * Cairo uses reference counting for  dynamically
   * allocated objects, so we need to call
   * cairo_surface_destroy() when we’re done with the
   * temporary surface. The context still maintains a
   * reference to the surface, so the memory for the
   * surface will not be freed until the context is.
   */
  cairo_surface_t * temp_surface =
    cairo_image_surface_create (
      CAIRO_FORMAT_ARGB32, 0, 0);
  cairo_t * layout_cr = cairo_create (temp_surface);
  cairo_surface_destroy (temp_surface);

  /* Create a PangoLayout, set the font and text */
  PangoLayout * layout =
    pango_cairo_create_layout (layout_cr);
  pango_layout_set_text (layout, text, -1);

  /* Load the font */
  PangoFontDescription * desc =
    pango_font_description_from_string (font_descr);
  pango_layout_set_font_description (layout, desc);
  pango_font_description_free (desc);

  /* get text dimensions (divide by pango scale to
   * get dimensions in pixels) */
  int width, height;
  pango_layout_get_size (layout, &width, &height);
  width /= PANGO_SCALE;
  height /= PANGO_SCALE;

  /* Get text dimensions and create a context to
   * render to (will render on the raw surface) */
  int stride =
    cairo_format_stride_for_width (
      CAIRO_FORMAT_ARGB32, width);
  unsigned char* surface_data =
    calloc (
      stride * height, sizeof (unsigned char));
  cairo_surface_t * surface =
    cairo_image_surface_create_for_data (
      surface_data, CAIRO_FORMAT_ARGB32,
      width, height, stride);
  cairo_t * cr =
    cairo_create (surface);

  /* Render */
  cairo_set_source_rgba (cr, 1, 1, 1, 1);
  pango_cairo_show_layout (cr, layout);

  /* generate an openGL texture ID for the rendered
   * data */
  Texture * texture =
    texture_new_from_raw_data (
      width, height, surface_data);

  /* Clean up */
  free (surface_data);
  g_object_unref (layout);
  cairo_destroy (layout_cr);
  cairo_destroy (cr);
  cairo_surface_destroy (surface);

  /* return the texture */
  return texture;
}
