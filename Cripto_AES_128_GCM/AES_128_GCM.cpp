#include "AES_128_GCM.h"
#include<iostream>


#pragma region Constructor and destructor

AES_128_GCM::AES_128_GCM()
{
	if (!(mCtx = EVP_CIPHER_CTX_new()))
	{
		std::cout << "Contextul nu a putut fi setat.";
		exit(1);
	}
}


AES_128_GCM::~AES_128_GCM()
{
	EVP_CIPHER_CTX_free(mCtx);
}

#pragma endregion

#pragma region Encryption methods

void AES_128_GCM::SetEncryptionDetails(byte * key, byte * iv)
{
	//Initialize the encryption operation.
	if (1 != EVP_EncryptInit(mCtx, EVP_aes_128_gcm(), NULL, NULL))
	{
		std::cout << "Nu s-a putut initializa operatia de criptare.";
		exit(2);
	}
	
	//Set IV lenght, not the default one.
	if (1 != EVP_CIPHER_CTX_ctrl(mCtx, EVP_CTRL_GCM_SET_IVLEN, STD_BLOCK_SIZE, NULL))
	{
		std::cout << "Nu s-a putut seta lungimea IV-ului pentru 128 de biti.";
		exit(3);
	}

	//Initialize key and IV.
	if (1 != EVP_EncryptInit(mCtx, NULL, key, iv))
	{
		std::cout << "Nu s-au putut initializa cheia si IV.";
		exit(4);
	}

}

void AES_128_GCM::ProvideAdditionalAuthDataEnc(std::string aadFile)
{
	std::ifstream aFile;
	aFile.open(aadFile);
	if (aFile.is_open())
	{
		int len;	//Not used, but needed in EVP_EncryptUpdate.
		byte * aad = new byte[STD_BLOCK_SIZE];
		int aadLength = 0;
		while (!aFile.eof())
		{
			aFile.read((char*)aad, STD_BLOCK_SIZE);
			aadLength = aFile.gcount();
			if (1 != EVP_EncryptUpdate(mCtx, NULL, &len, aad, aadLength))
			{
				std::cout << "Nu s-a putut adauga AAD.";
				exit(5);
			}
		}
	}
}

int AES_128_GCM::Encrypt(std::string input, std::string output, byte * tag)
{
	std::ifstream inputFile;
	std::ofstream outputFile;
	inputFile.open(input);
	outputFile.open(output);

	byte *data = new byte[STD_BLOCK_SIZE];
	byte *cipheredData = new byte[STD_BLOCK_SIZE];
	int totalLength = 0, cipheredLength, dataLength = 0;

	while (!inputFile.eof())
	{
		inputFile.read((char*)data, STD_BLOCK_SIZE);
		dataLength = inputFile.gcount();
		EVP_EncryptUpdate(mCtx, cipheredData, &cipheredLength, data, dataLength);
		totalLength += cipheredLength;
		outputFile.write((char*)cipheredData, cipheredLength);
	}

	EVP_EncryptFinal(mCtx, cipheredData + cipheredLength, &cipheredLength);
	totalLength += cipheredLength;

	//Get the tag.
	EVP_CIPHER_CTX_ctrl(mCtx, EVP_CTRL_GCM_GET_TAG, 16, tag);

	return totalLength;
}

#pragma endregion


#pragma region Decryption methods

void AES_128_GCM::SetDecryptionDetails(byte * key, byte * iv)
{
	//Initialize the encryption operation.
	if (1 != EVP_DecryptInit(mCtx, EVP_aes_128_gcm(), NULL, NULL))
	{
		std::cout << "Nu s-a putut initializa operatia de criptare.";
		exit(2);
	}

	//Set IV lenght, not the default one.
	if (1 != EVP_CIPHER_CTX_ctrl(mCtx, EVP_CTRL_GCM_SET_IVLEN, STD_BLOCK_SIZE, NULL))
	{
		std::cout << "Nu s-a putut seta lungimea IV-ului pentru 128 de biti.";
		exit(3);
	}

	//Initialize key and IV.
	if (1 != EVP_DecryptInit(mCtx, NULL, key, iv))
	{
		std::cout << "Nu s-au putut initializa cheia si IV.";
		exit(4);
	}

}

void AES_128_GCM::ProvideAdditionalAuthDataDec(std::string aadFile)
{
	std::ifstream aFile;
	aFile.open(aadFile);
	if (aFile.is_open())
	{
		int len;	//Not used, but needed in EVP_EncryptUpdate.
		byte * aad = new byte[STD_BLOCK_SIZE];
		int aadLength = 0;
		while (!aFile.eof())
		{
			aFile.read((char*)aad, STD_BLOCK_SIZE);
			aadLength = aFile.gcount();
			if (1 != EVP_DecryptUpdate(mCtx, NULL, &len, aad, aadLength))
			{
				std::cout << "Nu s-a putut adauga AAD.";
				exit(5);
			}
		}
	}
}

int AES_128_GCM::Decrypt(std::string input, std::string output, byte * tag)
{
	std::ifstream inputFile;
	std::ofstream outputFile;
	inputFile.open(input);
	outputFile.open(output);

	byte *data = new byte[STD_BLOCK_SIZE];
	byte *cipheredData = new byte[STD_BLOCK_SIZE];
	int totalLength = 0, cipheredLength = 0, dataLength;

	while (!inputFile.eof())
	{
		inputFile.read((char*)cipheredData, STD_BLOCK_SIZE);
		cipheredLength = inputFile.gcount();
		EVP_DecryptUpdate(mCtx, data, &dataLength, cipheredData, cipheredLength);
		totalLength += dataLength;
		outputFile.write((char*)data, dataLength);
	}

	//Get the tag.
	EVP_CIPHER_CTX_ctrl(mCtx, EVP_CTRL_GCM_SET_TAG, 16, tag);

	int ret = EVP_DecryptFinal(mCtx, data + dataLength, &dataLength);	
	
	if (ret > 0)
	{
		totalLength += cipheredLength;
		return totalLength;
	}
	else
	{
		std::cout << "Decriptarea a esuat.";
		return -1;
	}
}

#pragma endregion
