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

#include "Memory.hpp"
#include "QPointer.hpp"
#include "StringUtils.hpp"

#ifndef QENTEM_STRING_H_
#define QENTEM_STRING_H_

namespace Qentem {

/*
 * String container with null terminator and a taggable pointer.
 */
template <typename Char_T_>
class String {
  public:
    String() = default;

    String(String &&src) noexcept
        : storage_(static_cast<QPointer<Char_T_> &&>(src.storage_)),
          length_(src.Length()) {
        src.setLength(0);
    }

    String(const String &src) : length_(src.Length()) {
        if (IsNotEmpty()) {
            Char_T_ *des = allocate(Length() + 1);
            Memory::Copy(des, src.First(), (Length() * sizeof(Char_T_)));
            des[Length()] = 0;
        }
    }

    explicit String(SizeT len) : length_(len) {
        allocate(len + 1)[Length()] = 0;
    }

    String(Char_T_ *str, SizeT len) noexcept : length_(len) { setStorage(str); }

    String(const Char_T_ *str, SizeT len) : length_(len) {
        Char_T_ *des = allocate(len + 1);

        if (len != 0) {
            Memory::Copy(des, str, (Length() * sizeof(Char_T_)));
        }

        des[Length()] = 0;
    }

    explicit String(const Char_T_ *str)
        : String(str, StringUtils::Count(str)) {}

    ~String() { deallocate(Storage()); }

    String &operator=(String &&src) noexcept {
        if (this != &src) {
            deallocate(Storage());
            storage_ = static_cast<QPointer<Char_T_> &&>(src.storage_);
            setLength(src.Length());
            src.setLength(0);
        }

        return *this;
    }

    String &operator=(const String &src) {
        if (this != &src) {
            deallocate(Storage());
            setLength(src.Length());
            Char_T_ *des = allocate(Length() + 1);
            Memory::Copy(des, src.First(), (Length() * sizeof(Char_T_)));
            des[Length()] = 0;
        }

        return *this;
    }

    String &operator=(const Char_T_ *str) {
        SizeT len = StringUtils::Count(str);

        deallocate(Storage());
        setLength(len);
        Char_T_ *des = allocate(len + 1);

        if (len != 0) {
            Memory::Copy(des, str, (len * sizeof(Char_T_)));
        }

        des[len] = 0;

        return *this;
    }

    String &operator+=(String &&src) {
        Insert(src.First(), src.Length());
        deallocate(src.Storage());
        src.clearStorage();
        src.setLength(0);

        return *this;
    }

    String &operator+=(const String &src) {
        Insert(src.First(), src.Length());
        return *this;
    }

    String &operator+=(const Char_T_ *str) {
        Insert(str, StringUtils::Count(str));
        return *this;
    }

    String operator+(String &&src) const {
        String ns{Insert(*this, src)};
        src.deallocate(src.Storage());
        src.clearStorage();
        src.setLength(0);

        return ns;
    }

    inline String operator+(const String &src) const {
        return Insert(*this, src);
    }

    String operator+(const Char_T_ *str) const {
        const SizeT len = StringUtils::Count(str);
        String      ns  = String{Length() + len};
        Char_T_ *   des = ns.Storage();

        if (IsNotEmpty()) {
            Memory::Copy(des, First(), (Length() * sizeof(Char_T_)));
        }

        if (len != 0) {
            Memory::Copy((des + Length()), str, (len * sizeof(Char_T_)));
        }

        return ns;
    }

    inline bool operator==(const String &string) const noexcept {
        if (Length() != string.Length()) {
            return false;
        }

        return StringUtils::IsEqual(First(), string.First(), Length());
    }

    inline bool operator==(const Char_T_ *str) const noexcept {
        const SizeT len = StringUtils::Count(str);

        if (Length() != len) {
            return false;
        }

        return StringUtils::IsEqual(First(), str, len);
    }

    inline bool operator!=(const String &string) const noexcept {
        return (!(*this == string));
    }

    inline bool operator!=(const Char_T_ *str) const noexcept {
        return (!(*this == str));
    }

    inline bool IsEqual(const Char_T_ *str, SizeT length) const noexcept {
        if (Length() != length) {
            return false;
        }

        return StringUtils::IsEqual(First(), str, length);
    }

    void Reset() noexcept {
        deallocate(Storage());
        clearStorage();
        setLength(0);
    }

    Char_T_ *Eject() noexcept {
        Char_T_ *str = Storage();
        clearStorage();
        setLength(0);

        return str;
    }

    inline Char_T_ *Storage() const noexcept { return storage_.GetPointer(); }
    inline SizeT    Length() const noexcept { return length_; }
    inline const Char_T_ *First() const noexcept { return Storage(); }
    inline bool           IsEmpty() const noexcept { return (Length() == 0); }
    inline bool           IsNotEmpty() const noexcept { return !(IsEmpty()); }

    inline const Char_T_ *Last() const noexcept {
        if (IsNotEmpty()) {
            return (First() + (Length() - 1));
        }

        return nullptr;
    }

    static String Insert(const String &src1, const String &src2) {
        const SizeT ns_len = (src1.Length() + src2.Length());
        String      ns     = String{ns_len};
        Char_T_ *   des    = ns.Storage();

        if (src1.IsNotEmpty()) {
            Memory::Copy(des, src1.First(), (src1.Length() * sizeof(Char_T_)));
        }

        if (src2.IsNotEmpty()) {
            Memory::Copy((des + src1.Length()), src2.First(),
                         (src2.Length() * sizeof(Char_T_)));
        }

        return ns;
    }

    QENTEM_NOINLINE void Insert(const Char_T_ *str, SizeT len) {
        if ((str != nullptr) && (len != 0)) {
            Char_T_ *src = Storage();
            Char_T_ *des = allocate(Length() + len + 1);

            if (src != nullptr) {
                Memory::Copy(des, src, (Length() * sizeof(Char_T_)));
                deallocate(src);
            }

            Memory::Copy((des + Length()), str, (len * sizeof(Char_T_)));
            length_ += len;
            des[Length()] = 0;
        }
    }

    static String Trim(const String &str) {
        SizeT length = str.Length();
        SizeT offset = 0;
        StringUtils::SoftTrim(str.First(), offset, length);
        return String((str.First() + offset), length);
    }

    //////////// Private ////////////

  private:
    void     setStorage(Char_T_ *ptr) noexcept { storage_.Set(ptr); }
    Char_T_ *allocate(SizeT new_size) {
        Char_T_ *new_storage = Memory::Allocate<Char_T_>(new_size);
        setStorage(new_storage);
        return new_storage;
    }

    void deallocate(Char_T_ *old_storage) { Memory::Deallocate(old_storage); }
    void clearStorage() noexcept { setStorage(nullptr); }
    void setLength(SizeT new_length) noexcept { length_ = new_length; }

    QPointer<Char_T_> storage_{};
    SizeT             length_{0};
};

} // namespace Qentem

#endif
