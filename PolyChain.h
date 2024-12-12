#pragma once
#include "Point.h"
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <complex>
constexpr auto accuracy = 0.0001;


template<typename T>
class PolyChain {
private:
    static const double accuracy;
    Point<T>* _data;
    int _count;
    size_t _size;

public:
    PolyChain(T x, T y) : _size(10), _count(1) {
        _data = new Point<T>[_size];
        _data[0] = Point<T>(x, y);
    }

    PolyChain(size_t size) : _size(size), _count(0) {
        if (size <= 0) throw std::runtime_error("Invalid size in params");
        _data = new Point<T>[_size];
        _count = 0;
    }

    PolyChain(T m1, T m2, int count) : _size(count), _count(count) {
        if (m1 >= m2) throw std::runtime_error("Invalid interval in params");
        _data = new Point<T>[_size];
        for (int i = 0; i < _count; i++) {
            _data[i] = Point<T>(m1 + static_cast<T>(rand()) % (m2 - m1 + 1),
                m1 + static_cast<T>(rand()) % (m2 - m1 + 1));
        }
    }

    PolyChain(const PolyChain& other) : _size(other._size), _count(other._count) {
        _data = new Point<T>[_size];
        for (int i = 0; i < _count; i++) {
            _data[i] = other._data[i];
        }
    }


    ~PolyChain() {
        delete[] _data;
    }

    void SetCount(int newCount) { _count = newCount; }

    int GetCount() const { return _count; }

    size_t GetSize() const { return _size; }

    PolyChain operator=(const PolyChain& other) {
        if (this != &other) {
            delete[] _data;
            _size = other._size;
            _count = other._count;
            _data = new Point<T>[_size];
            for (int i = 0; i < _count; i++) {
                _data[i] = other._data[i];
            }
        } 
        return *this;
    }

    Point<T>& operator[](int idx) const {
        if (idx >= _count || idx < 0) throw std::out_of_range("Invalid idx");
        return _data[idx];
    }

    Point<T>& operator[](int idx) {
        if (idx >= _size || idx < 0) throw std::out_of_range("Invalid idx");
        return _data[idx];
    }   

    PolyChain operator+(Point<T> NewPoint) {
        if (_size < _count + 1) {
            PolyChain NewChain(_size + 10);
            for (int i = 0; i < _count; i++) {
                NewChain._data[i] = _data[i];
            }
            NewChain._data[_count] = NewPoint;
            NewChain._count = _count + 1;
            return NewChain;
        }
        _data[_count] = NewPoint;
        _count += 1;
        return *this;
    }

    PolyChain operator+(const PolyChain<T>& other) const {
        PolyChain result(this->GetSize() + other.GetSize());
        for (int i = 0; i < _count; i++) {
            result._data[i] = _data[i];
        }
        for (int i = 0; i < other.GetCount(); i++) {
            result._data[i + _count] = other._data[i];
        }
        result.SetCount(this->GetCount() + other.GetCount());
        return result;
    }


    double len() {
        double len = 0;
        for (int i = 0; i < _count-1; i++) {
            double XCatLen = abs(_data[i].GetX() - _data[i + 1].GetX());
            double YCatLen = abs(_data[i].GetY() - _data[i + 1].GetY());
            len += sqrt(XCatLen * XCatLen + YCatLen * YCatLen);
        }
        return len;
    }

    bool operator==(const PolyChain& other) const { 
        return std::abs(this->len() - other.len()) < accuracy;
    }

    bool operator!=(const PolyChain& other) const {
        return !(*this == other);
    }

    bool operator<(const PolyChain& other) const {
        return (other.len() - this->len()) > accuracy;
    }

    bool operator<=(const PolyChain& other) const {
        return (*this < other) || (*this == other);
    }

    bool operator>(const PolyChain& other) const {
        return (this->len() - other.len()) > accuracy;
    }

    bool operator>=(const PolyChain& other) const {
        return (*this > other) || (*this == other);
    }
};

template<typename T>
PolyChain<T> MakeIsoscelesTriangle() {
    PolyChain<T> Result(6);
    Result = Result + Point<T>(0, 0);
    Result = Result + Point<T>(10, 0);
    Result = Result + Point<T>(5, 0);
    Result = Result + Point<T>(10, 3);
    Result = Result + Point<T>(5, 0);
    Result = Result + Point<T>(0, 3);

    return Result;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const PolyChain<T>& chain) {
    for (int i = 0; i < chain.GetCount(); i++) {
        out << chain[i].GetX() << " " << chain[i].GetY() << " ";
    }
    return out;
}
