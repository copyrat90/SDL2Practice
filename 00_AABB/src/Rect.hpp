#pragma once

#include "GameObject.hpp"


class Rect : public GameObject
{
public:
    Rect(float x, float y, float w, float h, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int defaultStrength, bool fill = true);

    /**
     * @brief Updates previous position
     *
     * @param deltaTime
     */
    void Update(Uint32 deltaTime) override;
    void Render(SDL_Renderer*) const override;

    /**
     * @brief Checks if collided with other Rect
     * with AABB (Axis-Aligned Bounding Box) collision detection
     *
     * @param other The other Rect
     * @return true if there is any collision
     */
    bool CheckCollision(const Rect& other) const;

    /**
     * @brief Resolves collision by pushing away the Rect which has less colliderStrength_
     *
     * @param other The other Rect
     */
    void ResolveCollision(Rect& other);

    bool CheckPrevXAligned(const Rect& other) const;
    bool CheckPrevYAligned(const Rect& other) const;

protected:
    float left() const { return rect_.x; }
    float right() const { return rect_.x + rect_.w; }
    float top() const { return rect_.y; }
    float bottom() const { return rect_.y + rect_.h; }
    SDL_FPoint center() const { return { (left() + right()) / 2, (top() + bottom()) / 2 }; }

    float prevLeft() const { return prevRect_.x; }
    float prevRight() const { return prevRect_.x + prevRect_.w; }
    float prevTop() const { return prevRect_.y; }
    float prevBottom() const { return prevRect_.y + prevRect_.h; }
    SDL_FPoint prevCenter() const { return { (prevLeft() + prevRight()) / 2, (prevTop() + prevBottom()) / 2 }; }

    SDL_FRect rect_;
    SDL_FRect prevRect_;
    SDL_Color color_;
    int defaultStrength_;
    int temporaryStrength_;
    bool fill_;
};
