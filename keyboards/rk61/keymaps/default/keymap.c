
#include QMK_KEYBOARD_H

#define CAPS_LOCK_LED 28

enum layer_names {
    WINBASE,
    WINFN,
    MOUSEBASE,

};

enum custom_keycodes {
    KC_BASE_KEY = SAFE_RANGE,
    KC_MOUSE_KEY 
};

#define KC_BASE KC_BASE_KEY
#define KC_MOUSE KC_MOUSE_KEY

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WINBASE] = LAYOUT_60_ansi(
        QK_GESC,    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_BSPC,    
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,    KC_BSLS,    //
        KC_CAPS,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,                KC_ENT,     //60
        KC_LSFT,                KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_UP,      KC_RSFT,                //
        KC_LCTL,    KC_LGUI,    KC_LALT,                                        KC_SPC,                                         KC_LEFT,    KC_DOWN,    KC_RGHT,    MO(WINFN)   //8
    ),

    [WINFN] = LAYOUT_60_ansi(
        KC_GRV,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     QK_BOOT,
        KC_TRNS,    KC_BTN3,    KC_MS_U,    KC_BTN1,    KC_BTN2,    KC_TRNS,    KC_PSCR,    KC_SCRL,    KC_PAUS,    G(KC_BTN1), G(KC_BTN2), RGB_VAD,    RGB_VAI,    RGB_MOD,   
        KC_TRNS,    KC_MS_L,    KC_MS_D,    KC_MS_R,    KC_WH_U,    KC_TRNS,    KC_INS,     KC_HOME,    KC_PGUP,    KC_TRNS,    RGB_SPD,    RGB_SPI,                KC_TRNS,   
        KC_TRNS,                KC_PSTE,    KC_COPY,    KC_WH_D,    KC_TRNS,    KC_TRNS,    KC_DEL,     KC_END,     KC_PGDN,    RGB_HUI,    KC_SLSH,    KC_RSFT,   
        KC_TRNS,    KC_TRNS,    KC_TRNS,                                        KC_MOUSE,                                       KC_ALGR,    KC_APP,     KC_RCTL,    KC_TRNS
    ),


    [MOUSEBASE] = LAYOUT_60_ansi(
        KC_GRV,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_BASE,    KC_TRNS,
        KC_TRNS,    KC_BTN3,    KC_MS_U,    KC_BTN1,    KC_BTN2,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,   
        KC_TRNS,    KC_MS_L,    KC_MS_D,    KC_MS_R,    KC_WH_U,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                 KC_TRNS,   
        KC_TRNS,                KC_TRNS,    KC_TRNS,    KC_WH_D,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,   
        KC_TRNS,    KC_TRNS,    KC_TRNS,                                        KC_TRNS,                                        KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS
    )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_BASE:
            if(record->event.pressed) {
                set_single_persistent_default_layer(WINBASE);
            }
            return false;
        case KC_MOUSE:
            if(record->event.pressed) {
                set_single_persistent_default_layer(MOUSEBASE);
            }
            return false;
       case KC_ESC:
        if (get_mods() == MOD_BIT(KC_LALT)) {
            if (record->event.pressed) {

                register_code(KC_COMM);
            } else {
                unregister_code(KC_COMM);
            }

            return false;
        }
        return true;
        case KC_UP:
        if (get_mods() == MOD_BIT(KC_LALT)) {
            if (record->event.pressed) {

                register_code(KC_SLSH);
            } else {
                unregister_code(KC_SLSH);
            }

            return false;
        }
        return true;
        default:
            return true;  // Process all other keycodes normally
    }
    }

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        // Set capslock key to orange (capslock is led number 30)
        rgb_matrix_set_color(CAPS_LOCK_LED, 255, 130, 15);
    }
    return false;
}