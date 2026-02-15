/**
 * Copyright 2026 Thomas Hunkapiller <tom@furycodes.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#ifdef VIA_ENABLE
#    define DYNAMIC_KEYMAP_LAYER_COUNT 5
#endif

#ifndef __arm__
/* Disable unused features. */
#    define NO_ACTION_ONESHOT
#endif // __arm__


// ─── Sync-specific features ─────────────────────────────────────────────────
#ifdef SPLIT_KEYBOARD

// persist state across both halves, required for our fancy lighting
#   define SPLIT_LAYER_STATE_ENABLE

// enable syncing of the charybdis config, such as to read the sniping or drag scroll modes on the other half
#   define CHARYBDIS_CONFIG_SYNC

#endif // SPLIT_KEYBOARD

// ─── Pointing device ────────────────────────────────────────────────────────
#ifdef POINTING_DEVICE_ENABLE

// auto sniping enabled
#define AUTO_SNIPING_ENABLED

// inverts vertical scrolling
#   define CHARYBDIS_DRAGSCROLL_REVERSE_Y

// auto mouse layer
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
// ms auto mouse layer is active
#define AUTO_MOUSE_TIME 1200
// amount of mouse movement required to switch layers
#define AUTO_MOUSE_THRESHOLD 10

#define AUTO_MOUSE_DEBOUNCE 20

#endif // POINTING_DEVICE_ENABLE

// ─── RGB Matrix configuration ───────────────────────────────────────────────
#ifdef RGB_MATRIX_ENABLE

/** ms before auto-off, requires SPLIT_ACTIVITY_ENABLE to stay in sync across halves */
#    define RGB_MATRIX_TIMEOUT 900000

/** turns on our layer lighting effect */
#   define LAYER_INDICATOR_RGB_ENABLE
/** define this to darken transparent keys on indicator lights instead of showing the active animation. */
#   define LAYER_INDICATOR_TRANS_DARK


#endif // RGB_MATRIX_ENABLE
