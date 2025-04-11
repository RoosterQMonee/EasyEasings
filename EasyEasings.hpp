#pragma once

/*
* All easing functions are from https://easings.net :)
*/

#include <type_traits>
#include <concepts>
#include <cmath>

namespace EasyEasings {
    constexpr float PI = 3.1415926;

    template<typename T>
    concept Arithmetic = std::is_arithmetic_v<T>;

    template<typename T>
    using easing_return_t = std::conditional_t<
        std::is_integral_v<T>,
        double, // promote integers to double
        T       // preserve float/double types
    >;

    // Sine

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInSine(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(1 - cos((x * PI) / 2));
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseOutSine(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(sin((x * PI) / 2));
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInOutSine(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(-(cos(PI * x) - 1) / 2);
    }

    // Quad

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInQuad(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(x * x);
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseOutQuad(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(1 - (1 - x) * (1 - x));
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInOutQuad(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2);
    }

    // Cubic

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInCubic(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(x * x * x);
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseOutCubic(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(1 - pow(1 - x, 3));
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInOutCubic(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2);
    }

    // Quart

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInQuart(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(x * x * x * x);
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseOutQuart(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(1 - pow(1 - x, 4));
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInOutQuart(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(x < 0.5 ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2);
    }

    // Quint

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInQuint(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(x * x * x * x * x);
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseOutQuint(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(1 - pow(1 - x, 5));
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInOutQuint(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(x < 0.5
            ? 16 * x * x * x * x * x
            : 1 - pow(-2 * x + 2, 5) / 2);
    }

    // Expo

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInExpo(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(x == 0 ? 0 : pow(2, 10 * x - 10));
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseOutExpo(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(x == 1 ? 1 : 1 - pow(2, -10 * x));
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInOutExpo(T x) {
        using ReturnT = easing_return_t<T>;
        if (x == 0) return ReturnT{ 0 };
        if (x == 1) return ReturnT{ 1 };
        return static_cast<ReturnT>(x < 0.5
            ? pow(2, 20 * x - 10) / 2
            : (2 - pow(2, -20 * x + 10)) / 2);
    }

    // Circ

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInCirc(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(1 - sqrt(1 - x * x));
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseOutCirc(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(sqrt(1 - pow(x - 1, 2)));
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInOutCirc(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(x < 0.5
            ? (1 - sqrt(1 - 4 * x * x)) / 2
            : (sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2);
    }

    // Back

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInBack(T x) {
        using ReturnT = easing_return_t<T>;
        constexpr ReturnT c1 = 1.70158;
        constexpr ReturnT c3 = c1 + 1;
        return static_cast<ReturnT>(c3 * x * x * x - c1 * x * x);
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseOutBack(T x) {
        using ReturnT = easing_return_t<T>;
        constexpr ReturnT c1 = 1.70158;
        constexpr ReturnT c3 = c1 + 1;
        return static_cast<ReturnT>(1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2));
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInOutBack(T x) {
        using ReturnT = easing_return_t<T>;
        constexpr ReturnT c1 = 1.70158;
        constexpr ReturnT c2 = c1 * 1.525;
        return static_cast<ReturnT>(x < 0.5
            ? (pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
            : (pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2);
    }

    // Elastic

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInElastic(T x) {
        using ReturnT = easing_return_t<T>;
        if (x == 0) return ReturnT{ 0 };
        if (x == 1) return ReturnT{ 1 };
        constexpr ReturnT c4 = (2 * PI) / 3;
        return static_cast<ReturnT>(-pow(2, 10 * x - 10) * sin((x * 10 - 10.75) * c4));
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseOutElastic(T x) {
        using ReturnT = easing_return_t<T>;
        if (x == 0) return ReturnT{ 0 };
        if (x == 1) return ReturnT{ 1 };
        constexpr ReturnT c4 = (2 * PI) / 3;
        return static_cast<ReturnT>(pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1);
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInOutElastic(T x) {
        using ReturnT = easing_return_t<T>;
        constexpr ReturnT c5 = (2 * PI) / 4.5;
        if (x == 0) return ReturnT{ 0 };
        if (x == 1) return ReturnT{ 1 };
        return static_cast<ReturnT>(x < 0.5
            ? -(pow(2, 20 * x - 10) * sin((20 * x - 11.125) * c5)) / 2
            : (pow(2, -20 * x + 10) * sin((20 * x - 11.125) * c5)) / 2 + 1);
    }

    // Bounce helper

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseOutBounce(T x) {
        using ReturnT = easing_return_t<T>;
        constexpr ReturnT n1 = 7.5625;
        constexpr ReturnT d1 = 2.75;
        if (x < 1 / d1)
            return static_cast<ReturnT>(n1 * x * x);
        else if (x < 2 / d1)
            return static_cast<ReturnT>(n1 * (x -= 1.5 / d1) * x + 0.75);
        else if (x < 2.5 / d1)
            return static_cast<ReturnT>(n1 * (x -= 2.25 / d1) * x + 0.9375);
        else
            return static_cast<ReturnT>(n1 * (x -= 2.625 / d1) * x + 0.984375);
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInBounce(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(1 - EaseOutBounce(ReturnT{ 1 } - x));
    }

    template<Arithmetic T>
    constexpr easing_return_t<T> EaseInOutBounce(T x) {
        using ReturnT = easing_return_t<T>;
        return static_cast<ReturnT>(x < 0.5
            ? (1 - EaseOutBounce(ReturnT{ 1 } - 2 * x)) / 2
            : (1 + EaseOutBounce(2 * x - 1)) / 2);
    }
}; // namespace EasyEasings