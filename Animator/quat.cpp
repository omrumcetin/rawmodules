#include "quat.h"
#include <cmath>

quat angle_axis(float Angle, const vector3d& Axis)
{
    vector3d norm = normalized(Axis);
    float s = sinf(Angle * 0.5f);

    return quat(
        norm.x * s,
        norm.y * s,
        norm.z * s,
        cosf(Angle * 0.5f)
    );
}

quat from_to(const vector3d& InFrom, const vector3d& To)
{
    vector3d f = normalized(InFrom);
    vector3d t = normalized(To);
    if (f == t)
    {
        return quat();
    }
    else if (f == t * -1.f)
    {
        vector3d ortho = vector3d(1, 0, 0);
        if (fabsf(f.y) < fabsf(f.x))
        {
            ortho = vector3d(0, 1, 0);
        }
        if (fabsf(f.z) < fabs(f.y) && fabs(f.z) < fabsf(f.x))
        {
            ortho = vector3d(0, 0, 1);
        }
        vector3d axis = normalized(cross(f, ortho));
        return quat(axis.x, axis.y, axis.z, 0);
    }
    vector3d half = normalized(f + t);
    vector3d axis = cross(f, half);
    return quat(axis.x, axis.y, axis.z, dot(f, half));
}

vector3d get_axis(const quat& quat)
{
    return normalized(vector3d(quat.x, quat.y, quat.z));
}

float get_angle(const quat& quat)
{
    return 2.f * acosf(quat.w);
}

bool same_orientation(const quat& left, const quat& right)
{
    return 
        (
            fabsf(left.x - right.x) <= QUAT_EPSILON &&
            fabsf(left.y - right.y) <= QUAT_EPSILON &&
            fabsf(left.z - right.z) <= QUAT_EPSILON &&
            fabsf(left.w - right.w) <= QUAT_EPSILON 
        ) 
            ||
        (
            fabsf(left.x + right.x) <= QUAT_EPSILON &&
            fabsf(left.y + right.y) <= QUAT_EPSILON &&
            fabsf(left.z + right.z) <= QUAT_EPSILON &&
            fabsf(left.w + right.w) <= QUAT_EPSILON
        )
        ;
}

float dot(const quat& a, const quat& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float len_sq(const quat& q)
{
    return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}

float len(const quat& q)
{
    float lensq = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
    if (lensq < QUAT_EPSILON) return 0.f;
    return sqrtf(lensq);
}

void normalize(quat& q)
{
    float lensq = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
    if (lensq < QUAT_EPSILON) return;
    // inverse length
    float il{ 1.f / sqrtf(lensq) };
    q.x *= il;
    q.y *= il;
    q.z *= il;
    q.w *= il;
}

quat normalized(const quat& q)
{
    float lensq = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
    if (lensq < QUAT_EPSILON) return quat();
    // inverse length
    float il = 1.f / sqrtf(lensq);
    return quat
    (
        q.x * il,
        q.y * il,
        q.z * il,
        q.w * il
    );
}

quat conjugate(const quat& q)
{
    return quat
    (
        -q.x,
        -q.y,
        -q.z,
        q.w
    );
}

quat inverse(const quat& q)
{
    float lensq = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
    if (lensq < QUAT_EPSILON) return quat();
    float recip = 1.f / lensq;
    return quat(
        -q.x * recip,
        -q.y * recip,
        -q.z * recip,
        q.w * recip
    );
}

quat mix(const quat& from, const quat& to, float t)
{
    return from * (1.f - t) + to * t;
}

quat nlerp(const quat& from, const quat& to, float t)
{
    return normalized(from + (to - from) * t);
}

quat slerp(const quat& start, const quat& end, float t)
{
    if (fabsf(dot(start, end)) > 1.f - QUAT_EPSILON)
    {
        return nlerp(start, end, t);
    }

    quat delta = inverse(start) * end;
    return normalized((delta ^ t) * start);
}

quat look_rotation(const vector3d& direction, const vector3d& up)
{
    vector3d f = normalized(direction); // object forward
    vector3d u = normalized(up); // desired up
    vector3d r = cross(u, f); // object right
    u = cross(f, r); // object up

    // from world forward to object forward
    quat worldToObject = from_to(vector3d(0, 0, 1), f);

    // what direction is the new object up ?
    vector3d objectUp = worldToObject * vector3d(0, 1, 0);
    // from object up to desired up
    quat u2u = from_to(objectUp, u);

    // rotate to forward direction first
    // then twist to correct up
    quat result = worldToObject * u2u;

    // because we need rotation quat needs to be normalized.
    return normalized(result);
}

matrix4 quat_to_mat4(const quat& q)
{
    vector3d r = q * vector3d(1, 0, 0);
    vector3d u = q * vector3d(0, 1, 0);
    vector3d f = q * vector3d(0, 0, 1);
    return matrix4(
        r.x, r.y, r.z, 0,
        u.x, u.y, u.z, 0,
        f.x, f.y, f.z, 0,
          0,   0,   0, 1
    );
}

quat mat4_to_quat(const matrix4& m)
{
    vector3d up = normalized(vector3d(m.up.x, m.up.y, m.up.z));
    vector3d forward = normalized(vector3d(m.forward.x, m.forward.y, m.forward.z));
    vector3d right = cross(up, forward);
    up = cross(forward, right);
    return look_rotation(forward, up);
}

quat operator+(const quat& a, const quat& b)
{
    return quat(a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w);
}

quat operator-(const quat& a, const quat& b)
{
    return quat(a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w);
}

quat operator*(const quat& a, float f)
{
    return quat(a.x*f, a.y*f, a.z*f, a.w*f);
}

quat operator*(const quat& q1, const quat& q2)
{
    return quat(
        q2.x*q1.w + q2.y*q1.z - q2.z*q1.y + q2.w*q1.x,
       -q2.x*q1.z + q2.y*q1.w + q2.z*q1.x + q2.w*q1.y,
        q2.x*q1.y - q2.y*q1.x + q2.z*q1.w + q2.w*q1.z,
       -q2.x*q1.x - q2.y*q1.y - q2.z*q1.z + q2.w*q1.w
    );
}

vector3d operator*(const quat& q, const vector3d& v)
{
    return q.vector * 2.f * dot(q.vector, v) +
        v * (q.scalar * q.scalar - dot(q.vector, q.vector)) +
        cross(q.vector, v) * 2.f * q.scalar;
}

quat operator-(const quat& q)
{
    return quat(-q.x, -q.y, -q.z, -q.w);
}

bool operator==(const quat& left, const quat& right)
{
    return (
        fabsf(left.x - right.x) <= QUAT_EPSILON &&
        fabsf(left.y - right.y) <= QUAT_EPSILON &&
        fabsf(left.z - right.z) <= QUAT_EPSILON &&
        fabsf(left.w - right.w) <= QUAT_EPSILON
        );
}

bool operator!=(const quat& left, const quat& right)
{
    return !( left == right);
}

quat operator^(const quat& q, float f)
{
    float angle = 2.f * acosf(q.scalar);
    vector3d axis = normalized(q.vector);

    float halfCos = cosf(f * angle * 0.5f);
    float halfSin = sinf(f * angle * 0.5f);

    return quat(axis.x * halfSin,
        axis.y * halfSin,
        axis.z * halfSin,
        halfCos
    );
}
