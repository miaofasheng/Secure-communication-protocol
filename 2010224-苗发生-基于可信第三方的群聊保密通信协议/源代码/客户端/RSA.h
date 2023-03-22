#pragma once
#pragma once
#include<iostream>
#include<string>
#include<math.h>
#include<time.h>
#include<stdlib.h>
using namespace std;

const int MAX = 1025;
const int BIT = 512;
class Big_Int
{
public:
	bool num[MAX];
	bool sign;              //用来存储该大整数的符号
	Big_Int(unsigned int in);        //十进制转二进制的存储  
	Big_Int(string in);
	void GeneRandom(int n); //生成随机数，传入的n表示随机数的位数
	void Print();               //按十六进制输出结果
	bool operator[](int i) { return num[i]; };
	void Move_left(int i);
	void Move_right(int i);
	Big_Int ABS();
	bool Primer(int k);
	string output;
	void Fix_output();


	//以下是基于基本运算实现的一些更复杂的运算
	Big_Int Mod(Big_Int a, Big_Int b, Big_Int c);          //取余
	Big_Int Exp(Big_Int x, Big_Int y);                     //先指数乘，再取模，即result=（*this）^x (mod y)
	Big_Int Inverse(Big_Int x);                                //求x对y的逆元，即result* x = 1(mod y)
	//以下为友元函数的定义，即对一些运算符进行重载
	friend Big_Int operator+(Big_Int a, Big_Int b);
	friend Big_Int operator-(Big_Int a, Big_Int b);
	friend Big_Int operator*(Big_Int a, Big_Int b);
	friend Big_Int operator/(Big_Int a, Big_Int b);
	friend Big_Int operator%(Big_Int a, Big_Int b);
	friend bool operator>(Big_Int a, Big_Int b);
	friend bool operator==(Big_Int a, Big_Int b);
	friend bool operator!=(Big_Int a, Big_Int b);



};

Big_Int::Big_Int(unsigned int in) {
	if (in >= 0)
		sign = 0;
	else
		sign = 1;
	int i = 0;
	while (in)
	{
		num[i] = in % 2;
		in = in / 2;
		i++;
	}
	for (; i < MAX; i++)
	{
		num[i] = 0;
	}
	this->Fix_output();
}

Big_Int::Big_Int(string in)        // 十六进制转二进制存储（右边为最低位）
{
	int i, j = 0;
	int temp;
	for (i = 0; i < MAX; i++) {
		num[i] = 0;
	}
	for (i = in.length() - 1; i >= 0; i--) {
		if (in[i] >= 'a' && in[i] <= 'f') {
			temp = in[i] - 'a' + 10;
		}
		else {
			if (in[i] >= 'A' && in[i] <= 'F') {
				temp = in[i] - 'A' + 10;
			}
			else {
				temp = in[i] - '0';
			}
		}
		if (temp / 8) {
			num[4 * j + 3] = 1;
		}
		if ((temp % 8) / 4) {
			num[4 * j + 2] = 1;
		}
		if ((temp % 4) / 2) {
			num[4 * j + 1] = 1;
		}
		if (temp % 2) {
			num[4 * j] = 1;
		}
		j++;
	}
	sign = 0;
	this->Fix_output();
}

void Big_Int::GeneRandom(int n) {
	int wordnum = n / 16;
	srand(time(0));
	for (int i = 0; i < wordnum; i++)
	{
		Big_Int temp(rand());
		for (int j = 0; j < 16; j++)
			num[i * 16 + j] = temp[j];
	}
	for (int i = MAX - 1; i >= n; i--)
		num[i] = 0;
	num[n - 1] = 1;		//首位不为0保证位数正确
	num[0] = 1;		//末位不为零保证是奇数
	this->Fix_output();
}



Big_Int Big_Int::ABS()
{
	Big_Int temp = (*this);
	if (temp.sign == 0) {
		return temp;
	}
	else {
		temp.sign = !temp.sign;
		return temp;
	}
}

