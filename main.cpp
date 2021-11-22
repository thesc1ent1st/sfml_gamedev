#include <iostream> 
#include <vector>
#include <string>
#include <stdio.h>

#include "character.h"
#include "screen.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

std::vector<std::string> p1_sprite_path = {
        "./images/RunRight01.png",
        "./images/RunRight02.png",
        "./images/RunRight03.png",
        "./images/RunRight04.png"
};

int gcd(int a, int b);
void handle_key_code(sf::Keyboard::Key code, const Screen& screen, Character& p1);
void init_player_speed(Character& player, const Screen& screen);

int main(int argc, char** argv)
{
        sf::Music music;
        sf::Vector2f p1_start_loc = {
                0.0, 0.0
        };

        Screen screen("Ginga Ninja");
        Character p1(p1_sprite_path, 64.0, 64.0, p1_start_loc);

        if (!music.openFromFile("./music/No6.ogg"))
                return EXIT_FAILURE;

        music.play();
        init_player_speed(p1, screen);
        while (screen.window.isOpen()) {
                sf::Event event;
                while (screen.window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                                screen.window.close();

                        if (event.type == sf::Event::KeyPressed)
                                handle_key_code(event.key.code, screen, p1);
                }

                printf("(X:%f, Y:%f)\n", p1.getSprite().getPosition().x, p1.getSprite().getPosition().y);
                screen.window.clear(sf::Color::White);
                screen.window.draw(p1.getSprite());
                screen.window.display();
        }

        return 0;
}

void handle_key_code(sf::Keyboard::Key code, const Screen& screen, Character& p1)
{
        float sprite_height = p1.getScaleHeight();
        float sprite_width = p1.getScaleWidth();

        int screen_height = screen.getDesktop().height;
        int screen_width = screen.getDesktop().width;

        float dy = p1.getDy();
        float dx = p1.getDx();

        sf::Vector2f v2f_current = p1.getSprite().getPosition();
        sf::Vector2f v2f_next;

        v2f_next.x = v2f_current.x;
        v2f_next.y = v2f_current.y;

        switch (code) {
        case sf::Keyboard::Key::Up:
                v2f_next.y = (v2f_current.y - dy < -(sprite_height / 2)) ?
                        (screen_height - (sprite_height / 2)) :
                        (v2f_current.y - dy);
                break;

        case sf::Keyboard::Key::Down:
                v2f_next.y = (v2f_current.y + dy + (sprite_height / 2) > screen_height) ?
                        -(sprite_height / 2) :
                        (v2f_current.y + dy);
                break;

        case sf::Keyboard::Key::Left:
                v2f_next.x = (v2f_current.x - dx < -(sprite_width / 2)) ?
                        (screen_width - (sprite_width / 2)) :
                        (v2f_current.x - dx);
                break;

        case sf::Keyboard::Key::Right:
                v2f_next.x = (v2f_current.x + dx + (sprite_width / 2) > screen_width) ?
                        -(sprite_width / 2) :
                        (v2f_current.x + dx);
                break;
        default:
                return;
        }

        p1.getSprite().setPosition(v2f_next);
        p1.update_texture_state();
}

void init_player_speed(Character& player, const Screen& screen)
{
        float x, y, dxy;

        x = (float)gcd(screen.getDesktop().width, player.getScaleWidth());
        y = (float)gcd(screen.getDesktop().height, player.getScaleHeight());

        dxy = (float)gcd(x, y) / 4;

        player.setDy(dxy);
        player.setDx(dxy);
}

int gcd(int a, int b)
{
        if (b == 0)
                return a;
        return gcd(b, a % b);
}
