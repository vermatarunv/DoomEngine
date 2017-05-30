#include "InputComponent.h"
#include "Screen.h"


InputComponent::~InputComponent(void)
{
	parentScreen = nullptr;
}

InputComponent::InputComponent(InputComponent&& other)
{
	parentScreen = other.parentScreen;
}

InputComponent& InputComponent::operator = (const InputComponent& other)
{
	if(this != &other)
	{
		parentScreen = other.parentScreen;
	}
}

InputComponent& InputComponent::operator = (InputComponent&& other)
{
	parentScreen = other.parentScreen;
}

void InputComponent::ProcessUserInput()
{
	MSG message;
	if(PeekMessage(&message, 0, 0, NULL, PM_REMOVE))
	{
		ProcessEvents(message);
	}
}

void InputComponent::InjectParent(Screen* _parentScreen)
{
	parentScreen = _parentScreen;
}

void InputComponent::NotifyParent(EventMessage _em)
{
	parentScreen->SendEventMessage(_em);
}