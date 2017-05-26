#pragma once
#include "ScreenData.h"
#include "EventMessage.h"
#include <memory>
#include <Windows.h>
#include <d3d9.h>
#include <functional>

typedef void(* radnom)(void);

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
	std::shared_ptr<InputComponent> inputComponent;
	std::shared_ptr<GraphicComponent> graphicsComponent;
	std::shared_ptr<ScreenLogicComponent> screenLogicComponent;

	Screen(void);
	Screen(Screen&);
	virtual ~Screen(void);

	void SetDevices(LPDIRECT3DDEVICE9, HWND);
	std::unique_ptr<ScreenData> GetScreenData();

protected:
	virtual void SetupScreen() = 0;
	std::unique_ptr<Screen> RunScreen();
	virtual void EndScreen() = 0;
	void SetScreenData(std::unique_ptr<ScreenData>);
	void SendMessageGraphic(EventMessage);
	void SendMessageInput(EventMessage);
	void SendMessageAI(EventMessage);
	void ChangeInputCallable(radnom);
	virtual void ScreenRender()=0;

	Screen(radnom, std::unique_ptr<GraphicComponentSettings>, std::unique_ptr<ScreenLogicComponent>);
	Screen(Screen&&);
	
public:
	virtual std::unique_ptr<Screen> CreateGame() = 0;
};