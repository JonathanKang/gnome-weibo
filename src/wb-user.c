/*
 *  Weibird - View and compose weibo
 *  Copyright (C) 2019 Jonathan Kang <jonathankang@gnome.org>.
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

#include <json-glib/json-glib.h>

#include "wb-user.h"

G_DEFINE_TYPE (WbUser, wb_user, G_TYPE_OBJECT)

static void
wb_user_parse_json_object (WbUser *self,
                           JsonObject *jobject)
{
    self->id = json_object_get_int_member (jobject, "id");
    self->idstr = g_strdup (json_object_get_string_member (jobject, "idstr"));
    self->name = g_strdup (json_object_get_string_member (jobject, "name"));
    self->nickname = g_strdup (json_object_get_string_member (jobject, "remark"));
    self->location = g_strdup (json_object_get_string_member (jobject, "location"));
    self->profile_image_url = g_strdup (json_object_get_string_member (jobject,
                                                                       "profile_image_url"));
}

static void
wb_user_finalize (GObject *object)
{
    WbUser *self = WB_USER (object);

    g_free (self->idstr);
    g_free (self->name);
    g_free (self->nickname);
    g_free (self->location);
    g_free (self->description);
    g_free (self->url);
    g_free (self->profile_image_url);
    g_free (self->gender);
    g_free (self->created_at);

    G_OBJECT_CLASS (wb_user_parent_class)->finalize (object);
}

static void
wb_user_class_init (WbUserClass *klass)
{
		GObjectClass *object_class = G_OBJECT_CLASS (klass);

		object_class->finalize = wb_user_finalize;
}

static void
wb_user_init (WbUser *self)
{
}

/**
 * wb_user_new:
 *
 * Create a new #WbUser.
 *
 * Returns: (transfer full): a newly created #WbUser
 */
WbUser *
wb_user_new (JsonObject *jobject)
{
    WbUser *user;

    user = g_object_new (WB_TYPE_USER, NULL);

    wb_user_parse_json_object (user, jobject);

    return user;
}
