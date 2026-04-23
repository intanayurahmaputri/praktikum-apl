#ifndef HITUNG_TOKO_H
#define HITUNG_TOKO_H
#include <stdexcept>

namespace TokoLib {
    inline int hitungTotalDasar(int harga, int jumlah) {
        if (jumlah < 0 || harga < 0) {
            throw std::invalid_argument("Jumlah tidak boleh negatif!");
        }
        return harga * jumlah;
    }

    inline int hitungDenganPajak(int total, int persenPajak) {
        if (persenPajak < 0 || persenPajak > 100) throw std::invalid_argument("Pajak tidak valid (0-100)!");
        return total + (total * persenPajak / 100);
    }

    inline int hitungDenganDiskon(int total, int persenDiskon) {
        if (persenDiskon < 0 || persenDiskon > 100) {
            throw std::invalid_argument("Diskon tidak valid (0-100)!");
        }
        return total - (total * persenDiskon / 100);
    }

    inline bool validasiHarga(int harga) {
        return harga >= 20000;
    }
}

#endif