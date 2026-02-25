#ifdef LAYER_INDICATOR_RGB_ENABLE


/** Layers above this one trigger the activity indicators */
#   define TOP_BASE_LAYER LAYER_BASE

/** layer activity indicators color configuration. See qmk_firmware/quantum/color.h */
const hsv_t LAYER_INDICATOR_COLORS[] = {
    [LAYER_BASE] = {HSV_OFF},
    [LAYER_LOWER] = {HSV_BLUE},
    [LAYER_RAISE] = {HSV_GREEN},
    [LAYER_POINTER] = {HSV_PURPLE},
    [LAYER_DANGER] = {HSV_RED},
};


rgb_t hsv_to_rgb_adjusted_brightness(hsv_t color) {
    // use the current active rgb val as a cap so the built in rgb brightness controls work
    uint8_t const val = rgb_matrix_get_val();
    if (color.v > val) {
        color.v = val;
    }
    return hsv_to_rgb(color);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t const layer = get_highest_layer(layer_state);
    if (layer <= TOP_BASE_LAYER) {
        return false;
    }

    rgb_t const rgb_color = hsv_to_rgb_adjusted_brightness(LAYER_INDICATOR_COLORS[layer]);

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t const led = g_led_config.matrix_co[row][col];
            if (led == NO_LED || led < led_min || led >= led_max) {
                continue;
            }
            uint16_t const key = keymap_key_to_keycode(layer, MAKE_KEYPOS(row, col));
            switch (key) {
                case KC_TRNS:
#   ifndef LAYER_INDICATOR_TRANS_DARK
                // leave active matrix effect unchanged for transparent/fallthrough keys
                    break;
#   endif
                // dark no-op keys
                case KC_NO:
                    rgb_matrix_set_color(led, RGB_OFF);
                    break;
                // show an indicator for the key
                default:
                    rgb_matrix_set_color(led, rgb_color.r, rgb_color.g, rgb_color.b);
            }
        }
    }

    return false;
}


#endif // LAYER_INDICATOR_RGB_ENABLE
