#pragma once
#pragma once
#include <iostream>
#include <array>
#include <ctime>
#include <string>
#include <cstdlib>
using namespace std;

array<array<int, 16>, 2> input = { { { 0x00, 0x01, 0x00, 0x01, 0x01, 0xa1, 0x98, 0xaf, 0xda, 0x78, 0x17, 0x34, 0x86, 0x15, 0x35, 0x66 },
                                     { 0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34 } } };
array<array<int, 16>, 2> key = { { { 0x00, 0x01, 0x20, 0x01, 0x71, 0x01, 0x98, 0xae, 0xda, 0x79, 0x17, 0x14, 0x60, 0x15, 0x35, 0x94 },
                                   { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c } } };
array<array<int, 4>, 10> RCON = { {{0x01, 0x00, 0x00, 0x00},
                                   {0x02, 0x00, 0x00, 0x00},
                                   {0x04, 0x00, 0x00, 0x00},
                                   {0x08, 0x00, 0x00, 0x00},
                                   {0x10, 0x00, 0x00, 0x00},
                                   {0x20, 0x00, 0x00, 0x00},
                                   {0x40, 0x00, 0x00, 0x00},
                                   {0x80, 0x00, 0x00, 0x00},
                                   {0x1b, 0x00, 0x00, 0x00},
                                   {0x36, 0x00, 0x00, 0x00}} };
