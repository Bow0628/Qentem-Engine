/*
 * Copyright (c) 2020 Hani Ammar
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "String.hpp"

#ifndef QENTEM_DIGIT_H_
#define QENTEM_DIGIT_H_

#define QENTEM_DECIMAL_BASE_ 10
#define QENTEM_EXPONENT_MAX_LENGTH_ 5

namespace Qentem {

/*
 * Basic number conversion.
 */
class Digit {
  public:
    static UInt HexStringToNumber(const char *str, UInt length) noexcept {
        UInt value = 0;

        if (str != nullptr) {
            UInt base = 0;

            while (length != 0) {
                --length;

                if ((str[length] > '0') && (str[length] < ':')) {
                    // No use for 0
                    value +=
                        ((static_cast<UInt>(str[length]) - '0') << base); // 1-9
                } else if ((str[length] > '@') && (str[length] < 'G')) {  // A-F
                    value += ((static_cast<UInt>(str[length]) - '7') << base);
                } else if ((str[length] > '`') && (str[length] < 'g')) { // a-f
                    value += ((static_cast<UInt>(str[length]) - 'W') << base);
                }

                base += 4U;
            }
        }

        return value;
    }

    static UInt HexStringToNumber(const char *str) noexcept {
        return HexStringToNumber(str, String::Count<UInt>(str));
    }

    /*
     * "min" is the minimum digits. Zeros will be added to the left side, if the
     * number of digits is less than "mini"
     */
    inline static String NumberToString(unsigned long long number,
                                        UInt               min = 1) {
        return intToString(number, min, false);
    }

    static String NumberToString(long long ll_number, UInt min = 1) {
        if (ll_number < 0) {
            ll_number *= -1;
            return intToString(ll_number, min, true);
        }

        return intToString(ll_number, min, false);
    }

    inline static String NumberToString(unsigned long number, UInt min = 1) {
        return intToString(number, min, false);
    }

    static String NumberToString(long long_number, UInt min = 1) {
        if (long_number < 0) {
            long_number *= -1;
            return intToString(long_number, min, true);
        }

        return intToString(long_number, min, false);
    }

    inline static String NumberToString(unsigned int number, UInt min = 1) {
        return intToString(number, min, false);
    }

    static String NumberToString(int int_number, UInt min = 1) {
        if (int_number < 0) {
            int_number *= -1;
            return intToString(int_number, min, true);
        }

        return intToString(int_number, min, false);
    }

    /*
     * "min" is the minimum digits to the left of the pieried. Zeros will be
     * added if the digits on the left is less than "min". "r_min" is the same
     * as "min" but for the right side. "precision" is the precision of the
     * decimal.
     */

    inline static String NumberToString(double d_number, UInt min = 1,
                                        UInt r_min = 0, UInt precision = 0) {
        return doubleToString(d_number, min, r_min, precision);
    }

    inline static String NumberToString(float f_number, UInt min = 1,
                                        UInt r_min = 0, UInt precision = 0) {
        return doubleToString(static_cast<double>(f_number), min, r_min,
                              precision);
    }

    /////////////////////////////////////////////////////////////////

    inline static bool StringToNumber(double &number, const char *str,
                                      UInt length) noexcept {
        return stringToSignedFloat(number, str, length);
    }

    inline static bool StringToNumber(double &    number,
                                      const char *str) noexcept {
        return stringToSignedFloat(number, str, String::Count<UInt>(str));
    }

    inline static bool StringToNumber(float &number, const char *str,
                                      UInt length) noexcept {
        return stringToSignedFloat(number, str, length);
    }

    inline static bool StringToNumber(float &number, const char *str) noexcept {
        return stringToSignedFloat(number, str, String::Count<UInt>(str));
    }

    inline static bool StringToNumber(unsigned long long &number,
                                      const char *str, UInt length) noexcept {
        return stringToUnsignedInt(number, str, length);
    }

    inline static bool StringToNumber(unsigned long long &number,
                                      const char *        str) noexcept {
        return stringToUnsignedInt(number, str, String::Count<UInt>(str));
    }

    inline static bool StringToNumber(long long &number, const char *str,
                                      UInt length) noexcept {
        return stringToSignedInt(number, str, length);
    }

