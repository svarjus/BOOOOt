#include "pch.h"

bool GetAllData(std::vector<std::string>& tokens)
{
	if (WebPageData.empty()) {
		//printf("no available data!\n");
		return false;
	}

	const auto& begin = WebPageData.begin();
	const auto& end = WebPageData.end();

	if (WebPageData[0] == '[')
		WebPageData.erase(begin, begin + 1);

	if (WebPageData[WebPageData.size() - 1] == ']')
		WebPageData.erase(end - 1, end);

	//std::vector<std::string> tokens;

	TokenizeString(WebPageData, ',', tokens);


	return true;
	//for (auto& i : tokens) {
	//	std::cout << i << '\n';
	//}
}

size_t TokenizeString(std::string& expr, char delim, std::vector<std::string>& tokens)
{
	std::string token;
	for (const auto& i : expr) {

		if (i == delim) {
			token.erase(token.begin(), token.begin() + 1);
			token.erase(token.end()-1, token.end());

			tokens.push_back(token);
			token.clear();
			continue;
		}

		token.push_back(i);
	}

	return tokens.size();
}

Client::Client(const int32_t idx) {
	
	if (WebPageData.empty()) {
		printf("no available data!\n");
		return;
	}

	const auto& begin = WebPageData.begin();
	const auto& end = WebPageData.end();

	if (WebPageData[0] == '[')
		WebPageData.erase(begin, begin + 1);

	if (WebPageData[WebPageData.size()-1] == ']')
		WebPageData.erase(end-1, end);

	std::vector<std::string> tokens;

	TokenizeString(WebPageData, ',', tokens);

	for (auto& i : tokens) {
		std::cout << i << '\n';
	}

	//for (size_t i = 0; i < WebPageData.size(); i++) {

	//	 

	//}
}
