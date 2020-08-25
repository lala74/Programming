// 05/03/2020: Created by Minh-Duc-LA

#include <iostream>
#include <string>
#include <sstream>
#include <openssl/sha.h>
#include <openssl/md5.h>
#include <fstream>
#include <iomanip>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <string.h>
#include "HLT_shell_utils.h"
#include "HLT_utils.h"

#define BUFFSIZE 16384

using namespace std;

static const string CERTS_GENERATOR_PATH = "/media/data_current/etc/certs/certGen.sh";

/* SHA 256 */

static string to_hex(unsigned char s) {
    stringstream ss;
    ss  << std::setfill ('0') << std::setw(2)
        << hex << (int) s;
    return ss.str();
}

string HLT_sha256(string line) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, line.c_str(), line.length());
    SHA256_Final(hash, &sha256);

    string output = "";
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        output += to_hex(hash[i]);
    }
    return output;
}

/* MD5 */

string HLT_md5(const string &fname)
{

    char buffer[BUFFSIZE];
    unsigned char digest[MD5_DIGEST_LENGTH];

    stringstream ss;
    string md5string;

    ifstream ifs(fname, ifstream::binary);

    MD5_CTX md5Context;

    MD5_Init(&md5Context);

    while (ifs.good())
    {

        ifs.read(buffer, BUFFSIZE);

        MD5_Update(&md5Context, buffer, ifs.gcount());
    }

    ifs.close();

    int res = MD5_Final(digest, &md5Context);

    if (res == 0)  // hash failed
        return {}; // or raise an exception

    // set up stringstream format
    ss << hex << setfill('0');

    for (unsigned char uc : digest)
        ss << setw(2) << (int)uc;

    md5string = ss.str();

    return md5string;
}

/* Generate key to decrypt private key in USB stick */
string HLT_key() 
{
    string e1 = "03 0E 3A 0B 3B 0B 49 13 32 0B 00 00 2B 0D 00 03 0E 3A 0B 3B 05 49 13 38 0B 00 00 2C 28 00 03 0E 1C 0B 00 00 2D 1D 01 31 13 52 01 55 17 58 0B 59";
    string e2 = CERTS_GENERATOR_PATH;
    string e3 = szHLT_INFO;
    string e4 = "U2FsdGVkX1+VsQSvpTMjepbSNpapeu1If+fDKdLnyzM=";

    return HLT_sha256(e1) + HLT_sha256(e2 + e3) + HLT_sha256(e3) + e4 + HLT_sha256(e4 + e3);
}

/* aes-256-cbc decryption */

void handleOpenSSLErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

string decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv )
{

  EVP_CIPHER_CTX *ctx;
//   unsigned char *plaintexts;
  int len;
  int plaintext_len;
  unsigned char* plaintext = new unsigned char[ciphertext_len];
  bzero(plaintext,ciphertext_len);

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleOpenSSLErrors();

  /* Initialise the decryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleOpenSSLErrors();

  EVP_CIPHER_CTX_set_key_length(ctx, EVP_MAX_KEY_LENGTH);

 /* Provide the message to be decrypted, and obtain the plaintext output.
   * EVP_DecryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleOpenSSLErrors();

  plaintext_len = len;

  /* Finalise the decryption. Further plaintext bytes may be written at
   * this stage.
   */
  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleOpenSSLErrors();
  plaintext_len += len;


  /* Add the null terminator */
  plaintext[plaintext_len] = 0;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);
  string ret = (char*)plaintext;
  delete [] plaintext;
  return ret;
}

void initAES(const string& pass, unsigned char* salt, unsigned char* key, unsigned char* iv )
{
  bzero(key,sizeof(*key));
  bzero(iv,sizeof(*iv));

  EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), salt, (unsigned char*)pass.c_str(), pass.length(), 1, key, iv);
}

size_t calcDecodeLength(char* b64input) {
  size_t len = strlen(b64input), padding = 0;

  if (b64input[len-1] == '=' && b64input[len-2] == '=') //last two chars are =
    padding = 2;
  else if (b64input[len-1] == '=') //last char is =
    padding = 1;
  return (len*3)/4 - padding;
}

void Base64Decode( char* b64message, unsigned char** buffer, size_t* length)
{
  BIO *bio, *b64;

  int decodeLen = calcDecodeLength(b64message);
  *buffer = (unsigned char*)malloc(decodeLen + 1);
  (*buffer)[decodeLen] = '\0';

  bio = BIO_new_mem_buf(b64message, -1);
  b64 = BIO_new(BIO_f_base64());
  bio = BIO_push(b64, bio);

  //BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Do not use newlines to flush buffer
  *length = BIO_read(bio, *buffer, strlen(b64message));
  BIO_free_all(bio);
}

/* aes-256-cbc decryption main function */

string HLT_decrypt_aes(const string &content)
{
    char ciphertext_base64[content.length() + 1];
    strcpy(ciphertext_base64, content.c_str());
    // int decryptedtext_len, ciphertext_len;
    size_t cipher_len;
    unsigned char* ciphertext;
    unsigned char salt[8];
    ERR_load_crypto_strings();
    Base64Decode(ciphertext_base64, &ciphertext, &cipher_len);

    unsigned char key[32];
    unsigned char iv[32];

    if (strncmp((const char*)ciphertext,"Salted__",8) == 0) {
        memcpy(salt,&ciphertext[8],8);
        ciphertext += 16;
        cipher_len -= 16;
    }
    initAES(HLT_key(), salt, key, iv);

    string result = decrypt(ciphertext, cipher_len, key, iv);

    // Clean up
    EVP_cleanup();
    ERR_free_strings();    

    return result;
}

/* Certificate */

int HLT_generate_certificate(const string &tgu_sn)
{
    int iRet;
    string cmd;

    // Add execute permission for certGen file
    cmd = "chmod +x " + CERTS_GENERATOR_PATH;
    iRet = HLT_execute_cmd(cmd, "HLT_generate_certificate:");

    // Generate certificate with device ID = tgu serial number
    cmd = "sh " + CERTS_GENERATOR_PATH + " create_ic_device_certificate " + tgu_sn;
    iRet = HLT_execute_cmd(cmd, "HLT_generate_certificate:");

    return iRet;
}
