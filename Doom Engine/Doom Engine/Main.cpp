#include "DoomEngine.h"
#include <string>
#include "DEGame.h"
#include "GameScreen.h"
#include "GameSettings.h"

const int SCREENWIDTH = 1600;
const int SCREENHEIGHT = 900;


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPreviousInstance,LPSTR lpcmdline,int nCmdShow)
{
	DoomEngine engine;
	engine.SetupEngine(hInstance, 0, 0, SCREENWIDTH, SCREENHEIGHT);
	std::unique_ptr<GameScreen> screen1 = GameScreen::CreateScreen();
	std::unique_ptr<GameSettings> settings1 = GameSettings::CreateSettings();
	engine.RegisterGame(DEGame::CreateGame(std::move(screen1), std::move(settings1)));
	engine.RunEngine();
	return 0;
}