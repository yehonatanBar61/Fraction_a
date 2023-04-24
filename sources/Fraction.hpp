#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>
using namespace std;

namespace ariel{

    class Fraction
    {
    private:
        int numerator;
        int denominator;

    public:
        Fraction(int a, int b);
        Fraction();
        ~Fraction();

        int GetNumerator(){
            return this->numerator;
        }

        int GetDenominator(){
            return this->denominator;
        }

        void SetNumerator(int n){
            this->numerator = n;
        }

        void SetDenominator(int d){
            if(d == 0){
                throw std::invalid_argument("dividing by zero exeption");
            }else{
                this->denominator = d;
            }
        }

        Fraction operator+(Fraction const& other) const;
        Fraction operator+(const float& other){
            Fraction fraction = this->transfer(other);
            return *this + fraction;
        }
        friend Fraction operator+(const float& left, const Fraction& right);

        Fraction operator-(const Fraction& other) const;
        Fraction operator-(const float& other){
            Fraction fraction = this->transfer(other);
            return *this - fraction;
        }
        friend Fraction operator-(const float& left, const Fraction& right);

        Fraction operator*(const Fraction& other) const;
        Fraction operator*(const float& other){
            Fraction fraction = this->transfer(other);
            return *this * fraction;
        }
        friend Fraction operator*(const float& left, const Fraction& right);
            
        

        Fraction operator/(const Fraction& other) const;
        Fraction operator/(const float& other){
            Fraction fraction = this->transfer(other);
            return *this / fraction;
        }
        friend Fraction operator/(const float& left, const Fraction& right);

        bool operator==(const Fraction& other) const;
        bool operator==(const float& other){
            Fraction fraction = this->transfer(other);
            return (fraction == *this);
        }
        friend bool operator==(const float& left, const Fraction& right);

        bool operator>(const Fraction& other) const;
        bool operator>(const float& other){
            Fraction fraction = this->transfer(other);
            return (fraction > *this);
        }
        friend bool operator>(const float& left, const Fraction& right);

        bool operator>=(const Fraction& other) const;
        bool operator>=(const float& other){
            Fraction fraction = this->transfer(other);
            return (fraction >= *this);
        }
        friend bool operator>=(const float& left, const Fraction& right);

        bool operator<(const Fraction& other) const;
        bool operator<(const float& other){
            Fraction fraction = this->transfer(other);
            return (fraction < *this);
        }
        friend bool operator<(const float& left, const Fraction& right);

        bool operator<=(const Fraction& other) const;
        bool operator<=(const float& other){
            Fraction fraction = this->transfer(other);
            return (fraction <= *this);
        }
        friend bool operator<=(const float& left, const Fraction& right);

        Fraction operator ++();
        Fraction operator --();

        Fraction operator ++(int);
        Fraction operator --(int);
        
        friend ostream& operator<<(ostream& os, const Fraction& F);
        friend istream& operator>>( istream& input, Fraction& D );

        int gcd(int a, int b) const{
                if (b == 0) {
                    return a;
                }
            return gcd(b, a % b);
        }

        int lcm(int a, int b) const{
            return (a * b) / gcd(a, b);
        }

        // Converts from a double number to a fraction
        Fraction transfer(float other) const{
            int whole = int(other);//2
            double fractional = other - whole;//.0
            float temp = other;
            int mul = 1;
            while (fmod(temp, 10) != 0)
            {
                temp = temp * 10;
                mul = mul * 10;
            }
            temp /= 10;
            mul /= 10;
            int up = fmod(temp, mul);
            int down = mul;     
            Fraction f(up + whole * down, down);
            return this->reduction(f);
        }

        // Reduces the fraction
        // minus will always appear in the denominator
        Fraction reduction(Fraction& f) const{
            Fraction result;
            int gcd = this->gcd(f.numerator, f.denominator);
            result.denominator = f.denominator/gcd;
            result.numerator = f.numerator/gcd;
            return result;
        }

    };
    
    Fraction::Fraction(int a, int b){
        if(b == 0){
            throw std::invalid_argument("dividing by zero exeption");
        }else{
            this->numerator = a;
            this->denominator = b;
        } 
    }

    Fraction::Fraction(){
        this->numerator = 1;
        this->denominator = 1;
    }
    
    Fraction::~Fraction(){

    }

    Fraction Fraction::operator+(const Fraction& other) const{
        Fraction result;
        int lcm_value = lcm(this->denominator, other.denominator);
        int num1 = this->numerator * (lcm_value / this->denominator);
        int num2 = other.numerator * (lcm_value / other.denominator);
        result.numerator = num1 + num2;
        result.denominator = lcm_value;
        return this->reduction(result);
    }


