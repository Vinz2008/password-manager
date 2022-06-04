#include <sodium.h>

extern char* create_hash_from_password(char* password, char hash[crypto_pwhash_STRBYTES]);