#pragma once
#include <vector>
#include "ScreenData.h"
#include "EventMessage.h"
#include <memory>
#include <Windows.h>
#include <d3d9.h>
#include <functional>

class PhysicsComponent;
class GraphicComponentSettings;
class DEGame;
class InputComponent;
class GraphicComponent;

class Screen
{
	friend class DEGame;
	
private:
	std::unique_ptr<ScreenData> screenData;
	std::unique_ptr<InputComponent> inputComponent;
	std::shared_ptr<GraphicComponent> graphicComponent;
	std::unique_ptr<ScreenLogicComponent> screenLogicComponent;
	std::vector<EventMessage> messages;

	void SetDevices(LPDIRECT3DDEVICE9, HWND);
	//std::unique_ptr<ScreenData> GetScreenData();

	Screen(Screen&);
protected:
	int timeStep;
	bool KeepRunning;
	
	// Screen execution functions
	virtual std::unique_ptr<ScreenData> ScreenRender(std::unique_ptr<ScreenData>) = 0;
	void FlushMessages();
	std::unique_ptr<Screen> RunScreen();
	virtual void EndScreen() = 0;
	virtual std::unique_ptr<ScreenData> PreLogicUpdate(std::unique_ptr<ScreenData>) = 0;
	
	// Screen component changing functions
	virtual void SetupScreen() = 0;  
	void SetScreenData(std::unique_ptr<ScreenData>);
	void ChangeInputComponent(std::unique_ptr<InputComponent>);

	// Give Access ScreenData Access To GraphicComponent


	Screen(void);
	Screen(std::unique_ptr<InputComponent>, GraphicComponentSettings, std::unique_ptr<ScreenLogicComponent>, int);
	Screen(Screen&&);
	
public:
	// TODO: Optimze eventadding and removing
	std::vector<EventMessage>& GetEventMessages();
	void SendEventMessage(EventMessage);
	virtual ~Screen(void);
};