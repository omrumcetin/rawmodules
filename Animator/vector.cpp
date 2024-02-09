#include "vector.h"

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

float FVector::Dot(const FVector& InFirstVector, const FVector& InSecondVector)
{
    return InFirstVector.X * InSecondVector.X + InFirstVector.Y * InSecondVector.Y + InFirstVector.Z * InSecondVector.Z;
}