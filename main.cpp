#include <iostream>
#include <windows.h>
#include "httpClient.h"

int main()
{
	SetConsoleOutputCP(65001);

	auto future = PatchFacultyAsync(2, "スーパーゲームクリエイター科");

	while (true)
	{
		if (future.valid() && future.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
		{
			std::string res = future.get();
			std::cout << "PATCH結果: " << res << std::endl;

			auto getFuture = GetAllFacultiesAsync();
			std::string all = getFuture.get();
			std::cout << "現在の全学科一覧:\n" << all << std::endl;

			break;
		}
	}

	return 0;
}