    inline static bool StringToNumber(long long & number,
                                      const char *str) noexcept {
        return stringToSignedInt(number, str, String::Count<UInt>(str));
    }

    inline static bool StringToNumber(unsigned long &number, const char *str,
                                      UInt length) noexcept {
        return stringToUnsignedInt(number, str, length);
    }

    inline static bool StringToNumber(unsigned long &number,
                                      const char *   str) noexcept {
        return stringToUnsignedInt(number, str, String::Count<UInt>(str));
    }

    inline static bool StringToNumber(long &number, const char *str,
                                      UInt length) noexcept {
        return stringToSignedInt(number, str, length);
    }

    inline static bool StringToNumber(long &number, const char *str) noexcept {
        return stringToSignedInt(number, str, String::Count<UInt>(str));
    }

    inline static bool StringToNumber(unsigned int &number, const char *str,
                                      UInt length) noexcept {
        return stringToUnsignedInt(number, str, length);
    }

    inline static bool StringToNumber(unsigned int &number,
                                      const char *  str) noexcept {
        return stringToUnsignedInt(number, str, String::Count<UInt>(str));
    }

    inline static bool StringToNumber(int &number, const char *str,
                                      UInt length) noexcept {
        return stringToSignedInt(number, str, length);
    }

    inline static bool StringToNumber(int &number, const char *str) noexcept {
        return stringToSignedInt(number, str, String::Count<UInt>(str));
    }

    //////////// Private ////////////

  private:
    template <typename Type_>
    static bool stringToInt(Type_ &number, const char *str,
                            UInt length) noexcept {
        Type_ postion = 1;

        do {
            --length;
            const char c = str[length];

            if ((c > '/') && (c < ':')) {
                number += ((static_cast<Type_>(c) - '0') * postion);
                postion *= QENTEM_DECIMAL_BASE_;
            } else {
                return false;
            }
        } while (length != 0);

        return true;
    }

    template <typename Type_>
    static bool stringToUnsignedInt(Type_ &number, const char *str,
                                    UInt length) noexcept {
        number = 0;

        if ((str != nullptr) && (length != 0)) {
            if ((length > 1) && (str[0] == '0')) {
                return false; // No leanding zeros.
            }

            if (str[0] == '+') {
                UInt offset = 1;
                String::SoftTrim(str, offset, --length);

                if (length != 0) {
                    return stringToUnsignedInt(number, &(str[offset]), length);
                }
            } else if (stringToInt(number, str, length)) {
                return true;
            }

            number = 0;
        }

        return false;
    }

    template <typename Type_>
    static bool stringToSignedInt(Type_ &number, const char *s_str,
                                  UInt length) noexcept {
        number = 0;

        if ((s_str != nullptr) && (length != 0)) {
            if ((length > 1) && (s_str[0] == '0')) {
                return false; // No leanding zeros.
            }

            switch (s_str[0]) {
                case '-': {
                    UInt ni_offset = 1;
                    String::SoftTrim(s_str, ni_offset, --length);

                    if ((length != 0) &&
                        stringToSignedInt(number, &(s_str[ni_offset]),
                                          length)) {
                        number *= -1;
                        return true;
                    }

                    break;
                }

                case '+': {
                    UInt offset = 1;
                    String::SoftTrim(s_str, offset, --length);

                    if (length != 0) {
                        return stringToSignedInt(number, &(s_str[offset]),
                                                 length);
                    }

                    break;
                }

                default: {
                    if (stringToInt(number, s_str, length)) {
                        return true;
                    }
                }
            }

            number = 0;
        }

        return false;
    }

    template <typename Type_>
    static bool stringToSignedFloat(Type_ &number, const char *str,
                                    UInt length) noexcept {
        number = 0;

        if ((str != nullptr) && (length != 0)) {
            if (((length > 1) && ((str[0] == '0') && (str[1] != '.')))) {
                number = 0;
                return false; // No leanding zeros.
            }

            switch (str[0]) {
                case '-': {
                    UInt n_offset = 1;
                    String::SoftTrim(str, n_offset, --length);

                    if ((length != 0) &&
                        stringToSignedFloat(number, &(str[n_offset]), length)) {
                        number *= -1;
                        return true;
                    }

                    break;
                }

                case '+': {
                    UInt offset = 1;
                    String::SoftTrim(str, offset, --length);

                    if (length != 0) {
                        return stringToSignedFloat(number, &(str[offset]),
                                                   length);
                    }

                    break;
                }

                default: {
                    int exponent = 0;

                    if (parseExponent(exponent, str, length) &&
                        stringToFloat(number, exponent, str, length)) {
                        return true;
                    }
                }
            }

            number = 0;
        }

        return false;
    }

