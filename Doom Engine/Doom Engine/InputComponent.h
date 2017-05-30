#pragma once
#include "EventMessage.h"
#include <vector>
#include "Windows.h"


class InputComponent
{
	friend class Screen;

public:
	~InputComponent(void);
	
protected:
	void NotifyParent(EventMessage);

	virtual void ProcessEvents(MSG) = 0;
	
	InputComponent();
	InputComponent(const InputComponent&);
	InputComponent(InputComponent&&);
	InputComponent& operator = (const InputComponent&);
	InputComponent& operator = (InputComponent&&);

private:
	// HACK: Remove this delete later
	InputComponent(void) = delete;
	
	void ProcessUserInput();
	void InjectParent(Screen*);
	std::vector<EventMessage> events;

	Screen* parentScreen;
};