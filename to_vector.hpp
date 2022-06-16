// Range adaptors to create std::vector.
// ranges_util::to_list		Range to std::vector by estimated type.
// ranges_util::to_list_as	Range to std::vector by specified type.する。

#pragma once

#include <ranges>

namespace ranges_util
{
	class to_vector_fn
	{
	public:
		to_vector_fn() = default;

		template <std::ranges::input_range Range>
			requires std::same_as<std::ranges::iterator_t<Range>, std::ranges::sentinel_t<Range>>
		constexpr auto operator()(Range&& r) const {
			return std::vector<std::ranges::range_value_t<Range>>(std::ranges::begin(r), std::ranges::end(r));
		}

		template <std::ranges::input_range Range>
		constexpr auto operator()(Range&& r) const {
			std::vector<std::ranges::range_value_t<Range>> v;
			std::ranges::copy(std::ranges::begin(r), std::ranges::end(r), std::back_inserter(v));
			return std::move(v);
		}


		template <std::ranges::input_range Range>
		constexpr friend auto operator |(Range&& r, to_vector_fn f) {
			return f(r);
		}
	};
	const to_vector_fn to_vector;

	template <typename ElementT>
	class to_vector_as_fn
	{
	public:
		using element_type = ElementT;
		to_vector_as_fn() = default;

		template <std::ranges::input_range Range>
			requires std::same_as<std::ranges::iterator_t<Range>, std::ranges::sentinel_t<Range>>
		constexpr auto operator()(Range&& r) const {
			return std::vector<element_type>(std::ranges::begin(r), std::ranges::end(r));
		}

		template <std::ranges::input_range Range>
		constexpr auto operator()(Range&& r) const {
			std::vector<element_type> v;
			std::ranges::copy(std::ranges::begin(r), std::ranges::end(r), std::back_inserter(v));
			return std::move(v);
		}


		template <typename ElementT, std::ranges::input_range Range>
		constexpr friend auto operator |(Range&& r, to_vector_as_fn<ElementT> f) {
			return f(r);
		}
	};
	template <typename ElementT>
	const to_vector_as_fn<ElementT> to_vector_as;
}
