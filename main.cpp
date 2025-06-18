#include <iostream>
#include <windows.h>
#include "httpClient.h"

int main()
{
	SetConsoleOutputCP(65001);

	auto patchFuture = PatchFacultyAsync(2, "�X�[�p�[�Q�[���N���G�C�^�[��");

	while (true)
	{
		if (patchFuture.valid() && patchFuture.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
		{
			std::string res = patchFuture.get();
			std::cout << "PATCH����: " << res << std::endl;

			auto getFuture = GetALLFacultiesAsync();
			std::string all = getFuture.get();
			std::cout << "���݂̑S�w�Ȉꗗ:\n" << all << std::endl;

			break;
		}
	}
	
	return 0;
}