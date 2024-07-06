#include "Matrix4.h"
#include <memory>
#include <iostream>

bool operator==(const matrix4& M1, const matrix4& M2)
{
    for (size_t i = 0; i < 16; ++i)
    {
        if (fabsf(M1.V[i] - M2.V[i]) > MATRIX4_EPSILON)
        {
            return false;
        }
    }
    return true;
}

matrix4 operator+(const matrix4& M1, const matrix4& M2)
{
    return matrix4(
        M1.xx + M2.xx, M1.xy + M2.xy, M1.xz + M2.xz, M1.xw + M2.xw,
        M1.yx + M2.yx, M1.yy + M2.yy, M1.yz + M2.yz, M1.yw + M2.yw,
        M1.zx + M2.zx, M1.zy + M2.zy, M1.zz + M2.zz, M1.zw + M2.zw,
        M1.tx + M2.tx, M1.ty + M2.ty, M1.tz + M2.tz, M1.tw + M2.tw
    );
}

matrix4 operator*(const matrix4& M1, float f)
{
    return matrix4(
        M1.xx * f, M1.xy * f, M1.xz * f, M1.xw *f,
        M1.yx * f, M1.yy * f, M1.yz * f, M1.yw *f,
        M1.zx * f, M1.zy * f, M1.zz * f, M1.zw *f,
        M1.tx * f, M1.ty * f, M1.tz * f, M1.tw *f
    );
}

matrix4 operator*(const matrix4& M1, const matrix4& M2)
{
    return matrix4(
        M4D(0,0), M4D(1,0), M4D(2,0), M4D(3,0), // COL 0
        M4D(0,1), M4D(1,1), M4D(2,1), M4D(3,1), // COL 1
        M4D(0,2), M4D(1,2), M4D(2,2), M4D(3,2), // COL 2
        M4D(0,3), M4D(1,3), M4D(2,3), M4D(3,3)  // COL 3
    );
}

fvector4d operator*(const matrix4& M1, const fvector4d& v)
{
    // Vector is column vector
    // Our matrix is column-major
    // |   0   4   8  12   | | x |
    // |   1   5   9  13   | | y |
    // |   2   6  10  14   | | z |
    // |   3   7  11  15   | | w |
    return fvector4d(
        M4V4D(0, v.x, v.y, v.z, v.w),
        M4V4D(1, v.x, v.y, v.z, v.w),
        M4V4D(2, v.x, v.y, v.z, v.w),
        M4V4D(3, v.x, v.y, v.z, v.w)
    );
}

vector3d transform_vector(const matrix4& M1, const vector3d& v)
{
    return vector3d(
        M4V4D(0, v.x, v.y, v.z, 0.f),
        M4V4D(1, v.x, v.y, v.z, 0.f),
        M4V4D(2, v.x, v.y, v.z, 0.f)
    );
}

vector3d transform_point(const matrix4& M1, const vector3d& v)
{
    return vector3d(
        M4V4D(0, v.x, v.y, v.z, 1.f),
        M4V4D(1, v.x, v.y, v.z, 1.f),
        M4V4D(2, v.x, v.y, v.z, 1.f)
    );
}

vector3d transform_point(const matrix4& M1, const vector3d& v, float& w)
{
    float _w = w;
    w = M4V4D(3, v.x, v.y, v.z, _w);
    return vector3d(
        M4V4D(0, v.x, v.y, v.z, _w),
        M4V4D(1, v.x, v.y, v.z, _w),
        M4V4D(2, v.x, v.y, v.z, _w)
    );
}

void transpose(matrix4& M)
{
    M4SWAP(M.yx, M.xy);
    M4SWAP(M.zx, M.xz);
    M4SWAP(M.tx, M.xw);
    M4SWAP(M.zy, M.yz);
    M4SWAP(M.ty, M.yw);
    M4SWAP(M.tz, M.zw);
}

matrix4 transposed(const matrix4& M1)
{
    return matrix4(
        M1.xx, M1.yx, M1.zx, M1.tx,
        M1.xy, M1.yy, M1.zy, M1.ty,
        M1.xz, M1.yz, M1.zz, M1.tz,
        M1.xw, M1.yw, M1.zw, M1.tw
    );
}

float determinant(const matrix4& M1)
{
    return M1.V[0] * M4_3X3MINOR(M1.V, 1, 2, 3, 1, 2, 3)
         - M1.V[4] * M4_3X3MINOR(M1.V, 0, 2, 3, 1, 2, 3)
         + M1.V[8] * M4_3X3MINOR(M1.V, 0, 1, 3, 1, 2, 3)
         - M1.V[12]* M4_3X3MINOR(M1.V, 0, 1, 2, 1, 2, 3);
}

