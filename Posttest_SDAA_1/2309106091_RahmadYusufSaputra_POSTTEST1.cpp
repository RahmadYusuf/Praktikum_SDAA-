#include <iostream>
using namespace std;

void Menara_hanoi(int piringan, string Menara_asal, string Menara_tujuan, string Menara_sementara) {
    if (piringan == 1) {
        cout << "Pindahkan Piringan " << piringan << " dari " << Menara_asal << " ke " << Menara_tujuan << endl;
        return;
    }

    Menara_hanoi(piringan - 1, Menara_asal, Menara_sementara, Menara_tujuan);
    cout << "Pindahkan Piringan " << piringan << " dari " << Menara_asal << " ke " << Menara_tujuan << endl;
    Menara_hanoi(piringan - 1, Menara_sementara, Menara_tujuan, Menara_asal);
}

int main() {
    int piringan = 3;
    Menara_hanoi(piringan, "Menara Asal", "Menara Tujuan", "Menara Sementara");
    return 0;
}
