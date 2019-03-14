/*
 *  Weibird - view and compose weibo
 *  copyright (c) 2018-2019 jonathan kang <jonathankang@gnome.org>.
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

#include <glib.h>
#include <json-glib/json-glib.h>

#include "wb-timeline-list.h"
#include "wb-util.h"

/**
 * wb_util_format_time_string:
 * @time: the time string fetched from Weibo API
 *
 * This function parses the time string fetched from Weibo
 * API(for instance, Wed Mar 06 14:00:58 +0800 2019) and
 * return a meaningful time.
 *
 * Returns: A newly allocated string
 */
gchar *
wb_util_format_time_string (const gchar *time)
{
    const gchar *month_str[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                "July", "Aug", "Sep", "Oct", "Nov", "Dec"};
    gchar *ret;
    gchar *year;
    gchar *day;
    gchar * hour;
    gchar *minute;
    gboolean same_year;
    gboolean same_month;
    gboolean same_day;
    gboolean same_hour;
    gboolean same_minute;
    gchar **vector;
    GDateTime *now;

    g_return_val_if_fail (time != NULL, NULL);

    now = g_date_time_new_now_local ();
    vector = g_strsplit_set (time, " :", -1);
    year = g_strdup_printf ("%d", g_date_time_get_year (now));
    if (g_date_time_get_day_of_month (now) < 10)
    {
        /* Prefix "0" if it's smaller than 10. */
        day = g_strdup_printf ("0%d", g_date_time_get_day_of_month (now));
    }
    else
    {
        day = g_strdup_printf ("%d", g_date_time_get_day_of_month (now));
    }
    hour = g_strdup_printf ("%d", g_date_time_get_hour (now));
    minute = g_strdup_printf ("%d", g_date_time_get_minute (now));

    same_year = !g_strcmp0 (year, vector[7]);
    same_month = !g_strcmp0 (month_str[g_date_time_get_month (now) - 1], vector[1]);
    same_day = !g_strcmp0 (day, vector[2]);
    same_hour = !g_strcmp0 (hour, vector[3]);
    same_minute = !g_strcmp0 (minute, vector[4]);

    if (same_year && same_month && same_day && same_hour && same_minute)
    {
        ret = g_strdup_printf ("Just Now");
    }
    else if (same_year && same_month && same_day && same_hour)
    {
        ret = g_strdup_printf ("%d minutes ago",
                               g_date_time_get_minute (now) - atoi (vector[4]));
    }
    else if (same_year && same_month && same_day)
    {
        ret = g_strdup_printf ("%s:%s", vector[3], vector[4]);
    }
    else if ((same_year && same_month)
             || (same_year && !same_month))
    {
        ret = g_strdup_printf ("%s:%s %s %s",
                               vector[3], vector[4], vector[1], vector[2]);
    }
    else
    {
        ret = g_strdup_printf ("%s:%s %s %s %s",
                               vector[3], vector[4], vector[1], vector[2], vector[7]);
    }

    g_date_time_unref (now);
    g_free (year);
    g_free (day);
    g_free (hour);
    g_free (minute);
    g_strfreev (vector);

    return ret;
}

/**
 * wb_util_format_source_string:
 * @source: the source string fetched from Weibo API
 *
 * This function parses a <a> tag and returns the text.
 *
 * Returns: A newly allocated string
 */
gchar *
wb_util_format_source_string (const gchar *source)
{
    gchar **vector;
    gchar *ret;

    g_return_val_if_fail (source != NULL, NULL);

    /* Don't parse it when @source is an empty string */
    if (g_strcmp0 (source, "") == 0)
    {
        return NULL;
    }

    vector = g_strsplit_set (source, "<>", -1);
    ret = g_strdup (vector[2]);

    g_strfreev (vector);

    return ret;
}

/**
 * wb_util_thumbnail_to_original:
 * @thumbnail: the thumbnail uri string fetched from Weibo API
 *
 * This function converts a thumbnail uri string to the
 * original image uri string.
 *
 * Returns: A newly allocated uri string
 */
gchar *
wb_util_thumbnail_to_original (const gchar *thumbnail)
{
    gchar *ret;
    gchar *str;
    g_autofree gchar *part1 = NULL;

    g_return_val_if_fail (thumbnail != NULL, NULL);

    str = g_strrstr (thumbnail, "thumbnail");
    part1 = g_strndup (thumbnail, str - thumbnail);

    ret = g_strconcat (part1, "large", str + 9, NULL);

    return ret;
}

GtkWidget *
wb_util_scale_image (GdkPixbuf *pixbuf,
                     gint *width,
                     gint *height)
{
    GtkWidget *image;

    if (*width > MAX_WIDTH && *height > MAX_HEIGHT)
    {
        gdouble scale;
        GdkPixbuf *scaled_pixbuf;

        scale = (gdouble) MAX_WIDTH / *width;
        if (*height * scale > MAX_HEIGHT)
        {
            scale = (gdouble) MAX_HEIGHT / *height;
        }

        scaled_pixbuf = gdk_pixbuf_scale_simple (pixbuf,
                                                 *width * scale,
                                                 *height * scale,
                                                 GDK_INTERP_BILINEAR);
        *width *= scale;
        *height *= scale;

        image = gtk_image_new_from_pixbuf (scaled_pixbuf);

        g_object_unref (scaled_pixbuf);
    }
    else
    {
        image = gtk_image_new_from_pixbuf (pixbuf);
    }

    return image;
}
