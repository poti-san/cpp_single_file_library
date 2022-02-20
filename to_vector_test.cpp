#include <array>
#include <vector>

#include "to_vector.hpp"

int main()
{
	// std::views::iota�̎d�l�ɂ�薳�����[�v�ɂȂ�܂��B
	// auto v1{ std::views::iota(0) | ranges_util::to_vector };

	auto v2{ std::views::iota(0, 5) | ranges_util::to_vector };
	// { 0, 1, 2, 3, 4 }

	auto v3{ std::array{0, 1, 2, 3, 4} | ranges_util::to_vector };
	// { 0, 1, 2, 3, 4 }

	auto v4{ std::views::iota(0, 5) | ranges_util::to_vector_as<double> };
	// { 0.0, 1.0, 2.0, 3.0, 4.0 }

	return 0;
}