int S_box[16][16] = { {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
                     {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
                     {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
                     {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
                     {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
                     {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
                     {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
                     {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
                     {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
                     {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
                     {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
                     {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
                     {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
                     {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
                     {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
                     {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16} };
int S_box_inv[16][16] = { {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38,0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
                        {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},
                        {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d,0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
                        {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2,0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
                        {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
                        {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda,0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
                        {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a,0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
                        {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
                        {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea,0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
                        {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85,0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
                        {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
                        {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20,0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
                        {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31,0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
                        {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
                        {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0,0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
                        {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26,0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d} };
void Print(const array<int, 16>& e) {
    // Print a 1d version of the state
    printf("%.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x\n",
        e[0], e[1], e[2], e[3], e[4], e[5], e[6], e[7], e[8], e[9], e[10], e[11], e[12], e[13], e[14], e[15]);
}
// 十进制转二进制函数
string Dec_to_Bin(int decimal)
{
    string binary;
    while (decimal != 0) {
        binary = (decimal % 2 == 0 ? "0" : "1") + binary;
        decimal = decimal / 2;
    }
    while (binary.length() < 8) {
        binary = "0" + binary;
    }
    return binary;
}
// 二进制转十进制函数
int Bin_to_Dec(string Bin)
{
    int decimal = 0;
    int counter = 0;
    int size = Bin.length();
    for (int i = size - 1; i >= 0; i--)
    {
        if (Bin[i] == '1') {
            decimal += pow(2, counter);
        }
        counter++;
    }
    return decimal;
}
array<array<int, 4>, 4> Input_tran(const array<int, 16>& input) {
    // 将一维明文数据转换为矩阵明文数据
    array<array<int, 4>, 4> state = {};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[i][j] = input[i + 4 * j];
        }
    }
    return state;
}

array<int, 16> Output_tran(const array<array<int, 4>, 4>& state) {
    // 将矩阵数据转换为一维数据
    array<int, 16> output = {};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            output[i + 4 * j] = state[i][j];
        }
    }
    return output;
}
int S_byte(int& byte) {
    // S盒代换
    int x = byte >> 4; // 取高位为x值
    int y = byte & 0x0f; // 取地位为y值
    return S_box[x][y];

}
int Inverse_S_Byte(int& byte) {
    // S盒代换逆操作
    int x = byte >> 4;
    int y = byte & 0x0f;
    return S_box_inv[x][y];
}
auto byteSub(const array<array<int, 4>, 4>& state) {
    // 字节代换函数
    array<array<int, 4>, 4> result = {};
    int byte;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            byte = state[i][j];
            result[i][j] = S_byte(byte);
        }
    }
    return result;
}
auto Inverse_ByteSub(const array<array<int, 4>, 4>& state) {
    //字节代换逆变换
    array<array<int, 4>, 4> result = {};
    int byte;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            byte = state[i][j];
            result[i][j] = Inverse_S_Byte(byte);
        }
    }
    return result;
}

array<int, 4> shiftRow(const array<int, 4>& row, const int shift) {
    // 单个行移位函数
    array<int, 4> result = {};
    result = row;
    int t = shift;
    while (t > 0) {
        int temp = result[0];
        for (int i = 0; i < 3; i++) {
            result[i] = result[i + 1];
        }
        result[3] = temp;
        t--;
    }
    return result;
}
auto shiftRows(const array<array<int, 4>, 4>& state) {
    //整体行移位函数
    array<array<int, 4>, 4> result = {};
    for (int i = 0; i < 4; i++) {
        result[i] = shiftRow(state[i], i);
    }
    return result;
}
array<int, 4> Inverse_ShiftRow(const array<int, 4>& row, const int shift) {
    // 单个行移位逆变换
    array<int, 4> result = {};
    result = row;
    int t = shift;
    while (t > 0) {
        int temp = result[3];
        for (int i = 3; i > 0; i--) {
            result[i] = result[i - 1];
        }
        result[0] = temp;
        t--;
    }
    return result;
}
auto Inverse_ShiftRows(const array<array<int, 4>, 4>& state) {
    //整体行移位逆变换
    array<array<int, 4>, 4> result = {};
    for (int i = 0; i < 4; i++) {
        result[i] = Inverse_ShiftRow(state[i], i);
    }
    return result;
}


int Multi02(const int v) {
    // 一个字节与02在GF（2^8）上的乘法
    int s = v << 1;
    if (v & 0x80) {
        s &= 0xff;
        s = s ^ 0x1b;
    }
    return s;
}


array<int, 4> Four_byte_XOR(const array<int, 4>& wordA, const array<int, 4>& wordB) {
    // 四字节之间的异或
    array<int, 4> result = {};
    for (int i = 0; i < 4; i++) {
        result[i] = wordA[i] ^ wordB[i];
    }
    return result;
}



int Multi03(int v) {
    // 一个字节与03在GF（2^8）上的乘法
    return Multi02(v) ^ v;
}
auto mixColumn(const array<int, 4>& stateColumn) {
    // 单个列混合
    array<int, 4> result = {};

    result[0] = Multi02(stateColumn[0]) ^ Multi03(stateColumn[1]) ^ stateColumn[2] ^ stateColumn[3];
    result[1] = Multi02(stateColumn[1]) ^ Multi03(stateColumn[2]) ^ stateColumn[3] ^ stateColumn[0];
    result[2] = Multi02(stateColumn[2]) ^ Multi03(stateColumn[3]) ^ stateColumn[0] ^ stateColumn[1];
    result[3] = Multi02(stateColumn[3]) ^ Multi03(stateColumn[0]) ^ stateColumn[1] ^ stateColumn[2];

    return result;
}
auto mixColumns(const array<array<int, 4>, 4>& state) {
    // 整体列混合
    array<array<int, 4>, 4> result = {};
    array<int, 4> column = {};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            column[j] = state[j][i];
        }
        column = mixColumn(column);
        for (int j = 0; j < 4; j++) {
            result[j][i] = column[j];
        }
    }
    return result;
}
auto Inverse_MixColumns(const array<array<int, 4>, 4>& state) {
    //列混合逆变换
    array<array<int, 4>, 4> result = {};

    result = mixColumns(state);
    result = mixColumns(result);
    result = mixColumns(result);

    return result;
}


auto addRoundKey(const array<array<int, 4>, 4>& state, const array<int, 16>& roundKey) {
    // 密钥加
    array<array<int, 4>, 4> result = {};
    array<array<int, 4>, 4> keyWords = {};

    keyWords = Input_tran(roundKey);
    for (int i = 0; i < 4; i++) {
        result[i] = Four_byte_XOR(state[i], keyWords[i]);
    }
    return result;
}

array<int, 4> subByte(const array<int, 4>& word) {
    //密钥编排中的SubByte函数
    array<int, 4> result = {};
    int byte;
    for (int i = 0; i < 4; i++) {
        byte = word[i];
        result[i] = S_byte(byte);
    }
    return result;
}
array<int, 4> rotByte(const array<int, 4>& word) {
    // 密钥编排中的RotByte函数
    array<int, 4> result = {};
    result = shiftRow(word, 1);
    return result;
}
array<array<int, 16>, 11> Gen_subkeys(const array<int, 16>& key) {
    // 密钥编排
    array<array<int, 16>, 11> keySchedule = {};
    array<array<int, 4>, 44> W = {};
    array<int, 4> temp = {};
    // 密钥扩展
    for (int i = 0; i < 4; i++) {
        W[i] = { key[4 * i], key[4 * i + 1], key[4 * i + 2], key[4 * i + 3] };
    }
    for (int i = 4; i < 44; i++) {
        temp = W[i - 1];
        if (i % 4 == 0) {
            temp = Four_byte_XOR(subByte(rotByte(temp)), RCON[i / 4 - 1]);
        }
        W[i] = Four_byte_XOR(W[i - 4], temp);
    }
    //轮密钥选取
    keySchedule[0] = key;
    for (int i = 1; i < 11; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                keySchedule[i][4 * j + k] = W[4 * i + j][k];
            }
        }
    }
    return keySchedule;
}


//将加密流程封装为Encryption函数
array<array<int, 4>, 4> Encryption(const array<array<int, 4>, 4>& block, const array<array<int, 16>, 11> keySchedual) {
    array<array<int, 4>, 4> state = block;
    // 初始密钥加
    state = addRoundKey(state, keySchedual[0]);
    //九轮迭代
    for (int i = 1; i < 10; i++) {
        state = byteSub(state);
        state = shiftRows(state);
        state = mixColumns(state);
        state = addRoundKey(state, keySchedual[i]);
    }
    //结尾轮
    state = byteSub(state);
    state = shiftRows(state);
    state = addRoundKey(state, keySchedual[10]);
    return state;
}

//将解密流程封装为Decryption函数
array<array<int, 4>, 4> Decryption(const array<array<int, 4>, 4>& block, const array<array<int, 16>, 11> keySchedual) {
    array<array<int, 4>, 4> state = {};
    state = block;
    //结尾轮逆变换
    state = addRoundKey(state, keySchedual[10]);
    state = Inverse_ShiftRows(state);
    state = Inverse_ByteSub(state);
    //逆序九轮迭代
    for (int i = 9; i > 0; i--) {
        state = addRoundKey(state, keySchedual[i]);
        state = Inverse_MixColumns(state);
        state = Inverse_ShiftRows(state);
        state = Inverse_ByteSub(state);
    }
    //结尾密钥加
    state = addRoundKey(state, keySchedual[0]);
    return state;
}
