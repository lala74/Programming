// 05/03/2020: Created by Minh-Duc-LA
#ifndef __HLT_CRYPTO_H
#define __HLT_CRYPTO_H

#include <string>

using namespace std;

string HLT_sha256(string line);
string HLT_md5(const string& fname);
string HLT_key();
string HLT_decrypt_aes(const string& content);
int HLT_generate_certificate(const string& tgu_sn);

#endif /* __HLT_CRYPTO_H */