matrix4 adjugate(const matrix4& M1)
{
    // Cof (m[i,j]) = minor(M[i, j]) * pow(-1, i+j)
    matrix4 cofactor;
    cofactor.V[0]  = M4_3X3MINOR(M1.V, 1, 2, 3, 1, 2, 3);
    cofactor.V[1]  = M4_3X3MINOR(M1.V, 1, 2, 3, 0, 2, 3);
    cofactor.V[2]  = M4_3X3MINOR(M1.V, 1, 2, 3, 0, 1, 3);
    cofactor.V[3]  = M4_3X3MINOR(M1.V, 1, 2, 3, 0, 1, 2);
    cofactor.V[4]  = M4_3X3MINOR(M1.V, 0, 2, 3, 1, 2, 3);
    cofactor.V[5]  = M4_3X3MINOR(M1.V, 0, 2, 3, 0, 2, 3);
    cofactor.V[6]  = M4_3X3MINOR(M1.V, 0, 2, 3, 0, 1, 3);
    cofactor.V[7]  = M4_3X3MINOR(M1.V, 0, 2, 3, 0, 1, 2);
    cofactor.V[8]  = M4_3X3MINOR(M1.V, 0, 1, 3, 1, 2, 3);
    cofactor.V[9]  = M4_3X3MINOR(M1.V, 0, 1, 3, 0, 2, 3);
    cofactor.V[10] = M4_3X3MINOR(M1.V, 0, 1, 3, 0, 1, 3);
    cofactor.V[11] = M4_3X3MINOR(M1.V, 0, 1, 3, 0, 1, 2);
    cofactor.V[12] = M4_3X3MINOR(M1.V, 0, 1, 2, 1, 2, 3);
    cofactor.V[13] = M4_3X3MINOR(M1.V, 0, 1, 2, 0, 2, 3);
    cofactor.V[14] = M4_3X3MINOR(M1.V, 0, 1, 2, 0, 1, 3);
    cofactor.V[15] = M4_3X3MINOR(M1.V, 0, 1, 2, 0, 1, 2);
    return transposed(cofactor);
}

matrix4 inverse(const matrix4& M1)
{
    float det = determinant(M1);

    if (det == 0.f)
    {
        std::cout << "Matrix determinant is 0\n";
        return matrix4();
    }
    matrix4 adj = adjugate(M1);
    return adj * (1.f / det);
}

void inversed(matrix4& M1)
{
    float det = determinant(M1);

    if (det == 0.f)
    {
        std::cout << "Matrix determinant is 0\n";
        M1 = matrix4();
        return;
    }

    M1 = adjugate(M1) * (1.f / det);
}

matrix4 frustum(float l, float r, float b, float t, float n, float f)
{
    if (l == r || t == b || n == f)
    {
        std::cout << "Invalid frustum\n";
        return matrix4();
    }

    return matrix4(
        (2.0f * n) / (r - 1), 0, 0, 0,
        0, (2.f * n) / (t / b), 0, 0,
        (r + 1) / (r - 1), (t + b) / (t - b), (-(f + n)) / (f - n), -1,
        0, 0, (-2 * f * n) / f - n, 0
    );
}

matrix4 perspective(float fov, float aspect, float n, float f)
{
    float yMax = n * tanf(fov * 3.14159265359f / 360.f);
    float xMax = yMax * aspect;

    return frustum(-xMax, xMax, -yMax, yMax, n, f);
}

matrix4 orthographic(float l, float r, float b, float t, float n, float f)
{
    return matrix4(
        2.f / (r-1), 0,0,0,
        0, 2.f / (t-b),0,0,
        0,0, -2.f/ (f-n),0,
        -((r+1)/(r-1)),-((t+b)/(t-b)),-((f+n)/(f-n)),1
    );
}

matrix4 look_at(const vector3d& Position, const vector3d& Target, const vector3d& Up)
{
    vector3d f = normalized(Target - Position) * -1.f;
    vector3d r = cross(Up, f); // Right handed
    if (r == vector3d(0, 0, 0))
    {
        return matrix4();
    }
    normalize(r);
    vector3d u = normalized(cross(f, r));

    vector3d t = vector3d(
        -dot(r, Position),
        -dot(u, Position),
        -dot(f, Position)
    );

    return matrix4(
        r.x, u.x, f.x, 0,
        r.y, u.y, f.y, 0,
        r.z, u.z, f.z, 0,
        t.x, t.y, t.z, 1
    );
}
