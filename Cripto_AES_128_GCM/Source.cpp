#include "Initializer.h"
#include "AES_128_GCM.h"

using namespace std;

int main(int argc, char** argv)
{
	Initializer starter(argc, argv);
	AES_128_GCM aes;

	byte *tag = new byte[STD_BLOCK_SIZE];

	aes.SetEncryptionDetails(starter.GetKey(), starter.GetIV());
	aes.ProvideAdditionalAuthDataEnc(starter.GetAADFile());
	aes.Encrypt(starter.GetInputFile(), starter.GetOutputFile(), tag);

	aes.SetDecryptionDetails(starter.GetKey(), starter.GetIV());
	aes.ProvideAdditionalAuthDataDec(starter.GetAADFile());
	aes.Decrypt("output.enc", "decripted.txt", tag);

	//Everything went right.
	return 0;
}