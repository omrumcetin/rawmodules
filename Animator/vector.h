#pragma once

#define VECTOR_EPSILON 0.000001f

struct FVector
{
    union {
        struct {
            float X;
            float Y;
            float Z;
        };
        float V[3];
    };
    // default constructor
    FVector()
        : X(.0f)
        , Y(.0f)
        , Z(.0f)
    {

    };

    // each element
    inline FVector(float InX, float InY, float InZ)
        :X(InX)
        ,Y(InY)
        ,Z(InZ){}

    // pointer to float array
    inline FVector(float* InFV)
        :X(InFV[0])
        ,Y(InFV[1])
        ,Z(InFV[2]){}

    float LenSq() const;
    float Len() const;
    void Normalize();
    FVector Normalized() const;
};

inline FVector& operator+=(FVector& LeftOperand, const FVector& RightOperand);
inline FVector operator+(const FVector& LeftOperand, const FVector& RightOperand);
inline FVector operator-=(FVector& LeftOperand, const FVector& RightOperand);
inline FVector operator-(const FVector& LeftOperand, const FVector& RightOperand);
inline FVector operator*(const FVector& LeftOperand, const double& RightOperand);

// Return in Radians
float Angle(const FVector& v1, const FVector& v2);
float Dot(const FVector& InFirstVector, const FVector& InSecondVector);