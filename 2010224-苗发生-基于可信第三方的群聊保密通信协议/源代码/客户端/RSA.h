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
	bool sign;              //�����洢�ô������ķ���
	Big_Int(unsigned int in);        //ʮ����ת�����ƵĴ洢  
	Big_Int(string in);
	void GeneRandom(int n); //����������������n��ʾ�������λ��
	void Print();               //��ʮ������������
	bool operator[](int i) { return num[i]; };
	void Move_left(int i);
	void Move_right(int i);
	Big_Int ABS();
	bool Primer(int k);
	string output;
	void Fix_output();


	//�����ǻ��ڻ�������ʵ�ֵ�һЩ�����ӵ�����
	Big_Int Mod(Big_Int a, Big_Int b, Big_Int c);          //ȡ��
	Big_Int Exp(Big_Int x, Big_Int y);                     //��ָ���ˣ���ȡģ����result=��*this��^x (mod y)
	Big_Int Inverse(Big_Int x);                                //��x��y����Ԫ����result* x = 1(mod y)
	//����Ϊ��Ԫ�����Ķ��壬����һЩ�������������
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

Big_Int::Big_Int(string in)        // ʮ������ת�����ƴ洢���ұ�Ϊ���λ��
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
	num[n - 1] = 1;		//��λ��Ϊ0��֤λ����ȷ
	num[0] = 1;		//ĩλ��Ϊ�㱣֤������
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
	Big_Int result = Big_Int(0);      // ������Ϊ����ֵ
	int i;
	bool temp = 0;       // temp��ʾ��λ�Ƿ��λ       
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
						temp = 1;        //��λΪ1
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
	bool temp = 0;      //��ʾ֮ǰ��λ�Ľ�λ
	if (a.sign == b.sign) {
		if (!(b.ABS() > a.ABS()))     //����û��д��b.ABS()<=a.ABS()����Ϊ����ֻʵ���ˣ���>����Ԫ����ʵ�֣�δʵ��<=�ı�д
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

	Big_Int tempDiv = tempB;          // ѭ��������õ�����

	// �����㷨��һ�����صĳ����㷨�� ���ǰѳ����Ӵ���С���䣬�ͱ��������Ƚϡ�
	// �����������������λ3λ���aС��˵��a����b�ĵ���λӦ��Ҫ����1��
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
	result = a - (a / b) * b;    //������-����*ȡ���ĳ���=����
	return result;
}

bool operator>(Big_Int a, Big_Int b)
{
	bool greater = 0;
	int i;
	if (a.sign == 0 && b.sign == 1) {     //�������죬�ж��Ƿ���ȫ0
		greater = true;
		bool AllZero = true;      //�ж��Ƿ�ȫ0
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
		if (a.sign == 1 && b.sign == 0) {     //�������죬�ж��Ƿ���ȫ0
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
			if (a.sign == 0 && b.sign == 0) {    //������ͬ���Ҷ�Ϊ����
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
			else {                             //������ͬ���Ҷ�Ϊ����
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



// ͬ�����㣬ʵ�ֵ���a*b(mod c)
// �˷�ͬǰ��ֻ����ÿһ���Ĵ�����ȥ��c��Ĳ������ȡģ
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

// ��ָ���󣬵õ���y��ģ������ result=��*this��^x (mod y)
Big_Int Big_Int::Exp(Big_Int x, Big_Int y)
{
	Big_Int result(1);
	int i = MAX - 1;
	while (!x[i]) {
		i--;
	}           //�õ�x�����λ
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

// ���x����Ԫ����result*this=1(mod x)
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



//Miller-Rabin�������
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
	} //�õ��ö������������λ
	i++;
	int index;
	int length = 0;
	// �Ѷ���������λ�����ȱ��4�������������������ʮ���������
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


//�������
void Big_Int::Print()
{
	cout << output << endl;
}
