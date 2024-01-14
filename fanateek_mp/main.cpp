#include "main.h"

int main(int argc, char* argv[])
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    wchar_t* dur = new wchar_t[128];
    wchar_t* mode = new wchar_t[128];
    char key;
    std::wstring info{};
    bool isExit{ false };
    std::wstring mode_str{};
    std::wstring menu{ L"\n0 - Выбрать файл и начать воспроизведение\n2 - Закрыть файл\n3 - Выход\n" };

    std::wcout << menu;


    while (!isExit)
    {
        if (_kbhit())
        {
            key = std::tolower(_getch());

            switch (key)
            {
                case '0':
                {
                    std::wstring track_address{};

                    if (!getMp3(track_address))
                    {
                        return 0;
                    }

                    std::size_t track_begin_name = track_address.rfind('\\') + 1;
                    std::size_t track_size_name = track_address.rfind('.') - track_begin_name;
                    std::wstring track_name = track_address.substr(track_begin_name, track_size_name);
                    auto for_open = std::format(L"open \"{0}\" type mpegvideo alias mp3", track_address);
                    mciSendString(L"close mp3", NULL, 0, NULL);
                    mode_str = L"closed";

                    if (mciSendString(for_open.data(), NULL, 0, NULL))
                    {
                        std::wcout << L"Oops...\n";
                        break;
                    }
                    else
                    {
                        mciSendString(L"status mp3 length", dur, 128, 0);
                        std::uint32_t s_all{ std::stoi(dur) / 1000u }, m{ s_all / 60u }, s{ s_all % 60u };
                        info = std::format(L"{0}:{1:02}\t", m, s) + track_name + L"\n";
                    }

                    mciSendString(L"play mp3", NULL, 0, NULL);
                    break;
                }
                case '1':
                {
                    mciSendString(L"status mp3 mode", mode, 128, 0);
                    break;
                }
                case '2':
                {
                    mciSendString(L"close mp3", NULL, 0, NULL);
                    info = L"empty\n";
                    break;
                }
                case '3':
                {
                    mciSendString(L"close mp3", NULL, 0, NULL);
                    isExit = true;
                    break;
                }
                case '4':
                {
                    std::list<std::wstring> tracks;
                    multiGetMp3(tracks);
                }
            }
        }

        mciSendString(L"status mp3 mode", mode, 128, 0);

        if (mode_str != mode && mode[0] != '\0')
        {
            mode_str = mode;
            system("cls");
            std::wcout << mode_str << "\t" << info << menu;

            if (mode_str == L"stopped")
            {
                mciSendString(L"close mp3", NULL, 0, NULL);
            }
        }
    }

    _setmode(_fileno(stdout), _O_TEXT);
    delete[] dur;
    delete[] mode;
    return 0;
}