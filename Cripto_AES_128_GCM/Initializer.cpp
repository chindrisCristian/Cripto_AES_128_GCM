#include "Initializer.h"
#include<string>
#include<iostream>

using namespace std;

#pragma region Constructor and destructor

Initializer::Initializer(int arg_num, char ** arg_values)
{
	string inputFile, outputFile, keyFile, ivFile, aadFile;
	for (int i = 0; i < arg_num; i++)
	{
		if (!strcmp(arg_values[i], "-in"))
			inputFile = arg_values[i + 1];
		if (!strcmp(arg_values[i], "-out"))
			outputFile = arg_values[i + 1];
		if (!strcmp(arg_values[i], "-key"))
			keyFile = arg_values[i + 1];
		if (!strcmp(arg_values[i], "-iv"))
			ivFile = arg_values[i + 1];
		if (!strcmp(arg_values[i], "-aad"))
			aadFile = arg_values[i + 1];
	}

	SetInputFile(inputFile);
	SetOutputFile(outputFile);
	SetKeyValue(keyFile);
	SetIVValue(ivFile);
	SetAADFile(aadFile);
}

Initializer::~Initializer()
{
	if(mTMPfile)
		remove("in.tmp");
}

#pragma endregion


#pragma region Private methods

void Initializer::SetInputFile(std::string inputFile)
{
	mTMPfile = false;
	if (inputFile.empty())
	{
		cout << "Introduceti textul pe care doriti sa il criptati: ";
		string plainText;
		cin >> plainText;
		std::fstream tmp;
		tmp.open("in.tmp", ios::out);
		tmp << plainText;
		tmp.close();
		mInputFile = "in.tmp";
		mTMPfile = true;
	}
	else
	{
		mInputFile = inputFile;
	}
}

void Initializer::SetOutputFile(std::string outputFile)
{
	if (outputFile.empty())
	{
		cout << "Nu s-a introdus nici un fisier de iesire. Datele de iesire vor fi redirectate in fisierul data.enc";
		mOutputFile = "data.enc";
	}
	else
	{
		mOutputFile = outputFile;
	}
}

void Initializer::SetKeyValue(std::string keyFile)
{
	if (keyFile.empty())
	{
		cout << "Introduceti cheia de 128 biti: ";
		cin >> mKey;
	}
	else
	{
		ifstream key;
		key.open(keyFile);
		key >> mKey;
		key.close();
	}
}

void Initializer::SetIVValue(std::string ivFile)
{
	if (ivFile.empty())
	{
		cout << "Introduceti IV de 128 biti: ";
		cin >> mIV;
	}
	else
	{
		ifstream iv;
		iv.open(ivFile);
		iv >> mIV;
		iv.close();
	}
}

void Initializer::SetAADFile(std::string aadFile)
{
	if (aadFile.empty())
	{
		cout << "Nu s-a introdus AAD.";
	}
	else
	{
		mAADFile = aadFile;
	}
}

#pragma endregion

#pragma region Public methods

byte * Initializer::GetKey()
{
	return mKey;
}

byte * Initializer::GetIV()
{
	return mIV;
}

#pragma endregion
