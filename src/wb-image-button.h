/*
 *  Weibird - View and compose weibo
 *  Copyright (C) 2018-2019 Jonathan Kang <jonathankang@gnome.org>.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef WB_IMAGE_BUTTON_H_
#define WB_IMAGE_BUTTON_H_

#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef enum
{
    WB_MEDIA_TYPE_AVATAR,
    WB_MEDIA_TYPE_IMAGE
} WbMediaType;

#define WB_TYPE_IMAGE_BUTTON (wb_image_button_get_type ())
G_DECLARE_FINAL_TYPE (WbImageButton, wb_image_button, WB, IMAGE_BUTTON, GtkWidget)

gint wb_image_button_get_nth_media (WbImageButton *image_button);
WbMediaType wb_image_button_get_media_type (WbImageButton *image_button);
GdkPixbuf *wb_image_button_get_pixbuf (WbImageButton *image_button);
WbImageButton *wb_image_button_new (WbMediaType type,
                                    const gchar *uri,
                                    gint nth_media,
                                    gint width,
                                    gint height);

G_END_DECLS

#endif /* WB_IMAGE_BUTTON_H_ */
