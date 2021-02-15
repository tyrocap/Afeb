//
// Created by adam on 2/15/21.
//

#include <iostream>
#include <string>
#include <SDL.h>
#include <cstdlib>


// TODO: create an error handling class
void fatalError(std::string errorString) {
    std::cout << errorString << std::endl;
    std::cout << "Enter any key to quit..";
    int tmp;
    std::cin >> tmp;
    SDL_Quit();
    exit(1);
}
