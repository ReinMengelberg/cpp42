// ./Harl.cpp
#include "Harl.hpp"
#include <iostream>

Harl::Harl(void) {}

Harl::~Harl(void) {}

void Harl::debug(void) {
    std::cout << "[ DEBUG ]" << std::endl;
    std::cout << "I walked into the bike store and all the employees were doing "
              << "the macarena. Not a single bike was being sold!" << std::endl;
}

void Harl::info(void) {
    std::cout << "[ INFO ]" << std::endl;
    std::cout << "I asked an employee about a mountain bike and he just started "
              << "breakdancing. Another one was doing the salsa next to the BMX section. "
              << "Nobody here actually sells bikes!" << std::endl;
}

void Harl::warning(void) {
    std::cout << "[ WARNING ]" << std::endl;
    std::cout << "I've been coming to this bike store for years and not once has anyone "
              << "helped me buy a bike. They just keep dancing. The whole floor is a dance party."
              << std::endl;
}

void Harl::error(void) {
    std::cout << "[ ERROR ]" << std::endl;
    std::cout << "This is unacceptable! I want to speak to the manager now. "
              << "Oh wait, the manager is doing the robot in the back. This is not a bike store, "
              << "it's a dance studio!" << std::endl;
}

void Harl::complain(std::string level) {
    std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    void (Harl::*actions[4])(void) = {
        &Harl::debug,
        &Harl::info,
        &Harl::warning,
        &Harl::error
    };
    for (int i = 0; i < 4; i++) {
        if (levels[i] == level) {
            (this->*actions[i])();
            return;
        }
    }
}
