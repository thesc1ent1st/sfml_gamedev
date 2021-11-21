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

int main(int argc, char** argv)
{
        sf::Music music;

        Screen screen("Ginga Ninja");
        Character p1(p1_sprite_path, 64.0, 64.0, 0, 0);
        if (!music.openFromFile("./music/No6.ogg"))
                return EXIT_FAILURE;

        music.play();
        while (screen.window.isOpen()) {
                sf::Event event;
                while (screen.window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                                screen.window.close();

                        if (event.type == sf::Event::KeyPressed)
                                handle_key_code(event.key.code, screen, p1);
                }
#ifdef DEBUG
                printf("(X:%f, Y:%f)\n", game.p1.loc.pos_x, game.p1.loc.pos_y);
#endif // DEBUG
                p1.getSprite().setPosition(p1.curX(), p1.curY());
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

        float pos_y = p1.curY();
        float pos_x = p1.curX();

        float dy = p1.getDy();
        float dx = p1.getDx();

        switch (code) {
        case sf::Keyboard::Key::Up:
                pos_y = (pos_y - dy < -(sprite_height / 2)) ?
                        (screen_height - (sprite_height / 2)) :
                        (pos_y - dy);
                break;

        case sf::Keyboard::Key::Down:
                pos_y = (pos_y + dy + (sprite_height / 2) > screen_height) ?
                        -(sprite_height / 2) :
                        (pos_y + dy);
                break;

        case sf::Keyboard::Key::Left:
                pos_x = (pos_x - dx < -(sprite_width / 2)) ?
                        (screen_width - (sprite_width / 2)) :
                        (pos_x - dx);
                break;

        case sf::Keyboard::Key::Right:
                pos_x = (pos_x + dx + (sprite_width / 2) > screen_width) ?
                        -(sprite_width / 2) :
                        (pos_x + dx);
                break;
        default:
                return;
        }

        p1.setCurX(pos_x);
        p1.setCurY(pos_y);
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
