dofile("../assets/input/InputConstants.lua")

local converter = {
    [Range.ROTATE_CAMERA_X] = {
        minInput  = -512.0,
        maxInput  =  512.0,
        minOutput = -180.0,
        maxOutput =  180.0,
    },
    [Range.ROTATE_CAMERA_Y] = {
        minInput  = -512.0,
        maxInput  =  512.0,
        minOutput = -180.0,
        maxOutput =  180.0,
    },
}

return converter
