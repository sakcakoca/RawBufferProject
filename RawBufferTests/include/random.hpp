#pragma once

#include <concepts>
#include <limits>
#include <random>
#include <type_traits>
#include <cstddef>
#include <utility>

// Custom concept to check if a type is std::byte
template<typename T>
concept ByteType = std::same_as<T, std::byte>;

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
    template <typename T>
    requires std::integral<T>
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
     * @brief Generate a random std::byte number in a [from; to] range
     *        by std::uniform_int_distribution
     * @param from The first limit number of a random range (default is std::byte{0})
     * @param to The second limit number of a random range (default is std::byte{255})
     * @return A random std::byte number in a [from; to] range
     * @note Allow both: 'from' <= 'to' and 'from' >= 'to'
     * @note Prevent implicit type conversion
     */
    template <ByteType T = std::byte>
    static T get(T from = T{std::numeric_limits<std::underlying_type_t<T>>::min()},
                 T to = T{std::numeric_limits<std::underlying_type_t<T>>::max()})
    {
        using UnderlyingType = std::underlying_type_t<T>;
        auto from_value = static_cast<UnderlyingType>(from);
        auto to_value = static_cast<UnderlyingType>(to);

        return static_cast<T>(get<UnderlyingType>(from_value, to_value));
    }
};