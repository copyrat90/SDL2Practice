#include "Rect.hpp"

#include <cassert>


Rect::Rect(float x, float y, float w, float h, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int defaultStrength, bool fill)
    : rect_{ x, y, w, h }, color_{ r, g, b, a }, defaultStrength_(defaultStrength), temporaryStrength_(defaultStrength), fill_(fill)
{

}

void Rect::Update(Uint32 deltaTime)
{
    prevRect_ = rect_;
    temporaryStrength_ = defaultStrength_;
}

void Rect::Render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
    if (fill_)
        SDL_RenderFillRectF(renderer, &rect_);
    else
        SDL_RenderDrawRectF(renderer, &rect_);
}

bool Rect::CheckCollision(const Rect& other) const
{
    return this->left() < other.right() && other.left() < this->right()
        && this->bottom() > other.top() && other.bottom() > this->top();
}

void Rect::ResolveCollision(Rect& other)
{
    // other is the one pushed away
    // If other has more strength, push the other way around
    if (other.temporaryStrength_ > this->temporaryStrength_)
    {
        other.ResolveCollision(*this);
        return;
    }

    // propagate temporary strength
    other.temporaryStrength_ = this->temporaryStrength_;

    const SDL_FPoint centerVector{ other.rect_.x - this->rect_.x, other.rect_.y - this->rect_.y };
    if (CheckPrevXAligned(other) != CheckPrevYAligned(other))
    {
        // push vertically (Y axis)
        if (CheckPrevXAligned(other))
        {
            const float pushBackDistance = (this->rect_.h + other.rect_.h) / 2 - std::abs(centerVector.y);
            assert((pushBackDistance >= 0));
            // other is upper
            if (centerVector.y < 0)
                other.rect_.y -= pushBackDistance;
            // other is lower
            else
                other.rect_.y += pushBackDistance;
        }
        // push horizontally (X axis)
        else
        {
            const float pushBackDistance = (this->rect_.w + other.rect_.w) / 2 - std::abs(centerVector.x);
            assert((pushBackDistance >= 0));
            // other is right
            if (centerVector.x > 0)
                other.rect_.x += pushBackDistance;
            // other is left
            else
                other.rect_.x -= pushBackDistance;
        }
    }
    else
    {
        // push horizontally and vertically at the same time
        SDL_FPoint pushBackDistance{ (this->rect_.w + other.rect_.w) / 2 - std::abs(centerVector.x),
            (this->rect_.h + other.rect_.h) / 2 - std::abs(centerVector.y) };
        assert((pushBackDistance.x >= 0 && pushBackDistance.y >= 0));
        // push horizontally (X axis)
        if (centerVector.x > 0)
            other.rect_.x += pushBackDistance.x;
        else
            other.rect_.x -= pushBackDistance.x;
        // push vertically (Y axis)
        if (centerVector.y < 0)
            other.rect_.y -= pushBackDistance.y;
        else
            other.rect_.y += pushBackDistance.y;
    }
}

bool Rect::CheckPrevXAligned(const Rect& other) const
{
    return this->prevLeft() < other.prevRight() && other.prevLeft() < this->prevRight();
}

bool Rect::CheckPrevYAligned(const Rect& other) const
{
    return this->prevTop() < other.prevBottom() && other.prevTop() < this->prevBottom();
}
