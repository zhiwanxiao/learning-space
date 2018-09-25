#include "largeInt.h"

std::ostream& operator<<(std::ostream& os, const LargeInt& li) {
	os << (li.figure[0] == 0 ? "" : "-");
	const int capacity = li.capacity;
	for(int i = capacity-li.digits+1; i <= capacity; i++) {
		os << (int)li.figure[i];
	}
	return os;
}

std::istream& operator>>(std::istream& is, LargeInt& li) {
	int capacity = li.capacity;
	char s[capacity];/*input string's length must less than 'capacity' or array 's' will overflow*/
	is >> s;
	int len = sizeof(s)/sizeof(char);
	li.valuedByStr(s, len);
	return is;
}

LargeInt& LargeInt::toAbsolute() {
	this->figure[0] = 0;
	return *this;
}

LargeInt& LargeInt::toInverse() {
	this->figure[0] = !this->figure[0];
	return *this;
}

void LargeInt::valuedByInt(int i) {
	figure[0] = i >= 0 ? 0 : 1;// i is positive figure or not
	i = i >= 0 ? i : -i;// i = |i|
	figure[capacity] = i % 10;// copy the single figure to 'figure'
	digits = 1;// i absolutly is a single figure
	int d = 10;//d is a divisor
	int q;//q is a quotient
	while((q = i/d) > 0) {
		figure[capacity-digits] = q % 10;
		digits++;
		d *= 10;
	}
}

void LargeInt::toOnlyZero() {
	if(this->figure[0] == 1 && this->digits == 1 && this->figure[this->capacity] == 0) {
		this->toAbsolute();
	}
}

void LargeInt::valuedByStr(const char* str, int len) {
	int capacity = this->capacity;
	int temp = 0;
	for(int i = 0; i < len && str[i] != '\0'; i++, temp++);/*real calculation of length of array 's'*/
	len = temp;
	for(int i = 0; i < len; i++) {
		if(str[i] < '0' || str[i] > '9') {
			if(str[i] == '-' && i == 0 && len > 1) {
				continue;
			}
			std::cout << "input error!" << std::endl;
		}
	}
	int begin = this->digits = 0;
	int digit = len;
	this->figure[0] = (str[0] == '-' ? begin++, digit--, 1 : 0);
	for(int i = begin, count = 0; i < len; i++, count++) {
		this->figure[capacity-digit+1+count] = str[i]-'0';
		this->digits++;
	}
	if(this->figure[0] == 1 && this->figure[capacity] == 0 && this->digits == 1) {/*if li express '-0'*/
		this->figure[0] = 0;
	}
}

bool LargeInt::absLargeThan(const LargeInt& li) const{
	int digits1 = this->digits;
	int digits2 = li.digits;
	if(digits1 > digits2) {
		return true;
	} else if(digits1 == digits2) {
		int capacity = li.capacity;
		int start = capacity-digits1+1;
		for(; this->figure[start] == li.figure[start]
			&& start < capacity; start++);
		return (this->figure[start] > li.figure[start] ? true : false);
	} else {
		return false;
	}
}

LargeInt& LargeInt::operator<<(const int n) {
	LargeInt tmp(1);
	if(tmp > *this || n < 1) {
		return *this;
	}
	if(digits+n <= capacity) {
		for(int i = capacity-digits+1; i <= capacity; i++) {
			figure[i-n] = figure[i];
		}
		for(int i = 0; i < n; i++) {
			figure[capacity-i] = 0;
		}
		digits += n;
	} else {
		std::cout << "memory overflow!" << std::endl;
	}
	return *this;
}

LargeInt& LargeInt::operator>>(const int n) {
	if(n < 1) {
		return *this;
	}
	if(n >= digits) {
		digits = 1;
		figure[0] = figure[capacity] = 0;
		return *this;
	}
	for(int i = capacity; i >= capacity-digits+1+n; i--) {
		figure[i] = figure[i-n];
	}
	digits -= n;
	return *this;
}

LargeInt::LargeInt() {
	digits = 1;
	figure[capacity] = 0;
}

LargeInt::LargeInt(int i) {
	valuedByInt(i);
}

LargeInt::LargeInt(const char* str) {
	int i;
	for(i = 0; str[i] != '\0'; i++);
	this->valuedByStr(str, i);
}

bool operator>(const LargeInt& li1, const LargeInt& li2) {
	int sign1 = li1.figure[0];
	int sign2 = li2.figure[0];
	if(sign1 < sign2) {
		return true;
	} else if(sign1 == sign2) {
		if(sign1 == 0) {
			return li1.absLargeThan(li2);
		} else {
			return li2.absLargeThan(li1);
		}
	} else {
		return false;
	}
} 

bool operator==(const LargeInt& li1, const LargeInt& li2) {
	int sign1 = li1.figure[0];
	int sign2 = li2.figure[0];
	if(sign1 == sign2) {
		return (!li1.absLargeThan(li2) && !li2.absLargeThan(li1));
	} else {
		return false;
	}
}

bool operator>=(const LargeInt& li1, const LargeInt& li2) {
	return (li1 > li2 || li1 == li2);
}

bool operator<(const LargeInt& li1, const LargeInt& li2) {
	return !(li1 >= li2);
}

bool operator<=(const LargeInt& li1, const LargeInt& li2) {
	return !(li1 > li2);
}

bool operator!=(const LargeInt& li1, const LargeInt& li2) {
	return !(li1 == li2);
}

