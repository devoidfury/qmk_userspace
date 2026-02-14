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

#ifdef POINTING_DEVICE_ENABLE
#   define CHARYBDIS_DRAGSCROLL_REVERSE_Y // inverts vertical scrolling
#endif // POINTING_DEVICE_ENABLE


// persist state across both halves
#define SPLIT_LAYER_STATE_ENABLE
#define CHARYBDIS_CONFIG_SYNC
