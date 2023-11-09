#include <iostream>
#include <string>
#include <map>

// Fungsi untuk mengenkripsi teks
std::string encrypt(const std::string& text, const std::map<char, std::string>& encryptionMap) {
    std::string encryptedText;
    for (char c : text) {
        if (encryptionMap.find(c) != encryptionMap.end()) {
            encryptedText += encryptionMap.at(c);
        } else {
            encryptedText += c;
        }
    }
    return encryptedText;
}

// Fungsi untuk mendekripsi teks
std::string decrypt(const std::string& text, const std::map<char, std::string>& encryptionMap) {
    std::string decryptedText;
    std::map<std::string, char> decryptionMap;
    for (const auto& pair : encryptionMap) {
        decryptionMap[pair.second] = pair.first;
    }

    std::string currentSequence;
    for (char c : text) {
        currentSequence += c;
        if (decryptionMap.find(currentSequence) != decryptionMap.end()) {
            decryptedText += decryptionMap.at(currentSequence);
            currentSequence = "";
        }
    }
    return decryptedText;
}

int main() {
    std::map<char, std::string> encryptionMap;

    // Definisikan peta enkripsi
    encryptionMap['A'] = "CQ";
    encryptionMap['B'] = "AT ";
    encryptionMap['C'] = "AU ";
    encryptionMap['D'] = "AI ";
    encryptionMap['E'] = "BE ";
    encryptionMap['F'] = "CN ";
    encryptionMap['G'] = "BJ ";
    encryptionMap['H'] = "CK ";
    encryptionMap['I'] = "AB ";
    encryptionMap['J'] = "BX ";
    encryptionMap['K'] = "DI ";
    encryptionMap['L'] = "CI ";
    encryptionMap['M'] = "AY ";
    encryptionMap['N'] = "BR ";
    encryptionMap['O'] = "BQ ";
    encryptionMap['P'] = "AZ ";
    encryptionMap['Q'] = "DD ";
    encryptionMap['R'] = "AL ";
    encryptionMap['S'] = "DV ";
    encryptionMap['T'] = "CW ";
    encryptionMap['U'] = "AM ";
    encryptionMap['V'] = "BB ";
    encryptionMap['W'] = "CZ ";
    encryptionMap['X'] = "BD ";
    encryptionMap['Y'] = "DO ";
    encryptionMap['Z'] = "BC ";

    // ... Definisikan peta enkripsi untuk karakter lainnya ...

    std::string textToEncrypt;
    std::cout << "Masukkan teks yang ingin Anda enkripsi: ";
    std::getline(std::cin, textToEncrypt); // Menggunakan getline() untuk membaca seluruh baris

    // Proses enkripsi
    std::string encryptedText = encrypt(textToEncrypt, encryptionMap);
    std::cout << "Teks Terenkripsi: " << encryptedText << std::endl;

    // Proses dekripsi
    std::string decryptedText = decrypt(encryptedText, encryptionMap);
    std::cout << "Teks Terdekripsi: " << decryptedText << std::endl;

    return 0;
}
