#include <iostream>
#include <curl.h>
#include <string>
#include "json.hpp"
using json = nlohmann::json;

std::wstring ConvertString(const std::string& s)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), NULL, 0);

	std::wstring ws(len, 0);

	MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), &ws[0], len);

	return ws;
}

void WriteUtf8(const std::string& s)
{
	std::wstring ws = ConvertString(s);

	DWORD _;

	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), ws.c_str(), (DWORD)ws.size(), &_, nullptr);
}

size_t WriteCallback(void* c, size_t s, size_t n, std::string* o)
{
	o->append((char*)c, s * n);
	return s * n;
}

int main()
{
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

				WriteUtf8("ID: " + std::to_string(data["id"].get<int>()) + ", Name: " + data["name"].get<std::string>());
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		else
		{
			WriteUtf8("通信エラー");
		}

		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();
	return 0;
}