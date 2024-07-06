#pragma once
template <typename T>
struct vector4d
{
    union
    {
        struct
        {
            T x;
            T y;
            T z;
            T w;
        };
        T v[4];
    };

    inline vector4d() : x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}
    inline vector4d(T InX, T InY, T InZ, T InW) : x(InX), y(InY), z(InZ), w(InW) {}
    inline vector4d(T* FV) : x(FV[0]), y(FV[1]), y(FV[2]), z(FV[3]) {}
};

typedef vector4d<float> fvector4d;
typedef vector4d<int> ivector4d;
typedef vector4d<unsigned int> uivector4d;

template <typename T>
bool operator==(const vector4d<T>& LeftOperand, const vector4d<T>& RightOperand)
{
    for (size_t i{ 0 }; i < 4; ++i)
    {
        if (LeftOperand.v[i] != RightOperand.v[i])
            return false;
    }
    return true;
}