Big_Int operator+(Big_Int a, Big_Int b) {
	Big_Int result = Big_Int(0);      // 用于作为返回值
	int i;
	bool temp = 0;       // temp表示低位是否进位       
	if (a.sign == b.sign) {
		for (i = 0; i < MAX; i++) {
			if (a[i] == 0 && b[i] == 0 && temp == 0) {
				result.num[i] = 0;
				temp = 0;
			}
			else {
				if (a[i] == 1 && b[i] == 0 && temp == 0 ||
					a[i] == 0 && b[i] == 1 && temp == 0 ||
					a[i] == 0 && b[i] == 0 && temp == 1) {
					temp = 0;
					result.num[i] = 1;
				}
				else {
					if (a[i] == 1 && b[i] == 1 && temp == 0 ||
						a[i] == 0 && b[i] == 1 && temp == 1 ||
						a[i] == 1 && b[i] == 0 && temp == 1) {
						temp = 1;        //进位为1
						result.num[i] = 0;
					}
					else {
						if (a[i] == 1 && b[i] == 1 && temp == 1) {
							temp = 1;
							result.num[i] = 1;
						}
					}
				}
			}
		}
		result.sign = a.sign;
	}
	if (a.sign == 0 && b.sign == 1) {
		b.sign = !b.sign;
		return a - b;
	}
	if (a.sign == 1 && b.sign == 0) {
		b.sign = !b.sign;
		return b - a;
	}
	if (temp)        
	{
		cout << "Overflow" << endl;
	}
	return result;
}

void Big_Int::Move_left(int i)
{
	int k;
	for (k = MAX - 1; k > i - 1; k--) {
		num[k] = num[k - i];
	}
	for (k = 0; k < i; k++) {
		num[k] = 0;
	}
	this->Fix_output();
}

void Big_Int::Move_right(int i)
{
	int k;
	for (k = 0; k < MAX - i; k++) {
		num[k] = num[k + i];
	}
	for (k = MAX - 1; k > MAX - 1 - i; k--) {
		num[k] = 0;
	}
	this->Fix_output();
}

Big_Int operator-(Big_Int a, Big_Int b) {
	Big_Int result = Big_Int(0);
	int i;
	bool temp = 0;      //表示之前低位的借位
	if (a.sign == b.sign) {
		if (!(b.ABS() > a.ABS()))     //这里没有写成b.ABS()<=a.ABS()是因为下面只实现了！和>的友元函数实现，未实现<=的编写
		{
			for (i = 0; i < MAX; i++) {
				if (a[i] == 0 && b[i] == 0 && temp == 0 ||
					a[i] == 1 && b[i] == 0 && temp == 1 ||
					a[i] == 1 && b[i] == 1 && temp == 0) {
					result.num[i] = 0;
					temp = 0;
				}
				else {
					if (a[i] == 0 && b[i] == 0 && temp == 1 ||
						a[i] == 0 && b[i] == 1 && temp == 0 ||
						a[i] == 1 && b[i] == 1 && temp == 1) {
						temp = 1;
						result.num[i] = 1;
					}
					else {
						if (a[i] == 0 && b[i] == 1 && temp == 1) {
							temp = 1;
							result.num[i] = 0;
						}
						else {
							if (a[i] == 1 && b[i] == 0 && temp == 0) {
								temp = 0;
								result.num[i] = 1;
							}
						}
					}
				}
			}
			result.sign = a.sign;
		}
		else {
			result = (b - a);
			result.sign = !a.sign;
		}
	}
	if (a.sign == 0 && b.sign == 1) {
		b.sign = !b.sign;
		return a + b;
	}
	if (a.sign == 1 && b.sign == 0) {
		b.sign = !b.sign;
		return a + b;
	}
	if (temp) {
		cout << "Overflow" << endl;
	}
	return result;
};

Big_Int operator*(Big_Int a, Big_Int b)
{

	Big_Int result = Big_Int(0);
	int i;
	for (i = 0; i < MAX; i++) {
		if (b[i] == 1) {
			result = result + a;
		}
		a.Move_left(1);
	}
	if (a.sign == b.sign) {
		result.sign = 0;
	}
	else {
		result.sign = 1;
	}
	return result;
}

Big_Int operator/(Big_Int a, Big_Int b)
{
	Big_Int result = Big_Int(0);
	if (a.sign == b.sign) {
		result.sign = 0;
	}
	else {
		result.sign = 1;
	}
	int i, j;
	Big_Int tempA = a, tempB = b, ZERO(0);
	if (ZERO > tempA) {
		tempA.sign = !tempA.sign;
	}
	if (ZERO > tempB) {
		tempB.sign = !tempB.sign;
	}
	for (j = MAX - 1; j >= 0; j--) {
		if (b[j]) {
			break;
		}
	}

	Big_Int tempDiv = tempB;          // 循环遍历后得到除数

	// 以下算法是一个朴素的除法算法， 就是把除数从大往小扩充，和被除数作比较。
	// 例：如果扩充了左移位3位后比a小，说明a除以b的第三位应该要被置1；
	for (i = MAX - j - 1; i >= 0; i--) {
		tempDiv = tempB;
		tempDiv.Move_left(i);
		if (!(tempDiv > tempA)) {
			result.num[i] = 1;
			tempA = tempA - tempDiv;
		}
	}
	return result;
}

