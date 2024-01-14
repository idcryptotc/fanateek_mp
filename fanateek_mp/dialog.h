#pragma once

#include <Windows.h>
#include <string>
#include <list>
#include <format>

bool getMp3(std::wstring &track);
bool multiGetMp3(std::list<std::wstring>& tracks);