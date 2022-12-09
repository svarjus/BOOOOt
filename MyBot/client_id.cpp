#include "pch.h"

bool GetAllData(std::string& src, std::vector<std::string>& tokens)
{
	if (src.empty()) {
		//printf("no available data!\n");
		return false;
	}

	const auto& begin = src.begin();
	const auto& end = src.end();

	if (src[0] == '[')
		src.erase(begin, begin + 1);

	if (src[src.size() - 1] == ']')
		src.erase(end - 1, end);

	//std::vector<std::string> tokens;

	TokenizeString(src, ',', tokens);


	return true;
}

size_t TokenizeString(std::string& expr, char delim, std::vector<std::string>& tokens)
{
	std::string token;
	for (const auto& i : expr) {

		if (i == delim) {
			token.erase(token.begin(), token.begin() + 1);
			token.erase(token.end()-1, token.end());
			if(!token.empty())
				tokens.push_back(token);
			token.clear();
			continue;
		}
		if(i != ']' && i != '[')
			token.push_back(i);
	}
	token.erase(token.begin(), token.begin() + 1);
	token.erase(token.end() - 1, token.end());
	tokens.push_back(token);

	return tokens.size();
}