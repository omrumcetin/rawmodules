#pragma once
template <typename T>
struct vector2d
{
    union
    {
        struct
        {
            T x;
            T y;
        };
        T v[2];
    };

    inline vector2d(): x(T(0)), y(T(0)) {}
    inline vector2d(T InX, T InY) : x(InX), y(InY) {}
    inline vector2d(T* FV) : x(FV[0]), y(FV[1]) {}
};

typedef vector2d<float> fvector2d;
typedef vector2d<int> ivector2d;