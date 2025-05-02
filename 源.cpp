#include<iostream>
#include<ctime>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<iomanip>
extern "C" unsigned long long* g256_inverse(unsigned long long*);
#define ull unsigned long long
using namespace std;
const unsigned char S_Table[16][16] =
{
	0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
	0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
	0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
	0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
	0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
	0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
	0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
	0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
	0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
	0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
	0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
	0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
	0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
	0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
	0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
	0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};
const unsigned int Rcon[11] = { 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36 };
ull bs_plaintext[128];
ull bs_extendkey[15][128];
ull bs_ciphertext[128];
int ans1[30] = { 0x69,0xc4,0xe0,0xd8,0x6a,0x7b,0x04,0x30,0xd8,0xcd,0xb7,0x80,0x70,0xb4,0xc5,0x5a };
int ans2[30] = { 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f };
clock_t be, en;
double last = 0;
void display_bs()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				cout << (bs_plaintext[i * 8 + j * 32 + k] & 1);
			}
		}
	}
	cout << endl;
}
void show_ans1()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 7; j >= 0; j--)
		{
			cout << ((ans1[i] >> j) & 1);
		}
	}
	cout << endl;
}
void show_ans2()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 7; j >= 0; j--)
		{
			cout << ((ans2[i] >> j) & 1);
		}
	}
	cout << endl;
}
void show_round_key(int round)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				cout << ((bs_extendkey[round][i * 8 + j * 32 + k]) & 1);
			}
		}
	}
}
int trans(int x)
{
	return 7 - x;
}
int Key_S_Substitution(unsigned char(*ExtendKeyArray)[44], unsigned int nCol)
{
	int ret = 0;
	for (int i = 0; i < 4; i++)
	{
		ExtendKeyArray[i][nCol] = S_Table[(ExtendKeyArray[i][nCol]) >> 4][(ExtendKeyArray[i][nCol]) & 0x0F];
	}
	return ret;
}
int G_Function(unsigned char(*ExtendKeyArray)[44], unsigned int nCol)
{
	int ret = 0;
	for (int i = 0; i < 4; i++)
	{
		ExtendKeyArray[i][nCol] = ExtendKeyArray[(i + 1) % 4][nCol - 1];
	}
	Key_S_Substitution(ExtendKeyArray, nCol);
	ExtendKeyArray[0][nCol] ^= Rcon[nCol / 4];
	return ret;
}
int CalculateExtendKeyArray(const unsigned char(*PasswordArray)[4], unsigned char(*ExtendKeyArray)[44])
{
	int ret = 0;
	for (int i = 0; i < 16; i++)
	{
		ExtendKeyArray[i & 0x03][i >> 2] = PasswordArray[i & 0x03][i >> 2];
	}
	for (int i = 1; i < 11; i++)
	{
		G_Function(ExtendKeyArray, 4 * i);
		for (int k = 0; k < 4; k++)
		{
			ExtendKeyArray[k][4 * i] = ExtendKeyArray[k][4 * i] ^ ExtendKeyArray[k][4 * (i - 1)];
		}
		for (int j = 1; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				ExtendKeyArray[k][4 * i + j] = ExtendKeyArray[k][4 * i + j - 1] ^ ExtendKeyArray[k][4 * (i - 1) + j];
			}
		}
	}
	return ret;
}
int StringToArray(const unsigned char* String, unsigned char(*Array)[4])
{
	int ret = 0;
	for (int i = 0; i < 16; i++)
	{
		Array[i & 0x03][i >> 2] = String[i];
	}
	return ret;
}
void addroundkey(int round)
{
	for (int i = 0; i < 128; i++)
	{
		bs_plaintext[i] ^= bs_extendkey[round][i];
	}
}
void sbox(ull array[])
{
	ull *b = g256_inverse(array);
	for (int i = 0; i < 8; i++)
	{
		array[i] = b[i];
	}
}
void shiftrow()
{
	ull temp[40] = { 0 };
	//第二行
	for (int i = 32; i <= 40 - 1; i++)
	{
		temp[i - 32] = bs_plaintext[i];
	}
	for (int i = 32 + 8; i <= 63; i++)
	{
		bs_plaintext[i - 8] = bs_plaintext[i];
	}
	for (int i = 56; i <= 63; i++)
	{
		bs_plaintext[i] = temp[i - 56];
	}
	//第三行
	for (int i = 64; i <= 64 + 2 * 8 - 1; i++)
	{
		temp[i - 64] = bs_plaintext[i];
	}
	for (int i = 80; i <= 95; i++)
	{
		bs_plaintext[i - 16] = bs_plaintext[i];
	}
	for (int i = 80; i <= 95; i++)
	{
		bs_plaintext[i] = temp[i - 80];
	}
	//第四行
	for (int i = 120; i <= 127; i++)
	{
		temp[i - 120] = bs_plaintext[i];
	}
	for (int i = 119; i >= 96; i--)
	{
		bs_plaintext[i + 8] = bs_plaintext[i];
	}
	for (int i = 96; i <= 103; i++)
	{
		bs_plaintext[i] = temp[i - 96];
	}
}
ull bs_temp[130] = { 0 };
void mix_sol(int row, int col)
{
	int row1 = row, row2 = (row + 1) % 4, row3 = (row + 2) % 4, row4 = (row + 3) % 4;
	bs_temp[row * 32 + col * 8 + trans(0)] = bs_plaintext[row1 * 32 + col * 8 + trans(7)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(0)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(7)] ^ bs_plaintext[row3 * 32 + col * 8 + trans(0)] ^ bs_plaintext[row4 * 32 + col * 8 + trans(0)];
	bs_temp[row * 32 + col * 8 + trans(1)] = bs_plaintext[row1 * 32 + col * 8 + trans(0)] ^ bs_plaintext[row1 * 32 + col * 8 + trans(7)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(0)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(1)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(7)] ^ bs_plaintext[row3 * 32 + col * 8 + trans(1)] ^ bs_plaintext[row4 * 32 + col * 8 + trans(1)];
	bs_temp[row * 32 + col * 8 + trans(2)] = bs_plaintext[row1 * 32 + col * 8 + trans(1)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(1)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(2)] ^ bs_plaintext[row3 * 32 + col * 8 + trans(2)] ^ bs_plaintext[row4 * 32 + col * 8 + trans(2)];
	bs_temp[row * 32 + col * 8 + trans(3)] = bs_plaintext[row1 * 32 + col * 8 + trans(2)] ^ bs_plaintext[row1 * 32 + col * 8 + trans(7)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(2)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(3)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(7)] ^ bs_plaintext[row3 * 32 + col * 8 + trans(3)] ^ bs_plaintext[row4 * 32 + col * 8 + trans(3)];
	bs_temp[row * 32 + col * 8 + trans(4)] = bs_plaintext[row1 * 32 + col * 8 + trans(3)] ^ bs_plaintext[row1 * 32 + col * 8 + trans(7)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(3)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(4)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(7)] ^ bs_plaintext[row3 * 32 + col * 8 + trans(4)] ^ bs_plaintext[row4 * 32 + col * 8 + trans(4)];
	bs_temp[row * 32 + col * 8 + trans(5)] = bs_plaintext[row1 * 32 + col * 8 + trans(4)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(4)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(5)] ^ bs_plaintext[row3 * 32 + col * 8 + trans(5)] ^ bs_plaintext[row4 * 32 + col * 8 + trans(5)];
	bs_temp[row * 32 + col * 8 + trans(6)] = bs_plaintext[row1 * 32 + col * 8 + trans(5)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(5)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(6)] ^ bs_plaintext[row3 * 32 + col * 8 + trans(6)] ^ bs_plaintext[row4 * 32 + col * 8 + trans(6)];
	bs_temp[row * 32 + col * 8 + trans(7)] = bs_plaintext[row1 * 32 + col * 8 + trans(6)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(6)] ^ bs_plaintext[row2 * 32 + col * 8 + trans(7)] ^ bs_plaintext[row3 * 32 + col * 8 + trans(7)] ^ bs_plaintext[row4 * 32 + col * 8 + trans(7)];
}
void mixcolum()
{
	memset(bs_temp, 0, sizeof(bs_temp));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mix_sol(i, j);
		}
	}
	for (int i = 0; i < 128; i++)
	{
		bs_plaintext[i] = bs_temp[i];
	}
}
int AES_EnCryption(const unsigned char* PlainText, const unsigned char* PassWord, unsigned char* CipherText)
{
	int ret = 0, cnt = -1;
	unsigned char PlainArray[4][4];			
	unsigned char PasswordArray[4][4];		
	unsigned char ExtendKeyArray[4][44];	
	memset(PlainArray, 0, 16);
	memset(PasswordArray, 0, 16);
	memset(ExtendKeyArray, 0, 176);
	StringToArray(PlainText, PlainArray);
	StringToArray(PassWord, PasswordArray);
	CalculateExtendKeyArray(PasswordArray, ExtendKeyArray);
	for (int j = 0; j < 44; j++)
	{
		if (j % 4 == 0)cnt++;
		int col = j % 4;
		for (int i = 0; i < 4; i++)
		{
			for (int k = 7; k >= 0; k--)
			{
				if (((ExtendKeyArray[i][j] >> k) & 1))
				{
					bs_extendkey[cnt][i * 32 + col * 8 + (7 - k)] = 0xFFFFFFFFFFFFFFFF;
				}
				else
				{
					bs_extendkey[cnt][i * 32 + col * 8 + (7 - k)] = 0;
				}
			}
		}
	}
	//轮密钥bitslice化
	addroundkey(0);
	for (int i = 1; i < 10; i++)
	{
		be = clock();
		for (int j = 0; j < 16; j++)
		{
			sbox(&bs_plaintext[j * 8]);
		}
		en = clock();
		last += ((double)(en - be)) / CLK_TCK;
		shiftrow();	
		mixcolum();
		addroundkey(i);
	}
	for (int j = 0; j < 16; j++)
	{
		sbox(&bs_plaintext[j * 8]);
	}
	shiftrow();
	addroundkey(10);
	return ret;
}
void transform(unsigned char array[][17])
{
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			ull x = array[i][j];
			int row = j % 4, col = j / 4;
			for (int k = 7; k >= 0; k--)
			{
				ull y = (x >> k) & 1;
				bs_plaintext[row * 32 + col * 8 + trans(k)] |= (y << (ull)(i));
			}
		}
	}
}
void retrans(unsigned char array[][17])
{
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			int row = j % 4, col = j / 4;
			unsigned char temp = 0;
			for (int k = 0; k < 8; k++)
			{
				ull x = bs_plaintext[row * 32 + col * 8 + trans(k)];
				x = (x >> i) & 1;
				x <<= k;
				temp |= x;
			}
			array[i][col * 4 + row] = temp;
		}
	}
}
signed main()
{
	unsigned char plaintext[17] = {0x00,0x11,0x22,0x33,0x56,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
	unsigned char password[17] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
	unsigned char CipherText[17] = { 0 };
	unsigned char new_plaintext[70][17] = { 0 };
	unsigned char re_plaintext[70][17] = { 0 };
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			new_plaintext[i][j] = plaintext[j];
		}
	}
	clock_t start, stop;    //clock_t是clock()函数返回值的变量类型
	double duration;    // 记录被测函数运行时间，以s为单位
	start = clock();
	transform(new_plaintext);
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	double mingdura = duration;
	ull temp[130] = { 0 };
	for (int i = 0; i < 128; i++)
	{
		temp[i] = bs_plaintext[i];
	}
	cout << "64组明文为：" << endl;
	for (int i = 0; i < 64; i++)
	{
		if (i != 0 && i % 4 == 0)cout << endl;
		for (int j = 0; j < 16; j++)
		{
			ull x = new_plaintext[i][j];
			ull y = x >> 4;
			x = x & 0xF;
			cout << hex << y << hex << x;
		}
		cout << " ";
	}
	cout << endl;
	last = 0;
	for (int i = 1; i <= 10000; i++)
	{
		for (int j = 0; j < 128; j++)
		{
			bs_plaintext[j] = temp[j];
		}
		AES_EnCryption(plaintext, password, CipherText);
	}
	retrans(re_plaintext);
	cout << "64组密文为：" << endl;
	for (int i = 0; i < 64; i++)
	{
		if (i != 0 && i % 4 == 0)cout << endl;
		for (int j = 0; j < 16; j++)
		{
			ull x = re_plaintext[i][j];
			ull y = x >> 4;
			x = x & 0xF;
			cout << hex << y << hex << x;
		}
		cout << " ";
	}
	cout << endl;
	stop = clock();
	//cout << "S盒执行时间：" << last << endl;
	duration = ((double)(stop - start)) / CLK_TCK;  //计算运行时间
	cout << "加密总时间: " << duration << "秒" << endl;
	cout << "其中,明文bitslice化时间：" << fixed << setprecision(14) << mingdura << "秒," << "S盒执行时间：" << last << "秒" << endl;
}