    std::ostream& operator<<(std::ostream& os, const Fraction& F) {
        os << " " << F.numerator << "/" << F.denominator << " ";
        return os;
    }

    // input operator
    std::istream& operator>>(std::istream& input, Fraction& F) {
        // read the input as a string
        std::string inputStr;
        input >> inputStr;

        // parse the input string to extract the numerator and denominator
        std::istringstream ss(inputStr);
        std::string token;
        getline(ss, token, '/');
        F.numerator = std::stoi(token);
        getline(ss, token);
        F.denominator = std::stoi(token);

        return input;
    }

    Fraction Fraction::operator-(const Fraction& other) const{
        Fraction result;// 1/2, 2/4
        int lcm_value = lcm(this->denominator, other.denominator);// lcm = 4
        int num1 = this->numerator * (lcm_value / this->denominator);// 1 * 2
        int num2 = other.numerator * (lcm_value / other.denominator);// 2 * 1
        result.numerator = num1 - num2;// 2 - 2 = 0
        result.denominator = lcm_value;// 0/4
        return this->reduction(result);
    }


    Fraction Fraction::operator*(const Fraction& other) const{
        Fraction result;
        result.numerator = this->numerator * other.numerator;
        result.denominator = this->denominator * other.denominator;
        return this->reduction(result);
    }

    Fraction Fraction::operator/(const Fraction& other) const{
        Fraction result;

        result.denominator = this->denominator * other.numerator;
        result.numerator = this->numerator * other.denominator;
        return this->reduction(result);
    }
 
    bool Fraction::operator==(const Fraction& other) const{
        Fraction f1(this->numerator, this->denominator);
        Fraction f2(other.numerator, other.denominator);
        f1 = f1.reduction(f1);
        f2 = f2.reduction(f2);
        return (f1.denominator == f2.denominator && f1.numerator == f2.numerator);
    }

    bool Fraction::operator>(const Fraction& other) const{
        return (double(this->numerator)/this->denominator > double(other.numerator)/other.denominator);
    }

    bool Fraction::operator>=(const Fraction& other) const{
        return (double(this->numerator)/this->denominator >= double(other.numerator)/other.denominator);
    }

    bool Fraction::operator<(const Fraction& other) const{
        return (double(this->numerator)/this->denominator < double(other.numerator)/other.denominator);
    }

    bool Fraction::operator<=(const Fraction& other) const{
        return (double(this->numerator)/this->denominator <= double(other.numerator)/other.denominator);
    }

    Fraction Fraction::operator++(){
        this->numerator += this->denominator;
        this->reduction(*this);
        return *this;
    }

    Fraction Fraction::operator--(){
        this->numerator -= this->denominator;
        this->reduction(*this);
        return *this;
    }

    Fraction Fraction::operator ++(int){
        this->numerator += this->denominator;
        this->reduction(*this);
        return *this;
    }

    Fraction Fraction::operator --(int){
        this->numerator -= this->denominator;
        this->reduction(*this);
        return *this;
    }

    Fraction operator+(const float& left, const Fraction& right){
        Fraction fraction = right;
        return fraction + left;
    }

    Fraction operator-(const float& left, const Fraction& right){
        Fraction fraction = right;
        return fraction - left;
    }

    Fraction operator*(const float& left, const Fraction& right){
        Fraction fraction = right;
        return fraction * left;
    }

    Fraction operator/(const float& left, const Fraction& right){
        Fraction left_f;
        Fraction right_f = right;
        left_f = left_f.transfer(left);
        return left_f / right_f; 
    }

    bool operator==(const float& left, const Fraction& right){
        Fraction left_f;
        Fraction right_f = right;
        left_f = left_f.transfer(left);
        return left_f == right_f; 
    }

    bool operator>(const float& left, const Fraction& right){
        Fraction left_f;
        Fraction right_f = right;
        left_f = left_f.transfer(left);
        return left_f > right_f; 
    }

    bool operator>=(const float& left, const Fraction& right){
        Fraction left_f;
        Fraction right_f = right;
        left_f = left_f.transfer(left);
        return left_f >= right_f; 
    }

    bool operator<(const float& left, const Fraction& right){
        Fraction left_f;
        Fraction right_f = right;
        left_f = left_f.transfer(left);
        return left_f < right_f; 
    }

    bool operator<=(const float& left, const Fraction& right){
        Fraction left_f;
        Fraction right_f = right;
        left_f = left_f.transfer(left);
        return left_f <= right_f; 
    }



    
}

#endif