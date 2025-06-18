#include "httpClient.h"
#include <curl.h>
#include <sstream>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::future<std::string> GetAllFacultiesAsync()
{
	return std::async(std::launch::async, []() -> std::string
		{
			CURL* curl = curl_easy_init();
			if (!curl) return "CURL�������G���[";

			std::string response;
			curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/faculties");
			curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

			CURLcode res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);

			if (res != CURLE_OK)
			{
				return std::string("�擾�G���[:") + curl_easy_strerror(res);
			}

			return response;
		});
}

std::future<std::string> GetFacultyByIdAsync(int id)
{
	return std::async(std::launch::async, [id]() -> std::string
		{
			CURL* curl = curl_easy_init();
			if (!curl) return "CURL�������G���[";

			std::string response;
			std::stringstream url;
			url << "http://localhost:3000/faculties/" << id;

			curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
			curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

			CURLcode res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);

			if (res != CURLE_OK)
			{
				return std::string("�擾�G���[:") + curl_easy_strerror(res);
			}

			return response;
		});
}

std::future<std::string> PostFacultyAsync(const std::string& name)
{
	return std::async(std::launch::async, [name]() -> std::string
		{
			CURL* curl = curl_easy_init();
			if (!curl) return "CURL�������G���[";

			json body = {
				{ "name", name }
			};

			std::string bodyStr = body.dump();

			struct curl_slist* headers = nullptr;
			headers = curl_slist_append(headers, "Content-Type: application/json");

			std::string response;
			curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/faculties");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
			curl_easy_setopt(curl, CURLOPT_POST, 1L);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, bodyStr.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

			CURLcode res = curl_easy_perform(curl);
			
			curl_slist_free_all(headers);
			curl_easy_cleanup(curl);

			if (res != CURLE_OK)
			{
				return std::string("���M�G���[:") + curl_easy_strerror(res);
			}

			return response;
		});
}

std::future<std::string> PatchFacultyAsync(int id, const std::string& newName)
{
	return std::async(std::launch::async, [id, newName]() -> std::string
		{
			CURL* curl = curl_easy_init();
			if (!curl) return "CURL�������G���[";

			std::string response;
			std::stringstream url;
			url << "http://localhost:3000/faculties/" << id;

			json requestBody = {
				{ "name", newName }
			};

			std::string requestStr = requestBody.dump();

			struct curl_slist* headers = nullptr;
			headers = curl_slist_append(headers, "Content-Type: application/json");

			curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestStr.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

			CURLcode res = curl_easy_perform(curl);

			curl_slist_free_all(headers);
			curl_easy_cleanup(curl);

			if (res != CURLE_OK)
			{
				return std::string("�X�V�G���[:") + curl_easy_strerror(res);
			}

			return response;
		});
}

std::future<std::string> DeleteFacultyAsync(int id)
{
	return std::async(std::launch::async, [id]() -> std::string
		{
			CURL* curl = curl_easy_init();
			if (!curl) return "CURL�������G���[";

			std::string response;
			std::stringstream url;
			url << "http://localhost:3000/faculties/" << id;

			curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

			CURLcode res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);

			if (res != CURLE_OK)
			{
				return std::string("�폜�G���[:") + curl_easy_strerror(res);
			}

			return response;
		});
}








