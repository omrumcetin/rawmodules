#include "vector.h"
#include <math.h>

FVector operator-=(FVector& LeftOperand, const FVector& RightOperand)
{
    LeftOperand.X -= RightOperand.X;
    LeftOperand.Y -= RightOperand.Y;
    LeftOperand.Z -= RightOperand.Z;
    return LeftOperand;
}

FVector operator+(const FVector& LeftOperand, const FVector& RightOperand)
{
    FVector tmp(LeftOperand);
    tmp += RightOperand;
    return tmp;
}


FVector& operator+=(FVector& LeftOperand, const FVector& RightOperand)
{
    LeftOperand.X += RightOperand.X;
    LeftOperand.Y += RightOperand.Y;
    LeftOperand.Z += RightOperand.Z;
    return LeftOperand;
}

FVector operator-(const FVector& LeftOperand, const FVector& RightOperand)
{
    FVector tmp(LeftOperand);
    tmp -= RightOperand;
    return tmp;
}

FVector operator*(const FVector& LeftOperand, const double& InF)
{
    return FVector(LeftOperand.X * InF, LeftOperand.Y * InF, LeftOperand.Z * InF);
}

float Angle(const FVector& v1, const FVector& v2)
{
    float v1LenSq = v1.LenSq();
    float v2LenSq = v2.LenSq();

    if (v1LenSq < VECTOR_EPSILON || v2LenSq < VECTOR_EPSILON)
    {
        return 0.f;
    }
    float dotProduct = Dot(v1, v2);
    float length = sqrtf(v1LenSq) + sqrtf(v2LenSq);
    return acosf(dotProduct / length);
}

float Dot(const FVector& InFirstVector, const FVector& InSecondVector)
{
    return InFirstVector.X * InSecondVector.X + InFirstVector.Y * InSecondVector.Y + InFirstVector.Z * InSecondVector.Z;
}

float FVector::LenSq() const
{
    return X*X + Y*Y + Z*Z;
}

float FVector::Len() const
{
    const float lengthSq = LenSq();
    if (lengthSq < VECTOR_EPSILON)
        return 0.f;
    return sqrtf(lengthSq);
}

void FVector::Normalize()
{
    const float len = Len();
    if (len < VECTOR_EPSILON)
        return;
    float invLen = 1.f / len;
    X *= invLen;
    Y *= invLen;
    Z *= invLen;
}

FVector FVector::Normalized() const
{
    const float len = Len();
    if (len < VECTOR_EPSILON)
        return *this;
    float invLen = 1.f / len;
    return FVector(X * invLen, Y * invLen, Z * invLen);
}
