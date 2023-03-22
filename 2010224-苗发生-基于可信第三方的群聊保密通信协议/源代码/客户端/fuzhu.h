#pragma once
#include<iostream>
#include"RSA.h"
#include"AES.h"
#include<array>
using namespace std;
int hexToInt(string hex_str) {
	int r = 0;
	for (int i = 0; i < hex_str.length(); i++) {
		r *= 16;
		if (hex_str[i] >= '0' && hex_str[i] <= '9') {
			r += hex_str[i] - 48;
		}
		else if (hex_str[i] >= 'A' && hex_str[i] <= 'Z') {
			r += hex_str[i] - 55;
		}
		else
			r += hex_str[i] - 87;

	}
	return r;
}
string intToHex(int dec_int) {
	string r;
	while (dec_int) {
		int t = dec_int % 16;
		if (t < 10)
			r = char(t + 48) + r;
		else
			r = char(t + 55) + r;
		dec_int /= 16;
	}
	while (r.length() < 2) {
		r = '0' + r;
	}
	return r;
}


char* timestamp()
{
	time_t timep;
	time(&timep);
	char tmp[256];
	strftime(tmp, sizeof(tmp), "%H:%M:%S", localtime(&timep));
	return tmp;
}
Big_Int p("B0FA72FBB98B313503F335F2A0898DFB"), q("FD3D2105D2DD83B6B17F90F049694643");
Big_Int one(1);
Big_Int n = p * q, phi = (p - one) * (q - one);
//n.Print();
Big_Int e(10001);
Big_Int d = e.Inverse(phi);
Big_Int another_n("66F2BD4FB36D3466BC87D9D46C59698884BD256AD5F876ECC54E9B1D14E05F99");
string sN1, sN2;
array<int, 16> aes_key = { 11,11,11,11,11,11,11,51,11,11,11,11,22,22,22,22 };
array<int, 16> InitVector = { 0,1,0,1,0,1,0,1,0,1,1,0,0,1,0,1 };
array<int, 16> CBC_vector = InitVector;
array<array<int, 16>, 11> keySchedual = Gen_subkeys(aes_key);