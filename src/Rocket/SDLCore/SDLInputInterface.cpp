#include <Rocket/SDLCore/SDLInputInterface.h>

using namespace Rocket::Core::Input;

std::map<SDL_Scancode, KeyIdentifier> SDLInputInterface::keymap =
    {{SDL_SCANCODE_UNKNOWN, KI_UNKNOWN},
    {SDL_SCANCODE_A, KI_A},
    {SDL_SCANCODE_B, KI_B},
    {SDL_SCANCODE_C, KI_C},
    {SDL_SCANCODE_D, KI_D},
    {SDL_SCANCODE_E, KI_E},
    {SDL_SCANCODE_F, KI_F},
    {SDL_SCANCODE_G, KI_G},
    {SDL_SCANCODE_H, KI_H},
    {SDL_SCANCODE_I, KI_I},
    {SDL_SCANCODE_J, KI_J},
    {SDL_SCANCODE_K, KI_K},
    {SDL_SCANCODE_L, KI_L},
    {SDL_SCANCODE_M, KI_M},
    {SDL_SCANCODE_N, KI_N},
    {SDL_SCANCODE_O, KI_O},
    {SDL_SCANCODE_P, KI_P},
    {SDL_SCANCODE_Q, KI_Q},
    {SDL_SCANCODE_R, KI_R},
    {SDL_SCANCODE_S, KI_S},
    {SDL_SCANCODE_T, KI_T},
    {SDL_SCANCODE_U, KI_U},
    {SDL_SCANCODE_V, KI_V},
    {SDL_SCANCODE_W, KI_W},
    {SDL_SCANCODE_X, KI_X},
    {SDL_SCANCODE_Y, KI_Y},
    {SDL_SCANCODE_Z, KI_Z},
    {SDL_SCANCODE_1, KI_1},
    {SDL_SCANCODE_2, KI_2},
    {SDL_SCANCODE_3, KI_3},
    {SDL_SCANCODE_4, KI_4},
    {SDL_SCANCODE_5, KI_5},
    {SDL_SCANCODE_6, KI_6},
    {SDL_SCANCODE_7, KI_7},
    {SDL_SCANCODE_8, KI_8},
    {SDL_SCANCODE_9, KI_9},
    {SDL_SCANCODE_0, KI_0},
    {SDL_SCANCODE_RETURN, KI_RETURN},
    {SDL_SCANCODE_ESCAPE, KI_ESCAPE},
    {SDL_SCANCODE_BACKSPACE, KI_BACK},
    {SDL_SCANCODE_TAB, KI_TAB},
    {SDL_SCANCODE_SPACE, KI_SPACE},
    {SDL_SCANCODE_MINUS, KI_OEM_MINUS},
    {SDL_SCANCODE_EQUALS, KI_OEM_PLUS},
    {SDL_SCANCODE_LEFTBRACKET, KI_OEM_4},
    {SDL_SCANCODE_RIGHTBRACKET, KI_OEM_6},
    {SDL_SCANCODE_BACKSLASH, KI_OEM_5},
    {SDL_SCANCODE_SEMICOLON, KI_OEM_1},
    {SDL_SCANCODE_APOSTROPHE, KI_OEM_7},
    {SDL_SCANCODE_COMMA, KI_OEM_COMMA},
    {SDL_SCANCODE_PERIOD, KI_OEM_PERIOD},
    {SDL_SCANCODE_SLASH, KI_OEM_2},
    {SDL_SCANCODE_CAPSLOCK, KI_CAPITAL},
    {SDL_SCANCODE_F1, KI_F1},
    {SDL_SCANCODE_F2, KI_F2},
    {SDL_SCANCODE_F3, KI_F3},
    {SDL_SCANCODE_F4, KI_F4},
    {SDL_SCANCODE_F5, KI_F5},
    {SDL_SCANCODE_F6, KI_F6},
    {SDL_SCANCODE_F7, KI_F7},
    {SDL_SCANCODE_F8, KI_F8},
    {SDL_SCANCODE_F9, KI_F9},
    {SDL_SCANCODE_F10, KI_F10},
    {SDL_SCANCODE_F11, KI_F11},
    {SDL_SCANCODE_F12, KI_F12},
    {SDL_SCANCODE_F13, KI_F13},
    {SDL_SCANCODE_F14, KI_F14},
    {SDL_SCANCODE_F15, KI_F15},
    {SDL_SCANCODE_F16, KI_F16},
    {SDL_SCANCODE_F17, KI_F17},
    {SDL_SCANCODE_F18, KI_F18},
    {SDL_SCANCODE_F19, KI_F19},
    {SDL_SCANCODE_F20, KI_F20},
    {SDL_SCANCODE_F21, KI_F21},
    {SDL_SCANCODE_F22, KI_F22},
    {SDL_SCANCODE_F23, KI_F23},
    {SDL_SCANCODE_F24, KI_F24},
    {SDL_SCANCODE_PRINTSCREEN , KI_SNAPSHOT},
    {SDL_SCANCODE_SCROLLLOCK, KI_SCROLL},
    {SDL_SCANCODE_PAUSE, KI_PAUSE},
    {SDL_SCANCODE_INSERT, KI_INSERT},
    {SDL_SCANCODE_HOME, KI_HOME},
    {SDL_SCANCODE_PAGEUP, KI_PRIOR},
    {SDL_SCANCODE_DELETE, KI_DELETE},
    {SDL_SCANCODE_END, KI_END},
    {SDL_SCANCODE_PAGEDOWN, KI_NEXT},
    {SDL_SCANCODE_RIGHT, KI_RIGHT},
    {SDL_SCANCODE_LEFT, KI_LEFT},
    {SDL_SCANCODE_DOWN, KI_DOWN},
    {SDL_SCANCODE_UP, KI_UP},
    {SDL_SCANCODE_NUMLOCKCLEAR, KI_NUMLOCK},
    {SDL_SCANCODE_KP_DIVIDE, KI_DIVIDE},
    {SDL_SCANCODE_KP_MULTIPLY , KI_MULTIPLY},
    {SDL_SCANCODE_KP_MINUS, KI_SUBTRACT},
    {SDL_SCANCODE_KP_PLUS, KI_ADD},
    {SDL_SCANCODE_KP_ENTER, KI_NUMPADENTER},
    {SDL_SCANCODE_KP_1, KI_NUMPAD1},
    {SDL_SCANCODE_KP_2, KI_NUMPAD2},
    {SDL_SCANCODE_KP_3, KI_NUMPAD3},
    {SDL_SCANCODE_KP_4, KI_NUMPAD4},
    {SDL_SCANCODE_KP_5, KI_NUMPAD5},
    {SDL_SCANCODE_KP_6, KI_NUMPAD6},
    {SDL_SCANCODE_KP_7, KI_NUMPAD7},
    {SDL_SCANCODE_KP_8, KI_NUMPAD8},
    {SDL_SCANCODE_KP_9, KI_NUMPAD9},
    {SDL_SCANCODE_KP_0, KI_NUMPAD0},
    {SDL_SCANCODE_KP_PERIOD, KI_DECIMAL},
    {SDL_SCANCODE_KP_EQUALS, KI_OEM_NEC_EQUAL},
    {SDL_SCANCODE_EXECUTE, KI_EXECUTE},
    {SDL_SCANCODE_HELP, KI_HELP},
    {SDL_SCANCODE_SELECT, KI_SELECT},
    {SDL_SCANCODE_STOP, KI_MEDIA_STOP},
    {SDL_SCANCODE_MUTE, KI_VOLUME_MUTE},
    {SDL_SCANCODE_VOLUMEUP, KI_VOLUME_UP},
    {SDL_SCANCODE_VOLUMEDOWN, KI_VOLUME_DOWN},
    {SDL_SCANCODE_LCTRL, KI_LCONTROL},
    {SDL_SCANCODE_LSHIFT, KI_LSHIFT},
    {SDL_SCANCODE_LALT, KI_LMENU},
    {SDL_SCANCODE_LGUI, KI_LWIN},
    {SDL_SCANCODE_RCTRL, KI_RCONTROL},
    {SDL_SCANCODE_RSHIFT, KI_RSHIFT},
    {SDL_SCANCODE_RALT, KI_RMENU},
    {SDL_SCANCODE_RGUI, KI_RWIN},
    {SDL_SCANCODE_MODE, KI_MODECHANGE}}; 

