#pragma once

#include "vector4d.h"
#include "vector3d.h"

#define MATRIX4_EPSILON 0.000001f

#define M4D(v1Row, v2Col) \
    M1.V[0 * 4 + v1Row] * M2.V[v2Col * 4 + 0 ] + \
    M1.V[1 * 4 + v1Row] * M2.V[v2Col * 4 + 1 ] + \
    M1.V[2 * 4 + v1Row] * M2.V[v2Col * 4 + 2 ] + \
    M1.V[3 * 4 + v1Row] * M2.V[v2Col * 4 + 3 ]

#define M4V4D(M1Row, x, y, z, w) \
    x * M1.V[0 * 4 + M1Row] + \
    y * M1.V[1 * 4 + M1Row] + \
    z * M1.V[2 * 4 + M1Row] + \
    w * M1.V[3 * 4 + M1Row]

#define M4SWAP(x,y) \
    { float t = x; x = y ; y = t; }

#define M4_3X3MINOR(x, c0, c1, c2, r0, r1, r2) \
    (x[c0*4+r0] * (x[c1*4+r1] * x[c2*4+r2]  - x[c1*4+r2] * \
     x[c2*4+r1])- x[c1*4+r0]  * (x[c0*4+r1] * x[c2*4+r2] - \
     x[c0*4+r2] * x[c2*4+r1]) + x[c2*4+r0]  * (x[c0*4+r1] * \
     x[c1*4+r2] - x[c0*4+r2]  * x[c1*4+r1] ))

struct matrix4
{
    union
    {
        float V[16];
        struct
        {
            fvector4d right;
            fvector4d up;
            fvector4d forward;
            fvector4d position;
        };
        struct
        {
            //          row1    row2      row3     row4
            /*col1*/ float xx; float xy; float xz; float xw;
            /*col2*/ float yx; float yy; float yz; float yw;
            /*col3*/ float zx; float zy; float zz; float zw;
            /*col4*/ float tx; float ty; float tz; float tw;
        };
        // Column-row notation
        struct
        {
            float c0r0; float c0r1; float c0r2; float c0r3;
            float c1r0; float c1r1; float c1r2; float c1r3;
            float c2r0; float c2r1; float c2r2; float c2r3;
            float c3r0; float c3r1; float c3r2; float c3r3;
        };
        // row-column notation
        struct
        {
            float r0c0; float r0c1; float r0c2; float r0c3;
            float r1c0; float r1c1; float r1c2; float r1c3;
            float r2c0; float r2c1; float r2c2; float r2c3;
            float r3c0; float r3c1; float r3c2; float r3c3;
        };
    };
    // Create identity matrix
    inline matrix4() :
        xx(1), xy(0), xz(0), xw(0),
        yx(0), yy(1), yz(0), yw(0),
        zx(0), zy(0), zz(1), zw(0),
        tx(0), ty(0), tz(0), tw(0) {}
    // Create from float array
    inline matrix4(float* fv) :
        xx(fv[0]),  xy(fv[1]),  xz(fv[2]),  xw(fv[3]),
        yx(fv[4]),  yy(fv[5]),  yz(fv[6]),  yw(fv[7]),
        zx(fv[8]),  zy(fv[9]),  zz(fv[10]), zw(fv[11]),
        tx(fv[12]), ty(fv[13]), tz(fv[14]), tw(fv[15]) {}
    // Create from specifying matrix independantly
    inline matrix4(
        float In00, float In01, float In02, float In03,
        float In10, float In11, float In12, float In13,
        float In20, float In21, float In22, float In23,
        float In30, float In31, float In32, float In33
    ) :
        xx(In00), xy(In01), xz(In02), xw(In03),
        yx(In10), yy(In11), yz(In12), yw(In13),
        zx(In20), zy(In21), zz(In22), zw(In23),
        tx(In30), ty(In31), tz(In32), tw(In33) {}
};

bool operator==(const matrix4& M1, const matrix4& M2);
matrix4 operator+(const matrix4& M1, const matrix4& M2);
matrix4 operator*(const matrix4& M1, float f);
matrix4 operator*(const matrix4& M1, const matrix4& M2);
fvector4d operator*(const matrix4& M1, const fvector4d& V);
vector3d transform_vector(const matrix4& M1, const vector3d& V);
vector3d transform_point(const matrix4& M1, const vector3d& V);
vector3d transform_point(const matrix4& M1, const vector3d& V, float& w);
void transpose(matrix4& M);
matrix4 transposed(const matrix4& M1);
float determinant(const matrix4& M1);
matrix4 adjugate(const matrix4& M1);
matrix4 inverse(const matrix4& M1);
void inversed(matrix4& M1);

matrix4 frustum(float l, float  r, float b, float t, float n, float f);
matrix4 perspective(float fov, float aspect, float n, float f);
matrix4 orthographic(float l, float r, float b, float t, float n, float f);
matrix4 look_at(const vector3d& Position, const vector3d& Target, const vector3d& Up);