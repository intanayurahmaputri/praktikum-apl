#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>
#include <iomanip>
#include <algorithm>
#include "hitung_toko.h"

using namespace std;
using namespace TokoLib;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

struct Detail {
    int harga;
    int stok;
};

struct Produk {
    string name;
    string kategori;
    Detail detail;
};

struct Pesanan {
    int idxProduk;
    int jumlah;
};

struct Pengguna {
    string name;
    string password;
};

void pause() {
    cout << YELLOW << "\nTekan Enter untuk melanjutkan..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void clearScreen() {
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

void lihatProduk(Produk dataProduk[], int jumlahProduk) {
    cout << CYAN << "========================================================================\n";
    cout << left << setw(4) << "No" << setw(32) << "Nama Produk" << setw(18) << "Kategori" << setw(12) << "Harga" << "Stok\n";
    cout << "========================================================================\n" << RESET;

    for (int i = 0; i < jumlahProduk; i++) {
        cout << left << setw(4) << (i + 1) << setw(32) << dataProduk[i].name << setw(18) << dataProduk[i].kategori << "Rp" << setw(10) << dataProduk[i].detail.harga << dataProduk[i].detail.stok << endl;
    }
}

void lihatPesanan(Pesanan dataPesanan[], Produk dataProduk[], int jumlahPesanan) {
    cout << "\n==== PESANAN ANDA ====\n";
    if (jumlahPesanan == 0) {
        cout << "Belum ada pesanan.\n";
    } else {
        for (int i = 0; i < jumlahPesanan; i++) {
            int idx = dataPesanan[i].idxProduk;
            cout << i + 1 << ". " << dataProduk[idx].name << " | Jumlah: " << dataPesanan[i].jumlah << endl;
        }
    }
}

void tambahProduk(int &jumlahProduk, Produk dataProduk[]) {
    try {
        cout << "=== TAMBAH PRODUK (z'v'z) ===\n";
        if (jumlahProduk >= 10) {
            throw runtime_error("Gudang Penuh! Maksimal 10 produk.");
        }

        cout << "Nama Produk: "; getline(cin, dataProduk[jumlahProduk].name);
        if (dataProduk[jumlahProduk].name.empty()) {
            throw invalid_argument("Nama produk tidak boleh kosong.");
        }

        cout << "Kategori: "; getline(cin, dataProduk[jumlahProduk].kategori);
        if (dataProduk[jumlahProduk].kategori.empty()) {
            throw invalid_argument("Kategori tidak boleh kosong.");
        }
        
        cout << "Harga: "; string tempHarga; getline(cin, tempHarga);
        if (tempHarga.empty()) throw invalid_argument("Harga tidak boleh kosong.");
        if (!all_of(tempHarga.begin(), tempHarga.end(), ::isdigit)) throw invalid_argument("Harga tidak valid.");
        dataProduk[jumlahProduk].detail.harga = stoi(tempHarga);

        if (!validasiHarga(dataProduk[jumlahProduk].detail.harga)) {
            throw logic_error("Harga minimal adalah Rp20.000.");
        }

        cout << "Stok: "; string tempStok; getline(cin, tempStok);
        if (tempStok.empty()) throw invalid_argument("Stok tidak boleh kosong.");
        if (!all_of(tempStok.begin(), tempStok.end(), ::isdigit)) throw invalid_argument("Stok tidak valid.");
        dataProduk[jumlahProduk].detail.stok = stoi(tempStok);

        if (dataProduk[jumlahProduk].detail.stok < 0) throw logic_error("Stok tidak boleh negatif.");

        jumlahProduk++;
        cout << GREEN << "\n[SUCCESS] Produk berhasil ditambahkan.\n" << RESET;
    } catch (const exception& e) {
        cout << RED << "\n[ERROR] Terjadi Kesalahan: " << e.what() << RESET << endl;
    }
}

void ubahProduk(int &jumlahProduk, Produk dataProduk[]) {
    try {
        string tempUbah;
        cout << "\nNomor produk: "; getline(cin, tempUbah);
        if (tempUbah.empty()) throw invalid_argument("Nomor produk tidak boleh kosong.");
        if (!all_of(tempUbah.begin(), tempUbah.end(), ::isdigit)) throw invalid_argument("Nomor produk tidak valid.");
        int ubah = stoi(tempUbah);
        
        if (ubah < 1 || ubah > jumlahProduk) throw out_of_range("Nomor produk tidak ditemukan.");

        cout << "Harga baru: "; string tempHarga; getline(cin, tempHarga);
        if (tempHarga.empty()) throw invalid_argument("Harga tidak boleh kosong.");
        if (!all_of(tempHarga.begin(), tempHarga.end(), ::isdigit)) throw invalid_argument("Harga tidak valid.");
        int hargaBaru = stoi(tempHarga);

        if (!validasiHarga(hargaBaru)) throw logic_error("Harga minimal adalah Rp20.000.");

        cout << "Stok baru: "; string tempStok; getline(cin, tempStok);
        if (tempStok.empty()) throw invalid_argument("Stok tidak boleh kosong.");
        if (!all_of(tempStok.begin(), tempStok.end(), ::isdigit)) throw invalid_argument("Stok tidak valid.");
        int stokBaru = stoi(tempStok);

        if (stokBaru < 0) throw logic_error("Stok tidak boleh negatif.");

        dataProduk[ubah-1].detail.harga = hargaBaru;
        dataProduk[ubah-1].detail.stok = stokBaru;
        cout << GREEN << "\n[SUCCESS] Produk berhasil diperbarui.\n" << RESET;
    } catch (const exception& e) {
        cout << RED << "\n[ERROR] Terjadi Kesalahan: " << e.what() << RESET << endl;
    }
}

void hapusProduk(int &jumlahProduk, Produk dataProduk[]) {
    try {
        string tempHapus; cout << "\nNomor produk: "; getline(cin, tempHapus);
        if (tempHapus.empty()) throw invalid_argument("Nomor produk tidak boleh kosong.");
        if (!all_of(tempHapus.begin(), tempHapus.end(), ::isdigit)) throw invalid_argument("Nomor produk tidak valid.");
        int hapus = stoi(tempHapus);

        if (hapus > 0 && hapus <= jumlahProduk) {
            for (int i = hapus-1; i < jumlahProduk-1; i++) {
                dataProduk[i] = dataProduk[i+1];
            }
            jumlahProduk--;
            cout << GREEN << "\n[SUCCESS] Produk berhasil dihapus.\n" << RESET;
        } else {
            throw out_of_range("Nomor produk tidak ditemukan.");
        }
    } catch (const exception& e) {
        cout << RED << "\n[ERROR] Terjadi Kesalahan: " << e.what() << RESET << endl;
    }
}

void buatPesanan(int jumlahProduk, Produk dataProduk[], Pesanan dataPesanan[], int &jumlahPesanan) {
    try {
        string tempPilih, tempJumlah; cout << "\nPilih nomor produk: "; getline(cin, tempPilih);
        if (tempPilih.empty()) throw invalid_argument("Nomor produk tidak boleh kosong.");
        if (!all_of(tempPilih.begin(), tempPilih.end(), ::isdigit)) throw invalid_argument("Nomor produk tidak valid.");
        int pilihProduk = stoi(tempPilih);

        if (pilihProduk > 0 && pilihProduk <= jumlahProduk) {
            cout << "Jumlah beli: "; getline(cin, tempJumlah);
            if (tempJumlah.empty()) throw invalid_argument("Jumlah beli tidak boleh kosong.");
            if (!all_of(tempJumlah.begin(), tempJumlah.end(), ::isdigit)) throw invalid_argument("Jumlah beli tidak valid.");
            int jumlah = stoi(tempJumlah);

            if (jumlah <= 0) {
                throw logic_error("Jumlah beli harus lebih dari 0.");
            } else if (jumlahPesanan >= 10) {
                throw runtime_error("Pesanan sudah mencapai batas maksimum.");
            } else if (jumlah <= dataProduk[pilihProduk-1].detail.stok) {
                dataPesanan[jumlahPesanan].idxProduk = pilihProduk-1;
                dataPesanan[jumlahPesanan].jumlah = jumlah;
                jumlahPesanan++;
                cout << GREEN << "\n[SUCCESS] Pesanan berhasil ditambahkan.\n" << RESET;
            } else {
                throw runtime_error("Stok tidak cukup.");
            }
        } else {
            throw out_of_range("Nomor produk tidak ditemukan.");
        }
    } catch (const exception& e) {
        cout << RED << "\n[ERROR] Terjadi Kesalahan: " << e.what() << RESET << endl;
    }
}

void hapusPesanan(Pesanan dataPesanan[], int &jumlahPesanan) {
    try {
        string tempHapus; cout << "\nNomor pesanan: "; getline(cin, tempHapus);
        if (tempHapus.empty()) throw invalid_argument("Nomor pesanan tidak boleh kosong.");
        if (!all_of(tempHapus.begin(), tempHapus.end(), ::isdigit)) throw invalid_argument("Nomor pesanan tidak valid.");
        int hapus = stoi(tempHapus);

        if (hapus > 0 && hapus <= jumlahPesanan) {
            for (int i = hapus-1; i < jumlahPesanan-1; i++) {
                dataPesanan[i] = dataPesanan[i+1];
            }
            jumlahPesanan--;
            cout << GREEN << "\n[SUCCESS] Pesanan berhasil dihapus.\n" << RESET;
        } else {
            throw out_of_range("Nomor pesanan tidak ditemukan.");
        }
    } catch (const exception& e) {
        cout << RED << "\n[ERROR] Terjadi Kesalahan: " << e.what() << RESET << endl;
    }
}

int bayarPesanan(Pesanan dataPesanan[], Produk dataProduk[], int n, bool rekursif) {
    if (n <= 0) return 0;
    int totalSebelumnya = bayarPesanan(dataPesanan, dataProduk, n - 1, true);

    int idx = dataPesanan[n - 1].idxProduk;
    int harga = dataProduk[idx].detail.harga;
    int jumlah = dataPesanan[n - 1].jumlah;
    int subtotal = hitungTotalDasar(harga, jumlah);

    cout << RESET << left << setw(4) << n << setw(32) << dataProduk[idx].name << "Rp" << setw(10) << harga << setw(10) << jumlah << "Rp" << subtotal << endl;

    return totalSebelumnya + subtotal;
}

void bayarPesanan(Pesanan dataPesanan[], Produk dataProduk[], int &jumlahPesanan) {
    if (jumlahPesanan == 0) {
        cout << YELLOW << "Belum ada pesanan." << RESET;
    } else {
        try {
            cout << CYAN << "========================================================================\n";
            cout << left << setw(4) << "No" << setw(32) << "Nama Produk" << setw(12) << "Harga" << setw(10) << "Jumlah" << "Subtotal\n";
            cout << "========================================================================\n";
            int totalSebelumPajak = bayarPesanan(dataPesanan, dataProduk, jumlahPesanan, true);
            
            cout << "========================================================================\n";

            int totalDenganPajak = hitungDenganPajak(totalSebelumPajak, 5);

            int totalAkhir = totalDenganPajak;
            if (totalSebelumPajak > 100000) {
                totalAkhir = hitungDenganDiskon(totalDenganPajak, 10);
                cout << RESET << "Total        : Rp" << totalSebelumPajak << endl;
                cout << "Total + Pajak (5%): Rp" << totalDenganPajak << endl;
                cout << GREEN << "Total - Diskon 10%: Rp" << totalAkhir << RESET << endl;
            } else {
                cout << RESET << "Total        : Rp" << totalSebelumPajak << endl;
                cout << GREEN << "Total + Pajak (5%): Rp" << totalDenganPajak << RESET << endl;
            }
            string konfirmasi; cout << "\nKonfirmasi pembayaran (y/n): "; getline(cin, konfirmasi);
            if (konfirmasi.empty()) throw invalid_argument("Input tidak boleh kosong!");
            
            if (konfirmasi == "y" || konfirmasi == "Y") {
                for (int i = 0; i < jumlahPesanan; i++) {
                    int idx = dataPesanan[i].idxProduk;
                    dataProduk[idx].detail.stok -= dataPesanan[i].jumlah;
                }
                jumlahPesanan = 0;
                cout << "[SUCCESS] Pembayaran berhasil sebesar Rp" << totalAkhir << ". Terima kasih telah berbelanja!\n";
            } else if (konfirmasi == "n" || konfirmasi == "N") {
                cout << YELLOW << "[FAILED] Pembayaran dibatalkan.\n" << RESET;
                return;
            } else {
                throw invalid_argument("Pilihan konfirmasi tidak valid. Gunakan 'y' atau 'n'.");
            }
        } catch (const exception& e) {
            cout << RED << "\n[ERROR] Gagal memproses pembayaran: " << e.what() << RESET << endl;
        }
    }
}

void sortNamaDesc(Produk dataProduk[], int jumlahProduk) { //bubble sort
    for (int i = 0; i < jumlahProduk - 1; i++) {
        for (int j = 0; j < jumlahProduk - i - 1; j++) {
            if (dataProduk[j].name < dataProduk[j + 1].name) {
                swap(dataProduk[j], dataProduk[j + 1]);
            }
        }
    }
    cout << GREEN << "Produk berhasil diurutkan (Nama Z-A).\n" << RESET;
}

void sortHargaAsc(Produk dataProduk[], int jumlahProduk) { //selection sort
    for (int i = 0; i < jumlahProduk - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < jumlahProduk; j++) {
            if (dataProduk[j].detail.harga < dataProduk[minIndex].detail.harga) {
                minIndex = j;
            }
        }
        swap(dataProduk[i], dataProduk[minIndex]);
    }
    cout << GREEN << "Produk berhasil diurutkan (Harga termurah).\n" << RESET;
}

