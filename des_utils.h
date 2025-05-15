#ifndef DES_UTILS_H
#define DES_UTILS_H

#include <vector>
#include <string>
#include <openssl/des.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
using namespace std;
class DESUtils {
public:
    static vector<unsigned char> des_encrypt(const vector<unsigned char>& plaintext, const DES_cblock& key);
    static vector<unsigned char> des_decrypt(const vector<unsigned char>& ciphertext, const DES_cblock& key);
    static bool encrypt_file(const string& input_file, const string& output_file, const DES_cblock& key);
    static bool decrypt_file(const string& input_file, const string& output_file, const DES_cblock& key);
    static string base64_encode(const vector<unsigned char>& data);
    static vector<unsigned char> base64_decode(const string& encoded);
    static void generate_random_key(DES_cblock* key);
};

#endif