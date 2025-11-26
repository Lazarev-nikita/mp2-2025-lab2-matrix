#ifndef TMATRIX_H
#define TMATRIX_H

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cassert>
#include <cstddef>

using std::size_t;
using std::istream;
using std::ostream;
using std::runtime_error;
using std::length_error;
using std::out_of_range;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

template<typename T>
class TDynamicVector {
protected:
    size_t sz;
    T* pMem;
public:
    explicit TDynamicVector(size_t size = 1) : sz(size), pMem(nullptr) {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > static_cast<size_t>(MAX_VECTOR_SIZE))
            throw out_of_range("Vector size too large");
        pMem = new T[sz]();
    }

    TDynamicVector(T* arr, size_t s) : sz(s), pMem(nullptr) {
        if (arr == nullptr) throw std::invalid_argument("arr is null");
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > static_cast<size_t>(MAX_VECTOR_SIZE))
            throw out_of_range("Vector size too large");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }

    TDynamicVector(const TDynamicVector& v) : sz(v.sz), pMem(nullptr) {
        pMem = new T[sz]();
        for (size_t i = 0; i < sz; ++i) pMem[i] = v.pMem[i];
    }

    TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem) {
        v.pMem = nullptr;
        v.sz = 0;
    }

    ~TDynamicVector() { delete[] pMem; }

    TDynamicVector& operator=(const TDynamicVector& v) {
        if (this == &v) return *this;
        T* newmem = nullptr;
        if (v.sz > 0) {
            newmem = new T[v.sz];
            for (size_t i = 0; i < v.sz; ++i) newmem[i] = v.pMem[i];
        }
        delete[] pMem;
        pMem = newmem;
        sz = v.sz;
        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept {
        if (this == &v) return *this;
        delete[] pMem;
        pMem = v.pMem;
        sz = v.sz;
        v.pMem = nullptr;
        v.sz = 0;
        return *this;
    }

    size_t size() const noexcept { return sz; }

    T& operator[](int ind) {
        if (ind < 0 || static_cast<size_t>(ind) >= sz) throw out_of_range("Index out of range");
        return pMem[ind];
    }
    const T& operator[](int ind) const {
        if (ind < 0 || static_cast<size_t>(ind) >= sz) throw out_of_range("Index out of range");
        return pMem[ind];
    }

    T& at(size_t ind) {
        if (ind >= sz) throw out_of_range("Index out of range");
        return pMem[ind];
    }
    const T& at(size_t ind) const {
        if (ind >= sz) throw out_of_range("Index out of range");
        return pMem[ind];
    }

    bool operator==(const TDynamicVector& v) const noexcept {
        if (sz != v.sz) return false;
        for (size_t i = 0; i < sz; ++i)
            if (!(pMem[i] == v.pMem[i])) return false;
        return true;
    }

    bool operator!=(const TDynamicVector& v) const noexcept {
        return !(*this == v);
    }

    TDynamicVector operator+(const T& val) const {
        TDynamicVector tmp(*this);
        for (size_t i = 0; i < sz; ++i) tmp.pMem[i] += val;
        return tmp;
    }
    TDynamicVector operator-(const T& val) const {
        TDynamicVector tmp(*this);
        for (size_t i = 0; i < sz; ++i) tmp.pMem[i] -= val;
        return tmp;
    }
    TDynamicVector operator*(const T& val) const {
        TDynamicVector tmp(*this);
        for (size_t i = 0; i < sz; ++i) tmp.pMem[i] *= val;
        return tmp;
    }

    TDynamicVector operator+(const TDynamicVector& v) const {
        if (sz != v.sz) throw runtime_error("lengths are not equal");
        TDynamicVector res(*this);
        for (size_t i = 0; i < sz; ++i) res.pMem[i] += v.pMem[i];
        return res;
    }
    TDynamicVector operator-(const TDynamicVector& v) const {
        if (sz != v.sz) throw runtime_error("lengths are not equal");
        TDynamicVector res(*this);
        for (size_t i = 0; i < sz; ++i) res.pMem[i] -= v.pMem[i];
        return res;
    }

    T operator*(const TDynamicVector& v) const {
        if (sz != v.sz) throw runtime_error("lengths are not equal");
        T acc = T();
        for (size_t i = 0; i < sz; ++i) acc += pMem[i] * v.pMem[i];
        return acc;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    friend istream& operator>>(istream& istr, TDynamicVector& v) {
        for (size_t i = 0; i < v.sz; ++i) istr >> v.pMem[i];
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v) {
        for (size_t i = 0; i < v.sz; ++i) {
            if (i) ostr << ' ';
            ostr << v.pMem[i];
        }
        return ostr;
    }
};

template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>> {
private:
    using base_t = TDynamicVector<TDynamicVector<T>>;
    using base_t::pMem;
    using base_t::sz;
public:
    explicit TDynamicMatrix(size_t s = 1) : base_t(s) {
        if (sz == 0) throw out_of_range("Matrix size must be > 0");
        if (sz > static_cast<size_t>(MAX_MATRIX_SIZE)) throw out_of_range("Matrix size too large");
        for (size_t i = 0; i < sz; ++i) {
            pMem[i] = TDynamicVector<T>(sz);
        }
    }

    TDynamicMatrix(const TDynamicMatrix& m) : base_t(m.sz) {
        for (size_t i = 0; i < sz; ++i) pMem[i] = m.pMem[i];
    }

    TDynamicMatrix(TDynamicMatrix&& m) noexcept : base_t(std::move(m)) {}

    TDynamicMatrix& operator=(const TDynamicMatrix& m) {
        if (this == &m) return *this;
        base_t::operator=(m);
        for (size_t i = 0; i < sz; ++i) {
            if (pMem[i].size() != m.pMem[i].size()) pMem[i] = m.pMem[i];
        }
        return *this;
    }

    TDynamicMatrix& operator=(TDynamicMatrix&& m) noexcept {
        base_t::operator=(std::move(m));
        return *this;
    }

    TDynamicVector<T>& operator[](size_t ind) {
        if (ind >= sz) throw out_of_range("Row index out of range");
        return pMem[ind];
    }
    const TDynamicVector<T>& operator[](size_t ind) const {
        if (ind >= sz) throw out_of_range("Row index out of range");
        return pMem[ind];
    }

    bool operator==(const TDynamicMatrix& m) const noexcept {
        if (sz != m.size()) return false;
        for (size_t i = 0; i < sz; ++i)
            if (!(pMem[i] == m.pMem[i])) return false;
        return true;
    }
    bool operator!=(const TDynamicMatrix& m) const noexcept { return !(*this == m); }

    TDynamicMatrix operator*(const T& val) const {
        TDynamicMatrix res(*this);
        for (size_t i = 0; i < sz; ++i) res.pMem[i] = res.pMem[i] * val;
        return res;
    }

    TDynamicVector<T> operator*(const TDynamicVector<T>& v) const {
        if (v.size() != sz) throw length_error("dimensions mismatch");
        TDynamicVector<T> result(sz);
        for (size_t i = 0; i < sz; ++i) {
            T acc = T();
            for (size_t j = 0; j < sz; ++j) acc += pMem[i][static_cast<int>(j)] * v[static_cast<int>(j)];
            result[static_cast<int>(i)] = acc;
        }
        return result;
    }

    TDynamicMatrix operator+(const TDynamicMatrix& m) const {
        if (m.size() != sz) throw length_error("dimensions mismatch");
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; ++i) res.pMem[i] = pMem[i] + m.pMem[i];
        return res;
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m) const {
        if (m.size() != sz) throw length_error("dimensions mismatch");
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; ++i) res.pMem[i] = pMem[i] - m.pMem[i];
        return res;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m) const {
        if (m.size() != sz) throw length_error("dimensions mismatch");
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; ++i) {
            for (size_t j = 0; j < sz; ++j) {
                T sum = T();
                for (size_t k = 0; k < sz; ++k) {
                    sum += pMem[i][static_cast<int>(k)] * m.pMem[k][j];
                }
                res.pMem[i][j] = sum;
            }
        }
        return res;
    }

    friend istream& operator>>(istream& istr, TDynamicMatrix& v) {
        for (size_t i = 0; i < v.sz; ++i)
            for (size_t j = 0; j < v.sz; ++j)
                istr >> v.pMem[i][j];
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v) {
        for (size_t i = 0; i < v.sz; ++i) {
            for (size_t j = 0; j < v.sz; ++j) {
                if (j) ostr << ' ';
                ostr << v.pMem[i][j];
            }
            if (i + 1 < v.sz) ostr << '\n';
        }
        return ostr;
    }

    size_t size() const noexcept { return sz; }
    int get_size() const noexcept { return static_cast<int>(sz); }
};

#endif
