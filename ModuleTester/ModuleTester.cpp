#include "pch.h"
#include "CppUnitTest.h"

#include <cassert>
//#include "matrix4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixTester
{
	TEST_CLASS(MatrixTestClass)
	{
	public:
        // ----------------------- Attribute Definer ----------------------
        BEGIN_TEST_METHOD_ATTRIBUTE(CheckAddFunctionInMatrix)
            TEST_OWNER(L"Omrum Cetin")
            TEST_PRIORITY(1)
        END_TEST_METHOD_ATTRIBUTE()

        //----------------------- Attribute Definer ----------------------
        TEST_METHOD(CheckAddFunctionInMatrix)
        {
            /*matrix4 tempMatrix
            {
                10, 30, 40, 50,
                0 , 10, 20, 30,
                30, 30, 10, 20,
                60, 40, 10, 30
            };


             Addition Test
            matrix4 ResultMatrix = SourceMatrix + tempMatrix;
            matrix4 additionTestMatrix
            {
                11, 33, 44, 55,
                0 , 11, 22, 33,
                33, 33, 11, 22,
                66, 44, 11, 33
            };

            Assert::IsTrue(ResultMatrix == additionTestMatrix);*/
		}
  //      TEST_METHOD(CheckScaleMatrix)
  //      {
  //          matrix4 expectedMatrix
  //          {
  //              2 , 6, 8, 10,
  //              0 , 2, 4, 6,
  //              6 , 6, 2, 4,
  //              12, 8, 2, 6
  //          };

  //          // Addition Test
  //          matrix4 resultMatrix = SourceMatrix * 2;

  //          Assert::IsTrue(resultMatrix == expectedMatrix);
  //      }
  //      TEST_METHOD(CheckTranspose)
  //      {
  //          matrix4 ResultMatrix
  //          {
  //              1, 0, 3, 6,
  //              3, 1, 3, 4,
  //              4, 2, 1, 1,
  //              5, 3, 2, 3
  //          };

  //          // Transpose check
  //          transpose(SourceMatrix);

  //          Assert::IsTrue(SourceMatrix == ResultMatrix);
  //      }
  //      TEST_METHOD(CheckTransposed)
  //      {
  //          matrix4 TransposedSource
  //          {
  //              1, 0, 3, 6,
  //              3, 1, 3, 4,
  //              4, 2, 1, 1,
  //              5, 3, 2, 3
  //          };

  //          // Transpose check
  //          matrix4 tempTransposed = transposed(SourceMatrix);
  //          Assert::IsTrue(TransposedSource == tempTransposed);
  //      }
  //      //TEST_METHOD(CheckVector4DTransformViaMatrix)
  //      //{
  //      //    fvector4d expectedResult { 34, 30, 15, 29 };
  //      //    fvector4d v{ 1, 2, 3, 4};
  //      //    
  //      //    fvector4d result = SourceMatrix * v;
  //      //    Assert::IsTrue(result == expectedResult);
  //      //}
  //      //TEST_METHOD(CheckVector3DTransformViaMatrix)
  //      //{
  //      //    vector3d expectedResult{ 34, 30, 15};
  //      //    vector3d v{ 1, 2, 3};

  //      //    vector3d result = transform_vector(SourceMatrix, v);
  //      //    //Assert::IsTrue(result == expectedResult);
  //      //}
    private:
        // column major matrix
        /*matrix4 SourceMatrix
        {
            1, 3, 4, 5,
            0, 1, 2, 3,
            3, 3, 1, 2,
            6, 4, 1, 3
        };*/
    };
}