#include "character.h"
#include <SFML/Graphics.hpp>
#include <stdlib.h> /* exit(EXIT_FAILURE); */ 

Character::Character(const std::vector<std::string>& sprite_file_loc,
        float scale_height, float scale_width,
        float pos_x, float pos_y)
{
        this->state = 0;
        for (int i = 0; i < sprite_file_loc.size(); i++) {
                sf::Texture texture;
                if (!texture.loadFromFile(sprite_file_loc[i]))
                        exit(EXIT_FAILURE);
                texture.setSrgb(true);
                texture.setSmooth(true);
                this->texture.push_back(texture);
        }

        this->pos_x = pos_x;
        this->pos_y = pos_y;
        this->scale_height = scale_height;
        this->scale_width = scale_width;

        update_texture_state();

        sprite.setScale(
                (scale_width / texture[state].getSize().x),
                (scale_height / texture[state].getSize().y)
        );
}


void Character::update_texture_state()
{
        size_t next_state, cur_state;

        cur_state = getState();
        this->sprite.setTexture(getTexture());

        next_state = ++state % this->texture.size();
        setState(next_state);
}

sf::Texture& Character::getTexture() const
{
        sf::Texture* texture = &texture[getState()];

        return texture[getState()];
}
