#include "WindowSystem.h"
#include "Platform.h"

WindowSystem * CreateWindowSystem(Application * _own)
{
    WindowSystem* windowSystem;

    windowSystem = (WindowSystem*)malloc(sizeof(WindowSystem));

    windowSystem->own = _own;
    windowSystem->type = WINDOWTYPE_INIT;
    windowSystem->windows[0] =  CreateInitWindow(windowSystem);
    windowSystem->windows[1] = CreateSeatPracticeWindow(windowSystem);
    windowSystem->windows[2] = CreateWordPracticeWindow(windowSystem);
    windowSystem->windows[3] = CreateShortSentencePracticeWindow(windowSystem);

    windowSystem->ChangeWindow = _WindowSystem_ChangeWindow;
    windowSystem->Clear = _WindowSystem_Clear;
    windowSystem->Draw = _WindowSystem_Draw;
    windowSystem->Update = _WindowSystem_Update;

    return windowSystem;
}

int _WindowSystem_Update(WindowSystem * _this)
{
    _this->windows[0]->Update(_this->windows[0]);
    _this->windows[1]->Update(_this->windows[1]);
    _this->windows[2]->Update(_this->windows[2]);
    _this->windows[3]->Update(_this->windows[3]);

    return 0;
}

int _WindowSystem_Clear(WindowSystem * _this)
{
#if (_PLATFORM_TYPE == _PLATFORM_WIN32)
    return system("CLS");
#elif (_PLATFORM_TYPE == _PLATFORM_LINUX)
    return system("clear");
#endif
}

int _WindowSystem_Draw(WindowSystem * _this)
{
    return _this->windows[_this->type]->Draw(_this->windows[_this->type]);
}

int _WindowSystem_ChangeWindow(WindowSystem * _this, int _type)
{
    return _this->type = _type;
}