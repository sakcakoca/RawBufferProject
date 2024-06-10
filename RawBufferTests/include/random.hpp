#pragma once

#include <concepts>
#include <limits>
#include <random>
#include <type_traits>
#include <cstddef>
#include <utility>

// Custom concept to check if a type is std::byte, char, or unsigned char
template<typename T>
concept ByteOrCharType = std::same_as<T, std::byte> || std::same_as<T, char> || std::same_as<T, unsigned char>;

// Custom concept to check for integral types excluding char, unsigned char, std::byte, etc.
template<typename T>
concept IntegralExcludingCharAndByteType = std::integral<T> && !ByteOrCharType<T>;

struct Random
{

    /**
     * @brief Generate a random integer number in a [from; to] range
     *        by std::uniform_int_distribution
     * @tparam T The type of the integer
     * @param from The first limit number of a random range
     * @param to The second limit number of a random range
     * @return A random integer number in a [from; to] range
     * @note Allow both: 'from' <= 'to' and 'from' >= 'to'
     * @note Prevent implicit type conversion
     */
    template <IntegralExcludingCharAndByteType T>
    static T get(T from = std::numeric_limits<T>::min(),
        T to = std::numeric_limits<T>::max())
    {
        if (to < from) { // to should be smaller than from
            std::swap(to, from);
        }

        static std::random_device rd;
        static std::mt19937 engine_instance(rd());

        using IntegerDist = std::uniform_int_distribution<T>;
        return static_cast<T>(IntegerDist{from, to}(engine_instance));
    }

    /**
     * @brief Generate a random value for std::byte, char, or unsigned char in a [from; to] range
     *        by std::uniform_int_distribution
     * @tparam T The type of the value (std::byte, char, or unsigned char)
     * @param from The first limit number of a random range, 0 by default
     * @param to The second limit number of a random range, 255 by default
     * @return A random value in a [from; to] range
     * @note Allow both: 'from' <= 'to' and 'from' >= 'to'
     * @note Prevent implicit type conversion
     */
    template <ByteOrCharType T>
    static T get(T from = T{std::numeric_limits<T>::min( )},
                 T to = T{std::numeric_limits<T>::max( )})
    {
        using short_t = std::conditional_t<std::is_signed_v<T>, short, unsigned short>;
        auto from_value = static_cast<short_t>(from);
        auto to_value = static_cast<short_t>(to);

        return static_cast<T>(get<short_t>(from_value, to_value));
    }
};