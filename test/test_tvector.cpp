#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	int a[5] = { 1,2,3,4,5 };
	TDynamicVector<int> v1(a, 5);
	ASSERT_NO_THROW(v1 = v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(5), v2(5);
	TDynamicVector<int>* pv1 = &v1;
	TDynamicVector<int>* pv2 = &v2;
	EXPECT_NE(pv1, pv2);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(10);

	ASSERT_ANY_THROW((v.at(-1) = 5));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(10);

	ASSERT_ANY_THROW((v.at(MAX_VECTOR_SIZE) = 5));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<char> v(10);
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<char> v1(10);
	TDynamicVector<char> v2(10);
	ASSERT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(1);
	TDynamicVector<int> v2(10);
	v1 = v2;
	ASSERT_NO_THROW(v1[2]=5);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<char> v1(10);
	TDynamicVector<char> v2(15);
	ASSERT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<bool> v1(10);
	TDynamicVector<bool> v2(10);
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<bool> v(10);
	EXPECT_EQ(v, v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(6);
	EXPECT_NE(v1,v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(5);
	bool flag = 1;
	for (size_t i = 0; i < 5; ++i) if ((v + 5)[i] != 5) flag = 0;
	EXPECT_EQ(flag, 1);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(5);
	bool flag = 1;
	for (size_t i = 0; i < 5; ++i) if ((v - 5)[i] != -5) flag = 0;
	EXPECT_EQ(flag, 1);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(5);
	bool flag = 1;
	for (size_t i = 0; i < 5; ++i) v[i] = 5;
	for (size_t i = 0; i < 5; ++i) if ((v * 2)[i] != 10) flag = 0;
	EXPECT_EQ(flag, 1);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	bool flag = 1;
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);
	for (size_t i = 0; i < 5; ++i) v1[i] = v2[i] = i;
	for (size_t i = 0; i < 5; ++i) if ((v1 + v2)[i] != (2 * i)) flag = 0;
	EXPECT_EQ(flag, 1);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(6);
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	bool flag = 1;
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);
	for (size_t i = 0; i < 5; ++i) v1[i] = v2[i] = i;
	for (size_t i = 0; i < 5; ++i) if ((v1 - v2)[i] != 0) flag = 0;
	EXPECT_EQ(flag, 1);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(6);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	bool flag = 1;
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);
	for (size_t i = 0; i < 5; ++i) v1[i] = v2[i] = 1;
	EXPECT_EQ(5, (v1 * v2));
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(6);
	ASSERT_ANY_THROW(v1 * v2);
}

