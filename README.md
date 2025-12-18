# drawterm (dragged into the Liquid Glass era)

## Fork summary

- HiDPI-friendly Cocoa backend: logical vs device scaling, fractional scale slider, and raw-pixel mode (scale 0).
- Preferences dialog to set UI scale; scale also configurable via `DRAWTERM_SCALE` and persisted in user defaults.
- Mouse and resize paths honor logical scaling; raw mode keeps pixel-accurate frame buffer.
- Metal redraw path limits full-surface invalidation to scale/resize events; incremental flushes use region updates.
- macOS pasteboard bridge for text snarf/clipboard; getenv fixed to use host environment safely.
- Cocoa "Connect…" dialog to set CPU/auth hosts and ports, user, and optional saved password; defaults persist between runs.

## Description

This fork keeps drawterm working smoothly on modern macOS systems while retaining support for other platforms.

## Installation

- Unix: `CONF=unix make`
- Solaris (Sun cc): `CONF=sun make`
- Windows: use Mingw on Cygwin (Visual C is unsupported)
- macOS X11 (XQuartz): `CONF=osx-x11 make`
- macOS Cocoa: `CONF=osx-cocoa make` and then `cp drawterm gui-cocoa/drawterm.app/`
- Android: adjust Make.android\* and gui-android/Makefile for your toolchain, then `make -f Make.android`

## Usage

- Android: the five checkboxes map to the three mouse buttons and mouse wheel; `kb` toggles the soft keyboard.
- macOS Cocoa: use Drawterm → Connect… (Cmd+O) to enter CPU/auth endpoints and user; enable "Save password" to reuse it on next launch.

## Caveats

- Android: saved login details are stored as plaintext; secstore is not supported.
- macOS: saved passwords live in user defaults (plaintext); disable "Save password" if that is unacceptable.

## Binaries

- http://drawterm.9front.org/

## Source

- http://git.9front.org/plan9front/drawterm/HEAD/info.html

## Help

- No.
