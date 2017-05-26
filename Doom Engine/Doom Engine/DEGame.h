#pragma once
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include "GameSettings.h"
#include "Screen.h"
#include <memory>

class DoomEngine;

class DEGame final
{
	friend class DoomEngine;

public:

	static std::unique_ptr<DEGame> CreateGame(std::unique_ptr<GameSettings>, std::unique_ptr<Screen>);

protected:
	explicit DEGame();
	virtual ~DEGame();
	DEGame& operator=(DEGame&&);
	explicit DEGame(DEGame&&);

	void SetGameSettings(std::unique_ptr<GameSettings>&&);
	void SetFirstScreen(std::unique_ptr<Screen>&&);
	
private:
	static int instances;
	DoomEngine* parentDoomEngine;
	std::unique_ptr<Screen> screen;
	std::unique_ptr<GameSettings> settings;

	LPDIRECT3DDEVICE9 d3ddev;
	HWND window;
	
	DEGame(const DEGame&);
	DEGame& operator= (const DEGame&);
	
	void RegisterParent(DoomEngine* parentEngine, LPDIRECT3DDEVICE9, HWND);
	void RunGame();
};
