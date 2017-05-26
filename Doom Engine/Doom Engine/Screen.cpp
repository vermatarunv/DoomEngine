#include "Screen.h"
#include "InputComponent.h"
#include "GraphicComponent.h"
#include "ScreenLogicComponent.h"
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
	}
	return screenLogicComponent->GetNextScreen(); // Responsible for returning the new screen
}

void Screen::SendAll(EventMessage _em)
{
	graphicComponent->receive(_em);
	inputComponent->receive(_em);
	screenLogicComponent->receive(_em);
}

void Screen::SetScreenData(std::unique_ptr<ScreenData> _screenData)
{
	screenData = std::move(_screenData);
	screenData->SetupScreenData();
}
void Screen::SendMessageGraphic(EventMessage _em)
{
	graphicComponent->receive(_em);
}
void Screen::SendMessageInput(EventMessage _em)
{
	inputComponent->receive(_em);
}
void Screen::SendMessageAI(EventMessage _em)
{
	screenLogicComponent->receive(_em);
}
void Screen::ChangeInputCallable(DEInputCallable _inputCallable)
{
	inputComponent->SetCallable(_inputCallable);
}

Screen::Screen(DEInputCallable _inputFunction, std::unique_ptr<GraphicComponentSettings> _graphicSettings, std::unique_ptr<ScreenLogicComponent> _screenLogicComponent, int _timeStep)
	: inputComponent(_inputFunction), graphicComponent(std::move(_graphicSettings)), screenLogicComponent(std::move(_screenLogicComponent)), timeStep(_timeStep)
{}

Screen::Screen(Screen&& _other) 
	: screenData(std::move(_other.screenData)), graphicComponent(std::move(_other.graphicComponent)), inputComponent(std::move(_other.inputComponent)), screenLogicComponent(std::move(_other.screenLogicComponent))
{}

Screen::~Screen(void)
{

}