#include "InputComponent.h"


InputComponent::~InputComponent(void)
{}

InputComponent::InputComponent(DEInputCallable _inputCallable)
{
inputCallable = _inputCallable;
}

InputComponent::InputComponent(InputComponent&& other)
{
	inputCallable = other.inputCallable;
}

InputComponent& InputComponent::operator = (const InputComponent& other)
{
	if(this != &other)
	{
		inputCallable = other.inputCallable;
	}
}

InputComponent& InputComponent::operator = (InputComponent&& other)
{
	inputCallable = other.inputCallable;
}

void InputComponent::ProcessUserInput()
{
	MSG message;
	if(PeekMessage(&message, 0, 0, NULL, PM_REMOVE))
	{
		inputCallable(message);
	}
}

void InputComponent::receive(EventMessage em)
{

}

void InputComponent::SetCallable(DEInputCallable)
{
}