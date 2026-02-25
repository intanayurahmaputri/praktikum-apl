#include <iostream>

using namespace std;
int main() {
    string username;
    string password;
    string usernameBenar = "Aya";
    string passBenar = "062";
    int kesempatan = 0;
    string pilihan;

    cout << "====================================\n";
    cout << "      SISTEM KONVERSI WAKTU O_O\n";
    cout << "====================================\n";

    while (kesempatan < 3) {
        cout << "Username : "; cin >> username;
        cout << "Password : "; cin >> password;

        if (username == usernameBenar && password == passBenar) {
            cout << "\nLogin Berhasil!\n";
            break;
        } else {
            kesempatan++;
            cout << "Login Gagal! Sisa kesempatan: " << 3 - kesempatan << "\n\n";
        }
    }

    if (kesempatan == 3) {
        cout << "Anda gagal login 3 kali.\n";
        cout << "Program berhenti.\n";
        return 0;
    }


    cout << "\n====================================\n";
    cout << "             MENU :D\n";
    cout << "====================================\n";
    
    do {
        cout << "1. Jam -> Menit dan Detik\n";
        cout << "2. Menit -> Jam dan Detik\n";
        cout << "3. Detik -> Jam dan Menit\n";
        cout << "4. Keluar\n";
        cout << "====================================\n";
        cout << "Pilih menu (1-4): "; cin >> pilihan;

        if (pilihan == "1") {
            double jam;
            cout << "Masukkan jumlah Jam: "; cin >> jam;
            cout << "Hasil: " << jam * 60 << " menit dan " << jam * 3600 << " detik\n\n";
        }
        else if (pilihan == "2") {
            double menit;
            cout << "Masukkan jumlah Menit: "; cin >> menit;
            cout << "Hasil: " << menit / 60 << " jam dan " << menit * 60 << " detik\n\n";
        }
        else if (pilihan == "3") {
            double detik;
            cout << "Masukkan jumlah Detik: "; cin >> detik;
            cout << "Hasil: " << detik / 3600 << " jam dan " << detik / 60 << " menit\n\n";
        }
        else if (pilihan == "4") {
            cout << "Terima kasih. Program selesai.";
        }
        else {
            cout << "Pilihan tidak valid!\n\n";
        }
    } while (pilihan != "4");
    return 0;
}