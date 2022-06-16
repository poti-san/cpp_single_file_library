#include <array>
#include <list>

#include "to_list.hpp"

int main()
{
	auto l2{ std::views::iota(0, 5) | ranges_util::to_list };
	// { 0, 1, 2, 3, 4 }

	auto l3{ std::array{0, 1, 2, 3, 4} | ranges_util::to_list };
	// { 0, 1, 2, 3, 4 }

	auto l4{ std::views::iota(0, 5) | ranges_util::to_list_as<double> };
	// { 0.0, 1.0, 2.0, 3.0, 4.0 }

	return 0;
}
