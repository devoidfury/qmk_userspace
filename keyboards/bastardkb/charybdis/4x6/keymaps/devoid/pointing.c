
#ifdef POINTING_DEVICE_ENABLE


/** Automatically enable sniping-mode on the given layer. */
#ifdef AUTO_SNIPING_ENABLED
#   if defined(POINTING_DEVICE_AUTO_MOUSE_ENABLE)
#      define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_LOWER
#   else
#      define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER
#   endif
#endif


#ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));

#    ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    // Manage Auto Mouse enabling/disabling based on layer to avoid conflicts with sniping
    uint8_t layer = get_highest_layer(state);

    switch (layer) {
        case CHARYBDIS_AUTO_SNIPING_ON_LAYER:
            set_auto_mouse_enable(false); // disable Auto Mouse when in sniping layer
            break;

        default:
            set_auto_mouse_enable(true); // enable it again
            break;
    }
#    endif // POINTING_DEVICE_AUTO_MOUSE_ENABLE

    return state;
}
#endif


#    ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
void pointing_device_init_user(void) {
    // set default pointer layer
    set_auto_mouse_layer(LAYER_POINTER);
    // enable Auto Mouse by default
    set_auto_mouse_enable(true);
}

bool is_mouse_record_user(uint16_t keycode, keyrecord_t *record) {
    // treated as mouse keys (hold target layer while they are pressed and reset active layer timer).
    switch (keycode) {
        case SNIPING_MODE:
        // case SNIPING_MODE_TOGGLE:
        case DRAGSCROLL_MODE:
        // case DRAGSCROLL_MODE_TOGGLE:
        case DPI_MOD:
        case DPI_RMOD:
        case S_D_MOD:
        case S_D_RMOD:
            return true;
    }
    return false;
}

#    endif // POINTING_DEVICE_AUTO_MOUSE_ENABLE

#endif // POINTING_DEVICE_ENABLE
