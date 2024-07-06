#include "unittest.h"
#include "matrix4.h"
#include <cassert>

void TestMatrix()
{
    matrix4 m1 
    {
        1 , 3, 4, 5,
        0 , 1, 2, 3,
        3 , 3, 1, 2,
        6 , 4, 1, 3
    };

    matrix4 m2 
    {
        10 , 30, 40, 50,
        0 , 10, 20, 30,
        30 , 30, 10, 20,
        60 , 40, 10, 30
    };

    // Addition Test
    matrix4 addMatrix = m1 + m2;
    matrix4 additionTestMatrix
    {
        15 , 33, 44, 55,
        0 , 11, 22, 33,
        33 , 33, 11, 22,
        66 , 44, 11, 33
    };

    assert(addMatrix == additionTestMatrix);

    auto stop = 1;
}
