#ifdef LAYER_INDICATOR_RGB_ENABLE

#include "quantum.h"
#include "color.h"

// some default colors
__attribute__((weak)) hsv_t get_color_for_layer(uint8_t layer) {
    static const hsv_t LAYER_COLORS[] = {
        {HSV_ORANGE},
        {HSV_RED},
        {HSV_GREEN},
        {HSV_YELLOW},
        {HSV_PURPLE},
        {HSV_BLUE},
    };
    return LAYER_COLORS[layer % (sizeof(LAYER_COLORS)/sizeof(LAYER_COLORS[0]))];
}

#ifndef TOP_BASE_LAYER
#   define TOP_BASE_LAYER 0
#endif


rgb_t hsv_to_rgb_adjusted_brightness(hsv_t color) {
    // use the current active rgb val as a cap so the built in rgb brightness controls work
    uint8_t const val = rgb_matrix_get_val();
    if (color.v > val) {
        color.v = val;
    }
    return hsv_to_rgb(color);
}

bool rgb_matrix_indicators_layer_colors(void) {
    uint8_t const layer = get_highest_layer(layer_state);
    if (layer <= TOP_BASE_LAYER) {
        return false;
    }

#if defined(RGB_MATRIX_SPLIT)
    const uint8_t k_rgb_matrix_split[2] = RGB_MATRIX_SPLIT;
    uint8_t led_min = 0;
    uint8_t led_max = RGB_MATRIX_LED_COUNT;
    if (is_keyboard_left()) {
        if (led_max > k_rgb_matrix_split[0]) {
            led_max = k_rgb_matrix_split[0];
        }
    } else {
        if (led_min < k_rgb_matrix_split[1]) {
            led_min = k_rgb_matrix_split[1];
        }
    }
#endif

    rgb_t const rgb_color = hsv_to_rgb_adjusted_brightness(get_color_for_layer(layer));

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t const led = g_led_config.matrix_co[row][col];
            if (
                led == NO_LED
#if defined(RGB_MATRIX_SPLIT)
                || led < led_min || led >= led_max
#endif
            ) {
                continue;
            }
            uint16_t const key = keymap_key_to_keycode(layer, MAKE_KEYPOS(row, col));
            switch (key) {
                case KC_TRNS:
#ifndef LAYER_INDICATOR_TRANS_DARK
                // leave active matrix effect unchanged for transparent/fallthrough keys
                    break;
#endif
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