void sortStokDesc(Produk dataProduk[], int jumlahProduk) { //insertion sort
    for (int i = 1; i < jumlahProduk; i++) {
        Produk key = dataProduk[i];
        int j = i - 1;

        while (j >= 0 && dataProduk[j].detail.stok < key.detail.stok) {
            dataProduk[j + 1] = dataProduk[j];
            j--;
        }
        dataProduk[j + 1] = key;
    }
    cout << GREEN << "Produk berhasil diurutkan (Stok terbanyak).\n" << RESET;
}

int sequentialSearchHarga(Produk dataProduk[], int jumlahProduk, int targetHarga) {
    for (int i = 0; i < jumlahProduk; i++) {
        if (dataProduk[i].detail.harga == targetHarga) {
            return i;
        }
    }
    return -1;
}

void sortNamaAsc(Produk dataProduk[], int jumlahProduk) {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        for (int j = 0; j < jumlahProduk - i - 1; j++) {
            if (dataProduk[j].name > dataProduk[j + 1].name) {
                swap(dataProduk[j], dataProduk[j + 1]);
            }
        }
    }
    cout << GREEN << "Produk berhasil diurutkan (Nama A-Z).\n" << RESET;
}

int binarySearchNama(Produk dataProduk[], int jumlahProduk, string targetNama) {
    int kiri = 0, kanan = jumlahProduk - 1;
    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;

        if (dataProduk[tengah].name == targetNama) {
            return tengah;
        } else if (dataProduk[tengah].name < targetNama) {
            kiri = tengah + 1;
        } else {
            kanan = tengah - 1;
        }
    }
    return -1;
}

