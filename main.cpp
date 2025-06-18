#include <iostream>
#include <curl.h>
#include <windows.h>
#include "json.hpp"
using json = nlohmann::json;

size_t WriteCallback(void* c, size_t s, size_t n, std::string* o)
{
	o->append((char*)c, s * n);
	return s * n;
}

int main()
{
	SetConsoleOutputCP(65001);

	curl_global_init(CURL_GLOBAL_ALL);
	CURL* curl = curl_easy_init();

	if (curl)
	{
		std::string response;

		curl_easy_setopt(curl, CURLOPT_URL,
			"http://localhost:3000/faculties/1");

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		CURLcode res = curl_easy_perform(curl);

		if (res == CURLE_OK)
		{
			try
			{
				json data = json::parse(response);

				std::cout << "ID: " << data["id"]
					<< ", Name: " << data["name"]
					<< std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		else
		{
			std::cout << "’ÊMƒGƒ‰[" << std::endl;
		}

		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();
	return 0;
}