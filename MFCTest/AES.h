#pragma once
#define uchar unsigned char

void CloseFile();
int ZeroPadding(uchar str[], int Length);
void InitConsoleWindow();
void Encryption(uchar m_IptString[], uchar m_OptEncry[], uchar key[]);
void Decryption(uchar m_IptEncry[], uchar m_OptString[], uchar key2[]);
