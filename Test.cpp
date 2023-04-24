#include "doctest.h"
#include <iostream>
#include "Fraction.hpp"
using namespace ariel;
using namespace std;

TEST_CASE("Get and Set"){
    Fraction fraction(51,27);
    CHECK(fraction.GetNumerator() == 51);
    CHECK(fraction.GetDenominator() == 27);
    fraction.SetDenominator(28);
    fraction.SetNumerator(52);

    CHECK(fraction.GetDenominator() == 28);
    CHECK(fraction.GetNumerator() == 52);
}

TEST_CASE("/0"){
    Fraction fraction(7,8);
    CHECK_THROWS(fraction.SetDenominator(0));
    CHECK_THROWS(Fraction(10,0));
}


TEST_CASE("Test addition (+) "){
    Fraction fractionA(7,8);
    Fraction fractionB(3,1);
    Fraction z1 = fractionA + fractionB;
    CHECK(z1.GetNumerator() == 31);    
    CHECK(z1.GetDenominator() == 8);
    
    Fraction fractionC(1,2);
    Fraction z2 = fractionC+0.5;
    CHECK(z2.GetNumerator() == 1);    
    CHECK(z2.GetDenominator() == 1);
}

TEST_CASE("Test Subtraction (-) "){
    Fraction fractionA(7,8);
    Fraction fractionB(3,1);
    Fraction z1 = fractionA-fractionB;
    CHECK(z1.GetNumerator() == 17);    
    CHECK(z1.GetDenominator() == -8);
    
    Fraction fractionC(1,2);
    Fraction z2 = fractionC - 0.5;
    CHECK(z2.GetNumerator() == 0);    
}

TEST_CASE("Test reduction"){
    Fraction fractionA(2,4);
    Fraction fractionB(14,21);
    fractionA = fractionA.reduction(fractionA);
    fractionB = fractionB.reduction(fractionB);
    CHECK(fractionA.GetNumerator() == 1);    
    CHECK(fractionA.GetDenominator() == 2);
    
    CHECK(fractionB.GetNumerator() == 2);    
    CHECK(fractionB.GetDenominator() == 3);
}

TEST_CASE("Test division (/) "){
    Fraction fractionA(2,5);
    Fraction fractionB(6,7);
    Fraction z = fractionA/fractionB;
    //CHECK(z == 0.466);
    CHECK(z.GetNumerator() == 7);    
    CHECK(z.GetDenominator() == 15);    
}

TEST_CASE("Test * "){
    Fraction x(7,8);
    Fraction y(3,1);
    Fraction z = x*y;
    Fraction result(21, 8);
    CHECK(z == result);
    CHECK(z == 2.625);
}

TEST_CASE("Test (++) "){

    Fraction x(7,8);
    Fraction t(1,2);

    x++;
    ++t;


    CHECK(x == 1.875);
    CHECK(t == 1.5 );

}

TEST_CASE("Test (--) "){
    Fraction x(16,8);
    Fraction t(6,3);

    x--;
    --t;

    CHECK(x == 1.0);
    CHECK(t == 1.0 );


}

TEST_CASE("Test >,<,>=,<="){
    Fraction x(1,1);
    Fraction y(2,4);
    CHECK(x > y);
    CHECK(!(x == y));
    CHECK(x >= y);
    CHECK(!(x <= y));
    Fraction w(1,8);
    CHECK(w < y);

}
