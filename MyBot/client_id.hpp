#pragma once

#ifndef clientid
#define clientid

#include "pch.h"

inline std::string WebPageData;

size_t TokenizeString(std::string& expr, char delim, std::vector<std::string>& tokens);
bool GetAllData(std::vector<std::string>& tokens);
struct client_t
{
	std::string id;
};

class Client
{
public:

	Client(const int32_t idx);

private:
	client_t data{};
	std::string id;
};


#endif