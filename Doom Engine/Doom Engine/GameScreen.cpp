#include "GameScreen.h"
#include "GraphicComponentSettings.h"
#include "PhysicsComponentSettings.h"
#include "MyGameScreenData.h"
#include "ScreenLogicComponent.h"

MyGameScreen::~MyGameScreen(void)
{
}

std::unique_ptr<MyGameScreen> MyGameScreen::CreateGameScreen(DEInputCallable _inputCallabe, GraphicComponentSettings _graphicSettings, ScreenLogicComponent _screenLogic, PhysicsComponentSettings _physicsSettings)
{
	return std::move(new GameScreen(_inputCallabe, _graphicSettings, _screenLogic, _physicsSettings));
}

MyGameScreen::MyGameScreen(MyGameScreen&& _other)
	: physicsComponent(std::move(_other.physicsComponent))
{}

MyGameScreen::MyGameScreen(DEInputCallable _inputCallabe, GraphicComponentSettings _graphicSettings, ScreenLogicComponent _screenLogic, PhysicsComponentSettings _physicsSettings)
	: Screen(_inputCallabe, _graphicSettings, _screenLogic), physicsComponent(_physicsSettings)
{}

MyGameScreen& MyGameScreen::operator = (MyGameScreen&& other)
{
	Screen::operator=(std::move(other));
	physicsComponent = std::move(other.physicsComponent);
	return *this;
}

void MyGameScreen::SetupScreen()
{
	std::unique_ptr<ScreenData> _screenData(new MyGameScreenData());
	SetScreenData(std::move(_screenData));
}

void MyGameScreen::EndScreen()
{}

std::unique_ptr<ScreenData> MyGameScreen::PreLogicUpdate(std::unique_ptr<ScreenData> _screenData)
{
#warning // TODO: Update this function definition after defining the Baahu Physics Engine and the ScreenData
	_screenData = physicsComponent->Update(std::move(_screenData));	
}

void MyGameScreen::SendAll(EventMessage em)
{
	SendMessageGraphic(em);
	SendMessageInput(em);
	SendMessageAI(em);
	physicsComponent->receive(em);
}

void MyGameScreen::SendMessagePhysics(EventMessage em)
{
	physicsComponent->receive(em);
}

std::unique_ptr<ScreenData> MyGameScreen::ScreenRender(std::unique_ptr<ScreenData> _screenData)
{
	// TODO: Update this function definition after defining the GraphicsComopnent and the ScreenData
	return std::move(_screenData);
}