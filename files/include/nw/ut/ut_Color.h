#ifndef NW_UT_COLOR_H_
#define NW_UT_COLOR_H_

#include <nw/math/math_Types.h>

namespace nw { namespace ut {

struct FloatColor
{
public:
    typedef FloatColor SelfType;

    static const int ELEMENT_MIN        = 0;
    static const int ELEMENT_MAX        = 1;
    static const int ALPHA_MIN          = ELEMENT_MIN;
    static const int ALPHA_MAX          = ELEMENT_MAX;
    static const int ALPHA_OPACITY      = ALPHA_MAX;
    static const int ALPHA_TRANSPARENT  = ALPHA_MIN;

    FloatColor()
        : r(0.0f)
        , g(0.0f)
        , b(0.0f)
        , a(1.0f)
    {
    }

    explicit FloatColor(const nw::math::VEC4& vec)
        : r(vec.x)
        , g(vec.y)
        , b(vec.z)
        , a(vec.w)
    {
    }

    FloatColor(const SelfType& color)
        : r(color.r)
        , g(color.g)
        , b(color.b)
        , a(color.a)
    {
    }

    FloatColor(const SelfType& color, f32 alpha)
        : r(color.r)
        , g(color.g)
        , b(color.b)
        , a(alpha)
    {
    }

    FloatColor(f32 red, f32 green, f32 blue, f32 alpha)
        : r(red)
        , g(green)
        , b(blue)
        , a(alpha)
    {
    }

    ~FloatColor()
    {
    }

    SelfType& operator =(const nw::math::VEC4& vec)
    {
        this->Set( vec.x, vec.y, vec.z, vec.w );
        return *this;
    }

    operator f32*() { return &r; }
    operator const f32*() const { return &r; }

    const SelfType operator +(const SelfType& right) const
    {
        SelfType color(
            this->r + right.r,
            this->g + right.g,
            this->b + right.b,
            this->a + right.a
        );
        return color;
    }

    const SelfType operator -(const SelfType& right) const
    {
        SelfType color(
            this->r - right.r,
            this->g - right.g,
            this->b - right.b,
            this->a - right.a
        );
        return color;
    }

    const SelfType operator *(const SelfType& right) const
    {
        SelfType color(
            this->r * right.r,
            this->g * right.g,
            this->b * right.b,
            this->a * right.a
        );
        return color;
    }

    const SelfType operator /(const SelfType& right) const
    {
        SelfType color(
            (right.r != 0) ? (this->r / right.r) : ELEMENT_MAX,
            (right.g != 0) ? (this->g / right.g) : ELEMENT_MAX,
            (right.b != 0) ? (this->b / right.b) : ELEMENT_MAX,
            (right.a != 0) ? (this->a / right.a) : ELEMENT_MAX
        );
        return color;
    }

    SelfType& operator +=(const SelfType& rhs)
    {
        *this = *this + rhs;
        return *this;
    }

    SelfType& operator -=(const SelfType& rhs)
    {
        *this = *this - rhs;
        return *this;
    }

    SelfType& operator *=(const SelfType& rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    SelfType& operator /=(const SelfType& rhs)
    {
        *this = *this / rhs;
        return *this;
    }

    SelfType& operator +=(f32 right)
    {
        this->r += right;
        this->g += right;
        this->b += right;
        this->a += right;
        return *this;
    }

    SelfType& operator -=(f32 right)
    {
        this->r -= right;
        this->g -= right;
        this->b -= right;
        this->a -= right;
        return *this;
    }

    SelfType& operator *=(f32 right)
    {
        this->r *= right;
        this->g *= right;
        this->b *= right;
        this->a *= right;
        return *this;
    }

    SelfType& operator /=(f32 right)
    {
        if (right != 0.0f)
        {
            this->r /= right;
            this->g /= right;
            this->b /= right;
            this->a /= right;
        }
        else
        {
            this->r = ELEMENT_MAX;
            this->g = ELEMENT_MAX;
            this->b = ELEMENT_MAX;
            this->a = ELEMENT_MAX;
        }
        return *this;
    }

    bool        operator ==(const SelfType& rhs) const
    {
        return (r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a);
    }

    bool        operator !=(const SelfType& rhs) const
    {
        return !(*this == rhs);
    }

    void        Set(
                    f32 red,
                    f32 green,
                    f32 blue,
                    f32 alpha = ALPHA_OPACITY )
    {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }

    void        SetColor(
                    f32 red,
                    f32 green,
                    f32 blue )
    {
        r = red;
        g = green;
        b = blue;
    }

    void        SetAlpha( f32 alpha )
    {
        a = alpha;
    }

    void        Set(const SelfType& color) { operator =(color); }

    bool        IsTransparent() { return a <= 0.0f; }

    f32*        ToArray()       { return reinterpret_cast<f32*>( this ); }
    const f32*  ToArray() const { return reinterpret_cast<const f32*>( this ); }

protected:
    nw::math::VEC4&        ToVEC4()
    {
        return *reinterpret_cast<nw::math::VEC4*>(this);
    }

    const nw::math::VEC4&  ToVEC4() const
    {
        return *reinterpret_cast<const nw::math::VEC4*>(this);
    }

public:
    f32 r;
    f32 g;
    f32 b;
    f32 a;
};

} } // namespace nw::ut

#endif // NW_UT_COLOR_H_