Big_Int operator%(Big_Int a, Big_Int b)
{
	Big_Int result = Big_Int(0);
	result = a - (a / b) * b;    //被除数-除数*取整的除数=余数
	return result;
}

bool operator>(Big_Int a, Big_Int b)
{
	bool greater = 0;
	int i;
	if (a.sign == 0 && b.sign == 1) {     //符号相异，判断是否有全0
		greater = true;
		bool AllZero = true;      //判断是否全0
		for (i = 0; i < MAX; i++) {
			if (a[i] != 0 || b[i] != 0) {
				AllZero = false;
			}
		}
		if (AllZero) {
			greater = false;
		}
	}
	else {
		if (a.sign == 1 && b.sign == 0) {     //符号相异，判断是否有全0
			greater = false;
			bool AllZero = true;
			for (i = 0; i < MAX; i++) {
				if (a[i] != 0 || b[i] != 0) {
					AllZero = false;
				}
			}
			if (AllZero) {
				greater = false;
			}
		}
		else {
			if (a.sign == 0 && b.sign == 0) {    //符号相同，且都为正数
				for (i = MAX - 1; i >= 0; i--) {
					if (a[i] == 1 && b[i] == 0) {
						greater = true;
						break;
					}
					if (a[i] == 0 && b[i] == 1) {
						greater = false;
						break;
					}
				}
			}
			else {                             //符号相同，且都为负数
				for (i = MAX - 1; i >= 0; i--) {
					if (a[i] == 1 && b[i] == 0) {
						greater = false;
						break;
					}
					if (a[i] == 0 && b[i] == 1) {
						greater = true;
						break;
					}
				}
			}
		}
	}
	return greater;
}

bool operator==(Big_Int a, Big_Int b)
{
	int i;
	bool equal = true;
	if (a.sign != b.sign) {
		equal = false;
	}
	for (i = 0; i < MAX; i++) {
		if (a[i] != b[i]) {
			equal = false;
			break;
		}
	}
	return equal;
}

bool operator!=(Big_Int a, Big_Int b)
{
	int i;
	if (a.sign != b.sign) {
		return true;
	}
	for (i = 0; i < MAX; i++) {
		if (a[i] != b[i]) {
			return true;
		}
	}
	return false;
}



// 同余运算，实现的是a*b(mod c)
// 乘法同前，只是在每一步的处理后减去比c大的部分完成取模
Big_Int Big_Int::Mod(Big_Int a, Big_Int b, Big_Int c)
{
	Big_Int result = Big_Int(0);
	int i;
	for (i = 0; i < MAX; i++) {
		if (b[i] == 1) {
			result = result + a;
			while (result > c)
				result = result - c;
		}
		a.Move_left(1);
		while (a > c)
			a = a - c;
	}
	if (a.sign == b.sign) {
		result.sign = 0;
	}
	else {
		result.sign = 1;
	}
	result.Fix_output();
	return result;
}

// 乘指数后，得到对y的模数，即 result=（*this）^x (mod y)
Big_Int Big_Int::Exp(Big_Int x, Big_Int y)
{
	Big_Int result(1);
	int i = MAX - 1;
	while (!x[i]) {
		i--;
	}           //得到x的最高位
	int j;
	for (j = i; j >= 0; j--) {
		result = Mod(result, result, y);
		if (x[j]) {
			result = Mod(result, (*this), y);
		}
	}
	result.Fix_output();
	return result;
}

// 求对x的逆元，即result*this=1(mod x)
Big_Int Big_Int::Inverse(Big_Int x)
{
	Big_Int ZERO(0), ONE(1);
	Big_Int x1 = ONE, x2 = ZERO, x3 = x;
	Big_Int y1 = ZERO, y2 = ONE, y3 = (*this);
	Big_Int t1 = ZERO, t2 = ZERO, t3 = ZERO;
	if (y3 == ONE) {
		return ONE;
	}
	Big_Int q = ZERO;
	Big_Int g = ZERO;
	do {
		q = x3 / y3;
		t1 = x1 - q * y1;
		t2 = x2 - q * y2;
		t3 = x3 - q * y3;
		x1 = y1;
		x2 = y2;
		x3 = y3;
		y1 = t1;
		y2 = t2;
		y3 = t3;
	} while (!(y3 == ONE));
	g = y2;
	if (!(g > ZERO))
		g = x + g;
	g.Fix_output();
	return g;
}



