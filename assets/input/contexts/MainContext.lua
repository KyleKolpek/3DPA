dofile("RawInputConstants.lua")
dofile("InputConstants.lua")

context = {
    states = {
        RAW_BUTTON_W     = STATE_CAMERA_MOVE_FORWARD,
        RAW_BUTTON_S     = STATE_CAMERA_MOVE_BACK,
        RAW_BUTTON_A     = STATE_CAMERA_MOVE_LEFT,
        RAW_BUTTON_D     = STATE_CAMERA_MOVE_RIGHT,
        RAW_BUTTON_SPACE = STATE_CAMERA_MOVE_UP,
        RAW_BUTTON_C     = STATE_CAMERA_MOVE_DOWN,
        RAW_BUTTON_RIGHT_MOUSE = STATE_CAMERA_ROTATE,
    },
    actions = {
        RAW_BUTTON_LEFT_MOUSE = ACTION_ADD_CUBE,
    },
    ranges = {
        RAW_AXIS_MOUSE_X = RANGE_ROTATE_CAMERA_X,
        RAW_AXIS_MOUSE_Y = RANGE_ROTATE_CAMERA_Y,
    },
    sensitivities = {
        RANGE_ROTATE_CAMERA_X = 1.5,
        RANGE_ROTATE_CAMERA_Y = 1.5,
    },
}

return context