LargeInt operator+(const LargeInt& li1, const LargeInt& li2) {
	int sign1 = li1.figure[0];
	int sign2 = li2.figure[0];
	LargeInt li, larger, smaller;
	int capacity = li1.capacity;
	int digits = li1.absLargeThan(li2) ? li1.digits : li2.digits;
	li1.absLargeThan(li2) ? (larger = li1, smaller = li2) : (larger = li2, smaller = li1);
	if(sign1 == sign2) {/*addition*/
		int carry = 0;
		for(int i = capacity; i >= capacity-digits+1; i--) {
			int smallerTmp = smaller.figure[i];
			if(capacity-smaller.digits+1 > i) {
				smallerTmp = 0;
			}
			int tmp = larger.figure[i]+smallerTmp+carry;
			li.figure[i] = tmp % 10;
			carry = tmp >= 10 ? (tmp/10) : 0;
		}
		li.digits = digits;
		if(carry > 0) {
			if(capacity-digits > 0) {/*check of index out of array*/
				li.figure[capacity-digits] = carry;
				li.digits++;
			} else {
				std::cout << "index out of array!" << std::endl;
			}
		}
		li.figure[0] = sign1;
	} else {/*substraction*/
		int borrow = 0;
		int highestDigit = capacity;
		for(int i = capacity; i >= capacity-digits+1; i--) {
			int smallerTmp = smaller.figure[i];
			if(capacity-smaller.digits+1 > i) {
				smallerTmp = 0;
			}
			int tmp = larger.figure[i] - borrow - smallerTmp;
			if(tmp < 0) {
				tmp = larger.figure[i] - borrow + 10 - smallerTmp;
				borrow = 1;
			} else {
				borrow = 0;
			}
			if((li.figure[i] = tmp % 10) > 0) {
				highestDigit = i;
			}
		}
		li.digits = capacity - highestDigit + 1;
		li.figure[0] = larger.figure[0];
	}
	li.toOnlyZero();/*turn it's sign on 0 if it is 0*/
	return li;
}


LargeInt operator-(const LargeInt& li1, const LargeInt& li2) {
	LargeInt li = li2;
	li.toInverse();
	return li1 + li;
}

LargeInt operator*(const LargeInt& li1, const LargeInt& li2) {
	int digits1 = li1.digits;
	int digits2 = li2.digits;
	int capacity = li1.capacity;
	LargeInt sum;
	for(int i = capacity, moven1 = 0; i >= capacity-digits2+1; i--, moven1++) {
		LargeInt lineSum;
		for(int j = capacity, moven2 = 0; j >= capacity-digits1+1; j--, moven2++) {
			int tmp = (li2.figure[i] * li1.figure[j]);
			LargeInt temp(tmp);
			lineSum = lineSum + (temp << moven2);
		}
		sum = sum + (lineSum << moven1);
	}
	sum.figure[0] = ( li1.figure[0] + li2.figure[0] ) % 2;
	sum.toOnlyZero();/*turn it's sign on 0 if it is 0*/
	return sum;
}

LargeInt operator/(const LargeInt& li1, const LargeInt& li2) {
	if(li2 == 0) {
		std::cout << "division by0 causes an error!" << std::endl;
		return LargeInt(0);
	}
	LargeInt li3 = li1;/*local variable to cover function argument variable*/
	LargeInt li4 = li2;
	li3.toAbsolute();/*only the absolute is considered*/
	li4.toAbsolute();
	if(li3 > li4 || li3 == li4) {
		LargeInt quotient, remainder, subli1;
		subli1 = remainder = li3;
		int dif = li3.digits-li4.digits;/*difference of li1's digits and li2's digits*/
		subli1 >> dif;
		int moveNum = 0;/*right move count compare to length of li2*/
		int count = 0;
		quotient = LargeInt(0);
		while(!(moveNum+count >= li3.digits-li4.digits+1)) {
			if(li4 > subli1 && count == 0) {
				subli1 = remainder;
				subli1 >> (remainder.digits-li4.digits-(++moveNum));
				dif--;
			}
			for(int i = 0; i < 10; i++) {
				LargeInt li(i);
				if(!(li4*li > subli1) && li4*(li+1) > subli1) {
				/*   li2*i <= subli1 */
					quotient = (quotient<<1) + li;
					count++;
					remainder = subli1 - (li4*li);
					if(dif > 0) {
						dif--;
						remainder = (remainder<<1) + LargeInt(li3.figure[li3.capacity-dif]);
					}
					subli1 = remainder;
					//std::cout << "quotients " << li << " remainders " << remainder << " count:" << count << std::endl;
					break;
				}
			}
		}
		quotient.figure[0] = ( li1.figure[0] + li2.figure[0] ) % 2;
		quotient.toOnlyZero();/*turn it's sign on 0 if it is 0*/
		return quotient;
	} else {
		return LargeInt(0);
	}
}

LargeInt operator%(const LargeInt& li1, const LargeInt& li2) {
	if(li2 == 0) {
		std::cout << "division by0 causes an error!" << std::endl;
		return LargeInt(0);
	}
	/*  x % y = x - y * Lx/yJ  */
	LargeInt quotient = li1 / li2;
	/* that depends on what kind of complier you use
	if(quotient < 0 && quotient*li2 != li1) {// it's worked well when the quotient >= 0.but the quotient will takes upper value when the division turns out a negative number
				  // that means remander is not 0 and upper value must be taked
		quotient = quotient - LargeInt(1);// to value a negative number's lower value
	}	*/
	LargeInt li = li1 - li2 * quotient;
	return li;
}

LargeInt::~LargeInt() {
	
}
