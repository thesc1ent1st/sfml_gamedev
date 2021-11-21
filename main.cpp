#include <iostream> 
#include <vector>
#include <string>
#include <stdio.h> 

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#define SCREENWIDTH 800
#define SCREENHEIGHT 600

#define SPRITE_HEIGHT 64.0
#define SPRITE_WIDTH 64.0

struct Cordinates {
        float cur_x;
        float cur_y;
        float dx;
        float dy;
};

struct Character {
        std::vector<sf::Texture> texture;
        sf::Texture cur_texture;
        sf::Sprite sprite;
        Cordinates loc;
        size_t state;
};

int gcd(int a, int b);
bool init_player(Character& player, const std::vector<std::string>& sprite_file_loc, float height, float width);
void update_current_texture(Character& player);

int main(int argc, char** argv)
{
        sf::Music music;
        sf::Keyboard kb;
        Character p1;
        std::vector<std::string> sprite_loc = {
                "RunRight01.png",
                "RunRight02.png",
                "RunRight03.png",
                "RunRight04.png"
        };

        sf::RenderWindow window(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "Ginga Ninja");
        if (!music.openFromFile("No6.ogg"))
                return EXIT_FAILURE;

        if (!init_player(p1, sprite_loc, SPRITE_HEIGHT, SPRITE_WIDTH))
                return EXIT_FAILURE;

        music.play();
        while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                                window.close();

                        if (event.type == sf::Event::KeyPressed) {
                                switch (event.key.code) {
                                case sf::Keyboard::Key::Up:
                                        p1.loc.cur_y -= p1.loc.dy;
                                        if (p1.loc.cur_y < -(SPRITE_HEIGHT / 2))
                                                p1.loc.cur_y = SCREENHEIGHT - (SPRITE_HEIGHT / 2);
                                        update_current_texture(p1);
                                        break;

                                case sf::Keyboard::Key::Down:
                                        p1.loc.cur_y += p1.loc.dy;
                                        if (p1.loc.cur_y + (SPRITE_HEIGHT / 2) > SCREENHEIGHT)
                                                p1.loc.cur_y = -(SPRITE_HEIGHT / 2);
                                        update_current_texture(p1);
                                        break;

                                case sf::Keyboard::Key::Left:
                                        p1.loc.cur_x -= p1.loc.dx;
                                        if (p1.loc.cur_x < -(SPRITE_WIDTH / 2))
                                                p1.loc.cur_x = SCREENWIDTH - (SPRITE_WIDTH / 2);
                                        update_current_texture(p1);
                                        break;

                                case sf::Keyboard::Key::Right:
                                        p1.loc.cur_x += p1.loc.dx;
                                        if (p1.loc.cur_x + (SPRITE_WIDTH / 2) > SCREENWIDTH)
                                                p1.loc.cur_x = -(SPRITE_WIDTH / 2);
                                        update_current_texture(p1);
                                        break;
                                default:
                                        break;
                                }
                        }
                }
#ifdef DEBUG
                printf("(X:%f, Y:%f)\n", p1.loc.cur_x, p1.loc.cur_y);
#endif // DEBUG
                p1.sprite.setPosition(p1.loc.cur_x, p1.loc.cur_y);
                window.clear(sf::Color::White);
                window.draw(p1.sprite);
                window.display();
        }

        return EXIT_SUCCESS;
}


bool init_player(Character& player, const std::vector<std::string>& sprite_file_loc, float height, float width)
{
        sf::Color color(0, 0, 0, 0);
        float x, y;

        x = (float)gcd(SCREENWIDTH, width);
        y = (float)gcd(SCREENHEIGHT, height);
        player.loc.dy = player.loc.dx = (float)gcd(x, y);

        player.state = 0;
        for (int i = 0; i < sprite_file_loc.size(); i++) {
                sf::Texture texture;
                if (!texture.loadFromFile(sprite_file_loc[i]))
                        return false;
                texture.setSrgb(true);
                texture.setSmooth(true);

                player.texture.push_back(texture);
        }

        update_current_texture(player);

        player.sprite.setScale((width / player.texture[player.state].getSize().x),
                (height / player.texture[player.state].getSize().y));

        return true;
}

void update_current_texture(Character& player)
{
        player.sprite.setTexture(player.texture[player.state]);
        player.state = ++player.state % player.texture.size();
}

int gcd(int a, int b)
{
        if (b == 0)
                return a;
        return gcd(b, a % b);
}
