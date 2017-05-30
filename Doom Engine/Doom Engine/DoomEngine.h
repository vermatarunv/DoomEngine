#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include "DEGame.h"

template <typename T>
class Key { friend T; Key(){} Key(const Key&){} };

class DoomEngine final
{
public:
	DoomEngine(void);
	~DoomEngine();

	static LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

	void RegisterGame(std::unique_ptr<DEGame>);
	void SetupEngine(HINSTANCE hInstance, int int_XPos, int int_YPos, int _SCREENWIDTH, int _SCREENHEIGHT);
	void RunEngine();

private:
	HWND window;
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;
	std::unique_ptr<DEGame> Game;
	int SCREENWIDTH;
	int SCREENHEIGHT;

	DoomEngine(const DoomEngine&);

	HWND NewWindow(LPCTSTR str_Title, HINSTANCE hInstance, int int_XPos, int int_YPos, int int_Width, int int_Height);
	void CreateD3DDEVICE();
};