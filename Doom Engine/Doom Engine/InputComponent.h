#pragma once
#include "EventMessage.h"
#include <vector>
#include "Windows.h"

typedef void (*DEInputCallable)(MSG);

class InputComponent final
{
friend class Screen;
public:
	~InputComponent(void);
	
private:
	// HACK: Remove this delete later
	InputComponent(void) = delete;
	InputComponent(DEInputCallable);
	InputComponent(const InputComponent&);
	InputComponent(InputComponent&&);
	InputComponent& operator = (const InputComponent&);
	InputComponent& operator = (InputComponent&&);

	void ProcessUserInput();
	void receive(EventMessage);
	std::vector<EventMessage> events;
	DEInputCallable inputCallable;
	void SetCallable(DEInputCallable);
};