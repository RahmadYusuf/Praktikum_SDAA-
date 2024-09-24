#include <iostream>
#include <limits>
using namespace std;

// Struct untuk menyimpan informasi operator
struct Operator {
    string nama;
    string role; // sniper, guard, caster, vanguard
    int rarity;  // 1-6 bintang contoh: kalau bintang 3 maka keluarnya (***)
    string faction;
};

const int MAX_OPERATORS = 10;
Operator operators[MAX_OPERATORS];  // Array menyimpan operator
int totalOperators = 0;              // Jumlah operator yang ada

// Fungsi untuk menambah operator baru
void tambahOperator() {
    if (totalOperators < MAX_OPERATORS) {
        Operator *op = &operators[totalOperators];  // Pointer ke operator baru
        
        cout << "Masukkan nama operator: ";
        cin.ignore(); 
        getline(cin, op->nama);
        cout << "Masukkan role operator: ";
        getline(cin, op->role);
        
       
        cout << "Masukkan rarity operator (1-6): ";
        while (!(cin >> op->rarity) || op->rarity < 1 || op->rarity > 6) {
            cout << "Input tidak valid! Masukkan angka antara 1 hingga 6: ";
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        }

        cout << "Masukkan faction operator: ";
        cin.ignore(); 
        getline(cin, op->faction);
        
        totalOperators++;
        cout << "Operator berhasil ditambahkan!\n";
    } else {
        cout << "Kapasitas operator penuh!\n";
    }
}

// Fungsi untuk menampilkan operator
void tampilkanOperator() {
    if (totalOperators == 0) {
        cout << "Belum ada operator yang ditambahkan.\n";
    } else {
        for (int i = 0; i < totalOperators; i++) {
            Operator *op = &operators[i];  
            cout << "Operator " << i + 1 << ":\n";
            cout << "Nama: " << op->nama << "\n";
            cout << "Role: " << op->role << "\n";
            
            // Mencetak rarity
            cout << "Rarity: ";
            for (int j = 0; j < op->rarity; j++) {
                cout << '*'; // Menampilkan bintang
            }
            cout << "\nFaction: " << op->faction << "\n\n"; 
        }
    }
}

// Fungsi untuk mengedit operator
void editOperator() {
    if (totalOperators == 0) {
        cout << "Tidak ada operator yang bisa diedit.\n";
        return;
    }
    
    int indeks;
    cout << "Masukkan nomor operator yang ingin diedit (1 - " << totalOperators << "): ";
    cin >> indeks;

    if (indeks < 1 || indeks > totalOperators) {
        cout << "Indeks operator tidak valid.\n";
        return;
    }

    Operator *op = &operators[indeks - 1];  // Pointer ke operator yang dipilih
    
    cout << "Masukkan nama baru operator: ";
    cin.ignore(); 
    getline(cin, op->nama);
    cout << "Masukkan role baru operator: ";
    getline(cin, op->role);
    
    // Validasi input rarity
    cout << "Masukkan rarity baru operator (1-6): ";
    while (!(cin >> op->rarity) || op->rarity < 1 || op->rarity > 6) {
        cout << "Input tidak valid! Masukkan angka rarity 1-6: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Masukkan faction baru operator: ";
    cin.ignore(); 
    getline(cin, op->faction);

    cout << "Operator berhasil diedit!\n";
}

// Fungsi untuk menghapus operator
void hapusOperator() {
    if (totalOperators == 0) {
        cout << "Tidak ada operator yang bisa dihapus.\n";
        return;
    }

    int indeks;
    cout << "Masukkan nomor operator yang ingin dihapus (1 - " << totalOperators << "): ";
    cin >> indeks;

    if (indeks < 1 || indeks > totalOperators) {
        cout << "Indeks operator tidak valid.\n";
        return;
    }

  
    for (int i = indeks - 1; i < totalOperators - 1; i++) {
        operators[i] = operators[i + 1];
    }

    totalOperators--;  // Mengurangi jumlah total operator
    cout << "Operator berhasil dihapus!\n";
}

// Menu utama
int main() {
    int pilihan;
    
    do {
        cout << "\n=== Manajemen Operator Arknights ===\n";
        cout << "1. Tambah Operator\n";
        cout << "2. Tampilkan Operator\n";
        cout << "3. Edit Operator\n";
        cout << "4. Hapus Operator\n";
        cout << "5. Keluar\n";
        cout << "Pilih opsi (1-5): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahOperator();
                break;
            case 2:
                tampilkanOperator();
                break;
            case 3:
                editOperator();
                break;
            case 4:
                hapusOperator();
                break;
            case 5:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 5);
    
    return 0;
}
