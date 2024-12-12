#pragma once  
template<typename T>
class PolyChain;

template<typename T>
class Point {
    T _x;
    T _y;

public:

    Point() : _x(0), _y(0) {}
    Point(T x, T y) : _x(x), _y(y) {}

    T GetX() const { return _x; }
    T GetY() const { return _y; } 

    PolyChain<T> operator+(const PolyChain<T>& chain) {
        PolyChain<T> NewChain(chain.GetSize() + 1);
        NewChain[0] = *this;

        for (int i = 1; i <= chain.GetCount(); i++) {
            NewChain[i] = chain[i - 1];
        }

        NewChain.SetCount(chain.GetCount() + 1);
        return NewChain;
    }

};
