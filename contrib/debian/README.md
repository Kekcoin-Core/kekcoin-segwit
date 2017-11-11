
Debian
====================
This directory contains files used to package kekcoind/kekcoin-qt
for Debian-based Linux systems. If you compile kekcoind/kekcoin-qt yourself, there are some useful files here.

## kekcoin: URI support ##


kekcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install kekcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your kekcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/kekcoin128.png` to `/usr/share/pixmaps`

kekcoin-qt.protocol (KDE)

