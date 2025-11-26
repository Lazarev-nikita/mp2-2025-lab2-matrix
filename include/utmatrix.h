#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>

template <class T>
class TVector {
protected:
    T* p;
    int sz;
    int startIndex;

public:
    explicit TVector(int size = 0, int startIndex = 0)
        : p(nullptr), sz(0), startIndex(startIndex) {
        if (size < 0)
            throw std::invalid_argument("Size must be >= 0");
        if (startIndex < 0)
            throw std::invalid_argument("startIndex must be >= 0");

        if (size > 0) {
            p = new T[size];
            sz = size;
            std::fill(p, p + sz, T());
        }
    }

    TVector(const TVector& v)
        : p(nullptr), sz(0), startIndex(v.startIndex) {
        if (v.sz > 0) {
            p = new T[v.sz];
            sz = v.sz;
            std::copy(v.p, v.p + sz, p);
        }
    }

    TVector& operator=(const TVector& v) {
        if (this == &v)
            return *this;

        if (v.sz == 0) {
            delete[] p;
            p = nullptr;
            sz = 0;
            startIndex = v.startIndex;
            return *this;
        }

        T* newp = new T[v.sz];
        std::copy(v.p, v.p + v.sz, newp);

        delete[] p;

        p = newp;
        sz = v.sz;
        startIndex = v.startIndex;

        return *this;
    }

    ~TVector() {
        delete[] p;
    }

    int Size() const { return sz; }
    int StartIndex() const { return startIndex; }

    T& operator[](int pos) {
        if (pos < startIndex || pos >= startIndex + sz)
            throw std::out_of_range("Index out of range");
        return p[pos - startIndex];
    }

    const T& operator[](int pos) const {
        if (pos < startIndex || pos >= startIndex + sz)
            throw std::out_of_range("Index out of range");
        return p[pos - startIndex];
    }

    bool operator==(const TVector& v) const {
        if (sz != v.sz || startIndex != v.startIndex)
            return false;

        for (int i = 0; i < sz; i++)
            if (!(p[i] == v.p[i]))
                return false;

        return true;
    }

    bool operator!=(const TVector& v) const { return !(*this == v); }

    TVector operator+(const TVector& v) const {
        if (sz != v.sz || startIndex != v.startIndex)
            throw std::invalid_argument("Vectors incompatible for +");

        TVector res(sz, startIndex);
        for (int i = 0; i < sz; i++)
            res.p[i] = p[i] + v.p[i];

        return res;
    }

    TVector operator-(const TVector& v) const {
        if (sz != v.sz || startIndex != v.startIndex)
            throw std::invalid_argument("Vectors incompatible for -");

        TVector res(sz, startIndex);
        for (int i = 0; i < sz; i++)
            res.p[i] = p[i] - v.p[i];

        return res;
    }

    TVector operator*(const T& scalar) const {
        TVector res(sz, startIndex);
        for (int i = 0; i < sz; i++)
            res.p[i] = p[i] * scalar;

        return res;
    }
};


template <class T>
class TMatrix {
private:
    int n;
    TVector<T>* rows;

public:
    explicit TMatrix(int size = 0)
        : n(size), rows(nullptr) {
        if (size < 0)
            throw std::invalid_argument("Size must be >= 0");

        if (size > 0) {
            rows = new TVector<T>[n];
            for (int i = 0; i < n; i++) {
                rows[i] = TVector<T>(n - i, i);
            }
        }
    }

    TMatrix(const TMatrix& m)
        : n(m.n), rows(nullptr) {
        if (n > 0) {
            rows = new TVector<T>[n];
            for (int i = 0; i < n; i++)
                rows[i] = m.rows[i];
        }
    }

    TMatrix& operator=(const TMatrix& m) {
        if (this == &m)
            return *this;

        delete[] rows;

        n = m.n;
        rows = nullptr;

        if (n > 0) {
            rows = new TVector<T>[n];
            for (int i = 0; i < n; i++)
                rows[i] = m.rows[i];
        }

        return *this;
    }

    ~TMatrix() {
        delete[] rows;
    }

    int Size() const { return n; }

    TVector<T>& operator[](int i) {
        if (i < 0 || i >= n)
            throw std::out_of_range("Row index out of range");
        return rows[i];
    }

    const TVector<T>& operator[](int i) const {
        if (i < 0 || i >= n)
            throw std::out_of_range("Row index out of range");
        return rows[i];
    }

    bool operator==(const TMatrix& m) const {
        if (n != m.n)
            return false;

        for (int i = 0; i < n; i++)
            if (!(rows[i] == m.rows[i]))
                return false;

        return true;
    }

    bool operator!=(const TMatrix& m) const {
        return !(*this == m);
    }

    TMatrix operator+(const TMatrix& m) const {
        if (n != m.n)
            throw std::invalid_argument("Matrix sizes must be equal");

        TMatrix res(n);

        for (int i = 0; i < n; i++)
            res.rows[i] = rows[i] + m.rows[i];

        return res;
    }

    TMatrix operator-(const TMatrix& m) const {
        if (n != m.n)
            throw std::invalid_argument("Matrix sizes must be equal");

        TMatrix res(n);

        for (int i = 0; i < n; i++)
            res.rows[i] = rows[i] - m.rows[i];

        return res;
    }
};
