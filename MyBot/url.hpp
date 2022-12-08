#pragma once


#ifndef uurl
#define uurl

#include "pch.h"

struct MemoryStruct {
    char* memory;
    size_t size;
};

std::string FetchURLData(const char* url);
size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp);

#endif