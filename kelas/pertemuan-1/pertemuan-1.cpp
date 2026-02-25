#include <iostream>

using namespace std;
int main() {
    // int ayam;
    // cout << "Hello World!" << endl;
    // cout << "Masukkan jumlah ayam: ";
    // cin >> ayam;
    // cout << "Jumlah ayam yang dimasukkan: " << ayam << endl;
    // //endl: membuat baris baru
    // //komentar ini hanya satu baris
    // /*Ini adalah komentar
    // yang lebih dari satu baris
    // */
    // string nama;
    // cout << "Masukkan nama kamu: ";
    // getline(cin, nama);
    // //getline digunakan untuk membaca input yang mengandung spasi/lebih dari satu kata
    // //float terbatas, double lebih panjang angka setelah komanya
    // cout << "Halo, " << nama;
    // cout << "Size of char: " << sizeof(char) << endl;
    // cout << "Size of int: " << sizeof(int) << endl;
    // cout << "Size of float: " << sizeof(float) << endl;
    // cout << "Size of double: " << sizeof(double) << endl;
    // cout << "Size of long: " << sizeof(long);
    // int angka[5] = {1, 2, 3, 4, 5};
    // struct Mahasiswa {
    //     string nama;
    //     int umur;
    //     float ipk;
    // };
    // Mahasiswa mhs = {"Sipuwah", 20, 3.5};
    // cout << "Nama: " << mhs.nama << endl;
    // cout << "Umur: " << mhs.umur << endl;
    // cout << "IPK: " << mhs.ipk << endl;
    // int z = 1;
    // cout << "Sebelum increment " << z << endl;
    // cout << "Increment di depan " << ++z << ", sudah bertambah" << endl;
    // cout << "Increment di belakang " << z++ << ", belum bertambah" << endl;
    // cout << "Hasil akhir " << z << endl;
    
    // int age = 18;
    // if (age < 13) {
    //     cout << "Anak";
    // }
    // else if (age >= 13 && age <= 18) {
    //     cout << "Remaja";
    // }
    // else {
    //     cout << "Dewasa";
    // }

    // int nilai;
    // cout << " = Konversi Nilai Akademik =\n";
    // cout << "Masukkan nilai akhir (0-100): ";
    // cin >> nilai;
    // if (nilai < 0 || nilai > 100) {
    //     cout << "Error: Nilai harus 0-100.\n";
    //     return 1;
    // }
    // switch (nilai / 10) {
    //     case 10:
    //         cout << "Predikat: A (Sangat Baik)\n";
    //     break;
    //     case 9:
    //         cout << "Predikat: A (Sangat Baik)\n";
    //     break;
    //     case 8:
    //         cout << "Predikat: B (Baik)\n";
    //     break;
    //     case 7:
    //         cout << "Predikat: C (Cukup)\n";
    //     break;
    //     case 6:
    //         cout << "Predikat: D (Kurang)\n";
    //     break;
    //     default:
    //         cout << "Predikat: E (Gagal)\n";
    //     break;

    int i = 0;
    do {
        cout << i << endl;
        i++;
    } while (i < 5);
    return 0;
}