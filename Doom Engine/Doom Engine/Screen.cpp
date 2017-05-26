#include "Screen.h"


Screen::~Screen(void)
{

}


std::unique_ptr<ScreenData> Screen::GetScreenData(){}

std::unique_ptr<Screen> Screen::RunScreen(){}
void Screen::SetScreenData(std::unique_ptr<ScreenData>){}
void Screen::SendMessageGraphic(EventMessage){}
void Screen::SendMessageInput(EventMessage){}
void Screen::SendMessageAI(EventMessage){}
void Screen::ChangeInputCallable(DEInputCallable){}

Screen(DEInputCallable _inputCallable, std::unique_ptr<GraphicComponentSettings> _graphicSettings, std::unique_ptr<ScreenLogicComponent> _screenLogicComponent);