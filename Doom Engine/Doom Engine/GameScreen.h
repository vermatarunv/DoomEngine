#pragma once
#include "screen.h"
#include <memory>
#include <Windows.h>

class GraphicComponentSettings;
class ScreenLogicComponent;
class PhysicsComponentSettings;
class PhysicsComponent;

typedef void(*DEInputCallable)(MSG);

class MyGameScreen :
	public Screen
{
public:
	virtual ~MyGameScreen(void);
	
	// TODO: Make arguments are void and it self creates and sets the required GraphicComponentSettings, PhysicsComponentSettings
	static std::unique_ptr<MyGameScreen> CreateGameScreen(DEInputCallable, GraphicComponentSettings, ScreenLogicComponent, PhysicsComponentSettings);

protected:
	MyGameScreen(MyGameScreen&&);
	MyGameScreen& operator = (MyGameScreen&&);
	MyGameScreen(DEInputCallable, GraphicComponentSettings, ScreenLogicComponent, PhysicsComponentSettings);

	virtual void SetupScreen();
	virtual void EndScreen();
	virtual std::unique_ptr<ScreenData> PreLogicUpdate(std::unique_ptr<ScreenData>);
	virtual void SendAll(EventMessage);
	virtual std::unique_ptr<ScreenData> ScreenRender(std::unique_ptr<ScreenData>);
	void SendMessagePhysics(EventMessage);

private:
	MyGameScreen& operator = (const MyGameScreen&);
	MyGameScreen(void);

	std::unique_ptr<PhysicsComponent> physicsComponent;

};

