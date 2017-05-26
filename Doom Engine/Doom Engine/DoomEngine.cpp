#include "DoomEngine.h"



DoomEngine::DoomEngine(void)
{
	Game = nullptr;
	window = nullptr;
	d3ddev = nullptr;
	d3d = nullptr;
}

DoomEngine::~DoomEngine()
{
	if(Game)
		delete Game;
	if(window)
		DestroyWindow(window);
	if(d3ddev){
		d3ddev->Release();    // close and release the 3D device
		d3ddev = nullptr;
	}
	if(d3ddev){
		d3d->Release();    // close and release Direct3D
		d3d = nullptr;
	}
}

void DoomEngine::SetupEngine(HINSTANCE hInstance, int int_XPos, int int_YPos, int _SCREENWIDTH, int _SCREENHEIGHT)
{
	window = NewWindow((LPCTSTR) "Game", hInstance, int_XPos, int_YPos, _SCREENWIDTH, _SCREENHEIGHT);
	SCREENWIDTH = _SCREENWIDTH;
	SCREENHEIGHT = _SCREENHEIGHT;
	CreateD3DDEVICE();
}

void DoomEngine::RegisterGame(std::unique_ptr<DEGame> _Game)
{
	Game = std::move(_Game);
	Game->RegisterParent(this, d3ddev, window);
}

void DoomEngine::RunEngine()
{
	Game->RunGame();
	Game.release();
	d3ddev->Release();
	d3d->Release();
	DestroyWindow(window);
}

HWND DoomEngine::NewWindow(LPCTSTR str_Title,HINSTANCE hInstance, int int_XPos, int int_YPos, int int_Width, int int_Height)
{
	WNDCLASSEX wnd_Structure;
	ZeroMemory(&wnd_Structure, sizeof(WNDCLASSEX));
	wnd_Structure.cbSize = sizeof(WNDCLASSEX);
	wnd_Structure.style = CS_HREDRAW | CS_VREDRAW;
	// Might later change and add this to DEGame instead
	wnd_Structure.lpfnWndProc = DoomEngine::WinProc;
	wnd_Structure.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd_Structure.hInstance = hInstance;
	//wnd_Structure.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
	wnd_Structure.lpszClassName = "WindowClassName";
	//wnd_Structure.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	RegisterClassEx(&wnd_Structure);
	return CreateWindowEx(NULL, "WindowClassName", str_Title, WS_EX_TOPMOST | WS_POPUP, 0, 0, SCREENWIDTH, SCREENHEIGHT, NULL, NULL, GetModuleHandle(NULL), NULL);
}

LRESULT CALLBACK DoomEngine::WinProc(HWND han_Wind,UINT uint_Message,WPARAM parameter1,LPARAM parameter2)
{
	return DefWindowProc(han_Wind,uint_Message,parameter1,parameter2);
}

void DoomEngine::CreateD3DDEVICE()
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface
	D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information
	ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
	d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
	d3dpp.hDeviceWindow = window;    // set the window to be used by Direct3D
	// CHANGE CODE :: To use alpha values change this to D3DFMT_A8R8G8B8
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;    // set the back buffer format to 32-bit
	d3dpp.BackBufferWidth = SCREENWIDTH;    // set the width of the buffer
	d3dpp.BackBufferHeight = SCREENHEIGHT;    // set the height of the buffer
	d3dpp.EnableAutoDepthStencil = TRUE;    // automatically run the z-buffer for us
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;    // 16-bit pixel format for the z-buffer
	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
						D3DDEVTYPE_HAL,
						window,
						D3DCREATE_SOFTWARE_VERTEXPROCESSING,
						&d3dpp,
						&d3ddev);
	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);    // turn off the 3D lighting
	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}