int main() {
    Pengguna admin = { "Aya", "062" };
    Pengguna dataPembeli[10] = {
        {"Ayu", "123"}
    };

    Produk dataProduk[10] = {
        {"AYE! Nude Eyeshadow Pallete", "Eye Makeup", {55000, 10}},
        {"AYE! Coral Glossy Tint", "Lip Makeup", {35000, 10}},
        {"AYE! Autumn Brown Blush", "Cheek Makeup", {40000, 10}},
        {"AYE! Curling Black Mascara", "Eye Makeup", {79000, 10}},
        {"AYE! Ivory Cushion W/ SPF++", "Base Makeup", {98000, 10}}
    };

    Pesanan dataPesanan[10];

    int jumlahProduk = 5;
    int jumlahPesanan = 0;
    int jumlahPembeli = 1;

    string enter;
    string username, password;
    bool loginAdmin = false;
    bool loginPembeli = false;
    int kesempatan;
    string pilihan;

    while (true) {
        try {
            clearScreen();
            cout << CYAN << "=============================================\n";
            cout << "     SISTEM PENJUALAN TOKO KOSMETIK >.<      \n";
            cout << "=============================================\n" << RESET;
            cout << "1. Daftar\n2. Masuk\n3. Keluar\n\nPilih (1/2/3): "; getline(cin, pilihan);
            if (pilihan.empty()) throw invalid_argument("Input tidak boleh kosong!");

            if (pilihan == "1") {
                if (jumlahPembeli >= 10) {
                    cout << "\nPendaftaran sudah penuh.\n";
                    pause();
                } else {
                    clearScreen();
                    cout << "=== PENDAFTARAN PEMBELI U_U ===\n";
                    try {
                        cout << "Username: "; getline(cin, username);
                        if (username.empty()) {
                            throw invalid_argument("Username tidak boleh kosong.");
                        }

                        cout << "Password: "; getline(cin, password);
                        if (password.empty()) {
                            throw invalid_argument("Password tidak boleh kosong.");
                        }

                        string inputName = username;
                        string inputPass = password;

                        bool usernameAda = false;
                        for (int i = 0; i < jumlahPembeli; i++) {
                            if (inputName == dataPembeli[i].name) {
                                usernameAda = true;
                                break;
                            }
                        }

                        if (inputName == admin.name || usernameAda) {
                            throw logic_error("Username sudah digunakan.");
                        }

                        dataPembeli[jumlahPembeli].name = inputName;
                        dataPembeli[jumlahPembeli].password = inputPass;
                        jumlahPembeli++;
                        cout << GREEN << "Pendaftaran berhasil.\n" << RESET;
                    } catch (const exception& e) {
                        cout << RED << "\n[ERROR] " << e.what() << RESET << endl;
                    }
                }
                pause();
            } else if (pilihan == "2") {
                loginAdmin = false;
                loginPembeli = false;
                kesempatan = 0;
                while (kesempatan < 3) {
                    clearScreen();
                    cout << "\n=== MASUK KE AKUN O,O ===\n";
                    try {
                        cout << "Username: "; getline(cin, username);
                        if (username.empty()) {
                            throw invalid_argument("Username tidak boleh kosong.");
                        }

                        cout << "Password: "; getline(cin, password);
                        if (password.empty()) {
                            throw invalid_argument("Password tidak boleh kosong.");
                        }

                        if (username == admin.name && password == admin.password) {
                            loginAdmin = true;
                            cout << GREEN << "\nSelamat! Anda berhasil masuk sebagai ADMIN.\n" << RESET;
                            pause();
                            break;
                        }

                        bool loginBerhasil = false;
                        for (int i = 0; i < jumlahPembeli; i++) {
                            if (username == dataPembeli[i].name && password == dataPembeli[i].password) {
                                loginBerhasil = true;
                                loginPembeli = true;
                                jumlahPesanan = 0;
                                cout << GREEN << "\nSelamat! Anda berhasil masuk sebagai PEMBELI.\n" << RESET;
                                pause();
                                break;
                            }
                        }

                        if (!loginBerhasil) {
                            throw runtime_error("Username atau password salah!");
                        } else {
                            kesempatan = 0;
                            break;
                        }
                    } catch (const exception& e) {
                        kesempatan++;
                        cout << RED << "\n[ERROR] " << e.what() << RESET << endl;
                        cout << "\nSisa kesempatan: " << 3 - kesempatan << endl;
                        
                        if (kesempatan < 3) {
                            cout << YELLOW << "Silakan coba lagi.\n" << RESET;
                            pause();
                        }
                        
                        if (kesempatan == 3) {
                            cout << RED << "Kesempatan login habis! Silakan coba beberapa saat lagi." << RESET;
                            return 0;
                        }
                    }
                }

                if (loginAdmin) {
                    do {
                        try {
                        clearScreen();
                        cout << "\n=== MENU ADMIN >u< ===\n";
                        cout << "1. Tambah Produk\n";
                        cout << "2. Lihat Produk\n";
                        cout << "3. Ubah Produk\n";
                        cout << "4. Hapus Produk\n";
                        cout << "5. Urutkan Produk\n";
                        cout << "6. Cari Produk\n";
                        cout << "7. Keluar\n";
                        cout << "----------------------\nPilih: "; getline(cin, pilihan);
                        if (pilihan.empty()) throw invalid_argument("Input tidak boleh kosong!");

                        if (pilihan == "1") {
                            clearScreen();
                            tambahProduk(jumlahProduk, dataProduk);
                            pause();
                        } else if (pilihan == "2") {
                            clearScreen();
                            lihatProduk(dataProduk, jumlahProduk);
                            pause();
                        } else if (pilihan == "3") {
                            clearScreen();
                            lihatProduk(dataProduk, jumlahProduk);
                            ubahProduk(jumlahProduk, dataProduk);
                            pause();
                        } else if (pilihan == "4") {
                            clearScreen();
                            lihatProduk(dataProduk, jumlahProduk);
                            hapusProduk(jumlahProduk, dataProduk);
                            pause();
                        } else if (pilihan == "5") {
                            clearScreen();
                            string pilihSort;
                            cout << "\n======== MENU PENGURUTAN PRODUK >;< ========\n";
                            cout << "1. Sort Berdasarkan Nama (Z-A)\n";
                            cout << "2. Sort Berdasarkan Harga (Murah-Mahal)\n";
                            cout << "3. Sort Berdasarkan Stok (Terbanyak)\n";
                            cout << "--------------------------------------------\n";
                            cout << "Pilih: "; getline(cin, pilihSort);
                            if (pilihSort.empty()) throw invalid_argument("Input tidak boleh kosong!");

                            if (pilihSort == "1") {
                                sortNamaDesc(dataProduk, jumlahProduk);
                                lihatProduk(dataProduk, jumlahProduk);
                            } else if (pilihSort == "2") {
                                sortHargaAsc(dataProduk, jumlahProduk);
                                lihatProduk(dataProduk, jumlahProduk);
                            } else if (pilihSort == "3") {
                                sortStokDesc(dataProduk, jumlahProduk);
                                lihatProduk(dataProduk, jumlahProduk);
                            } else {
                                cout << RED << "Pilihan tidak valid.\n" << RESET;
                            }
                            pause();
                        } else if (pilihan == "6") {
                            clearScreen();
                            try {
                                string pilihCari;
                                cout << "\n===== MENU SEARCHING =====\n";
                                cout << "1. Cari berdasarkan Harga\n"; //sequential search
                                cout << "2. Cari berdasarkan Nama\n"; //binary search
                                cout << "--------------------------\n";
                                cout << "Pilih: "; getline(cin, pilihCari);
                                if (pilihCari.empty()) throw invalid_argument("Input tidak boleh kosong!");

                                if (pilihCari == "1") {
                                    string tempHarga; cout << "\nMasukkan harga yang dicari: "; getline(cin, tempHarga);
                                    if (tempHarga.empty()) throw invalid_argument("Input tidak boleh kosong!");
                                    if (!all_of(tempHarga.begin(), tempHarga.end(), ::isdigit)) throw invalid_argument("Input harga harus angka!");
                                    int harga = stoi(tempHarga);
                                    int hasil = sequentialSearchHarga(dataProduk, jumlahProduk, harga);

                                    if (hasil != -1) {
                                        cout << "\nProduk ditemukan:\n";
                                        cout << dataProduk[hasil].name << " | " << dataProduk[hasil].kategori << " | Rp" << dataProduk[hasil].detail.harga << endl;
                                    } else {
                                        cout << "[!] Produk tidak ditemukan.\n";
                                    }
                                } else if (pilihCari == "2") {
                                    string nama; cout << "\nMasukkan nama produk: "; getline(cin, nama);
                                    if (nama.empty()) {
                                        throw invalid_argument("Nama produk tidak boleh kosong!");
                                    }

                                    sortNamaAsc(dataProduk, jumlahProduk);
                                    int hasil = binarySearchNama(dataProduk, jumlahProduk, nama);

                                    if (hasil != -1) {
                                        cout << "\nProduk ditemukan:\n";
                                        cout << dataProduk[hasil].name << " | " << dataProduk[hasil].kategori << " | Rp" << dataProduk[hasil].detail.harga << endl;
                                    } else {
                                        cout << "[!] Produk tidak ditemukan.\n";
                                    }
                                } else {
                                    cout << RED << "Pilihan tidak valid.\n" << RESET;
                                }
                            } catch (const exception& e) {
                                cout << RED << "\n[ERROR] " << e.what() << RESET << endl;
                            }
                            pause();
                        } else if (pilihan == "7") {
                            break;
                        } else {
                            cout << RED << "\nPilihan tidak valid." << RESET;
                            pause();
                        }
                        } catch (const exception& e) {
                            cout << RED << "\n[ERROR] " << e.what() << RESET << endl;
                            pause();
                        }
                    } while (pilihan != "7");
                } else if (loginPembeli) {
                    do {
                        try {
                        clearScreen();
                        cout << "\n==== MENU PEMBELI ^w^ ====\n";
                        cout << "1. Buat Pesanan\n";
                        cout << "2. Lihat Produk & Pesanan\n";
                        cout << "3. Hapus Pesanan\n";
                        cout << "4. Bayar Pesanan\n";
                        cout << "5. Keluar\n";
                        cout << "--------------------------\nPilih: "; getline(cin, pilihan);
                        if (pilihan.empty()) throw invalid_argument("Input tidak boleh kosong!");

                        if (pilihan == "1") {
                            clearScreen();
                            lihatProduk(dataProduk, jumlahProduk);
                            buatPesanan(jumlahProduk, dataProduk, dataPesanan, jumlahPesanan);
                            pause();
                        } else if (pilihan == "2") {
                            clearScreen();
                            lihatProduk(dataProduk, jumlahProduk);
                            lihatPesanan(dataPesanan, dataProduk, jumlahPesanan);
                            pause();
                        } else if (pilihan == "3") {
                            clearScreen();
                            lihatPesanan(dataPesanan, dataProduk, jumlahPesanan);
                            hapusPesanan(dataPesanan, jumlahPesanan);
                            pause();
                        } else if (pilihan == "4") {
                            clearScreen();
                            bayarPesanan(dataPesanan, dataProduk, jumlahPesanan);
                            pause();
                        } else if (pilihan == "5") {
                            break;
                        } else {
                            cout << RED << "\nPilihan tidak valid." << RESET;
                            pause();
                        }
                        } catch (const exception& e) {
                            cout << RED << "\n[ERROR] " << e.what() << RESET << endl;
                            pause();
                        }
                    } while (pilihan != "5");
                }
            } else if (pilihan == "3") {
                clearScreen();
                cout << GREEN << "\nTerima kasih telah mengunjungi AYE'S COSMETICS.\n" << RESET;
                break;
            } else {
                cout << RED << "\nPilihan tidak valid.\n" << RESET;
                pause();
            }
        } catch (const exception& e) {
            cout << RED << "\n[ERROR] Terjadi Kesalahan: " << e.what() << RESET << endl;
            pause();
        }
    }
    return 0;
}