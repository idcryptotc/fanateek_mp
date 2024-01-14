#include "dialog.h"

bool getMp3(std::wstring& track)
{
    OPENFILENAME ofn;
    wchar_t szFile[260]{};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"Music (*.mp3)\0*.mp3\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (!GetOpenFileName(&ofn))
    {
        return FALSE;
    }
    else
    {
        track = ofn.lpstrFile;
    }

    return TRUE;
}

bool multiGetMp3(std::list<std::wstring>& tracks)
{
    OPENFILENAME ofn;
    int s = 2 * 1024 * 1024;
    wchar_t* szFile = new wchar_t[s];

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(*szFile) * s;
    ofn.lpstrFilter = L"Music (*.mp3)\0*.mp3\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_EXPLORER;

    if (!GetOpenFileName(&ofn))
    {
        delete[] szFile;
        return FALSE;
    }
    else
    {
        std::wstring track_name{};

        for (std::size_t offset = ofn.nFileOffset; ofn.lpstrFile[offset]; offset = std::wcslen(track_name.c_str()) + offset + 1)
        {
            track_name = ofn.lpstrFile + offset;
            tracks.push_back(std::format(L"{0}\\{1}", ofn.lpstrFile, track_name));
        }
    }

    delete[] szFile;
    return TRUE;
}