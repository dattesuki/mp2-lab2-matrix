#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> v1(5);
	ASSERT_NO_THROW(v1=v1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> v1(5),v2(5);
	TDynamicMatrix<int>* pv1=&v1;
	TDynamicMatrix<int>* pv2 = &v2;
	EXPECT_NE(pv1,pv2);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> v(5);
	EXPECT_EQ(v.size(), 5);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> v(5);
	v[1][1] = 5;
	EXPECT_EQ(v[1][1],5);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index1)
{
	TDynamicMatrix<int> v(5);
	ASSERT_ANY_THROW(v.at(0).at(-1) = 5);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index2)
{
	TDynamicMatrix<int> v(5);
	ASSERT_ANY_THROW(v.at(-1).at(0) = 5);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index1)
{
	TDynamicMatrix<int> v(5);
	ASSERT_ANY_THROW(v.at(MAX_MATRIX_SIZE).at(0) = 5);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index2)
{
	TDynamicMatrix<int> v(5);
	ASSERT_ANY_THROW(v.at(0).at(MAX_MATRIX_SIZE) = 5);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> v(5);
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> v1(5);
	TDynamicMatrix<int> v2(5);
	ASSERT_NO_THROW(v1 = v2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> v1(5);
	TDynamicMatrix<int> v2(6);
	v1 = v2;
	ASSERT_NO_THROW(v1[5][5]=0);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> v1(5);
	TDynamicMatrix<int> v2(6);
	ASSERT_NO_THROW(v1 = v2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> v1(5);
	TDynamicMatrix<int> v2(5);
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> v(5);
	EXPECT_EQ(v, v);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> v1(5);
	TDynamicMatrix<int> v2(6);
	EXPECT_NE(v1, v2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> v1(5);
	TDynamicMatrix<int> v2(5);
	bool flag = 1;
	for (size_t i = 0; i < 5; ++i) {
		for (size_t j = 0; j < 5; ++j) {
			v2[i][j] = 2 * (v1[i][j] = i);
		}
	}
	for (size_t i = 0; i < 5; ++i) {
		for (size_t j = 0; j < 5; ++j) {
			if ((v1 + v2)[i][j] != (3 * i)) flag = 0;
		}
	}
	EXPECT_EQ(flag, 1);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> v1(5);
	TDynamicMatrix<int> v2(6);
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> v1(5);
	TDynamicMatrix<int> v2(5);
	bool flag = 1;
	for (size_t i = 0; i < 5; ++i) {
		for (size_t j = 0; j < 5; ++j) {
			v2[i][j] = 2 * (v1[i][j] = i);
		}
	}
	for (size_t i = 0; i < 5; ++i) {
		for (size_t j = 0; j < 5; ++j) {
			if ((v2 - v1)[i][j] != (i)) flag = 0;
		}
	}
	EXPECT_EQ(flag, 1);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> v1(5);
	TDynamicMatrix<int> v2(6);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicMatrix, res_mult_matrix)
{
	TDynamicMatrix<int> v1(3);
	TDynamicMatrix<int> v2(3);
	TDynamicMatrix<int> v3(3);
	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			v1[i][j] = v2[i][j] = i * 3 + (j+1); 
		}
	}
	// две матрицы 
	// 1 2 3
	// 4 5 6
	// 7 8 9
	v3[0][0] = 30;
	v3[0][1] = 36;
	v3[0][2] = 42;
	v3[1][0] = 66;
	v3[1][1] = 81;
	v3[1][2] = 96;
	v3[2][0] = 102;
	v3[2][1] = 126;
	v3[2][2] = 150;
	EXPECT_EQ((v1*v2),v3);
}









/*

//тесты для CRS



TEST(TDynamicMatrixCRS, can_create_copied_matrix)
{
	TDynamicMatrixCRS<int> m(5); //используется конструктор для TDynamicMatrix, проверка работы преобразования типа
	ASSERT_NO_THROW(TDynamicMatrixCRS<int> m1(m));
}

TEST(TDynamicMatrixCRS, is_equal_copied_matrix_CRS)
{
	TDynamicMatrixCRS<int> v1(5);
	TDynamicMatrixCRS<int> v2=v1;
	EXPECT_EQ(v1,v2);
}

TEST(TDynamicMatrixCRS, copied_matrix_has_its_own_memory)
{
	TDynamicMatrixCRS<int> v1(5), v2(5);
	TDynamicMatrixCRS<int>* pv1 = &v1;
	TDynamicMatrixCRS<int>* pv2 = &v2;
	EXPECT_NE(pv1, pv2);
}

TEST(TDynamicMatrixCRS, can_get_size)
{
	TDynamicMatrixCRS<int> v(5);
	EXPECT_EQ(v.size(), 5);
}




TEST(TDynamicMatrixCRS, res_mult_matrix1)
{
	TDynamicMatrix<int> v1(3);
	TDynamicMatrix<int> v2(3);
	TDynamicMatrix<int> v3(3);
	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			v1[i][j] = v2[i][j] = i * 3 + (j + 1);
		}
	}
	// две матрицы 
	// 1 2 3
	// 4 5 6
	// 7 8 9
	v3[0][0] = 30;
	v3[0][1] = 36;
	v3[0][2] = 42;
	v3[1][0] = 66;
	v3[1][1] = 81;
	v3[1][2] = 96;
	v3[2][0] = 102;
	v3[2][1] = 126;
	v3[2][2] = 150;
	TDynamicMatrixCRS<int> v1_CRS=v1;
	EXPECT_EQ((v1_CRS * v2), v3);
}


TEST(TDynamicMatrixCRS, res_mult_matrix2)
{
	TDynamicMatrix<int> v1(3);
	TDynamicMatrix<int> v2(3);
	TDynamicMatrix<int> v3(3);
	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			v1[i][j] = v2[i][j] = i * 3 + (j + 1);
		}
	}
	// две матрицы 
	// 1 2 3
	// 4 5 6
	// 7 8 9
	v3[0][0] = 30;
	v3[0][1] = 36;
	v3[0][2] = 42;
	v3[1][0] = 66;
	v3[1][1] = 81;
	v3[1][2] = 96;
	v3[2][0] = 102;
	v3[2][1] = 126;
	v3[2][2] = 150;
	TDynamicMatrixCRS<int> v2_CRS = v2;
	EXPECT_EQ((v1 * v2_CRS), v3);
}*/
