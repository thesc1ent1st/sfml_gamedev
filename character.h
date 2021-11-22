#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <vector>
#include <string>
#include <iostream> 
#include <SFML/Graphics/Sprite.hpp>

class Character {
public:
        Character(const std::vector<std::string>& sprite_file_loc,
                float sprite_height, float sprite_width,
                const sf::Vector2f loc);

        void update_texture_state();

        float getDy() const { return dy; }
        void setDy(float dy_) { dy = dy_; }

        float getDx() const { return dx; }
        void setDx(float dx_) { dx = dx_; }

        size_t getState() const { return state; }
        void setState(const size_t& state_) { state = state_; }

        sf::Sprite& getSprite() { return sprite; }
        float getScaleWidth() const { return scale_width; }
        float getScaleHeight() const { return scale_height; }

        sf::Texture& getTexture() { return texture[this->getState()]; }

private:
        std::vector<sf::Texture> texture;
        sf::Sprite sprite;
        size_t state;
        float scale_height, scale_width, dx, dy;
};

#endif // __CHARACTER_H__