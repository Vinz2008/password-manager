#include <string.h>
#include <sodium.h>

char* create_hash_from_password(char* password, char hash[crypto_pwhash_STRBYTES]){
    if (crypto_pwhash_str(hash, password, strlen(password), crypto_pwhash_OPSLIMIT_SENSITIVE, crypto_pwhash_MEMLIMIT_SENSITIVE) != 0){
        printf("Can't create hash\n");
        exit(1);
    }
    return hash;
}