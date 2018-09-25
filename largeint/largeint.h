/*
	[illustraction]
		this is a integer larger than c/c++ int, you can modify the length of it any time so that it fits the difference of scale.
		the operating efficiency in your program may not the best, because the design of this class is not the most effective and smartest.
		so you should condider about how complex the application when you use it.
	class LargeInt:
	- construct function:
		LargeInt(): a default figure 0.
		LargeInt(int): you can give a int figure to initialize.
			such as: LargeInt li(1); //it's a figure express 1.
		LargeInt(const char*): you can also give a string like "1234567890" to initialize
			such as: LargeInt li("1234567890"); //it's a figure express 1234567890.
					 LargeInt li("1234567890987456321"); //it's a figure express 1234567890987456321.
	- member function:
		LargeInt& toAbsolute(): a member function which change itselfs value to absolute value.
	- operator function:
		support: +, -, *, /, %, >, >=, <, <=, ==.
		prototype:
			bool operator>(const LargeInt&, const LargeInt&);
			bool operator==(const LargeInt&, const LargeInt&);
			bool operator>=(const LargeInt&, const LargeInt&);
			bool operator<(const LargeInt&, const LargeInt&);
			bool operator<=(const LargeInt&, const LargeInt&);
			bool operator!=(const LargeInt&, const LargeInt&);
			LargeInt operator+(const LargeInt&, const LargeInt&);
			LargeInt operator-(const LargeInt&, const LargeInt&);
			LargeInt operator*(const LargeInt&, const LargeInt&);
			LargeInt operator/(const LargeInt&, const LargeInt&);
			LargeInt operator%(const LargeInt&, const LargeInt&);
		note: - above all is global friend function for class LargeInt.
			  - no such as '+=', '*=', '++'... remember that when you use it.
	- input & output:
		two global overload function '>>' & '<<' for istream & ostream included.
		you can: LargeInt a, b;
				 std::cin >> a >> b; // do NOT try to input such as "000", "+21", "-001". a correct and effiective figure will be received successful.
				 					 // successful input: "10", "-5", "101".
				 std::cout << a << "," << b << std::endl;
*/
#ifndef LARGEINT_H
#define LARGEINT_H

#include <iostream>
#define LARGEINT_CAPACITY 200 /* the length of figure, you can modify it any time if you want */

class LargeInt {
	private:
		enum {capacity = LARGEINT_CAPACITY}; /*to modify a large integer's digit capacity. its required to recompile*/
		char figure[capacity+1];/*adds one char to express its a positive/negative figures*/
		int digits;
		
		void valuedByInt(int i);
		void valuedByStr(const char* str, int len);
		void toOnlyZero();/*check of a negative zero*/
		LargeInt& toInverse();/*a switch of +/- for a number*/
		bool absLargeThan(const LargeInt& li) const;/*its return true if this largeint's absolute value larger than 'li'*/
		LargeInt& operator<<(const int n);
		LargeInt& operator>>(const int n);
	public:
		LargeInt();
		LargeInt(int i);
		LargeInt(const char* str);
		LargeInt& toAbsolute();
		friend std::ostream& operator<<(std::ostream& os, const LargeInt& li);
		friend std::istream& operator>>(std::istream& is, LargeInt& li);
		friend bool operator>(const LargeInt& li1, const LargeInt& li2);
		friend bool operator==(const LargeInt& li1, const LargeInt& li2);
		friend bool operator>=(const LargeInt& li1, const LargeInt& li2);
		friend bool operator<(const LargeInt& li1, const LargeInt& li2);
		friend bool operator<=(const LargeInt& li1, const LargeInt& li2);
		friend bool operator!=(const LargeInt& li1, const LargeInt& li2);
		friend LargeInt operator+(const LargeInt& li1, const LargeInt& li2);
		friend LargeInt operator-(const LargeInt& li1, const LargeInt& li2);
		friend LargeInt operator*(const LargeInt& li1, const LargeInt& li2);
		friend LargeInt operator/(const LargeInt& li1, const LargeInt& li2);
		friend LargeInt operator%(const LargeInt& li1, const LargeInt& li2);
		~LargeInt();
};
#endif // end of LARGEINT_H
