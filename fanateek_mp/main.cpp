#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include "main.h"

#pragma comment(lib, "Winmm.lib")
#pragma warning(push)
#pragma warning(disable: 6031)

int main(int argc, char* argv[])
{
    OPENFILENAME ofn;
    wchar_t szFile[260]{};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"Music(*.mp3)\0*.mp3\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    std::wstring track;

    if (!GetOpenFileName(&ofn))
    {
        return 0;
    }
    else
    {
        track = ofn.lpstrFile;
    }

    auto for_open = std::format(L"open \"{0}\" type mpegvideo alias mp3", track);

    if (mciSendString(for_open.data(), NULL, 0, NULL))
    {
        std::cout << "Oops...\n";
    }

    wchar_t *dur = new wchar_t[128];
    wchar_t *mode = new wchar_t[128];
    mciSendString(L"status mp3 length", dur, 128, 0);
    mciSendString(L"play mp3", NULL, 0, NULL);
    mciSendString(L"status mp3 mode", mode, 128, 0);

    _getch();
    mciSendString(L"status mp3 mode", mode, 128, 0);
    mciSendString(L"close mp3", NULL, 0, NULL);
    delete[] dur;
    delete[] mode;
    return 0;
}