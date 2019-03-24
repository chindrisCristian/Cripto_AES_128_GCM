#pragma once
#include<fstream>

#define	STD_BLOCK_SIZE	16

using byte = unsigned char;

class Initializer
{
private:
	std::string				mInputFile;
	std::string				mOutputFile;
	std::string				mAADFile;
	bool					mTMPfile;
	byte					mKey[STD_BLOCK_SIZE];
	byte					mIV[STD_BLOCK_SIZE];

public:
	Initializer(int arg_num, char ** arg_values);
	~Initializer();

	std::string				GetInputFile() {
		return mInputFile;
	}
	std::string				GetOutputFile() {
		return mOutputFile;
	}
	std::string				GetAADFile() {
		return mAADFile;
	}

	byte *					GetKey();
	byte *					GetIV();

private:
	void					SetInputFile(std::string inputFile);
	void					SetOutputFile(std::string outputFile);
	void					SetKeyValue(std::string keyFile);
	void					SetIVValue(std::string ivFile);
	void					SetAADFile(std::string aadFile);
};

