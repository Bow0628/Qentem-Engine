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

#include "Common.hpp"

#ifndef QENTEM_FIXEDARRAY_H_
#define QENTEM_FIXEDARRAY_H_

namespace Qentem {

// C Array.

template <typename Type_, UInt Size_T_>
class FixedArray {
  public:
    FixedArray()  = default;
    ~FixedArray() = default;

    FixedArray(FixedArray &&)      = delete;
    FixedArray(const FixedArray &) = delete;
    FixedArray &operator=(FixedArray &&) = delete;
    FixedArray &operator=(const FixedArray &) = delete;

    void operator+=(Type_ &&item) {
        if (!(IsFull())) {
            storage_[Size()] = static_cast<Type_ &&>(item);
            ++index_;
            return;
        }

        throw 1;
    }

    void operator+=(const Type_ &item) {
        *this += static_cast<Type_ &&>(Type_(item));
    }

    inline void Clear() noexcept {
        // C Arrays inside c++ invoke destructor on every element once they are
        // destructed. Copy and move operators of 'Type_' should handel reseting
        // their struct.
        index_ = 0;
    }

    inline Type_ *Storage() noexcept { return &(storage_[0]); }
    inline UInt   Size() const noexcept { return index_; }
    inline UInt   Capacity() const noexcept { return Size_T_; }
    inline bool   IsEmpty() const noexcept { return (Size() == 0); }
    inline bool   IsNotEmpty() const noexcept { return !(IsEmpty()); }
    inline bool   IsFull() const noexcept { return (Size() == Capacity()); }
    inline const Type_ *First() const noexcept { return &(storage_[0]); }
    inline const Type_ *End() const noexcept {
        return (&(storage_[0]) + Size());
    }

    //////////// Private ////////////

  private:
    Type_ storage_[Size_T_]{};
    UInt  index_{0};
};

} // namespace Qentem

#endif
