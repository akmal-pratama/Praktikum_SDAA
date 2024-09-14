#include <iostream>
using namespace std;

void pindahkanPiringan(int jumlah_piringan, char menara_asal, char menara_tujuan, char menara_sementara) {
    if (jumlah_piringan == 1) {
        cout << "Pindahkan piringan 1 dari menara " << menara_asal << " ke menara " << menara_tujuan << endl;
        cout << "-----------------------------------------" << endl;
        return;
    }
    
    pindahkanPiringan(jumlah_piringan - 1, menara_asal, menara_sementara, menara_tujuan);

    cout << "Pindahkan piringan " << jumlah_piringan << " dari menara " << menara_asal << " ke menara " << menara_tujuan << endl;
    cout << "-----------------------------------------" << endl;
    
    pindahkanPiringan(jumlah_piringan - 1, menara_sementara, menara_tujuan, menara_asal);
}

int main() {
    int jumlah_piringan = 3;
    cout << "Langkah-langkah untuk memindahkan " << jumlah_piringan << " piringan pada Menara Hanoi:" << endl;
    
    pindahkanPiringan(jumlah_piringan, 'A', 'C', 'B');
    
    return 0;
}