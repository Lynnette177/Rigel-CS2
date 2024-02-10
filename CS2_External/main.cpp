#include "Offsets.h"
#include "Cheats.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include "auth.hpp"
#include <string>
#include "utils.hpp"
#include "skStr.h"
using namespace KeyAuth;
std::string name = "lite"; // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = "ss3JcGuVnA"; // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = "f642b9e7ae0fb54bac4e8f5f3d3820dbd56f8213eb0221606fd25970681a87e7"; // app secret, the blurred text on licenses tab and other tabs
std::string version = "1.0"; // leave alone unless you've changed version on website
std::string url = skCrypt("https://keyauth.win/api/1.2/").decrypt(); // change if you're self-hosting

api KeyAuthApp(name, ownerid, secret, version, url);
std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);
const std::string compilation_date = (std::string)skCrypt(__DATE__);
const std::string compilation_time = (std::string)skCrypt(__TIME__);
int main()
{
	if (1) {
		std::string consoleTitle = (std::string)skCrypt("ChumChum Loader - Ver:  ") + compilation_date ;
		SetConsoleTitleA(consoleTitle.c_str());
		std::cout << skCrypt("\n\nConnecting..");
		KeyAuthApp.init();
		if (!KeyAuthApp.data.success)
		{
			std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
			Sleep(1500);
			exit(0);
		}


		//Optional - check if HWID or IP blacklisted

		if (KeyAuthApp.checkblack()) {
			abort();
		}


		//std::cout << skCrypt("\n\n App data:");
		//std::cout << skCrypt("\n Number of users: ") << KeyAuthApp.data.numUsers;
		//std::cout << skCrypt("\n Number of online users: ") << KeyAuthApp.data.numOnlineUsers;
		//std::cout << skCrypt("\n Number of keys: ") << KeyAuthApp.data.numKeys;
		std::cout << skCrypt("\n Version: ") << KeyAuthApp.data.version;
		//std::cout << skCrypt("\n Customer panel link: ") << KeyAuthApp.data.customerPanelLink;
		//std::cout << skCrypt("\n Checking session validation status (remove this if causing your loader to be slow)");
		KeyAuthApp.check();
		std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;

		if (std::filesystem::exists(".\\test.json")) //change test.txt to the path of your file :smile:
		{
			if (!CheckIfJsonKeyExists(".\\test.json", "username"))
			{
				std::string key = ReadFromJson(".\\test.json", "license");
				KeyAuthApp.license(key);
				if (!KeyAuthApp.data.success)
				{
					std::remove(".\\test.json");
					std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
					Sleep(1500);
					exit(0);
				}
				std::cout << skCrypt("\nAuto logged in...");
			}
			else
			{
				std::string username = ReadFromJson(".\\test.json", "username");
				std::string password = ReadFromJson(".\\test.json", "password");
				KeyAuthApp.login(username, password);
				if (!KeyAuthApp.data.success)
				{
					std::remove(".\\test.json");
					std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
					Sleep(1500);
					exit(0);
				}
				std::cout << skCrypt("\nSucceed");
			}
			KeyAuthApp.log("Somebody else is using");
		}
		else
		{
			std::string username;
			std::string password;
			std::string key;
			std::cout << skCrypt("\n Input Your License: ");
			std::cin >> key;
			KeyAuthApp.license(key);
			if (!KeyAuthApp.data.success)
			{
				std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
				Sleep(1500);
				exit(0);
			}
			if (username.empty() || password.empty())
			{
				WriteToJson(".\\test.json", "license", key, false, "", "");
				std::cout << skCrypt("Succeed");
			}
			else
			{
				WriteToJson(".\\test.json", "username", username, true, "password", password);
				std::cout << skCrypt("Succeed");
			}


		}

		std::cout << skCrypt("\nUser Data:");
		//std::cout << skCrypt("\n Username: ") << KeyAuthApp.data.username;
		std::cout << skCrypt("\n IP Addr: ") << KeyAuthApp.data.ip;
		std::cout << skCrypt("\n HWID: ") << KeyAuthApp.data.hwid;
		std::cout << skCrypt("\n Activated at: ") << tm_to_readable_time(timet_to_tm(string_to_timet(KeyAuthApp.data.createdate)));
		std::cout << skCrypt("\n Last Log in: ") << tm_to_readable_time(timet_to_tm(string_to_timet(KeyAuthApp.data.lastlogin)));
		std::cout << skCrypt("\n License Information: \n ");

		for (int i = 0; i < KeyAuthApp.data.subscriptions.size(); i++) { // Prompto#7895 was here
			auto sub = KeyAuthApp.data.subscriptions.at(i);
			//std::cout << skCrypt("\n name: ") << sub.name;
			std::cout << skCrypt("Expires:") << tm_to_readable_time(timet_to_tm(string_to_timet(sub.expiry)));
		}

		std::cout << skCrypt("\n Checking..");
		KeyAuthApp.check();
		std::cout << skCrypt("\n Status:") << KeyAuthApp.data.message;
	}


	auto ProcessStatus = ProcessMgr.Attach("cs2.exe");
	if (ProcessStatus != StatusCode::SUCCEED)
	{
		std::cout << "[ERROR] Failed to attach process, StatusCode:" << ProcessStatus << std::endl;
		goto END;
	}

	if (!Offset::UpdateOffsets())
	{
		std::cout << "[ERROR] Failed to update offsets." << std::endl;
		goto END;
	}

	if (!gGame.InitAddress())
	{
		std::cout << "[ERROR] Failed to call InitAddress()." << std::endl;
		goto END;
	}

	//std::cout << "[Game] Pid:" << ProcessMgr.ProcessID << std::endl;
	//std::cout << "[Game] Client:" << gGame.GetClientDLLAddress() << std::endl;

	//std::cout << "Offset:" << std::endl;
	//std::cout << "--EntityList:" << std::setiosflags(std::ios::uppercase) << std::hex << Offset::EntityList << std::endl;
	//std::cout << "--Matrix:" << std::setiosflags(std::ios::uppercase) << std::hex << Offset::Matrix << std::endl;
	//std::cout << "--LocalPlayerController:" << std::setiosflags(std::ios::uppercase) << std::hex << Offset::LocalPlayerController << std::endl;
	//std::cout << "--ViewAngles:" << std::setiosflags(std::ios::uppercase) << std::hex << Offset::ViewAngle << std::endl;
	//std::cout << "--LocalPlayerPawn:" << std::setiosflags(std::ios::uppercase) << std::hex << Offset::LocalPlayerPawn << std::endl;

	std::cout << "\nChumChum Loaded..." << std::endl;

	try
	{
		Gui.AttachAnotherWindow("Counter-Strike 2", "SDL_app", Cheats::Run);
	}
	catch (OSImGui::OSException& e)
	{
		try
		{
			Gui.AttachAnotherWindow("反恐精英：全球攻势", "SDL_app", Cheats::Run);
		}
		catch (OSImGui::OSException& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

END:
	system("pause");
	return 0;
}
std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}
