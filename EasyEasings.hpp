#ifndef EASING_HPP_INCLUDED
#define EASING_HPP_INCLUDED

#include <cmath>
#include <concepts>
#include <type_traits>
#include <limits>
#include <utility>
#include <numbers>

namespace easing {

    /**
     * @brief Arithmetic concept: any built-in arithmetic type
     */
    template <typename T>
    concept arithmetic = std::is_arithmetic_v<T>;

    /**
     * @brief Normalize input type to floating point for internal math.
     *
     * Converting to long double for intermediate reduces precision issues.
     */
    template <arithmetic T>
    using calc_t = long double;

    /**
     * @brief Clamp a value to [0,1]. Not used to silently mask errors but helps numerical stability.
     */
    template <arithmetic T>
    inline constexpr T clamp01(T x) noexcept {
        if (x <= T(0)) return T(0);
        if (x >= T(1)) return T(1);
        return x;
    }

    /**
     * @brief Return whether value is (nearly) zero for the calc_t precision.
     */
    inline constexpr bool almost_zero(long double x) noexcept {
        long double ax = x < 0 ? -x : x;
        return ax <= std::numeric_limits<long double>::epsilon();
    }

    /**
     * @brief Identity (linear) easing.
     */
    template <arithmetic T>
    inline constexpr T linear(T t) noexcept {
        using CT = calc_t<T>;
        return static_cast<T>(static_cast<CT>(t));
    }

    // create in/out/in_out wrappers for polynomial base functions
    template <arithmetic T, typename F>
    inline constexpr T ease_in_impl(T t, F&& f) noexcept {
        using CT = calc_t<T>;
        CT ct = static_cast<CT>(t);
        return static_cast<T>(f(ct));
    }

    template <arithmetic T, typename F>
    inline constexpr T ease_out_impl(T t, F&& f) noexcept {
        using CT = calc_t<T>;
        CT ct = static_cast<CT>(t);
        return static_cast<T>(1 - f(1 - ct));
    }

    template <arithmetic T, typename F>
    inline constexpr T ease_in_out_impl(T t, F&& f) noexcept {
        using CT = calc_t<T>;
        CT ct = static_cast<CT>(t);
        if (ct < CT(0.5L)) {
            return static_cast<T>(CT(0.5L) * f(ct * 2));
        }
        else {
            return static_cast<T>(CT(1.0L) - CT(0.5L) * f((CT(1.0L) - ct) * 2));
        }
    }

    // x^n for small integer n; faster than pow() and constexpr-friendly
    inline constexpr long double pw(long double x, int n) noexcept {
        long double r = 1;
        while (n-- > 0) r *= x;
        return r;
    }

    /**
     * @name Quad (power 2)
     * @{ */
    template <arithmetic T>
    inline constexpr T in_quad(T t) noexcept {
        return ease_in_impl<T>(t, [](long double x) { return x * x; });
    }

