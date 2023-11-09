#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Fungsi untuk membersihkan teks dengan menghilangkan spasi dan mengganti 'J' dengan 'I'
string cleanText(string text) {
    string cleanedText = "";
    for (char c : text) {
        if (isalpha(c)) {
            if (c == 'J') {
                cleanedText += 'I';
            } else {
                cleanedText += toupper(c);
            }
        }
    }
    return cleanedText;
}

// Fungsi untuk mencari posisi karakter dalam matriks Playfair
void findPosition(char playfairMatrix[5][5], char c, int &row, int &col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (playfairMatrix[i][j] == c) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

// Fungsi untuk mengenkripsi teks
string encrypt(string plaintext, string key) {
    char playfairMatrix[5][5];

    // Inisialisasi matriks Playfair dengan karakter 'X'
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            playfairMatrix[i][j] = 'X';
        }
    }

    // Isi matriks Playfair dengan kata kunci
    string keyWithoutDuplicates = "";
    for (char c : key) {
        if (keyWithoutDuplicates.find(c) == string::npos) {
            keyWithoutDuplicates += c;
        }
    }

    string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    int keyIndex = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (keyIndex < keyWithoutDuplicates.length()) {
                playfairMatrix[i][j] = keyWithoutDuplicates[keyIndex];
                keyIndex++;
            } else {
                for (char c : alphabet) {
                    if (keyWithoutDuplicates.find(c) == string::npos) {
                        playfairMatrix[i][j] = c;
                        keyWithoutDuplicates += c;
                        break;
                    }
                }
            }
        }
    }

    // Enkripsi teks
    string ciphertext = "";
    for (int i = 0; i < plaintext.length(); i += 2) {
        char c1 = plaintext[i];
        char c2 = (i + 1 < plaintext.length()) ? plaintext[i + 1] : 'X';

        int r1, r2, col1, col2;
        findPosition(playfairMatrix, c1, r1, col1);
        findPosition(playfairMatrix, c2, r2, col2);

        if (r1 == r2) {
            c1 = playfairMatrix[r1][(col1 + 1) % 5];
            c2 = playfairMatrix[r2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            c1 = playfairMatrix[(r1 + 1) % 5][col1];
            c2 = playfairMatrix[(r2 + 1) % 5][col2];
        } else {
            c1 = playfairMatrix[r1][col2];
            c2 = playfairMatrix[r2][col1];
        }

        ciphertext += c1;
        ciphertext += c2;
    }

    return ciphertext;
}

// Fungsi untuk mendeskripsi teks
string decrypt(string ciphertext, string key) {
    char playfairMatrix[5][5];

    // Inisialisasi matriks Playfair dengan karakter 'X'
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            playfairMatrix[i][j] = 'X';
        }
    }

    // Isi matriks Playfair dengan kata kunci
    string keyWithoutDuplicates = "";
    for (char c : key) {
        if (keyWithoutDuplicates.find(c) == string::npos) {
            keyWithoutDuplicates += c;
        }
    }

    string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    int keyIndex = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (keyIndex < keyWithoutDuplicates.length()) {
                playfairMatrix[i][j] = keyWithoutDuplicates[keyIndex];
                keyIndex++;
            } else {
                for (char c : alphabet) {
                    if (keyWithoutDuplicates.find(c) == string::npos) {
                        playfairMatrix[i][j] = c;
                        keyWithoutDuplicates += c;
                        break;
                    }
                }
            }
        }
    }

    // Deskripsi teks
    string plaintext = "";
    for (int i = 0; i < ciphertext.length(); i += 2) {
        char c1 = ciphertext[i];
        char c2 = (i + 1 < ciphertext.length()) ? ciphertext[i + 1] : 'X';

        int r1, r2, col1, col2;
        findPosition(playfairMatrix, c1, r1, col1);
        findPosition(playfairMatrix, c2, r2, col2);

        if (r1 == r2) {
            c1 = playfairMatrix[r1][(col1 - 1 + 5) % 5];
            c2 = playfairMatrix[r2][(col2 - 1 + 5) % 5];
        } else if (col1 == col2) {
            c1 = playfairMatrix[(r1 - 1 + 5) % 5][col1];
            c2 = playfairMatrix[(r2 - 1 + 5) % 5][col2];
        } else {
            c1 = playfairMatrix[r1][col2];
            c2 = playfairMatrix[r2][col1];
        }

        plaintext += c1;
        plaintext += c2;
    }

    return plaintext;
}

int main() {
    string key, plaintext, ciphertext;

    cout << "Masukkan kunci (huruf kapital tanpa spasi): ";
    cin >> key;
    cout << "Masukkan plaintext (huruf kapital tanpa spasi): ";
    cin >> plaintext;

    // Membersihkan teks
    plaintext = cleanText(plaintext);
    key = cleanText(key);

    // Enkripsi plaintext
    ciphertext = encrypt(plaintext, key);
    cout << "Ciphertext: " << ciphertext << endl;

    // Deskripsi ciphertext
    string decryptedText = decrypt(ciphertext, key);
    cout << "Plaintext setelah deskripsi: " << decryptedText << endl;

    return 0;
}
