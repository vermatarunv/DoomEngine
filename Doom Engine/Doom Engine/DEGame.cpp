#include "DEGame.h"

int DEGame::instances = 0;

std::unique_ptr<DEGame> DEGame::CreateGame(std::unique_ptr<GameSettings> _settings, std::unique_ptr<Screen> _screen)
{
	instances++;
	if(instances>1)
	{
		return std::unique_ptr<DEGame>(nullptr);
	}
	std::unique_ptr<DEGame> tempGame(new DEGame());
	tempGame->SetFirstScreen(std::move(_screen));
	tempGame->SetGameSettings(std::move(_settings));
	return tempGame;
}

void DEGame::SetGameSettings(std::unique_ptr<GameSettings>&& _settings)
{
	settings = std::move(_settings);
}

void DEGame::SetFirstScreen(std::unique_ptr<Screen>&& _screen)
{
	screen = std::move(_screen);
	screen->SetDevices(d3ddev, window);
}

DEGame::DEGame(DEGame&& other) : parentDoomEngine(other.parentDoomEngine), screen(std::move(other.screen)), settings(std::move(other.settings))
{}
DEGame& DEGame::operator=(DEGame&& other)
{
	parentDoomEngine = other.parentDoomEngine;
	screen = std::move(other.screen);
	settings = std::move(other.settings);
}
DEGame::~DEGame(void)
{
	parentDoomEngine = nullptr;
}

void DEGame::RegisterParent(DoomEngine* _parentDoomEngine, LPDIRECT3DDEVICE9 _d3ddev, HWND _window)
{
	parentDoomEngine = _parentDoomEngine;
	d3ddev = _d3ddev;
	window = _window;
}

void DEGame::RunGame()
{
	while(screen)
	{
		screen->SetupScreen();
		std::unique_ptr<Screen> tempScreen = std::move(screen->RunScreen());
		screen->EndScreen();
		screen = std::move(tempScreen);
	}
}