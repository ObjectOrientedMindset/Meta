#pragma once

//Entry Point
#ifdef MT_PLATFORM_WINDOWS


extern Meta::Application* Meta::CreateApplication();

int main(int argc, char** argv)
{
	Meta::Log::Init();
	MT_CORE_INFO("Log Initialized!");

	auto app = Meta::CreateApplication();
	app->run();
	delete app;
	return 0;
}


#endif
