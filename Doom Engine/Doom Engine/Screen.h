#pragma once
#include "ScreenData.h"
#include "EventMessage.h"
#include <memory>
#include <Windows.h>
#include <d3d9.h>
#include <functional>

typedef void(*DEInputCallable)(void);

class GraphicComponentSettings;
class DEGame;
class InputComponent;
class GraphicComponent;

class Screen
{
	friend class DEGame;
	friend class ScreenLogicComponent;

private:
	std::unique_ptr<ScreenData> screenData;
	std::unique_ptr<InputComponent> inputComponent;
	std::shared_ptr<GraphicComponent> graphicComponent;
	std::unique_ptr<ScreenLogicComponent> screenLogicComponent;

	
	void SetDevices(LPDIRECT3DDEVICE9, HWND);
	//std::unique_ptr<ScreenData> GetScreenData();

protected:
	virtual void SetupScreen() = 0;  // SetScreenData
	std::unique_ptr<Screen> RunScreen();
	virtual void EndScreen() = 0;
	virtual std::unique_ptr<ScreenData> PreLogicUpdate(std::unique_ptr<ScreenData>) = 0;
	void SetScreenData(std::unique_ptr<ScreenData>);
	void SendMessageGraphic(EventMessage);
	void SendMessageInput(EventMessage);
	void SendMessageAI(EventMessage);
	virtual void SendAll(EventMessage);
	void ChangeInputCallable(DEInputCallable);
	virtual std::unique_ptr<ScreenData> ScreenRender(std::unique_ptr<ScreenData>)=0;
	int timeStep;
	bool KeepRunning;

	Screen(void);
	Screen(Screen&);
	Screen(DEInputCallable, std::unique_ptr<GraphicComponentSettings>, std::unique_ptr<ScreenLogicComponent>, int);
	Screen(Screen&&);
	
public:
	virtual ~Screen(void);
};