    static bool parseExponent(int &exponent, const char *str,
                              UInt &length) noexcept {
        UInt offset = (length - 1);

        if (offset != 0) {
            UInt offset2    = 0;
            UInt MAX_LENGTH = QENTEM_EXPONENT_MAX_LENGTH_; // e(-|+)xxx
            int  sign       = 0;

            do {
                const char c = str[offset];

                if ((c < '0') || (c > '9')) {
                    switch (c) {
                        case '.': {
                            return true;
                        }

                        case 'e':
                        case 'E': {
                            if (MAX_LENGTH == QENTEM_EXPONENT_MAX_LENGTH_) {
                                // No number.
                                return false;
                            }

                            offset2    = offset;
                            MAX_LENGTH = 0;
                            continue;
                        }

                        case '-':
                        case '+': {
                            if ((MAX_LENGTH == QENTEM_EXPONENT_MAX_LENGTH_) ||
                                (sign != 0)) {
                                // No number, or double sign.
                                return false;
                            }

                            sign = ((c == '-') ? -1 : 1);
                            break;
                        }

                        default: {
                            return false;
                        }
                    }
                }

                --MAX_LENGTH;
                --offset;
            } while ((offset != 0) && (MAX_LENGTH != 0));

            if (offset2 != 0) {
                if (sign != 0) {
                    ++offset2;
                }

                while (++offset2 < length) {
                    exponent *= QENTEM_DECIMAL_BASE_;
                    exponent += (str[offset2] - '0');
                }

                if (sign == -1) {
                    exponent *= -1;
                }

                length = offset;
            }
        }

        return true;
    }

    template <typename Type_>
    static bool stringToFloat(Type_ &number, int exponent, const char *str,
                              UInt length) noexcept {
        unsigned long long w_number = 0;
        UInt               len      = ((length < 18) ? length : 17);
        UInt               offset   = 0;
        char               c;
        bool               has_dot = false;

        do {
            c = str[offset];
            ++offset;

            if ((c > '/') && (c < ':')) {
                w_number *= QENTEM_DECIMAL_BASE_;
                w_number += (static_cast<ULong>(c) - '0');
            } else if (c == '.') {
                if (has_dot || (offset == length)) {
                    return false;
                }

                has_dot = true;
                break;
            } else {
                return false;
            }
        } while (offset < len);

        if (has_dot) {
            Type_ base = 1;
            len        = ((length < 20) ? length : 19);

            do {
                c = str[offset];

                if ((c > '/') && (c < ':')) {
                    base *= QENTEM_DECIMAL_BASE_;
                    number += (static_cast<Type_>(c) - '0') / base;
                } else {
                    return false;
                }

                ++offset;
            } while (offset < len);
        } else if (offset != length) {
            do {
                c = str[offset];

                if ((c > '/') && (c < ':')) {
                    ++exponent;
                } else if (c == '.') {
                    break;
                } else {
                    return false;
                }

                ++offset;
            } while (offset < length);
        }

        number += static_cast<Type_>(w_number);

        if (exponent != 0) {
            bool negative = false;

            if (exponent < 0) {
                negative = true;
                exponent *= -1;
            }

            do {
                Type_ number2;

                if (exponent > 9) {
                    number2 = 1E10;
                    exponent -= QENTEM_DECIMAL_BASE_;
                } else {
                    number2 = 1E1;
                    --exponent;
                }

                if (negative) {
                    number /= number2;
                } else {
                    number *= number2;
                }
            } while (exponent != 0);
        }

        return true;
    }

