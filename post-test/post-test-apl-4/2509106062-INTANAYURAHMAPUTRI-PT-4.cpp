#include <iostream>
using namespace std;

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

void clearScreen() {
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
//Kode untuk membersihkan layar berdasarkan sistem operasi yang digunakan ini saya dapatkan dari website Stack Overflow.
}

void lihatProduk(Produk *dataProduk, int jumlahProduk) {
    Produk *pointer = dataProduk;

    cout << "=====================================================================\n";
    cout << "No  Nama Produk                    Kategori        Harga     Stok\n";
    cout << "=====================================================================\n";

    for (int i = 0; i < jumlahProduk; i++) {
        cout << i + 1 << "   ";

        cout << (pointer + i)->name;
        int spasi1 = 30 - (pointer + i)->name.length();
        for (int j = 0; j < spasi1; j++) cout << " ";

        cout << (pointer + i)->kategori;
        int spasi2 = 17 - (pointer + i)->kategori.length();
        for (int j = 0; j < spasi2; j++) cout << " ";

        cout << (pointer + i)->detail.harga << "      ";
        cout << (pointer + i)->detail.stok << endl;
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
    cout << "=== TAMBAH PRODUK (z'v'z) ===";
    if (jumlahProduk >= 10) {
        cout << "\nJumlah produk sudah mencapai batas maksimum gudang penyimpanan.\n";
    } else {
        cout << "\nNama Produk: ";
        getline(cin >> ws, dataProduk[jumlahProduk].name);

        cout << "Kategori: ";
        getline(cin >> ws, dataProduk[jumlahProduk].kategori);

        cout << "Harga: "; cin >> dataProduk[jumlahProduk].detail.harga;

        if (dataProduk[jumlahProduk].detail.harga < 20000) {
            cout << "\nHarga tidak boleh kurang dari Rp20.000,00.\n";
        } else {
            cout << "Stok: "; cin >> dataProduk[jumlahProduk].detail.stok;
            if (dataProduk[jumlahProduk].detail.stok < 0) {
                cout << "\nStok tidak boleh negatif.\n";
            } else {
                jumlahProduk++;
                cout << "\nProduk berhasil ditambahkan.\n";
            }
        }
    }
}

void ubahProduk(int &jumlahProduk, Produk dataProduk[]) {
    int ubah;
    cout << "\nNomor produk: "; cin >> ubah;
    
    if (ubah > 0 && ubah <= jumlahProduk) {
        int hargaBaru;
        int stokBaru;
        cout << "Harga baru: "; cin >> hargaBaru;

        if (hargaBaru < 20000) {
            cout << "Harga tidak boleh kurang dari Rp20.000,00.\n";
        } else {
            cout << "Stok baru: "; cin >> stokBaru;

            if (stokBaru < 0) {
                cout << "Stok tidak boleh negatif.\n";
            } else {
                dataProduk[ubah-1].detail.harga = hargaBaru;
                dataProduk[ubah-1].detail.stok = stokBaru;
                cout << "Produk diperbarui.\n";
            }
        }
    } else {
        cout << "Nomor tidak valid.\n";
    }
}

void hapusProduk(int &jumlahProduk, Produk dataProduk[]) {
    int hapus;
    cout << "\nNomor produk: "; cin >> hapus;

    if (hapus > 0 && hapus <= jumlahProduk) {
        for (int i = hapus-1; i < jumlahProduk-1; i++) {
            dataProduk[i] = dataProduk[i+1];
        }
        jumlahProduk--;
        cout << "Produk dihapus.\n";
    } else {
        cout << "Pilihan tidak valid.\n";
    }
}

void buatPesanan(int jumlahProduk, Produk dataProduk[], Pesanan dataPesanan[], int &jumlahPesanan) {
    int pilihProduk, jumlah;
    cout << "\nPilih nomor produk: "; cin >> pilihProduk;

    if (pilihProduk > 0 && pilihProduk <= jumlahProduk) {
        cout << "Jumlah beli: "; cin >> jumlah;

        if (jumlah <= 0) {
            cout << "Jumlah harus lebih dari 0.\n";
        } else if (jumlahPesanan >= 10) {
            cout << "Pesanan sudah mencapai batas maksimum.\n";
        } else if (jumlah <= dataProduk[pilihProduk-1].detail.stok) {

            dataPesanan[jumlahPesanan].idxProduk = pilihProduk-1;
            dataPesanan[jumlahPesanan].jumlah = jumlah;
            jumlahPesanan++;

            cout << "Pesanan berhasil ditambahkan.\n";
        } else {
            cout << "Stok tidak cukup.\n";
        }
    } else {
        cout << "Nomor tidak valid.\n";
    }
}

void hapusPesanan(Pesanan dataPesanan[], int &jumlahPesanan) {
    int hapus;
    cout << "\nNomor pesanan: "; cin >> hapus;

    if (hapus > 0 && hapus <= jumlahPesanan) {
        for (int i = hapus-1; i < jumlahPesanan-1; i++) {
            dataPesanan[i] = dataPesanan[i+1];
        }
        jumlahPesanan--;
        cout << "Pesanan dihapus.\n";
    } else {
        cout << "Nomor tidak valid.\n";
    }
}

int hitungTotal(Pesanan dataPesanan[], Produk dataProduk[], int jumlahPesanan) {
    if (jumlahPesanan == 0) return 0;
    int idx = dataPesanan[jumlahPesanan - 1].idxProduk;
    int harga = dataProduk[idx].detail.harga;
    int jumlah = dataPesanan[jumlahPesanan - 1].jumlah;
    return (harga * jumlah) + hitungTotal(dataPesanan, dataProduk, jumlahPesanan - 1);
}

int hitungTotal(Pesanan dataPesanan[], Produk dataProduk[], int jumlahPesanan, int pajak) {
    int total = hitungTotal(dataPesanan, dataProduk, jumlahPesanan);
    total = total + (total * pajak / 100);
    return total;
}

void bayarPesanan(Pesanan *dataPesanan, Produk *dataProduk, int *jumlahPesanan) {
    if (*jumlahPesanan == 0) {
        cout << "Belum ada pesanan.";
    } else {
        cout << "=====================================================================\n";
        cout << "No  Nama Produk                    Harga     Jumlah     Subtotal\n";
        cout << "=====================================================================\n";

        for (int i = 0; i < *jumlahPesanan; i++) {
            int idx = dataPesanan[i].idxProduk;
            string nama = dataProduk[idx].name;
            int harga = dataProduk[idx].detail.harga;
            int jumlah = dataPesanan[i].jumlah;
            int subtotal = harga * jumlah;

            cout << i + 1 << "   ";

            cout << nama;
            int spasi1 = 30 - nama.length();
            for (int j = 0; j < spasi1; j++) cout << " ";

            cout << harga;
            int spasi2 = 10 - to_string(harga).length();
            for (int j = 0; j < spasi2; j++) cout << " ";

            cout << jumlah;
            int spasi3 = 10 - to_string(jumlah).length();
            for (int j = 0; j < spasi3; j++) cout << " ";

            cout << subtotal << endl;
        }

        cout << "=====================================================================\n";

        int total = hitungTotal(dataPesanan, dataProduk, *jumlahPesanan);
        int totalPajak = hitungTotal(dataPesanan, dataProduk, *jumlahPesanan, 5);

        cout << "Total        : Rp" << total << endl;
        cout << "Total + Pajak: Rp" << totalPajak << endl;

        string konfirmasi;
        cout << "\nKonfirmasi (y/n): "; cin >> konfirmasi;

        if (konfirmasi == "y" || konfirmasi == "Y") {
            for (int i = 0; i < *jumlahPesanan; i++) {
                int idx = dataPesanan[i].idxProduk;
                dataProduk[idx].detail.stok -= dataPesanan[i].jumlah;
            }
            *jumlahPesanan = 0;
            cout << "Pembayaran berhasil.\n";
        } else {
            cout << "Pembayaran dibatalkan.\n";}
    }
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
    int kesempatan;
    string pilihan;

    while (true) {
        clearScreen();
        cout << "=== SISTEM PENJUALAN TOKO KOSMETIK >.< ===\n";
        cout << "Selamat datang di AYE'S COSMETICS!\n";
        cout << "1. Daftar\n2. Masuk\n3. Keluar\n\nPilih (1/2/3): ";
        cin >> pilihan;

        if (pilihan == "1") {
            if (jumlahPembeli >= 10) {
                cout << "\nPendaftaran sudah penuh.\n";
                cout << "Lanjutkan (y): "; cin >> enter;
                continue;
            } else {
                clearScreen();
                cout << "=== PENDAFTARAN PEMBELI U_U ===\n";
                cout << "Username: "; cin >> dataPembeli[jumlahPembeli].name;
                cout << "Password: "; cin >> dataPembeli[jumlahPembeli].password;
                bool usernameAda = false;

                for (int i = 0; i < jumlahPembeli; i++) {
                    if (dataPembeli[jumlahPembeli].name == dataPembeli[i].name) {
                        usernameAda = true;
                        break;
                    }
                }

                if (dataPembeli[jumlahPembeli].name == admin.name || usernameAda) {
                    cout << "Username sudah digunakan oleh pengguna lain.\n\n";
                    cout << "Lanjutkan (y): "; cin >> enter;
                    continue;
                } else {
                    jumlahPembeli++;
                    cout << "Pendaftaran berhasil.\n\n";
                    cout << "Lanjutkan (y): "; cin >> enter;
                }
            }
        } else if (pilihan == "2") {
            loginAdmin = false;
            kesempatan = 0;
            while (kesempatan < 3) {
                clearScreen();
                cout << "\n=== MASUK KE AKUN O,O ===\n";
                cout << "Username: "; cin >> username;
                cout << "Password: "; cin >> password;
                
                if (username == admin.name && password == admin.password) {
                    loginAdmin = true;
                    cout << "\nSelamat! Anda berhasil masuk sebagai ADMIN.\n";
                    cout << "Lanjutkan (y): "; cin >> enter;
                    break;
                } else {
                    bool loginBerhasil = false;
                    for (int i = 0; i < jumlahPembeli; i++) {
                        if (username == dataPembeli[i].name && password == dataPembeli[i].password) {
                            loginBerhasil = true;
                            cout << "\nSelamat! Anda berhasil masuk sebagai PEMBELI.\n";
                            cout << "Lanjutkan (y): "; cin >> enter;
                            break;
                        }
                    }
                    if (loginBerhasil) {
                        break;
                    } else {
                        kesempatan++;
                        cout << "Gagal masuk. Sisa kesempatan: " << 3 - kesempatan << endl;
                        cout << "\nLanjutkan (y): "; cin >> enter;
                        if (kesempatan == 3) {
                            clearScreen();
                            cout << "Maaf, kesempatan sudah habis. Silahkan coba beberapa saat lagi.\n";
                            return 0;
                        }
                    }
                }
            }

            if (loginAdmin) {
                do {
                    clearScreen();
                    cout << "\n=== MENU ADMIN >u< ===\n";
                    cout << "1. Tambah Produk\n";
                    cout << "2. Lihat Produk\n";
                    cout << "3. Ubah Produk\n";
                    cout << "4. Hapus Produk\n";
                    cout << "5. Keluar\n\nPilih: ";
                    cin >> pilihan;

                    if (pilihan == "1") {
                        clearScreen();
                        tambahProduk(jumlahProduk, dataProduk);
                        cout << "Lanjutkan (y): "; cin >> enter;
                        continue;
                    } else if (pilihan == "2") {
                        clearScreen();
                        lihatProduk(dataProduk, jumlahProduk);
                        cout << "\nLanjutkan (y): "; cin >> enter;
                        continue;
                    } else if (pilihan == "3") {
                        clearScreen();
                        lihatProduk(dataProduk, jumlahProduk);
                        ubahProduk(jumlahProduk, dataProduk);
                        cout << "\nLanjutkan (y): "; cin >> enter;
                        continue;
                    } else if (pilihan == "4") {
                        clearScreen();
                        lihatProduk(dataProduk, jumlahProduk);
                        hapusProduk(jumlahProduk, dataProduk);
                        cout << "\nLanjutkan (y): "; cin >> enter;
                        continue;
                    } else if (pilihan == "5") {
                        break;
                    } else {
                        cout << "\nPilihan tidak valid.";
                        cout << "\nLanjutkan (y): "; cin >> enter;
                    }
                } while (pilihan != "5");
            } else {
                do {
                    clearScreen();
                    cout << "\n==== MENU PEMBELI ^w^ ====\n";
                    cout << "1. Buat Pesanan\n";
                    cout << "2. Lihat Produk & Pesanan\n";
                    cout << "3. Hapus Pesanan\n";
                    cout << "4. Bayar Pesanan\n";
                    cout << "5. Keluar\n\nPilih: ";
                    cin >> pilihan;

                    if (pilihan == "1") {
                        clearScreen();
                        lihatProduk(dataProduk, jumlahProduk);
                        buatPesanan(jumlahProduk, dataProduk, dataPesanan, jumlahPesanan);
                        cout << "\nLanjutkan (y): "; cin >> enter;
                    } else if (pilihan == "2") {
                        clearScreen();
                        lihatProduk(dataProduk, jumlahProduk);
                        lihatPesanan(dataPesanan, dataProduk, jumlahPesanan);
                        cout << "\nLanjutkan (y): "; cin >> enter;
                    } else if (pilihan == "3") {
                        clearScreen();
                        lihatPesanan(dataPesanan, dataProduk, jumlahPesanan);
                        hapusPesanan(dataPesanan, jumlahPesanan);
                        cout << "\nLanjutkan (y): "; cin >> enter;
                    } else if (pilihan == "4") {
                    clearScreen();
                    bayarPesanan(dataPesanan, dataProduk, &jumlahPesanan);
                    cout << "\nLanjutkan (y): "; cin >> enter;
                    } else if (pilihan == "5") {
                        break;
                    } else {
                        cout << "\nPilihan tidak valid.";
                        cout << "\nLanjutkan (y): "; cin >> enter;
                    }
                } while (pilihan != "5");
            }
        } else if (pilihan == "3") {
            clearScreen();
            cout << "\nTerima kasih telah mengunjungi AYE'S COSMETICS.\n";
            break;
        } else {
            cout << "\nPilihan tidak valid.\n";
            cout << "Lanjutkan (y): "; cin >> enter;
        }
    }
    return 0;
}