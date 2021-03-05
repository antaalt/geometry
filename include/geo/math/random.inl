#pragma once

#include <random>
#include <chrono>

namespace geometry {

template <typename T>
inline T random() {

	if constexpr (std::is_floating_point<T>::value)
		return random<T>(static_cast<T>(0), static_cast<T>(1));
	else if constexpr (std::is_integral<T>::value)
		return random<T>(static_cast<T>(0), std::numeric_limits<T>::max());
	else
		static_assert(false, "Invalid type");
}

template <typename T>
inline T random(T range) {
	return random(-range, range);
}

template <typename T>
inline T random(T start, T end) {
	static thread_local std::mt19937 g(std::chrono::system_clock::now().time_since_epoch().count());
	if constexpr (std::is_floating_point<T>::value)
	{
		std::uniform_real_distribution<T> d(start, end);
		return d(g);
	}
	else if constexpr (std::is_integral<T>::value)
	{
		std::uniform_int_distribution<T> d(start, end);
		return d(g);
	}
	else
	{
		static_assert(false, "Invalid type");
	}
}

}