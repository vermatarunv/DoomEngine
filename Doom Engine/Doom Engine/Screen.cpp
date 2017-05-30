#include "Screen.h"
#include "InputComponent.h"
#include "GraphicComponent.h"
#include "ScreenLogicComponent.h"
#include "GraphicComponentSettings.h"
#include "ScreenData.h"

Screen::~Screen(void)
{
	OutputDebugString("Screen Base Class Destroyed\n");
}

//std::unique_ptr<ScreenData> Screen::GetScreenData(){
//	return std::move(screenData);
//}

std::unique_ptr<Screen> Screen::RunScreen()
{
	KeepRunning = true;
	double currentTime = timeGetTime();
	double accumulator = 0.0;
	while(KeepRunning)
	{
		double newTime = timeGetTime();
		double frameTime = newTime - currentTime;
		currentTime = newTime;
		accumulator += frameTime;
		inputComponent->ProcessUserInput();
		screenData = screenLogicComponent->RunAI(std::move(screenData)); // Responsible for setting KeepRunning to false
		while(accumulator >= timeStep)
		{
			screenData = PreLogicUpdate(std::move(screenData));
			accumulator-=timeStep;
		}
		const double alpha = accumulator / timeStep;
		graphicComponent->SetupRender(alpha, timeStep);
		screenData = ScreenRender(std::move(screenData));
		FlushMessages();
	}
	return screenLogicComponent->GetNextScreen(); // Responsible for returning the new screen
}

std::vector<EventMessage>& Screen::GetEventMessages()
{
	return messages;
}

void Screen::FlushMessages()
{
	for(int i=0; i<messages.size(); ++i)
	{
		if(messages[i].deletion) messages.erase(messages.begin()+i);
	}
}

void Screen::SendEventMessage(EventMessage _em)
{
	messages.push_back(_em);
}

void Screen::SetScreenData(std::unique_ptr<ScreenData> _screenData)
{
	screenData = std::move(_screenData);
	screenData->SetupScreenData();
}

void Screen::ChangeInputComponent(std::unique_ptr<InputComponent> _inputComponent)
{
	inputComponent = std::move(_inputComponent);
}

Screen::Screen(std::unique_ptr<InputComponent> _inputComponent, GraphicComponentSettings _graphicSettings, std::unique_ptr<ScreenLogicComponent> _screenLogicComponent, int _timeStep)
	: inputComponent(std::move(_inputComponent)), graphicComponent(_graphicSettings), screenLogicComponent(std::move(_screenLogicComponent)), timeStep(_timeStep)
{
	inputComponent->InjectParent(this);
	graphicComponent->InjectParent(this);
	screenLogicComponent->InjectParent(this);
}

Screen::Screen(Screen&& _other) 
	: screenData(std::move(_other.screenData)), graphicComponent(std::move(_other.graphicComponent)), inputComponent(std::move(_other.inputComponent)), screenLogicComponent(std::move(_other.screenLogicComponent))
{}

Screen::~Screen(void)
{

}