#pragma once
#include <openssl/evp.h>
#include<fstream>

#define STD_BLOCK_SIZE	16

using byte = unsigned char;

class AES_128_GCM
{
private:
	EVP_CIPHER_CTX *			mCtx;

public:
	AES_128_GCM();
	~AES_128_GCM();

	void						SetEncryptionDetails(byte* key, byte* iv);
	void						ProvideAdditionalAuthDataEnc(std::string aadFile);
	int							Encrypt(std::string inputFile, std::string outputFile, byte *tag);



	void						SetDecryptionDetails(byte* key, byte* iv);
	void						ProvideAdditionalAuthDataDec(std::string aadFile);
	int							Decrypt(std::string inputFile, std::string outputFile, byte *tag);
};

