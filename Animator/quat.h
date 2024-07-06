#pragma once

#include "vector3d.h"
#include "matrix4.h"

#define QUAT_EPSILON 0.000001f

struct quat
{
    union
    {
        struct
        {
            float x;
            float y;
            float z;
            float w;
        };
        struct
        {
            vector3d vector;
            float scalar;
        };
    };
    // Formulas
    // v1 X v2 = axis * sin?
    // v1 . v2 = cos?


    inline quat() :
        x(0), y(0), z(0), w(1) {}

    inline quat(float InX, float InY, float InZ, float InW)
        : x(InX), y(InY), z(InZ), w(InW) {}
};

quat angle_axis(float Angle, const vector3d& Axis);
quat from_to(const vector3d& InFrom, const vector3d& To);
vector3d get_axis(const quat& quat);
float get_angle(const quat& quat);
bool same_orientation(const quat& left, const quat& right);
float dot(const quat& a, const quat& b);
float len_sq(const quat& a);
float len(const quat& q);

// Just rotation, non normalized ones add skew(egik, yamuk) info in it.
void normalize(quat& q);
quat normalized(const quat& q);
// Flips axis of its rotation
quat conjugate(const quat& q);
quat inverse(const quat& q);
// Mix
quat mix(const quat& from, const quat& to, float t);
quat nlerp(const quat& from, const quat& to, float t);
quat slerp(const quat& start, const quat& end, float t);
quat look_rotation(const vector3d& direction, const vector3d& up);

matrix4 quat_to_mat4(const quat& q);
quat mat4_to_quat(const matrix4& m);


quat operator+(const quat& a, const quat& b);
quat operator-(const quat& a, const quat& b);
quat operator*(const quat& a, float f);
quat operator*(const quat& q1, const quat& q2);
vector3d operator*(const quat& q, const vector3d& v);
quat operator-(const quat& q);
bool operator==(const quat& left, const quat& right);
bool operator!=(const quat& left, const quat& right);
quat operator^(const quat& q, float f);
