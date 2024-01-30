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
    std::wstring menu
    {
        std::format(L"\n0 - {0}\n1 - {1}\n2 - {2}\n3 - {3}\n"
        , L"Выбрать файл и начать воспроизведение"
            , L"Выбрать несколько файлов"
            , L"Закрыть файл"
            , L"Выход")
    };
    std::list<std::wstring> tracks;

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

                    if (getMp3(track_address))
                    {
                        std::size_t track_begin_name = track_address.rfind('\\') + 1;
                        std::size_t track_size_name = track_address.rfind('.') - track_begin_name;
                        std::wstring track_name = track_address.substr(track_begin_name, track_size_name);
                        std::wstring for_open = std::format(L"open \"{0}\" type mpegvideo alias mp3", track_address);
                        mciSendString(L"close mp3", NULL, 0, NULL);
                        mode_str = L"closed";

                        switch (mciSendString(for_open.data(), NULL, 0, NULL))
                        {
                            case 0:
                            {
                                mciSendString(L"status mp3 length", dur, 128, 0);
                                std::uint32_t s_all{ std::stoi(dur) / 1000u }, m{ s_all / 60u }, s{ s_all % 60u };
                                info = std::format(L"{0}:{1:02}\t", m, s) + track_name + L"\n";
                                mciSendString(L"play mp3", NULL, 0, NULL);
                                break;
                            }
                            case MCIERR_INTERNAL:
                            {
                                std::wcout << "Не могу воспроизвести песенку. Попробуйте установить кодеки\n";
                                break;
                            }
                            default:
                            {
                                std::wcout << L"Oops... Звоните в рельсу\n";
                                break;
                            }
                        }
                    }

                    break;
                }
                case '1':
                {
                    if (multiGetMp3(tracks))
                    {
                        
                    }

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