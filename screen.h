#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <SFML/Window/VideoMode.hpp> /* sf::VideoMode */ 
#include <SFML/Graphics.hpp> /* sf::RenderWindow */ 

class Screen {
public:
        sf::RenderWindow window;
        Screen(const std::string& name);
        sf::VideoMode getDesktop() const { return desktop; }

private:
        sf::VideoMode desktop;
};

#endif // __SCREEN_H__