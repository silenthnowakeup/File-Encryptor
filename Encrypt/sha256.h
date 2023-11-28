#ifndef SHA256_H
#define SHA256_H


#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <QByteArray>

// Левые циклические сдвиги
#define ROTL(x, n) (((x) << (n)) | ((x) >> (32-(n))))

// Побитовые операции
#define Ch(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define Maj(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define Sigma0(x) (ROTL(x, 2) ^ ROTL(x, 13) ^ ROTL(x, 22))
#define Sigma1(x) (ROTL(x, 6) ^ ROTL(x, 11) ^ ROTL(x, 25))
#define sigma0(x) (ROTL(x, 7) ^ ROTL(x, 18) ^ ((x) >> 3))
#define sigma1(x) (ROTL(x, 17) ^ ROTL(x, 19) ^ ((x) >> 10))

const uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};


class SHA256 {
public:
    SHA256();
    std::string hash(const std::string& input);

private:
    uint32_t H[8];  // Инициализация переменных хеш-значения

    // Вспомогательные функции
    std::string preprocess(const std::string& input);
    void processBlock(const uint8_t* block);
};

//class SHA256 {
//public:
//    SHA256();
//    QByteArray hash(const QByteArray& input);

//private:
//    uint32_t H[8];  // Initialization of hash variables

//    // Helper functions
//    QByteArray preprocess(const QByteArray& input);
//    void processBlock(const uint8_t* block);
//};

//SHA256::SHA256() {
//    // Initialization of hash variables
//    H[0] = 0x6a09e667;
//    H[1] = 0xbb67ae85;
//    H[2] = 0x3c6ef372;
//    H[3] = 0xa54ff53a;
//    H[4] = 0x510e527f;
//    H[5] = 0x9b05688c;
//    H[6] = 0x1f83d9ab;
//    H[7] = 0x5be0cd19;
//}
#endif // SHA256_H
