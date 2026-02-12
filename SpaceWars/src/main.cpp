#include <iostream>
#include "Framework/Application.h"

int main()
{
    std::cout << "Welcome to SpaceWars" << std::endl;
    
	std::unique_ptr<sw::Application> app = std::make_unique<sw::Application>();
    app->Run();
    return 0;
}