    template <typename Type_>
    static String intToString(Type_ number, UInt min, bool negative) {
        constexpr UInt end_offset = 20;
        UInt           length     = end_offset;

        char *str = HAllocator::Allocate<char>(end_offset + 1);

        /*
         *  18446744073709551615 MAX unsigned long long 20
         *  -9223372036854775807 MAX long long          19 + (-|+) = 20
         *
         *  4294967295           MAX unsigned long      10
         *  -2147483647          MAX long               10 + (-|+) = 11
         *
         *  65535                MAX unsigned int       5
         *  -32767               MAX int                5 + (-|+) = 6
         */

        while (number != 0) {
            --length;
            str[length] = char((number % QENTEM_DECIMAL_BASE_) + '0');
            number /= QENTEM_DECIMAL_BASE_;
        }

        min = (end_offset - min);

        while (length > min) {
            str[--length] = '0';
        }

        if (negative) {
            str[--length] = '-';
        }

        min = 0;
        while (length < end_offset) {
            str[min] = str[length];
            ++min;
            ++length;
        }

        str[min] = '\0';
        return String(str, min);
    }

    static void extractExponent(double &number, int &exponent) noexcept {
        if (number > 1E19) {
            do {
                if (number > 1E99) {
                    exponent += 100;
                    number /= 1E100;
                } else if (number > 1E9) {
                    exponent += QENTEM_DECIMAL_BASE_;
                    number /= 1E10;
                } else {
                    ++exponent;
                    number /= QENTEM_DECIMAL_BASE_;
                }
            } while (number > 9);
        } else {
            do {
                if (number < 1E-99) {
                    exponent -= 100;
                    number *= 1E100;
                } else if (number < 1E-9) {
                    exponent -= QENTEM_DECIMAL_BASE_;
                    number *= 1E10;
                } else {
                    --exponent;
                    number *= QENTEM_DECIMAL_BASE_;
                }
            } while (number < 0.9);
        }
    }

