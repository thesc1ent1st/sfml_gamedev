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
                float pos_x, float pos_y);

        void update_texture_state();

        float getDy() const { return dy; }
        void setDy(float dy_) { dy = dy_; }

        float getDx() const { return dx; }
        void setDx(float dx_) { dx = dx_; }

        float curX() const { return pos_x; }
        void setCurX(float curX) { pos_x = curX; }

        float curY() const { return pos_y; }
        void setCurY(float curY) { pos_y = curY; }

        size_t getState() const { return state; }
        void setState(const size_t& state_) { state = state_; }

        sf::Sprite getSprite() const { return sprite; }
        sf::Texture& getTexture() const;
        float getScaleWidth() const { return scale_width; }
        float getScaleHeight() const { return scale_height; }

private:
        std::vector<sf::Texture> texture;
        sf::Sprite sprite;
        size_t state;
        float scale_height, scale_width, pos_x, pos_y, dx, dy;
};

#endif // __CHARACTER_H__