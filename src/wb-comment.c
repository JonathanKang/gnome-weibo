/*
 *  Weibird - view and compose weibo
 *  copyright (c) 2019 jonathan kang <jonathankang@gnome.org>.
 *
 *  this program is free software: you can redistribute it and/or modify
 *  it under the terms of the gnu general public license as published by
 *  the free software foundation, either version 3 of the license, or
 *  (at your option) any later version.
 *
 *  this program is distributed in the hope that it will be useful,
 *  but without any warranty; without even the implied warranty of
 *  merchantability or fitness for a particular purpose.  see the
 *  gnu general public license for more details.
 *
 *  you should have received a copy of the gnu general public license
 *  along with this program.  if not, see <http://www.gnu.org/licenses/>.
 */

#include <json-glib/json-glib.h>

#include "wb-comment.h"

G_DEFINE_TYPE (WbComment, wb_comment, G_TYPE_OBJECT)

static void
wb_comment_parse_json_object (WbComment *self,
                              JsonObject *jobject)
{
    JsonObject *user_object;

    self->created_at = g_strdup (json_object_get_string_member (jobject, "created_at"));
    self->id = json_object_get_int_member (jobject, "id");
    self->text = g_strdup (json_object_get_string_member (jobject, "text"));
    self->idstr = g_strdup (json_object_get_string_member (jobject, "idstr"));

    if (json_object_has_member (jobject, "user"))
    {
        user_object = json_object_get_object_member (jobject, "user");
        self->user = wb_user_new (user_object);
    }
}

static void
wb_comment_finalize (GObject *object)
{
    WbComment *self = WB_COMMENT (object);

    g_free (self->created_at);
    g_free (self->text);
    g_free (self->idstr);
    g_object_unref (self->user);

    G_OBJECT_CLASS (wb_comment_parent_class)->finalize (object);
}

static void
wb_comment_class_init (WbCommentClass *klass)
{
		GObjectClass *object_class = G_OBJECT_CLASS (klass);

		object_class->finalize = wb_comment_finalize;
}

static void
wb_comment_init (WbComment *self)
{
}

/**
 * wb_comment_new:
 *
 * Create a new #WbComment.
 *
 * Returns: (transfer full): a newly created #WbComment
 */
WbComment *
wb_comment_new (JsonObject *jobject)
{
    WbComment *comment;

    comment = g_object_new (WB_TYPE_COMMENT, NULL);

    wb_comment_parse_json_object (comment, jobject);

    return comment;
}
