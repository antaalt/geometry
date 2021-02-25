#pragma once 

#include <type_traits>

namespace geometry {

template<typename T> using IsFloatingPoint = std::enable_if_t<std::is_floating_point_v<T>>;
template<typename T> using IsInteger = std::enable_if_t<std::is_integral_v<T>>;

};