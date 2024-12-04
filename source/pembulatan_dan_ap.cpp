#include "pembulatan_dan_ap.h"
#include <string>

int hitungAngkaPenting(const std::string &s) {
    int totalAP = 0;                // Menunjukkan total angka penting
    int nolKanan = 0;
    bool nolDiKiri = true;          // Menunjukkan apakah sudah menemukan angka bukan nol
    bool desimal;
    
    // Menghitung angka penting
    for (char c: s) {
        if (c == '0' && nolDiKiri) continue; // Abaikan nol awal

        if (c == '.') {
            desimal = true;
        }
        else if ((c != '0' || desimal) && nolKanan > 0) {
            totalAP++;
            totalAP += nolKanan;
            nolKanan = 0;
        }
        else if (c != '0') {
            totalAP++;                      // Angka bukan nol dihitung sebagai angka penting
            nolDiKiri = false;
        }
        else if (c == '0' && !nolDiKiri) {
            nolKanan++;
        }
        
    }
    if (nolKanan > 0 && desimal) {
        totalAP += nolKanan;
    }
    return totalAP;
}

void pembulatan_AP(std::string &s, int jumlahAP) {
    // Jika ada desimal hapus desimal tambahin di akhir program
    int letakDesimal = s.find('.');
    if (letakDesimal != std::string::npos) {
        s.erase(s.begin() + letakDesimal);
    }
    
    // Ulangi hingga angka pentingnya sama dengan jumlah AP
    while (hitungAngkaPenting(s) > jumlahAP) { 

        for (int i = s.length() - 1; i >= 0; i--) {
            if (s[i] == '0') continue;
            if (s[i] == '.') continue;

            // Pembulatan ke atas
            if (s[i] > '5') {
                // Cek apakah angka sebelumnya 9 dan 2 karakter sebelumnya terdefinisi
                if (s[i-1] == '9' && (i - 2 < 0)) {
                    s[i] = '0'; s[i-1] = '0';
                    s.insert(s.begin(), '1');
                    if(letakDesimal != std::string::npos) letakDesimal++;
                    break;
                }
                // Jika karakter sebelumnya bukan koma tambahkan karakter sebelumnya
                else if (s[i-1] != '.') {
                    s[i-1] += 1;
                }
                s[i] = '0';
            }
            // Pembulatan jika sama dengan 50
            else if (s[i] == '5' && (s[i+1] == '0' || s[i+1] == '\0')) {
                if ((s[i -1] - '0') % 2 == 1) {
                    s[i-1] += 1;
                }
                s[i] = '0';
            }
            // Jika dibawah 50 langsung hapus
            else {
                s[i] = '0';
            }

            if (s[i] == ':') {
            s[i] = '0';
            s[i-1]++;
            }

            break;
        }
        if (letakDesimal != std::string::npos && s[letakDesimal] == ':') {
            s[letakDesimal] = '0';
            s[letakDesimal - 1]++;
        }
        if(s[0] == ':') {
            s[0] = '0';
            s.insert(s.begin(), '1');
        }
    }
    if (letakDesimal != std::string::npos) {
        s.insert(s.begin() + letakDesimal, '.');

        if (stold(s) >= 1) { 
            s.erase(letakDesimal);
        }
        else {
            for (size_t i = s.size() - 1; i >= 0; i --) {
                if (s[i] != '0' && s[i] != '.') {
                    s.erase(i + 1);
                    return;
                }
            }
        }
    }
}

int hitung_Presisi(const std::string &s , int min) {
    int desimal = s.find('.');
    if (desimal != std::string::npos) {
        return s.size() - 1 - desimal;
    }
    
    int diDepanKoma = 0;
    for (int i = s.size(); i >= 0; i--) {
        if (s[i] == '0') {
            diDepanKoma++;
        }
    }
    if (min >= 0) {
        return 0;
    }
    else {
        return -diDepanKoma;
    }
}
