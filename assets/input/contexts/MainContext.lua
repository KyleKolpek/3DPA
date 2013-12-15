dofile("../assets/input/contexts/RawInputConstants.lua")
dofile("../assets/input/contexts/InputConstants.lua")

local context = {
    states = {
        [RawButton.W]     = State.CAMERA_MOVE_FORWARD,
        [RawButton.S]     = State.CAMERA_MOVE_BACK,
        [RawButton.A]     = State.CAMERA_MOVE_LEFT,
        [RawButton.D]     = State.CAMERA_MOVE_RIGHT,
        [RawButton.SPACE] = State.CAMERA_MOVE_UP,
        [RawButton.C]     = State.CAMERA_MOVE_DOWN,
        [RawButton.RIGHT_MOUSE] = State.CAMERA_ROTATE,
    },
    actions = {
        [RawButton.LEFT_MOUSE] = Action.ADD_CUBE,
    },
    ranges = {
        [RawAxis.MOUSE_X] = Range.ROTATE_CAMERA_X,
        [RawAxis.MOUSE_Y] = Range.ROTATE_CAMERA_Y,
    },
    sensitivities = {
        [Range.ROTATE_CAMERA_X] = 1.5,
        [Range.ROTATE_CAMERA_Y] = 1.5,
    },
}

return context
