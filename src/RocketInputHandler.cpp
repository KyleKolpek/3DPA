
unsigned int generateRocketModifiers(InputMap &map)
{
	int key_modifier_state = 0;

	if (x_state & KMOD_SHIFT)
		key_modifier_state |= Rocket::Core::Input::KM_SHIFT;

	if (x_state & KMOD_CAPS)
		key_modifier_state |= Rocket::Core::Input::KM_CAPSLOCK;

	if (x_state & KMOD_CTRL)
		key_modifier_state |= Rocket::Core::Input::KM_CTRL;

	if (x_state & KMOD_ALT)
		key_modifier_state |= Rocket::Core::Input::KM_ALT;

	if (x_state & KMOD_NUM)
		key_modifier_state |= Rocket::Core::Input::KM_NUMLOCK;

	return key_modifier_state;
}

void handleRocketInput(InputMap &map)
{
    unsigned int modifiers = generateRocketModifiers(map);
    if(/*Button Press*/)
        context->ProcessMouseButtonDown(button_index, modifiers);
    if(/*Button Release*/)
        context->ProcessMouseButtonUp(button_index, modifiers);
    if(/*Mouse Wheel*/)
        context->ProcessMouseWheel(direction/*-1 or 1*/, modifiers);
    if(/*Key Press*/)
        context->ProcessKeyDown(key_identifier, modifiers);
        context->ProcessTextInput(character);
    if(/*Key Release*/)
        context->ProcessKeyUp(key_identifier, modifiers);
    if(/*Mouse Motion*/)
        context->ProcessMouseMove(deltaX, deltaY, modifiers);
}

