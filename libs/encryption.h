#include <sodium.h>

extern void create_hash_from_password(char* password, char hash[crypto_pwhash_STRBYTES]);

extern void encrypt_str(char* str, char* encrypted_str, char hash[crypto_pwhash_STRBYTES], int isLastLine);