    template <arithmetic T>
    inline constexpr T out_quad(T t) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        return static_cast<T>(1 - (1 - x) * (1 - x));
    }

    template <arithmetic T>
    inline constexpr T in_out_quad(T t) noexcept {
        return ease_in_out_impl<T>(t, [](long double x) { return x * x; });
    }
    /** @} */

    /**
     * @name Cubic (power 3)
     * @{ */
    template <arithmetic T>
    inline constexpr T in_cubic(T t) noexcept {
        return ease_in_impl<T>(t, [](long double x) { return pw(x, 3); });
    }

    template <arithmetic T>
    inline constexpr T out_cubic(T t) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        CT y = 1 - x;
        return static_cast<T>(1 - pw(y, 3));
    }

    template <arithmetic T>
    inline constexpr T in_out_cubic(T t) noexcept {
        return ease_in_out_impl<T>(t, [](long double x) { return pw(x, 3); });
    }
    /** @} */

    /**
     * @name Quart (power 4)
     * @{ */
    template <arithmetic T>
    inline constexpr T in_quart(T t) noexcept {
        return ease_in_impl<T>(t, [](long double x) { return pw(x, 4); });
    }

    template <arithmetic T>
    inline constexpr T out_quart(T t) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        return static_cast<T>(1 - pw(1 - x, 4));
    }

    template <arithmetic T>
    inline constexpr T in_out_quart(T t) noexcept {
        return ease_in_out_impl<T>(t, [](long double x) { return pw(x, 4); });
    }
    /** @} */

    /**
     * @name Quint (power 5)
     * @{ */
    template <arithmetic T>
    inline constexpr T in_quint(T t) noexcept {
        return ease_in_impl<T>(t, [](long double x) { return pw(x, 5); });
    }

    template <arithmetic T>
    inline constexpr T out_quint(T t) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        return static_cast<T>(1 - pw(1 - x, 5));
    }

    template <arithmetic T>
    inline constexpr T in_out_quint(T t) noexcept {
        return ease_in_out_impl<T>(t, [](long double x) { return pw(x, 5); });
    }
    /** @} */

    /**
     * @name Sine
     * @{ */
    template <arithmetic T>
    inline T in_sine(T t) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        return static_cast<T>(1 - std::cos(x * std::numbers::pi_v<long double> / 2));
    }

    template <arithmetic T>
    inline T out_sine(T t) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        return static_cast<T>(std::sin(x * std::numbers::pi_v<long double> / 2));
    }

    template <arithmetic T>
    inline T in_out_sine(T t) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        return static_cast<T>(-0.5L * (std::cos(std::numbers::pi_v<long double> *x) - 1));
    }
    /** @} */

    /**
     * @name Exponential
     * @{ */
    template <arithmetic T>
    inline constexpr T in_expo(T t) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        return static_cast<T>(almost_zero(x) ? 0 : std::pow(2.0L, 10.0L * (x - 1.0L)));
    }

    template <arithmetic T>
    inline constexpr T out_expo(T t) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        return static_cast<T>(almost_zero(1 - x) ? 1 : 1 - std::pow(2.0L, -10.0L * x));
    }

    template <arithmetic T>
    inline T in_out_expo(T t) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        if (almost_zero(x)) return static_cast<T>(0);
        if (almost_zero(1 - x)) return static_cast<T>(1);
        if (x < 0.5L)
            return static_cast<T>(0.5L * std::pow(2.0L, (20.0L * x) - 10.0L));
        else
            return static_cast<T>(1.0L - 0.5L * std::pow(2.0L, -20.0L * x + 10.0L));
    }
    /** @} */

    /**
     * @name Circular
     * @{ */
    template <arithmetic T>
    inline constexpr T in_circ(T t) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        return static_cast<T>(1 - std::sqrt(1 - x * x));
    }

    template <arithmetic T>
    inline constexpr T out_circ(T t) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        CT y = 1 - x;
        return static_cast<T>(std::sqrt(1 - y * y));
    }

    template <arithmetic T>
    inline constexpr T in_out_circ(T t) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        if (x < 0.5L)
            return static_cast<T>((1 - std::sqrt(1 - 4 * x * x)) * 0.5L);
        else {
            CT y = (2 * x) - 1;
            return static_cast<T>((std::sqrt(1 - y * y) + 1) * 0.5L);
        }
    }
    /** @} */

    /**
     * @name Back (overshoot)
     * @{ */
    template <arithmetic T>
    inline T in_back(T t, long double s = 1.70158L) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        return static_cast<T>(x * x * ((s + 1) * x - s));
    }

    template <arithmetic T>
    inline T out_back(T t, long double s = 1.70158L) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        CT y = 1 - x;
        return static_cast<T>(1 - (y * y * ((s + 1) * y - s)));
    }

    template <arithmetic T>
    inline T in_out_back(T t, long double s = 1.70158L) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        CT s2 = s * 1.525L;
        if (x < 0.5L) {
            CT xx = 2 * x;
            return static_cast<T>(0.5L * (xx * xx * ((s2 + 1) * xx - s2)));
        }
        else {
            CT xx = 2 * x - 2;
            return static_cast<T>(0.5L * (xx * xx * ((s2 + 1) * xx + s2) + 2));
        }
    }
    /** @} */

    /**
     * @name Elastic
     * @{ */
    template <arithmetic T>
    inline T in_elastic(T t, long double amplitude = 1.0L, long double period = 0.3L) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        if (almost_zero(x) || almost_zero(1 - x)) return static_cast<T>(x);
        CT a = amplitude;
        CT p = period;
        CT s = p / (2 * std::numbers::pi_v<long double>) * std::asin(1.0L / a);
        CT inv = -(a * std::pow(2.0L, 10.0L * (x - 1.0L)) * std::sin((x - 1.0L - s) * (2 * std::numbers::pi_v<long double>) / p));
        return static_cast<T>(inv);
    }

    template <arithmetic T>
    inline T out_elastic(T t, long double amplitude = 1.0L, long double period = 0.3L) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        if (almost_zero(x) || almost_zero(1 - x)) return static_cast<T>(x);
        CT a = amplitude;
        CT p = period;
        CT s = p / (2 * std::numbers::pi_v<long double>) * std::asin(1.0L / a);
        CT val = a * std::pow(2.0L, -10.0L * x) * std::sin((x - s) * (2 * std::numbers::pi_v<long double>) / p) + 1.0L;
        return static_cast<T>(val);
    }

    template <arithmetic T>
    inline T in_out_elastic(T t, long double amplitude = 1.0L, long double period = 0.45L) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        if (almost_zero(x) || almost_zero(1 - x)) return static_cast<T>(x);
        CT a = amplitude;
        CT p = period;
        CT s = p / (2 * std::numbers::pi_v<long double>) * std::asin(1.0L / a);
        CT xx = x * 2.0L;
        if (xx < 1.0L) {
            CT val = -0.5L * (a * std::pow(2.0L, 10.0L * (xx - 1.0L)) * std::sin((xx - 1.0L - s) * (2 * std::numbers::pi_v<long double>) / p));
            return static_cast<T>(val);
        }
        else {
            CT val = a * std::pow(2.0L, -10.0L * (xx - 1.0L)) * std::sin((xx - 1.0L - s) * (2 * std::numbers::pi_v<long double>) / p) * 0.5L + 1.0L;
            return static_cast<T>(val);
        }
    }
    /** @} */

    /**
     * @name Bounce
     * @{ */
    inline constexpr long double bounce_out_ld(long double t) noexcept {
        if (t < (1.0L / 2.75L)) {
            return 7.5625L * t * t;
        }
        else if (t < (2.0L / 2.75L)) {
            long double tt = t - (1.5L / 2.75L);
            return 7.5625L * tt * tt + 0.75L;
        }
        else if (t < (2.5L / 2.75L)) {
            long double tt = t - (2.25L / 2.75L);
            return 7.5625L * tt * tt + 0.9375L;
        }
        else {
            long double tt = t - (2.625L / 2.75L);
            return 7.5625L * tt * tt + 0.984375L;
        }
    }

    template <arithmetic T>
    inline constexpr T out_bounce(T t) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        return static_cast<T>(bounce_out_ld(x));
    }

    template <arithmetic T>
    inline constexpr T in_bounce(T t) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        return static_cast<T>(1.0L - bounce_out_ld(1.0L - x));
    }

    template <arithmetic T>
    inline constexpr T in_out_bounce(T t) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        if (x < 0.5L)
            return static_cast<T>(0.5L * (1.0L - bounce_out_ld(1.0L - 2.0L * x)));
        else
            return static_cast<T>(0.5L * (bounce_out_ld(2.0L * x - 1.0L) + 1.0L));
    }
    /** @} */

    /**
     * @brief Commonly-used named easing identifiers
     */
    enum class Ease {
        Linear,
        InQuad,
        OutQuad,
        InOutQuad,
        InCubic,
        OutCubic,
        InOutCubic,
        InQuart,
        OutQuart,
        InOutQuart,
        InQuint,
        OutQuint,
        InOutQuint,
        InSine,
        OutSine,
        InOutSine,
        InExpo,
        OutExpo,
        InOutExpo,
        InCirc,
        OutCirc,
        InOutCirc,
        InBack,
        OutBack,
        InOutBack,
        InElastic,
        OutElastic,
        InOutElastic,
        InBounce,
        OutBounce,
        InOutBounce
    };

    /**
     * @brief Evaluate a named easing
     * @tparam T arithmetic type
     */
    template <arithmetic T>
    inline T evaluate(Ease e, T t) noexcept {
        using CT = calc_t<T>;
        CT x = static_cast<CT>(t);
        if (x <= CT(0)) return T(0);
        if (x >= CT(1)) return T(1);
        switch (e) {
        case Ease::Linear: return linear<T>(t);
        case Ease::InQuad: return in_quad<T>(t);
        case Ease::OutQuad: return out_quad<T>(t);
        case Ease::InOutQuad: return in_out_quad<T>(t);
        case Ease::InCubic: return in_cubic<T>(t);
        case Ease::OutCubic: return out_cubic<T>(t);
        case Ease::InOutCubic: return in_out_cubic<T>(t);
        case Ease::InQuart: return in_quart<T>(t);
        case Ease::OutQuart: return out_quart<T>(t);
        case Ease::InOutQuart: return in_out_quart<T>(t);
        case Ease::InQuint: return in_quint<T>(t);
        case Ease::OutQuint: return out_quint<T>(t);
        case Ease::InOutQuint: return in_out_quint<T>(t);
        case Ease::InSine: return in_sine<T>(t);
        case Ease::OutSine: return out_sine<T>(t);
        case Ease::InOutSine: return in_out_sine<T>(t);
        case Ease::InExpo: return in_expo<T>(t);
        case Ease::OutExpo: return out_expo<T>(t);
        case Ease::InOutExpo: return in_out_expo<T>(t);
        case Ease::InCirc: return in_circ<T>(t);
        case Ease::OutCirc: return out_circ<T>(t);
        case Ease::InOutCirc: return in_out_circ<T>(t);
        case Ease::InBack: return in_back<T>(t);
        case Ease::OutBack: return out_back<T>(t);
        case Ease::InOutBack: return in_out_back<T>(t);
        case Ease::InElastic: return in_elastic<T>(t);
        case Ease::OutElastic: return out_elastic<T>(t);
        case Ease::InOutElastic: return in_out_elastic<T>(t);
        case Ease::InBounce: return in_bounce<T>(t);
        case Ease::OutBounce: return out_bounce<T>(t);
        case Ease::InOutBounce: return in_out_bounce<T>(t);
        default: return linear<T>(t);
        }
    }

} // namespace easing

#endif // EASING_HPP_INCLUDED
