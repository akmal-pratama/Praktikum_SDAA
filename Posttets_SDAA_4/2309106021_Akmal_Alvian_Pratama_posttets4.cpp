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

// Head untuk Stack dan Queue
Barang* stackTop = nullptr;
Barang* queueFront = nullptr;
Barang* queueRear = nullptr;

// Fungsi-fungsi input validation (tidak berubah)
int inputInt(const char* prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input harus berupa angka. Coba lagi.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

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

// Fungsi untuk membuat node baru
Barang* createBarang() {
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
    return barangBaru;
}

// Fungsi untuk menambah barang ke linked list
void tambahBarang() {
    Barang* barangBaru = createBarang();

    if (head == nullptr) {
        head = barangBaru;
    } else {
        Barang* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = barangBaru;
    }

    cout << "Barang berhasil ditambahkan!\n";
}

// Fungsi untuk menampilkan semua barang dalam bentuk tabel
void tampilkanTabelBarang(Barang* start) {
    if (start == nullptr) {
        cout << "Tidak ada barang di stok.\n";
        return;
    }

    cout << left << setw(10) << "Kode" 
         << setw(30) << "Nama Barang" 
         << setw(20) << "Kategori" 
         << setw(10) << "Stok" 
         << setw(15) << "Harga" << endl;
    cout << "---------------------------------------------------------------\n";
    
    Barang* temp = start;
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
    tampilkanTabelBarang(head);
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
                head = temp->next;
            } else {
                prev->next = temp->next;
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

// Implementasi Stack

// Push: Menambah barang ke Stack
void pushStack() {
    Barang* barangBaru = createBarang();
    barangBaru->next = stackTop;
    stackTop = barangBaru;
    cout << "Barang berhasil ditambahkan ke Stack!\n";
}

// Pop: Menghapus barang teratas dari Stack
void popStack() {
    if (stackTop == nullptr) {
        cout << "Stack kosong.\n";
        return;
    }
    Barang* temp = stackTop;
    stackTop = stackTop->next;
    cout << "Barang " << temp->nama << " telah dihapus dari Stack.\n";
    delete temp;
}

// Peek: Melihat barang teratas di Stack
void peekStack() {
    if (stackTop == nullptr) {
        cout << "Stack kosong.\n";
        return;
    }
    cout << "Barang teratas di Stack:\n";
    tampilkanTabelBarang(stackTop);
}

// Implementasi Queue

// Enqueue: Menambah barang ke Queue
void enqueueQueue() {
    Barang* barangBaru = createBarang();
    if (queueRear == nullptr) {
        queueFront = queueRear = barangBaru;
    } else {
        queueRear->next = barangBaru;
        queueRear = barangBaru;
    }
    cout << "Barang berhasil ditambahkan ke Queue!\n";
}

// Dequeue: Menghapus barang terdepan dari Queue
void dequeueQueue() {
    if (queueFront == nullptr) {
        cout << "Queue kosong.\n";
        return;
    }
    Barang* temp = queueFront;
    queueFront = queueFront->next;
    if (queueFront == nullptr) {
        queueRear = nullptr;
    }
    cout << "Barang " << temp->nama << " telah dihapus dari Queue.\n";
    delete temp;
}

// Front: Melihat barang terdepan di Queue
void frontQueue() {
    if (queueFront == nullptr) {
        cout << "Queue kosong.\n";
        return;
    }
    cout << "Barang terdepan di Queue:\n";
    tampilkanTabelBarang(queueFront);
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
        cout << "5. Push ke Stack\n";
        cout << "6. Pop dari Stack\n";
        cout << "7. Peek Stack\n";
        cout << "8. Enqueue ke Queue\n";
        cout << "9. Dequeue dari Queue\n";
        cout << "10. Lihat Front Queue\n";
        cout << "11. Keluar\n";
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
                pushStack();
                break;
            case 6:
                popStack();
                break;
            case 7:
                peekStack();
                break;
            case 8:
                enqueueQueue();
                break;
            case 9:
                dequeueQueue();
                break;
            case 10:
                frontQueue();
                break;
            case 11:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 11);

    return 0;
}