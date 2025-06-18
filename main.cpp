#include <iostream>
#include <windows.h>
#include <string>
#include "httpClient.h"

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

int main()
{
	SetConsoleOutputCP(65001);

	auto future = PatchFacultyAsync(2, "スーパーゲームクリエイター科");

	while (true)
	{
		if (future.valid() && future.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
		{
			std::string res = future.get();
			WriteUtf8("PATCH結果:" + res + "\n");

			auto getFuture = GetAllFacultiesAsync();
			std::string all = getFuture.get();
			WriteUtf8("現在の全学科一覧:\n" + all + "\n");

			break;
		}
	}

	return 0;
}
