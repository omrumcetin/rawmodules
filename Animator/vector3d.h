#pragma once

#define VECTOR_EPSILON 0.000001f

struct vector3d
{
    union {
        struct {
            float x;
            float y;
            float z;
        };
        float v[3];
    };
    // default constructor
    vector3d()
        : x(.0f)
        , y(.0f)
        , z(.0f)
    {

    };

    // each element
    inline vector3d(float InX, float InY, float InZ)
        :x(InX)
        ,y(InY)
        ,z(InZ){}

    // pointer to float array
    inline vector3d(float* InFV)
        :x(InFV[0])
        ,y(InFV[1])
        ,z(InFV[2]){}
};

vector3d& operator+=(vector3d& LeftOperand, const vector3d& RightOperand);
vector3d operator+(const vector3d& LeftOperand, const vector3d& RightOperand);
vector3d operator-=(vector3d& LeftOperand, const vector3d& RightOperand);
vector3d operator-(const vector3d& LeftOperand, const vector3d& RightOperand);
vector3d operator*(const vector3d& LeftOperand, const double& RightOperand);
bool operator==(const vector3d& LeftOperand, const vector3d& RightOperand);
bool operator!=(const vector3d& LeftOperand, const vector3d& RightOperand);

// Return in Radians
float angle(const vector3d& v1, const vector3d& v2);
float dot(const vector3d& InFirstVector, const vector3d& InSecondVector);
float len_sq(const vector3d&) ;
float len(const vector3d&) ;
void normalize(vector3d&);
vector3d normalized(const vector3d&);
vector3d project(const vector3d&, const vector3d&);
vector3d reject(const vector3d&, const vector3d&);
vector3d cross(const vector3d&, const vector3d&);
vector3d lerp(const vector3d&, const vector3d&, float);
vector3d slerp(const vector3d&, const vector3d&, float);
vector3d nlerp(const vector3d&, const vector3d&, float);

// We wont use this in animations. But its good for physics and AI ??
vector3d reflect(const vector3d&, const vector3d&);