SDLInputInterface::SDLInputInterface(Rocket::Core::Context * const context):
    context(context)
{
}

SDLInputInterface::~SDLInputInterface()
{
}

int SDLInputInterface::generateRocketModifiers(SDL_Event &event) 
{
	int rocketModifiers = 0;
    uint16_t sdlModifiers = event.key.keysym.mod;

	if(sdlModifiers & KMOD_SHIFT)
		rocketModifiers |= Rocket::Core::Input::KM_SHIFT;

	if(sdlModifiers & KMOD_CAPS)
		rocketModifiers |= Rocket::Core::Input::KM_CAPSLOCK;

	if(sdlModifiers & KMOD_CTRL)
		rocketModifiers |= Rocket::Core::Input::KM_CTRL;

	if(sdlModifiers & KMOD_ALT)
		rocketModifiers |= Rocket::Core::Input::KM_ALT;

	if(sdlModifiers & KMOD_NUM)
		rocketModifiers |= Rocket::Core::Input::KM_NUMLOCK;

	return rocketModifiers;
}

void SDLInputInterface::handleRocketInput(SDL_Event event)
{
    int modifiers = generateRocketModifiers(event);
    switch(event.type)
    {
        case SDL_KEYDOWN:
            context->ProcessKeyDown(keymap[event.key.keysym.scancode], modifiers);
            break;
        case SDL_KEYUP:
            context->ProcessKeyUp(keymap[event.key.keysym.scancode], modifiers);
            break;
        case SDL_MOUSEBUTTONDOWN:
        {
            int button;
            switch(event.button.button)
            {
                case SDL_BUTTON_LEFT:     button = 0;    break;
                case SDL_BUTTON_RIGHT:    button = 1;    break;
                case SDL_BUTTON_MIDDLE:   button = 2;    break;
            }
            context->ProcessMouseButtonDown(button, modifiers);
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            int button;
            switch(event.button.button)
            {
                case SDL_BUTTON_LEFT:     button = 0;    break;
                case SDL_BUTTON_RIGHT:    button = 1;    break;
                case SDL_BUTTON_MIDDLE:   button = 2;    break;
            }
            context->ProcessMouseButtonUp(button, modifiers);
            break;
        }
        case SDL_MOUSEWHEEL:
            context->ProcessMouseWheel(-event.wheel.y, modifiers);
            break;
        case SDL_MOUSEMOTION:
            context->ProcessMouseMove(event.motion.x,
                                      event.motion.y,
                                      modifiers);
            break;
        case SDL_TEXTINPUT:
            context->ProcessTextInput(event.text.text);
            break;
    }
}