//Miller-Rabin素数检测
bool Big_Int::Primer(int primer) {
	//cout << 1;
	int s = 0;
	Big_Int temp = (*this), ONE(1), ZERO(0), THREE(3), TWO(2);
	temp = temp - ONE;
	while (temp[0] == 0) {
		temp.Move_right(1);
		s++;
		//cout << 1;
	}
	//srand((unsigned)time(0));
	Big_Int a = (*this) - ONE;
	Big_Int b = ZERO;

	while (primer--) {
		b.GeneRandom(BIT / 32);
		Big_Int c = (*this) - THREE;
		b = b % c;
		b = b + TWO;
		Big_Int y = b.Exp(temp, (*this));
		if (y == ONE || y == a) {
			return true;
		}
		for (int j = 1; j <= s - 1 && y != a; j++) {
			y.Exp(TWO, (*this));
			if (y == ONE) {
				return false;
			}
		}
		if (y != a)
			return false;
	}
	return true;
}





void Big_Int::Fix_output() {
	if (this->sign == 1) {
		cout << '-';
	}
	char result[MAX];
	int i;
	for (i = MAX - 1; i >= 0; i--) {
		if ((*this)[i] == 1) {
			break;
		}
	} //得到该二进制数的最高位
	i++;
	int index;
	int length = 0;
	// 把二进制数的位数长度变成4的整数倍，便于下面的十六进制输出
	switch (i % 4) {
	case 1:
		length = i + 3;
		break;
	case 2:
		length = i + 2;
		break;
	case 3:
		length = i + 1;
		break;
	case 0:
		length = i;
		break;
	}
	for (index = 0; index < length; index = index + 4) {
		if ((*this)[index] == 0 && (*this)[index + 1] == 0 && (*this)[index + 2] == 0 && (*this)[index + 3] == 0) {
			result[index / 4] = '0';
		}
		if ((*this)[index] == 1 && (*this)[index + 1] == 0 && (*this)[index + 2] == 0 && (*this)[index + 3] == 0) {
			result[index / 4] = '1';
		}
		if ((*this)[index] == 0 && (*this)[index + 1] == 1 && (*this)[index + 2] == 0 && (*this)[index + 3] == 0) {
			result[index / 4] = '2';
		}
		if ((*this)[index] == 1 && (*this)[index + 1] == 1 && (*this)[index + 2] == 0 && (*this)[index + 3] == 0) {
			result[index / 4] = '3';
		}
		if ((*this)[index] == 0 && (*this)[index + 1] == 0 && (*this)[index + 2] == 1 && (*this)[index + 3] == 0) {
			result[index / 4] = '4';
		}
		if ((*this)[index] == 1 && (*this)[index + 1] == 0 && (*this)[index + 2] == 1 && (*this)[index + 3] == 0) {
			result[index / 4] = '5';
		}
		if ((*this)[index] == 0 && (*this)[index + 1] == 1 && (*this)[index + 2] == 1 && (*this)[index + 3] == 0) {
			result[index / 4] = '6';
		}
		if ((*this)[index] == 1 && (*this)[index + 1] == 1 && (*this)[index + 2] == 1 && (*this)[index + 3] == 0) {
			result[index / 4] = '7';
		}
		if ((*this)[index] == 0 && (*this)[index + 1] == 0 && (*this)[index + 2] == 0 && (*this)[index + 3] == 1) {
			result[index / 4] = '8';
		}
		if ((*this)[index] == 1 && (*this)[index + 1] == 0 && (*this)[index + 2] == 0 && (*this)[index + 3] == 1) {
			result[index / 4] = '9';
		}
		if ((*this)[index] == 0 && (*this)[index + 1] == 1 && (*this)[index + 2] == 0 && (*this)[index + 3] == 1) {
			result[index / 4] = 'A';
		}
		if ((*this)[index] == 1 && (*this)[index + 1] == 1 && (*this)[index + 2] == 0 && (*this)[index + 3] == 1) {
			result[index / 4] = 'B';
		}
		if ((*this)[index] == 0 && (*this)[index + 1] == 0 && (*this)[index + 2] == 1 && (*this)[index + 3] == 1) {
			result[index / 4] = 'C';
		}
		if ((*this)[index] == 1 && (*this)[index + 1] == 0 && (*this)[index + 2] == 1 && (*this)[index + 3] == 1) {
			result[index / 4] = 'D';
		}
		if ((*this)[index] == 0 && (*this)[index + 1] == 1 && (*this)[index + 2] == 1 && (*this)[index + 3] == 1) {
			result[index / 4] = 'E';
		}
		if ((*this)[index] == 1 && (*this)[index + 1] == 1 && (*this)[index + 2] == 1 && (*this)[index + 3] == 1) {
			result[index / 4] = 'F';
		}
	}
	result[index / 4] = '\0';
	output = result;
}


//进行输出
void Big_Int::Print()
{
	cout << output << endl;
}