    static String doubleToString(double number, UInt min, UInt r_min,
                                 UInt precision) {
        constexpr UInt max_length = 19;
        // 1844674407370955161 == 19
        // 0.18446744073709551 == 19

        char               tmp[max_length];
        unsigned long long fraction        = 0;
        UInt               fraction_length = 0;
        UInt               end_offset      = max_length;
        UInt               offset          = 0;
        int                exponent        = 0;
        UInt               exponent_length = 0;
        const bool         negative        = (number < 0);
        const bool         no_exponent     = (r_min != 0);

        if (negative) {
            number *= -1;
            ++offset;
        }

        if ((number > 1E19) || ((number != 0) && (number < 1E-17))) {
            extractExponent(number, exponent);
            r_min           = 0;
            precision       = 15;
            exponent_length = QENTEM_EXPONENT_MAX_LENGTH_;
        }

        unsigned long long left_number =
            static_cast<unsigned long long>(number);

        unsigned long long tmp_number = left_number;

        while (tmp_number != 0) {
            --end_offset;
            tmp[end_offset] = char((tmp_number % QENTEM_DECIMAL_BASE_) + '0');
            tmp_number /= QENTEM_DECIMAL_BASE_;
        }

        UInt left_length = (max_length - end_offset);

        if (end_offset != 0) { // Full
            number -= static_cast<double>(left_number);

            if (number != 0) {
                UInt precision2 = 17;

                if (left_length != 0) {
                    --precision2;
                    precision2 -= left_length;
                }

                if ((precision == 0) || (precision > precision2)) {
                    precision = precision2;
                }

                fraction = extractFraction(number, precision);

                if ((precision < 17) &&
                    ((fraction % QENTEM_DECIMAL_BASE_) > 4)) {
                    fraction /= QENTEM_DECIMAL_BASE_;
                    ++fraction;
                } else {
                    fraction /= QENTEM_DECIMAL_BASE_;
                }

                // Removing all zeros from the fraction.
                while ((precision != 0) &&
                       ((fraction % QENTEM_DECIMAL_BASE_) == 0)) {
                    fraction /= QENTEM_DECIMAL_BASE_;
                    --precision;
                }

                if ((precision == 0) && (fraction == 1)) {
                    fraction = 0;
                    ++left_number;
                    end_offset = max_length;

                    while (left_number != 0) {
                        --end_offset;
                        tmp[end_offset] =
                            char((left_number % QENTEM_DECIMAL_BASE_) + '0');
                        left_number /= QENTEM_DECIMAL_BASE_;
                    }

                    left_length = (max_length - end_offset);
                }

                fraction_length = precision;
            }
        }

        if ((fraction_length != 0) || no_exponent) {
            if (r_min > fraction_length) {
                r_min -= fraction_length;
            } else {
                r_min = 0;
            }

            ++fraction_length; // One for '.'
        }

        UInt str_len = fraction_length + r_min + offset + exponent_length + 1U;

        char *str;
        if (min < left_length) {
            // Using "offset" for the (-) sign
            str_len += left_length;
            str = HAllocator::Allocate<char>(str_len);
        } else {
            str_len += min;
            str = HAllocator::Allocate<char>(str_len);

            min -= left_length;
            while (min != 0) {
                str[offset] = '0';
                ++offset;
                --min;
            }
        }

        if (negative) {
            str[0] = '-';
        }

        while (end_offset < max_length) {
            str[offset] = tmp[end_offset];
            ++offset;
            ++end_offset;
        }

        if (fraction_length != 0) {
            end_offset = --fraction_length;

            while (fraction != 0) {
                --end_offset;
                tmp[end_offset] = char((fraction % QENTEM_DECIMAL_BASE_) + '0');
                fraction /= QENTEM_DECIMAL_BASE_;
            }

            if (((end_offset == 0) && (exponent == 0)) || (left_length != 0) ||
                no_exponent) {
                UInt offset2 = end_offset;

                str[offset] = '.';
                ++offset;

                while (end_offset != 0) {
                    str[offset] = '0';
                    ++offset;
                    --end_offset;
                }

                while (offset2 < fraction_length) {
                    str[offset] = tmp[offset2];
                    ++offset;
                    ++offset2;
                }

                while (r_min != 0) {
                    str[offset] = '0';
                    ++offset;
                    --r_min;
                }
            } else {
                offset = (negative) ? 1 : 0;
                --exponent;
                exponent -= static_cast<int>(end_offset);

                str[offset] = tmp[end_offset];
                ++offset;
                ++end_offset;

                if (end_offset != fraction_length) {
                    str[offset] = '.';
                    ++offset;

                    do {
                        str[offset] = tmp[end_offset];
                        ++offset;
                        ++end_offset;
                    } while (end_offset < fraction_length);
                }
            }
        }

        if (exponent != 0) {
            str[offset] = 'e';
            ++offset;

            if (exponent < 0) {
                exponent *= -1;
                str[offset] = '-';
                ++offset;
            }

            end_offset = 4;

            while (exponent != 0) {
                --end_offset;
                tmp[end_offset] = char((exponent % QENTEM_DECIMAL_BASE_) + '0');
                exponent /= QENTEM_DECIMAL_BASE_;
            }

            while (end_offset < 4) {
                str[offset] = tmp[end_offset];
                ++offset;
                ++end_offset;
            }
        }

        str[offset] = '\0';
        return String(str, offset);
    }

    static unsigned long long extractFraction(double number,
                                              UInt   precision) noexcept {
        switch (precision) {
            case 1: {
                number *= 1E2;
                break;
            }

            case 2: {
                number *= 1E3;
                break;
            }

            case 3: {
                number *= 1E4;
                break;
            }

            case 4: {
                number *= 1E5;
                break;
            }

            case 5: {
                number *= 1E6;
                break;
            }

            case 6: {
                number *= 1E7;
                break;
            }

            case 7: {
                number *= 1E8;
                break;
            }

            case 8: {
                number *= 1E9;
                break;
            }

            case 9: {
                number *= 1E10;
                break;
            }

            case 10: {
                number *= 1E11;
                break;
            }

            case 11: {
                number *= 1E12;
                break;
            }

            case 12: {
                number *= 1E13;
                break;
            }

            case 13: {
                number *= 1E14;
                break;
            }

            case 14: {
                number *= 1E15;
                break;
            }

            case 15: {
                number *= 1E16;
                break;
            }

            case 16: {
                number *= 1E17;
                break;
            }

            default: {
                number *= 1E18;
            }
        }

        return static_cast<unsigned long long>(number);
    }
};

} // namespace Qentem

#endif
