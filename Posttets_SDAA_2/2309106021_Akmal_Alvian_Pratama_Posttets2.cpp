#include <iostream>
#include <cstring>
#include <iomanip>  // Untuk perataan tabel
#include <limits>   // Untuk validasi input angka
using namespace std;

// Struct untuk menyimpan data barang
struct Barang {
    int kode;
    char nama[50];
    char kategori[30];
    int stok;
    float harga;
};

// Deklarasi array barang dengan kapasitas maksimum 100
Barang daftarBarang[100];
int jumlahBarang = 0;

// Fungsi untuk memastikan input berupa integer
int inputInt(const char* prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear(); // Menghapus flag error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang salah
            cout << "Input harus berupa angka. Coba lagi.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

// Fungsi untuk memastikan input berupa float
float inputFloat(const char* prompt) {
    float value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input harus berupa angka desimal. Coba lagi.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

// Fungsi untuk memastikan input string tidak kosong
void inputString(const char* prompt, char* output, int size) {
    while (true) {
        cout << prompt;
        cin.getline(output, size);
        if (strlen(output) == 0) {
            cout << "Input tidak boleh kosong. Coba lagi.\n";
        } else {
            break;
        }
    }
}

// Fungsi untuk menambah barang
void tambahBarang() {
    if (jumlahBarang < 100) {
        Barang* barangBaru = &daftarBarang[jumlahBarang];

        barangBaru->kode = inputInt("Masukkan kode barang: ");
        inputString("Masukkan nama barang: ", barangBaru->nama, 50);
        inputString("Masukkan kategori barang: ", barangBaru->kategori, 30);

        barangBaru->stok = inputInt("Masukkan stok barang: ");
        while (barangBaru->stok < 0) {
            cout << "Stok tidak boleh negatif. Coba lagi.\n";
            barangBaru->stok = inputInt("Masukkan stok barang: ");
        }

        barangBaru->harga = inputFloat("Masukkan harga barang: ");
        while (barangBaru->harga <= 0) {
            cout << "Harga harus lebih dari 0. Coba lagi.\n";
            barangBaru->harga = inputFloat("Masukkan harga barang: ");
        }

        jumlahBarang++;
        cout << "Barang berhasil ditambahkan!\n";
    } else {
        cout << "Stok penuh, tidak dapat menambah barang lagi.\n";
    }
}

// Fungsi untuk menampilkan semua barang dalam bentuk tabel
void tampilkanTabelBarang() {
    cout << left << setw(10) << "Kode" 
         << setw(30) << "Nama Barang" 
         << setw(20) << "Kategori" 
         << setw(10) << "Stok" 
         << setw(15) << "Harga" << endl;
    cout << "---------------------------------------------------------------\n";
    
    for (int i = 0; i < jumlahBarang; i++) {
        Barang* barang = &daftarBarang[i];
        cout << left << setw(10) << barang->kode 
             << setw(30) << barang->nama 
             << setw(20) << barang->kategori 
             << setw(10) << barang->stok 
             << setw(15) << fixed << setprecision(2) << barang->harga << endl;
    }
    cout << "---------------------------------------------------------------\n";
}

// Fungsi untuk melihat semua barang
void lihatBarang() {
    if (jumlahBarang == 0) {
        cout << "Tidak ada barang di stok.\n";
    } else {
        tampilkanTabelBarang();
    }
}

// Fungsi untuk mengubah barang berdasarkan kode
void ubahBarang() {
    int kode = inputInt("Masukkan kode barang yang ingin diubah: ");

    for (int i = 0; i < jumlahBarang; i++) {
        if (daftarBarang[i].kode == kode) {
            Barang* barang = &daftarBarang[i];
            cout << "Barang ditemukan, masukkan data baru.\n";

            inputString("Masukkan nama barang: ", barang->nama, 50);
            inputString("Masukkan kategori barang: ", barang->kategori, 30);

            barang->stok = inputInt("Masukkan stok barang: ");
            while (barang->stok < 0) {
                cout << "Stok tidak boleh negatif. Coba lagi.\n";
                barang->stok = inputInt("Masukkan stok barang: ");
            }

            barang->harga = inputFloat("Masukkan harga barang: ");
            while (barang->harga <= 0) {
                cout << "Harga harus lebih dari 0. Coba lagi.\n";
                barang->harga = inputFloat("Masukkan harga barang: ");
            }

            cout << "Data barang berhasil diubah!\n";
            return;
        }
    }
    cout << "Barang dengan kode tersebut tidak ditemukan.\n";
}

// Fungsi untuk menghapus barang berdasarkan kode
void hapusBarang() {
    int kode = inputInt("Masukkan kode barang yang ingin dihapus: ");

    for (int i = 0; i < jumlahBarang; i++) {
        if (daftarBarang[i].kode == kode) {
            for (int j = i; j < jumlahBarang - 1; j++) {
                daftarBarang[j] = daftarBarang[j + 1];
            }
            jumlahBarang--;
            cout << "Barang berhasil dihapus!\n";
            return;
        }
    }
    cout << "Barang dengan kode tersebut tidak ditemukan.\n";
}

// Fungsi utama
int main() {
    int pilihan;
    do {
        cout << "\nManajemen Stok Barang Indomaret\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Lihat Barang\n";
        cout << "3. Ubah Barang\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Keluar\n";
        cout << "Pilih opsi: ";
        pilihan = inputInt("");

        switch (pilihan) {
            case 1:
                tambahBarang();
                break;
            case 2:
                lihatBarang();
                break;
            case 3:
                ubahBarang();
                break;
            case 4:
                hapusBarang();
                break;
            case 5:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);

    return 0;
}