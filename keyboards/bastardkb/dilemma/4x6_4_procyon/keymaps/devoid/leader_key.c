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

/** If leader key feature is enabled, use that, otherwise make it a dragscroll toggle key */
#ifdef LEADER_ENABLE
#   define KC_SCRL_FN QK_LEAD
#else
#   define KC_SCRL_FN DRG_TOG
#endif

// keycode: QK_LEAD
#ifdef LEADER_ENABLE

#include "version.h"
#include "version_git.h"

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_V)) {
        // leader, v - qmk-firmware version info
        SEND_STRING(
            "QMK " QMK_REMOTE_URL ">" QMK_BRANCH "@" QMK_COMMIT "\n"
            USERSPACE_REMOTE_URL ">" USERSPACE_BRANCH "@" USERSPACE_COMMIT "\n"
            "Compiled " QMK_BUILDDATE
        );
    }
}

#endif


