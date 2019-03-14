# Weibird

Weibird is a GTK+ client for viewing and composing weibo.

It’s still heavily under development. Some features are working in progress or to be implemented.

## Translations

i18n is not yet supported at the moment.

## Contributing

Contributions are welcome (code, design, ideas, etc).

## Dependencies

* `glib-2.0`
* `gtk+-3.0`
* `json-glib-1.0`
* `libsoup-2.4`
* `meson` (the building system)
* `rest-0.7`
* `webkit2gtk-4.0`

## Compiling

```
meson ./builddir --prefix=/usr
ninja -C ./builddir
ninja -C ./builddir install
```

## Installing

You can also install Weibird using flatpak. Check this [page](https://flathub.org/apps/details/com.jonathankang.Weibird) for more information.
