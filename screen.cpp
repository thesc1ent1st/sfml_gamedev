#include "screen.h"

Screen::Screen(const std::string& name)
{
        this->desktop = sf::VideoMode::getDesktopMode();
        this->window.create(
                sf::VideoMode(this->desktop.width, this->desktop.height, this->desktop.bitsPerPixel),
                name
        );

        // screen.window.setFramerateLimit(32);
}