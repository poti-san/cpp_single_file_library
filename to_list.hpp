// Rangesのパイプライン演算子で使用できるstd::listへの変換を提供します。
// ranges_util::to_list		型を推測してstd::listを作成する。
// ranges_util::to_list_as	型を指定してstd::listを作成する。

#pragma once

#include <ranges>

namespace ranges_util
{
	class to_list_fn
	{
	public:
		to_list_fn() = default;

		template <std::ranges::input_range Range>
			requires std::same_as<std::ranges::iterator_t<Range>, std::ranges::sentinel_t<Range>>
		constexpr auto operator()(Range&& r) const {
			return std::list<std::ranges::range_value_t<Range>>(
				std::ranges::begin(r), std::ranges::end(r));
		}

		template <std::ranges::input_range Range>
		constexpr auto operator()(Range&& r) const {
			std::list<std::ranges::range_value_t<Range>> l;
			std::ranges::copy(std::ranges::begin(r), std::ranges::end(r), std::back_inserter(l));
			return std::move(l);
		}

		template <std::ranges::input_range Range>
		constexpr friend auto operator |(Range&& r, to_list_fn f) {
			return f(r);
		}
	};
	const to_list_fn to_list;

	template <typename ElementT>
	class to_list_as_fn
	{
	public:
		using element_type = ElementT;
		to_list_as_fn() = default;

		template <std::ranges::input_range Range>
			requires std::same_as<std::ranges::iterator_t<Range>, std::ranges::sentinel_t<Range>>
		constexpr auto operator()(Range&& r) const {
			return std::list<element_type>(std::ranges::begin(r), std::ranges::end(r));
		}

		template <std::ranges::input_range Range>
		constexpr auto operator()(Range&& r) const {
			std::list<element_type> l;
			std::ranges::copy(std::ranges::begin(r), std::ranges::end(r), std::back_inserter(l));
			return std::move(l);
		}


		template <typename ElementT, std::ranges::input_range Range>
		constexpr friend auto operator |(Range&& r, to_list_as_fn<ElementT> f) {
			return f(r);
		}
	};
	template <typename ElementT>
	const to_list_as_fn<ElementT> to_list_as;
}
