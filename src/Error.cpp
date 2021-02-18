//
// Created by adam on 2/15/21.
//

#include <SDL.h>
#include <cstdlib>
#include <iostream>
#include <string>

namespace Afeb {
    // TODO: create an error handling class
    void fatalError(std::string errorString)
    {
        std::cout << errorString << std::endl;
        std::cout << "Enter any key to quit..";
        int tmp;
        std::cin >> tmp;
        SDL_Quit();
        exit(1);
    }

} // namespace Afeb
