#include "GameFramework/GameApplication.h"
#include "EntryPoint.h"


snw::Application* GetApplication()
{
	return new sw::GameApplication{};
}