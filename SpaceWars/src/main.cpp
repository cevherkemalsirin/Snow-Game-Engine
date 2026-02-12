#include <iostream>
#include "Framework/Application.h"

int main()
{
    std::cout << "Welcome to SpaceWars" << std::endl;
    
	sw::Application app;
    app.Run();
    return 0;
}
