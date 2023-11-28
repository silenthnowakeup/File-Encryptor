#include "sha256.h"


SHA256::SHA256() {
    // Инициализация переменных хеш-значения
    H[0] = 0x6a09e667;
    H[1] = 0xbb67ae85;
    H[2] = 0x3c6ef372;
    H[3] = 0xa54ff53a;
    H[4] = 0x510e527f;
    H[5] = 0x9b05688c;
    H[6] = 0x1f83d9ab;
    H[7] = 0x5be0cd19;
}

std::string SHA256::hash(const std::string& input) {
    // Предварительная обработка входных данных
    std::string paddedInput = preprocess(input);

    // Обработка блоков данных
    for (size_t i = 0; i < paddedInput.length(); i += 64) {
        processBlock(reinterpret_cast<const uint8_t*>(&paddedInput[i]));
    }

    // Формирование итогового хеш-значения
    std::stringstream result;
    for (int i = 0; i < 8; ++i) {
        result << std::hex << std::setfill('0') << std::setw(8) << H[i];
    }

    return result.str();
}

std::string SHA256::preprocess(const std::string& input) {
    std::string result = input;

    // Добавление бита "1"
    result += (char)0x80;

    // Добавление дополнительных битов "0", если не хватает места
    while ((result.length() + 8) % 64 != 0) {
        result += (char)0x00;
    }

    // Добавление длины сообщения (в битах)
    uint64_t length = input.length() * 8;
    result += (char)(length >> 56);
    result += (char)(length >> 48);
    result += (char)(length >> 40);
    result += (char)(length >> 32);
    result += (char)(length >> 24);
    result += (char)(length >> 16);
    result += (char)(length >> 8);
    result += (char)length;

    return result;
}

void SHA256::processBlock(const uint8_t* block) {
    uint32_t W[64];

    // Расширение блока в 64 слова
    for (int t = 0; t < 16; ++t) {
        W[t] = (block[t * 4] << 24) | (block[t * 4 + 1] << 16) | (block[t * 4 + 2] << 8) | block[t * 4 + 3];
    }
    for (int t = 16; t < 64; ++t) {
        W[t] = sigma1(W[t - 2]) + W[t - 7] + sigma0(W[t - 15]) + W[t - 16];
    }

    // Инициализация переменных для текущего блока
    uint32_t a = H[0];
    uint32_t b = H[1];
    uint32_t c = H[2];
    uint32_t d = H[3];
    uint32_t e = H[4];
    uint32_t f = H[5];
    uint32_t g = H[6];
    uint32_t h = H[7];

    // Основной цикл
    for (int t = 0; t < 64; ++t) {
        uint32_t T1 = h + Sigma1(e) + Ch(e, f, g) + K[t] + W[t];
        uint32_t T2 = Sigma0(a) + Maj(a, b, c);

        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    // Обновление переменных хеш-значения
    H[0] += a;
    H[1] += b;
    H[2] += c;
    H[3] += d;
    H[4] += e;
    H[5] += f;
    H[6] += g;
    H[7] += h;
}

//QByteArray SHA256::hash(const QByteArray& input) {
//    // Preprocess the input data
//    QByteArray paddedInput = preprocess(input);

//    // Process data blocks
//    for (size_t i = 0; i < paddedInput.size(); i += 64) {
//        processBlock(reinterpret_cast<const uint8_t*>(paddedInput.constData() + i));
//    }

//    // Form the final hash value
//    QByteArray result;
//    for (int i = 0; i < 8; ++i) {
//        result.append(reinterpret_cast<const char*>(&H[i]), sizeof(H[i]));
//    }

//    return result;
//}

//QByteArray SHA256::preprocess(const QByteArray& input) {
//    QByteArray result = input;

//    // Append the bit "1"
//    result.append((char)0x80);

//    // Append additional bits "0" if needed
//    while ((result.size() + 8) % 64 != 0) {
//        result.append((char)0x00);
//    }

//    // Append the length of the message (in bits)
//    uint64_t length = input.size() * 8;
//    result.append((char)(length >> 56));
//    result.append((char)(length >> 48));
//    result.append((char)(length >> 40));
//    result.append((char)(length >> 32));
//    result.append((char)(length >> 24));
//    result.append((char)(length >> 16));
//    result.append((char)(length >> 8));
//    result.append((char)length);

//    return result;
//}

//void SHA256::processBlock(const uint8_t* block) {
//    uint32_t W[64];

//    // Expand the block into 64 words
//    for (int t = 0; t < 16; ++t) {
//        W[t] = (block[t * 4] << 24) | (block[t * 4 + 1] << 16) | (block[t * 4 + 2] << 8) | block[t * 4 + 3];
//    }
//    for (int t = 16; t < 64; ++t) {
//        W[t] = sigma1(W[t - 2]) + W[t - 7] + sigma0(W[t - 15]) + W[t - 16];
//    }

//    // Initialize variables for the current block
//    uint32_t a = H[0];
//    uint32_t b = H[1];
//    uint32_t c = H[2];
//    uint32_t d = H[3];
//    uint32_t e = H[4];
//    uint32_t f = H[5];
//    uint32_t g = H[6];
//    uint32_t h = H[7];

//    // Main loop
//    for (int t = 0; t < 64; ++t) {
//        uint32_t T1 = h + Sigma1(e) + Ch(e, f, g) + K[t] + W[t];
//        uint32_t T2 = Sigma0(a) + Maj(a, b, c);

//        h = g;
//        g = f;
//        f = e;
//        e = d + T1;
//        d = c;
//        c = b;
//        b = a;
//        a = T1 + T2;
//    }

//    // Update hash variables
//    H[0] += a;
//    H[1] += b;
//    H[2] += c;
//    H[3] += d;
//    H[4] += e;
//    H[5] += f;
//    H[6] += g;
//    H[7] += h;
//}

