/**
 * @file sprite.hpp
 * @brief Defines the sprite class which can be used for drawing textures
 */
#ifndef SPRITE_H
#define SPRITE_H

#pragma once
#include <citro2d.h>
#include "m3d/graphics/boundingBox.hpp"
#include "m3d/graphics/color.hpp"
#include "m3d/graphics/drawable.hpp"
#include "m3d/graphics/texture.hpp"
#include "m3d/graphics/vertex.hpp"

namespace m3d {
    /**
     * @brief A sprite, which can be used to draw textures
     */
    class Sprite: public Drawable {
    public:
        /**
         * @brief Initializes the sprite
         */
        Sprite();

        /**
         * @brief Initializes the sprite with a spritesheet
         * @param t_spriteSheet The path to the spritesheet
         * @param t_imageId The index of the image from the spritesheet to use
         */
        Sprite(const std::string& t_spriteSheet, int t_imageId = 0);

        /**
         * @brief Sets the x position of the sprite
         * @param t_x The x position
         */
        void setXPosition(int t_x);

        /**
         * @brief Returns the x position of the sprite
         * @return The x position
         */
        int getXPosition();

        /**
         * @brief Sets the y position of the sprite
         * @param t_y The y position
         */
        void setYPosition(int t_y);

        /**
         * @brief Returns the y position of the sprite
         * @return The y position
         */
        int getYPosition();

        /**
         * @brief Sets the position of the sprite
         * @param t_x The x position
         * @param t_y The y position
         */
        void setPosition(int t_x, int t_y);

        /**
         * @brief Sets the position of the sprite
         * @param t_vector The vector representing the position
         * @note The first component of the vector is the x position, the second component is the y position
         */
        void setPosition(m3d::Vector2f t_vector);

        /**
         * @brief Moves the sprite a certain offset on the x-axis
         * @param t_offset The offset to move
         */
        void moveX(int t_offset);

        /**
         * @brief Moves the sprite a certain offset on the y-axis
         * @param t_offset The offset to move
         */
        void moveY(int t_offset);

        /**
         * @brief Moves the sprite a certain offset
         * @param t_offsetX The offset to move on the x-axis
         * @param t_offsetY The offset to move on the y-axis
         */
        void move(int t_offsetX, int t_offsetY);

        /**
         * @brief Moves the sprite a certain offset
         * @param t_vector The vector to move
         * @note The first component of the vector is the offset to move on the x-axis, the second component is the offset on the y-axis
         */
        void move(Vector2f t_vector);

        /**
         * @brief Sets the center of the sprite on the x-axis
         * @param t_x The center on the x-axis
         */
        void setCenterX(int t_x);

        /**
         * @brief Returns the center of the sprite on the x-axis
         * @return The center on the x-axis
         */
        int getCenterX();

        /**
         * @brief Sets the center of the sprite on the y-axis
         * @param t_y The center on the y-axis
         */
        void setCenterY(int t_y);

        /**
         * @brief Returns the center of the sprite on the y-axis
         * @return The center on the y-axis
         */
        int getCenterY();

        /**
         * @brief Sets the center of the sprite
         * @param t_x The center on the x-axis
         * @param t_y The center on the y-axis
         */
        void setCenter(int t_x, int t_y);

        /**
         * @brief Sets the center of the sprite
         * @param t_vector The vector representing the center
         * @note The first component of the vector is the x center, the second component is the y center
         */
        void setCenter(Vector2f t_vector);

        /**
         * @brief Sets the sprite's scale along the x-axis
         * @param t_scale The sprite's x-scale
         */
        void setXScale(float t_scale);

        /**
         * @brief Returns the sprite's scale along the x-axis
         * @return The sprite's x-scale
         */
        float getXScale();

        /**
         * @brief Sets the sprite's scale along the y-axis
         * @param t_scale The sprite's y-scale
         */
        void setYScale(float t_scale);

        /**
         * @brief Returns the sprite's scale along the y-axis
         * @return The sprite's y-scale
         */
        float getYScale();

        /**
         * @brief Sets the sprite's scale
         * @param t_xScale The scale along the x-axis
         * @param t_yScale The scale along the y-axis
         */
        void setScale(float t_xScale, float t_yScale);

        /**
         * @brief Scales a sprite along the x-axis
         * @param t_delta The value to add to the current scale
         */
        void scaleX(float t_delta);

        /**
         * @brief Scales a sprite along the y-axis
         * @param t_delta The value to add to the current scale
         */
        void scaleY(float t_delta);

        /**
         * @brief Scales a sprite along both axes
         * @param t_deltaX The value to add to the current x-scale
         * @param t_deltaY The value to add to the current y-scale
         */
        void scale(float t_deltaX, float t_deltaY);

        /**
         * @brief Sets the rotation of the sprite
         * @param t_rotation The rotation of the sprite
         * @param t_radians  Whether or not to use radians instead of degrees
         * @note By default, t_rotation has to be in degrees
         * @note The sprite always rotates around it's center
         */
        void setRotation(float t_rotation, bool t_radians = false);

        /**
         * @brief Rotates the sprite
         * @param t_delta    The value to add to the current rotation
         * @param t_radians  Whether or not to use radians instead of degrees
         * @note By default, t_delta has to be in degrees
         * @note The sprite always rotates around it's center
         */
        void rotate(float t_delta, bool t_radians = false);

        /**
         * @brief Sets the color to tint the sprite with
         * @param t_color The tint color
         */
        void setTint(m3d::Color t_color);

        /**
         * @brief Returns the current tint color of the sprite
         * @return The tint color
         */
        m3d::Color getTint();

        /**
         * @brief Sets the color tint blending strength of the sprite
         * @param t_blend The tint blending strength (0.0-1.0)
         */
        void setBlend(float t_blend);

        /**
         * @brief Returns the color tint blending strength of the sprite
         * @return The tint blending strength (0.0-1.0)
         */
        float getBlend();

        /**
         * @brief Sets the opacity of the sprite
         * @param t_opacity The new opacity (0-255)
         */
        void setOpacity(unsigned int t_opacity);

        /**
         * @brief Returns the current opacity of the sprite
         * @return The opacity of the sprite
         */
        float getOpacity();

        /**
         * @brief Sets the spritesheet of the sprite
         * @param t_spriteSheet The path to the spritesheet
         * @param t_imageId The index of the image from the spritesheet to use
         */
        void setSpriteSheet(const std::string& t_spriteSheet, int t_imageId = 0);

        /**
         * @brief Sets the texture of the sprite
         * @param t_texture The m3d::Texture to use
         */
        void setTexture(m3d::Texture& t_texture);

        /**
         * @brief Returns the path to the spritesheet assigned to the sprite
         * @return The path to the spritesheet
         */
        const std::string& getSpriteSheet();

        /**
         * @brief Draws the shape
         * @param t_context the RenderContext
         */
        void draw(m3d::RenderContext t_context);

    private:
        void updateTint();

        /* data */
        int m_posX, m_posY, m_centerX, m_centerY, m_opacity, m_index;
        float m_scaleX, m_scaleY, m_rotation, m_blendStrength;
        std::string m_spriteSheetPath;
        m3d::Color m_tintColor;
        C2D_Sprite m_sprite;
        C2D_ImageTint m_imageTint;
        C2D_SpriteSheet m_spriteSheet;
    };
} /* m3d */

#endif /* end of include guard: SPRITE_H */
