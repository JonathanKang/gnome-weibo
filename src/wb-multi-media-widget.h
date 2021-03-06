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

#ifndef WB_MULTI_MEDIA_WIDGET_H_
#define WB_MULTI_MEDIA_WIDGET_H_

#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define WB_TYPE_MULTI_MEDIA_WIDGET (wb_multi_media_widget_get_type ())
G_DECLARE_FINAL_TYPE (WbMultiMediaWidget, wb_multi_media_widget, WB, MULTI_MEDIA_WIDGET, GtkGrid)

void wb_multi_media_widget_populate_images (WbMultiMediaWidget *self,
                                            const GArray *pic_uris);
WbMultiMediaWidget *wb_multi_media_widget_new (void);

G_END_DECLS

#endif /* WB_MULTI_MEDIA_WIDGET_H_ */
