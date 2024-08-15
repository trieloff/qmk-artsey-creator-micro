// Copyright 2022 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes {
    LED_LEVEL = SAFE_RANGE,
};

enum layers {
    _ART_BASE,
    _ART_NUM,
    _ART_CUS,
    _ART_PUNC,
    _ART_MOU,
    _ART_NAV,
    _ART_SYM,
};

#include "aliases.c"
#include "combos.c"


// layout
// scroll wheel,     key,    key,     knob
// key,              key,    key,     key
// key,              key,    key,     key
// m pad,            key,    key,     layer pad

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_ART_BASE] = LAYOUT(
        KC_MPLY,     KC_F9,         KC_F12,         QK_BOOT,
        BASE_1_1,    BASE_1_2,      BASE_1_3,       BASE_1_4,
        BASE_2_1,    BASE_2_2,      BASE_2_3,       BASE_2_4,
        KC_F17,      GUI_T(KC_F10), SGUI_T(KC_F13), KC_F18
    ),
    [_ART_NUM] = LAYOUT(
        _______, _______, _______, _______,
        NUM_1_1, NUM_1_2, NUM_1_3, NUM_1_4,
        NUM_2_1, NUM_2_2, NUM_2_3, NUM_2_4,
        _______, _______, _______, _______
    ),
    [_ART_PUNC] = LAYOUT(
        _______, _______, _______, _______,
        PUNC_1_1, PUNC_1_2, PUNC_1_3, PUNC_1_4,
        PUNC_2_1, PUNC_2_2, PUNC_2_3, PUNC_2_4,
        _______, _______, _______, _______
    ),
    [_ART_CUS] = LAYOUT(
        _______, _______, _______, _______,
        CUS_1_1, CUS_1_2, CUS_1_3, CUS_1_4,
        CUS_2_1, CUS_2_2, CUS_2_3, CUS_2_4,
        _______, _______, _______, _______
    ),
    [_ART_SYM] = LAYOUT(
        _______, _______, _______, _______,
        SYM_1_1, SYM_1_2, SYM_1_3, SYM_1_4,
        SYM_2_1, SYM_2_2, SYM_2_3, SYM_2_4,
        _______, _______, _______, _______
    ),
    [_ART_MOU] = LAYOUT(
        _______, _______, _______, _______,
        MOU_1_1, MOU_1_2, MOU_1_3, MOU_1_4,
        MOU_2_1, MOU_2_2, MOU_2_3, MOU_2_4,
        _______, _______, _______, _______
    ),
    [_ART_NAV] = LAYOUT(
        _______, _______, _______, _______,
        NAV_1_1, NAV_1_2, NAV_1_3, NAV_1_4,
        NAV_2_1, NAV_2_2, NAV_2_3, NAV_2_4,
        _______, _______, _______, _______
    ),
};

typedef union {
    uint32_t raw;
    struct {
        uint8_t led_level : 3;
    };
} work_louder_config_t;

work_louder_config_t work_louder_config;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LED_LEVEL:
            if (record->event.pressed) {
                work_louder_config.led_level++;
                if (work_louder_config.led_level > 4) {
                    work_louder_config.led_level = 0;
                }
                work_louder_micro_led_all_set((uint8_t)(work_louder_config.led_level * 255 / 4));
                eeconfig_update_user(work_louder_config.raw);
                layer_state_set_kb(layer_state);
            }
            break;
    }
    return true;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    { ENCODER_CCW_CW(KC_PGDN, KC_PGUP),           ENCODER_CCW_CW(S(KC_F12), S(KC_F11))  },
    { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______)  },
    { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______)  },
    { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______)  },
    { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______)  },
    { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______)  },
    { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______)  },
};
#endif


layer_state_t layer_state_set_user(layer_state_t state) {
    layer_state_cmp(state, 1) ? work_louder_micro_led_1_on(): work_louder_micro_led_1_off();
    layer_state_cmp(state, 2) ? work_louder_micro_led_2_on(): work_louder_micro_led_2_off();
    layer_state_cmp(state, 3) ? work_louder_micro_led_3_on(): work_louder_micro_led_3_off();

    return state;
}

void eeconfig_init_user(void) {
    work_louder_config.raw = 0;
    work_louder_config.led_level = 1;
    eeconfig_update_user(work_louder_config.raw);
}

void matrix_init_user(void) {
    work_louder_config.raw = eeconfig_read_user();
    work_louder_micro_led_all_set((uint8_t)(work_louder_config.led_level * 255 / 4));
}
