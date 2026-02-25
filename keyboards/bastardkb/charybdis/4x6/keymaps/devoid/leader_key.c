
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
            "QMK " QMK_REMOTE_URL "/" QMK_BRANCH "@" QMK_COMMIT "\n"
            USERSPACE_REMOTE_URL "/" USERSPACE_BRANCH "@" USERSPACE_COMMIT "\n"
            "Compiled " QMK_BUILDDATE
        );
    } else if (leader_sequence_one_key(0)) {
        // leader - toggle drag scroll
        charybdis_set_pointer_dragscroll_enabled(!charybdis_get_pointer_dragscroll_enabled());
    }
}

#endif


