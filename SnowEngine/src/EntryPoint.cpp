#include "EntryPoint.h"
#include "Framework/Application.h"

int main()
{
	snw::Application* app = GetApplication();
	if (app)
	{
		app->Run();
		delete app;
	}
	
}

