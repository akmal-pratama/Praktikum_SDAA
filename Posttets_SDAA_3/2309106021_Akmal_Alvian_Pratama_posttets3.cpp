#include <iostream>
#include <cstring>
#include <iomanip>  
#include <limits>   
using namespace std;

// Struct untuk menyimpan data barang di dalam node linked list
struct Barang {
    int kode;
    char nama[50];
    char kategori[30];
    int stok;
    float harga;
    Barang* next;
};

// Head dari linked list
Barang* head = nullptr;

// Fungsi untuk memastikan input berupa integer
int inputInt(const char* prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear(); // Menghapus flag error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

// Fungsi untuk menambah barang ke linked list
void tambahBarang() {
    Barang* barangBaru = new Barang;

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

    barangBaru->next = nullptr;

    if (head == nullptr) {
        head = barangBaru; // Jika list kosong, node baru menjadi head
    } else {
        Barang* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = barangBaru; // Tambahkan node di akhir list
    }

    cout << "Barang berhasil ditambahkan!\n";
}

// Fungsi untuk menampilkan semua barang dalam bentuk tabel
void tampilkanTabelBarang() {
    if (head == nullptr) {
        cout << "Tidak ada barang di stok.\n";
        return;
    }

    cout << left << setw(10) << "Kode" 
         << setw(30) << "Nama Barang" 
         << setw(20) << "Kategori" 
         << setw(10) << "Stok" 
         << setw(15) << "Harga" << endl;
    cout << "---------------------------------------------------------------\n";
    
    Barang* temp = head;
    while (temp != nullptr) {
        cout << left << setw(10) << temp->kode 
             << setw(30) << temp->nama 
             << setw(20) << temp->kategori 
             << setw(10) << temp->stok 
             << setw(15) << fixed << setprecision(2) << temp->harga << endl;
        temp = temp->next;
    }
    cout << "---------------------------------------------------------------\n";
}

// Fungsi untuk melihat semua barang
void lihatBarang() {
    tampilkanTabelBarang();
}

// Fungsi untuk mengubah barang berdasarkan kode
void ubahBarang() {
    int kode = inputInt("Masukkan kode barang yang ingin diubah: ");

    Barang* temp = head;
    while (temp != nullptr) {
        if (temp->kode == kode) {
            cout << "Barang ditemukan, masukkan data baru.\n";

            inputString("Masukkan nama barang: ", temp->nama, 50);
            inputString("Masukkan kategori barang: ", temp->kategori, 30);

            temp->stok = inputInt("Masukkan stok barang: ");
            while (temp->stok < 0) {
                cout << "Stok tidak boleh negatif. Coba lagi.\n";
                temp->stok = inputInt("Masukkan stok barang: ");
            }

            temp->harga = inputFloat("Masukkan harga barang: ");
            while (temp->harga <= 0) {
                cout << "Harga harus lebih dari 0. Coba lagi.\n";
                temp->harga = inputFloat("Masukkan harga barang: ");
            }

            cout << "Data barang berhasil diubah!\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Barang dengan kode tersebut tidak ditemukan.\n";
}

// Fungsi untuk menghapus barang berdasarkan kode
void hapusBarang() {
    int kode = inputInt("Masukkan kode barang yang ingin dihapus: ");

    Barang* temp = head;
    Barang* prev = nullptr;

    while (temp != nullptr) {
        if (temp->kode == kode) {
            if (prev == nullptr) {
                head = temp->next; // Jika barang ada di head
            } else {
                prev->next = temp->next; // Jika barang ada di tengah atau akhir
            }
            delete temp;
            cout << "Barang berhasil dihapus!\n";
            return;
        }
        prev = temp;
        temp = temp->next;
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