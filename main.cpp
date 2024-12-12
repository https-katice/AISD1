#include "PolyChain.h"
#include <iostream>

int main() {
    try {
        PolyChain<int> chain1(5, 10);
        std::cout << chain1 << "\n";

        PolyChain<int> chain2(3);
        std::cout << chain2.GetSize() << "\n";

        chain2 = chain2 + Point<int>(1, 1);
        chain2 = chain2 + Point<int>(2, 2);
        chain2 = chain2 + Point<int>(3, 3);
        std::cout << chain2 << "\n";

        std::cout << "chain2[1]: (" << chain2[1].GetX() << ", " << chain2[1].GetY() << ")\n";

        PolyChain<int> chain3(0, 10, 5);
        std::cout << "random points in range " << chain3 << "\n";

        PolyChain<int> chain4 = chain3;
        std::cout << "copy of chain3 " << chain4 << "\n";

        PolyChain<int> chain5 = Point<int>(50,50) + chain3;
        std::cout << "point in start of chain " << chain5 << "\n";

        PolyChain<int> chain9 = chain3 + Point<int>(25,25);
        std::cout << "point in end of chain " << chain9 << "\n";

        PolyChain<int> chain10 = chain5 + chain9;
        std::cout << "chain + chain " << chain10 << "\n";

        chain2 = chain1;
        std::cout << chain1 << "\n";

        PolyChain<int> chain6(2);
        chain6 = chain6 + Point<int>(0, 0);
        chain6 = chain6 + Point<int>(8, 0);
        std::cout << "len of chain6 " << chain6.len() << "\n";

        using Complex = std::complex<double>;

        PolyChain<Complex> chain7(3);
        chain7 + Point<Complex>(Complex(0, 0), Complex(0, 0));
        chain7 + Point<Complex>(Complex(3, 4), Complex(3, 0));
        chain7 + Point<Complex>(Complex(6, 8), Complex(6, 8));

        
        std::cout << "len with complex points " << chain7.len() << "\n";

        PolyChain<int> chain8(6);
        std::cout << chain2.GetSize() << "\n";

        chain8 = chain8 + Point<int>(0, 0);
        chain8 = chain8 + Point<int>(0, 10);
        chain8 = chain8 + Point<int>(0, 5);
        chain8 = chain8 + Point<int>(3, 10);
        chain8 = chain8 + Point<int>(0, 5);
        chain8 = chain8 + Point<int>(3, 0);
        std::cout << chain8 << "\n";

        try {
            chain2[10];
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Initialization error: " << e.what() << "\n";
    }

    return 0;
}
 