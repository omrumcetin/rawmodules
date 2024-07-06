#include "vector3d.h"
#include <math.h>

vector3d operator-=(vector3d& LeftOperand, const vector3d& RightOperand)
{
    LeftOperand.x -= RightOperand.x;
    LeftOperand.y -= RightOperand.y;
    LeftOperand.z -= RightOperand.z;
    return LeftOperand;
}

vector3d operator+(const vector3d& LeftOperand, const vector3d& RightOperand)
{
    vector3d tmp(LeftOperand);
    tmp += RightOperand;
    return tmp;
}


vector3d& operator+=(vector3d& LeftOperand, const vector3d& RightOperand)
{
    LeftOperand.x += RightOperand.x;
    LeftOperand.y += RightOperand.y;
    LeftOperand.z += RightOperand.z;
    return LeftOperand;
}

vector3d operator-(const vector3d& LeftOperand, const vector3d& RightOperand)
{
    vector3d tmp(LeftOperand);
    tmp -= RightOperand;
    return tmp;
}

vector3d operator*(const vector3d& LeftOperand, const double& InF)
{
    return vector3d(LeftOperand.x * InF, LeftOperand.y * InF, LeftOperand.z * InF);
}

bool operator==(const vector3d& LeftOperand, const vector3d& RightOperand)
{
    vector3d diff(LeftOperand - RightOperand);
    return len_sq(diff) < VECTOR_EPSILON;
}

bool operator!=(const vector3d& LeftOperand, const vector3d& RightOperand)
{
    return !(LeftOperand == RightOperand);
}

float angle(const vector3d& v1, const vector3d& v2)
{
    float v1LenSq = len_sq(v1);
    float v2LenSq = len_sq(v2);

    if (v1LenSq < VECTOR_EPSILON || v2LenSq < VECTOR_EPSILON)
    {
        return 0.f;
    }
    float dotProduct = dot(v1, v2);
    float length = sqrtf(v1LenSq) + sqrtf(v2LenSq);
    return acosf(dotProduct / length);
}

float dot(const vector3d& InFirstVector, const vector3d& InSecondVector)
{
    return InFirstVector.x * InSecondVector.x + InFirstVector.y * InSecondVector.y + InFirstVector.z * InSecondVector.z;
}

float len_sq(const vector3d& V)
{
    return V.x *V.x + V.y*V.y + V.z * V.z;
}

float len(const vector3d& V) 
{
    const float lengthSq = len_sq(V);
    if (lengthSq < VECTOR_EPSILON)
        return 0.f;
    return sqrtf(lengthSq);
}

vector3d project(const vector3d& V1, const vector3d& V2)
{
    float magBSq = len(V2);
    if (magBSq < VECTOR_EPSILON)
    {
        return vector3d();
    }
    float scale = dot(V1, V2) / magBSq;
    return V2 * scale;
}

vector3d reject(const vector3d& V1, const vector3d& V2)
{
    vector3d proj = project(V1, V2);
    return V1 - proj;
}

vector3d cross(const vector3d& V1, const vector3d& V2)
{
    return vector3d(
        V1.y * V2.z - V2.y * V1.z,
        V1.x * V2.z - V1.z * V2.x,
        V1.x * V2.y - V1.y * V2.x
    );
}

vector3d lerp(const vector3d& V1, const vector3d& V2, float Alpha)
{
    return vector3d(
        V1.x + (V2.x - V1.x) * Alpha,
        V1.y + (V2.y - V1.y) * Alpha,
        V1.z + (V2.z - V1.z) * Alpha 
    );
}

vector3d slerp(const vector3d& V1, const vector3d& V2, float Alpha)
{
    if (Alpha < .01f) return lerp(V1, V2, Alpha);
    vector3d from = normalized(V1);
    vector3d to = normalized(V2);

    float theta = angle(from, to);
    float sinTheta = sinf(theta);

    float a = sinf((1.f - Alpha) * theta) / sinTheta;
    float b = sinf(Alpha * theta) / sinTheta;

    return from * a + to * b;
}

vector3d nlerp(const vector3d& V1, const vector3d& V2, float Alpha)
{
    vector3d linear = lerp(V1, V2, Alpha);
    return normalized(linear);
}

vector3d reflect(const vector3d& V1, const vector3d& V2)
{
    float magV2Sq = len(V2);
    if (magV2Sq < VECTOR_EPSILON)
        return vector3d();
    float scale = dot(V1, V2) / magV2Sq;
    vector3d proj2 = V2 * (scale * 2);
    return V1 - proj2;
}

void normalize(vector3d& V)
{
    const float l = len(V);
    if (l < VECTOR_EPSILON)
        return;
    float invLen = 1.f / l;
    V.x *= invLen;
    V.y *= invLen;
    V.z *= invLen;
}

vector3d normalized(const vector3d& V)
{
    const float lenSq = len_sq(V);
    if (lenSq < VECTOR_EPSILON)
        return V;
    float invLen = 1.f / sqrtf(lenSq);
    return vector3d(V.x * invLen, V.y * invLen, V.z * invLen);
}