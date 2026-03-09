#include <iostream>
#include "Framework/Application.h"

int main()
{
    std::cout << "Welcome to SpaceWars" << std::endl;
    
	std::unique_ptr<sw::Application> app = std::make_unique<sw::Application>(800,600,"Shapes");
    app->Run();
    return 0;
}