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

int main() {
    Pengguna admin = {"Aya", "062"}; //2509106062 (diambil dari tiga digit terakhir NIM)
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
    int kesempatan = 0;
    string pilihan;  

    while (true) {
        system("cls");
        cout << "=== SISTEM PENJUALAN TOKO KOSMETIK >.< ===\n";
        cout << "Selamat datang di AYE'S COSMETICS!\n";
        cout << "1. Daftar\n2. Masuk\nPilih (1/2): ";
        cin >> pilihan;

        if (pilihan == "1") {
            if (jumlahPembeli >= 10) {
                cout << "\nPendaftaran sudah penuh.\n";
                cout << "Lanjutkan (y): "; cin >> enter;
                continue;
            } else {
                system("cls");
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
            break;
        } else {
            cout << "Pilihan tidak valid.\n\n";
            cout << "Lanjutkan (y): "; cin >> enter;
        }
    }
    
    while (kesempatan < 3) {
        system("cls");
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
                    system("cls");
                    cout << "Maaf, kesempatan sudah habis. Silahkan coba beberapa saat lagi.\n";
                    return 0;
                }
            }
        }
    }

    if (loginAdmin) {
        do {
            system("cls");
            cout << "\n=== MENU ADMIN  >u< ===\n";
            cout << "1. Tambah Produk\n";
            cout << "2. Lihat Produk\n";
            cout << "3. Ubah Produk\n";
            cout << "4. Hapus Produk\n";
            cout << "5. Keluar\n";
            cout << "Pilih: "; cin >> pilihan;

            if (pilihan == "1") {
                system("cls");
                if (jumlahProduk >= 10) {
                    cout << "Jumlah produk sudah mencapai batas maksimum.\n";
                    cout << "Lanjutkan (y): "; cin >> enter;
                } else {
                    cout << "\nNama Produk: ";
                    getline(cin >> ws, dataProduk[jumlahProduk].name);

                    cout << "Kategori: ";
                    getline(cin >> ws, dataProduk[jumlahProduk].kategori);

                    cout << "Harga: "; cin >> dataProduk[jumlahProduk].detail.harga;

                    if (dataProduk[jumlahProduk].detail.harga < 20000) {
                        cout << "\nHarga tidak boleh kurang dari Rp20.000,00.\n";
                        cout << "Lanjutkan (y): "; cin >> enter;
                    } else {
                        cout << "Stok: "; cin >> dataProduk[jumlahProduk].detail.stok;
                        if (dataProduk[jumlahProduk].detail.stok < 0) {
                            cout << "\nStok tidak boleh negatif.\n";
                            cout << "Lanjutkan (y): "; cin >> enter;
                        } else {
                            jumlahProduk++;
                            cout << "\nProduk berhasil ditambahkan.\n";
                            cout << "Lanjutkan (y): "; cin >> enter;
                        }
                    }
                }
            } else if (pilihan == "2") {
                system("cls");
                cout << "=====================================================================\n";
                cout << "No  Nama Produk                    Kategori        Harga     Stok\n";
                cout << "=====================================================================\n";

                for (int i = 0; i < jumlahProduk; i++) {
                    cout << i+1 << "   ";

                    cout << dataProduk[i].name;
                    int spasi1 = 30 - dataProduk[i].name.length();
                    for (int j = 0; j < spasi1; j++) cout << " ";

                    cout << dataProduk[i].kategori;
                    int spasi2 = 17 - dataProduk[i].kategori.length();
                    for (int j = 0; j < spasi2; j++) cout << " ";

                    cout << dataProduk[i].detail.harga << "      ";
                    cout << dataProduk[i].detail.stok << endl;
                }
                cout << "\nLanjutkan (y): "; cin >> enter;
            } else if (pilihan == "3") {
                system("cls");
                cout << "=====================================================================\n";
                cout << "No  Nama Produk                    Kategori        Harga     Stok\n";
                cout << "=====================================================================\n";

                for (int i = 0; i < jumlahProduk; i++) {
                    cout << i+1 << "   ";

                    cout << dataProduk[i].name;
                    int spasi1 = 30 - dataProduk[i].name.length();
                    for (int j = 0; j < spasi1; j++) cout << " ";

                    cout << dataProduk[i].kategori;
                    int spasi2 = 17 - dataProduk[i].kategori.length();
                    for (int j = 0; j < spasi2; j++) cout << " ";

                    cout << dataProduk[i].detail.harga << "      ";
                    cout << dataProduk[i].detail.stok << endl;
                }

                int ubah;
                cout << "\nNomor produk: "; cin >> ubah;
                
                if (ubah > 0 && ubah <= jumlahProduk) {
                    int hargaBaru;
                    int stokBaru;

                    cout << "Harga baru: ";
                    cin >> hargaBaru;

                    if (hargaBaru < 20000) {
                        cout << "\nHarga tidak boleh kurang dari Rp20.000,00.\n";
                        cout << "Lanjutkan (y): "; cin >> enter;
                    } else {
                        cout << "Stok baru: ";
                        cin >> stokBaru;

                        if (stokBaru < 0) {
                            cout << "\nStok tidak boleh negatif.\n";
                            cout << "Lanjutkan (y): "; cin >> enter;
                        } else {
                            dataProduk[ubah-1].detail.harga = hargaBaru;
                            dataProduk[ubah-1].detail.stok = stokBaru;

                            cout << "\nProduk diperbarui.\n";
                            cout << "Lanjutkan (y): "; cin >> enter;
                        }
                    }
                } else {
                    cout << "Nomor tidak valid.\n";
                    cout << "\nLanjutkan (y): "; cin >> enter;
                }
            } else if (pilihan == "4") {
                system("cls");
                cout << "=====================================================================\n";
                cout << "No  Nama Produk                    Kategori        Harga     Stok\n";
                cout << "=====================================================================\n";

                for (int i = 0; i < jumlahProduk; i++) {
                    cout << i+1 << "   ";

                    cout << dataProduk[i].name;
                    int spasi1 = 30 - dataProduk[i].name.length();
                    for (int j = 0; j < spasi1; j++) cout << " ";

                    cout << dataProduk[i].kategori;
                    int spasi2 = 17 - dataProduk[i].kategori.length();
                    for (int j = 0; j < spasi2; j++) cout << " ";

                    cout << dataProduk[i].detail.harga << "      ";
                    cout << dataProduk[i].detail.stok << endl;
                }

                int hapus;
                cout << "\nNomor produk: "; cin >> hapus;

                if (hapus > 0 && hapus <= jumlahProduk) {
                    for (int i = hapus-1; i < jumlahProduk-1; i++) {
                        dataProduk[i] = dataProduk[i+1];
                    }
                    jumlahProduk--;
                    cout << "Produk dihapus.\n";
                    cout << "\nLanjutkan (y): "; cin >> enter;
                } else {
                    cout << "Pilihan tidak valid.\n";
                    cout << "\nLanjutkan (y): "; cin >> enter;
                }
            } else if (pilihan == "5") {
                break;
            } else {
                cout << "\nPilihan tidak valid.";
                cout << "\nLanjutkan (y): "; cin >> enter;
            }
        } while (pilihan != "5");
    } else {
        do {
            system("cls");
            cout << "\n==== MENU PEMBELI ^w^ ====\n";
            cout << "1. Lihat Produk\n";
            cout << "2. Buat Pesanan\n";
            cout << "3. Lihat Pesanan\n";
            cout << "4. Hapus Pesanan\n";
            cout << "5. Bayar Pesanan\n";
            cout << "6. Keluar\n";
            cout << "Pilih: "; cin >> pilihan;
            
            int pilihProduk, jumlah;

            if (pilihan == "1") {
                system("cls");
                cout << "=====================================================================\n";
                cout << "No  Nama Produk                    Kategori        Harga     Stok\n";
                cout << "=====================================================================\n";

                for (int i = 0; i < jumlahProduk; i++) {
                    cout << i+1 << "   ";

                    cout << dataProduk[i].name;
                    int spasi1 = 30 - dataProduk[i].name.length();
                    for (int j = 0; j < spasi1; j++) cout << " ";

                    cout << dataProduk[i].kategori;
                    int spasi2 = 17 - dataProduk[i].kategori.length();
                    for (int j = 0; j < spasi2; j++) cout << " ";

                    cout << dataProduk[i].detail.harga << "      ";
                    cout << dataProduk[i].detail.stok << endl;
                }
                cout << "\nLanjutkan (y): "; cin >> enter;
            } else if (pilihan == "2") {
                system("cls");
                cout << "=====================================================================\n";
                cout << "No  Nama Produk                    Kategori        Harga     Stok\n";
                cout << "=====================================================================\n";

                for (int i = 0; i < jumlahProduk; i++) {
                    cout << i+1 << "   ";

                    cout << dataProduk[i].name;
                    int spasi1 = 30 - dataProduk[i].name.length();
                    for (int j = 0; j < spasi1; j++) cout << " ";

                    cout << dataProduk[i].kategori;
                    int spasi2 = 17 - dataProduk[i].kategori.length();
                    for (int j = 0; j < spasi2; j++) cout << " ";

                    cout << dataProduk[i].detail.harga << "      ";
                    cout << dataProduk[i].detail.stok << endl;
                }

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
                cout << "\nLanjutkan (y): "; cin >> enter;
            } else if (pilihan == "3") {
                system("cls");
                cout << "\n=== PESANAN ANDA ===\n";
                if (jumlahPesanan == 0) {
                    cout << "Belum ada pesanan.\n";
                } else {
                    for (int i = 0; i < jumlahPesanan; i++) {
                        int idx = dataPesanan[i].idxProduk;
                        cout << i+1 << ". " << dataProduk[idx].name << " | Jumlah: " << dataPesanan[i].jumlah << endl;
                    }
                }
                cout << "\nLanjutkan (y): "; cin >> enter;
            } else if (pilihan == "4") {
                system("cls");
                cout << "\n=== PESANAN ANDA ===\n";
                if (jumlahPesanan == 0) {
                    cout << "Belum ada pesanan.\n";
                } else {
                    for (int i = 0; i < jumlahPesanan; i++) {
                        int idx = dataPesanan[i].idxProduk;
                        cout << i+1 << ". " << dataProduk[idx].name << " | Jumlah: " << dataPesanan[i].jumlah << endl;
                    }
                }

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
                cout << "\nLanjutkan (y): "; cin >> enter;
            } else if (pilihan == "5") {
                system("cls");
                cout << "\n=== BAYAR PESANAN ===\n";
                if (jumlahPesanan == 0) {
                    cout << "Belum ada pesanan.\n";
                } else {
                    int total = 0;

                    for (int i = 0; i < jumlahPesanan; i++) {
                        int idx = dataPesanan[i].idxProduk;
                        int harga = dataProduk[idx].detail.harga;
                        int jumlah = dataPesanan[i].jumlah;

                        cout << i+1 << ". " << dataProduk[idx].name << " | Jumlah: " << jumlah << " | Rp" << harga * jumlah << endl;
                        total += harga * jumlah;
                    }

                    string konfirmasi;
                    cout << "\nTotal bayar: Rp" << total << endl;
                    cout << "Konfirmasi beli? (y/n): "; cin >> konfirmasi;
                    if (konfirmasi == "y" || konfirmasi == "Y") {
                        for (int i = 0; i < jumlahPesanan; i++) {
                            int idx = dataPesanan[i].idxProduk;
                            int jml = dataPesanan[i].jumlah;

                            dataProduk[idx].detail.stok -= jml;
                        }
                        jumlahPesanan = 0;
                        cout << "Pembelian berhasil.\n";
                    } else {
                        cout << "Pembelian dibatalkan.\n";
                    }
                }
                cout << "\nLanjutkan (y): "; cin >> enter;
            } else if (pilihan == "6") {
                break;
            } else {
                cout << "\nPilihan tidak valid.";
                cout << "\nLanjutkan (y): "; cin >> enter;
            }
        } while (pilihan != "6");
    }
    system("cls");
    cout << "\nTerima kasih telah mengunjungi AYE'S COSMETICS.\n";
    return 0;
}