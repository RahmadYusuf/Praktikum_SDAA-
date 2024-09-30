#include <iostream>
#include <limits>
using namespace std;

// Struct inked List
struct Node {
    string nama;
    string role;    // sniper, guard, caster, vanguard
    int rarity;     // 1-6 bintang, contoh: kalau bintang 3 maka tampilkan (***)
    string faction;
    Node* next;     // Pointer ke node berikutnya
};


void tambahOperator(Node*& Head) {
    Node* newNode = new Node();
    
    cout << "Masukkan nama operator: ";
    cin.ignore();  
    getline(cin, newNode->nama);
    
    cout << "Masukkan role operator : ";
    getline(cin, newNode->role);
    
    cout << "Masukkan rarity (1-6): ";
    while (!(cin >> newNode->rarity) || newNode->rarity < 1 || newNode->rarity > 6) {
        cout << "Rarity tidak valid, masukkan angka antara 1 hingga 6: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cin.ignore(); 
    cout << "Masukkan faction: ";
    getline(cin, newNode->faction);

   
    newNode->next = Head;
    Head = newNode;
    cout << "Operator berhasil ditambahkan!\n";
}


void tampilkanOperator(Node* Head) {
    if (Head == nullptr) {
        cout << "Tidak ada operator yang ditambahkan.\n";
        return;
    }

    Node* temp = Head;
    while (temp != nullptr) {
        cout << "\nNama: " << temp->nama << endl;
        cout << "Role: " << temp->role << endl;
        cout << "Rarity: ";
        for (int i = 0; i < temp->rarity; ++i) {
            cout << "*";  // Menampilkan rarity sebagai bintang
        }
        cout << endl;
        cout << "Faction: " << temp->faction << endl;
        cout << "--------------------------\n";
        temp = temp->next;
    }
}

void editOperator(Node* Head) {
    if (Head == nullptr) {
        cout << "Tidak ada operator yang bisa diedit.\n";
        return;
    }

    string nama;
    cout << "Masukkan nama operator yang ingin diedit: ";
    cin.ignore();
    getline(cin, nama);

    Node* temp = Head;
    while (temp != nullptr) {
        if (temp->nama == nama) {
            cout << "Masukkan nama baru: ";
            getline(cin, temp->nama);
            cout << "Masukkan role baru : ";
            getline(cin, temp->role);
            cout << "Masukkan rarity baru (1-6): ";
            while (!(cin >> temp->rarity) || temp->rarity < 1 || temp->rarity > 6) {
                cout << "Rarity tidak valid, masukkan angka antara 1 hingga 6: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore();
            cout << "Masukkan faction baru: ";
            getline(cin, temp->faction);
            cout << "Operator berhasil diedit!\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Operator dengan nama " << nama << " tidak ditemukan.\n";
}

void hapusOperator(Node*& Head) {
    if (Head == nullptr) {
        cout << "Tidak ada operator yang bisa dihapus.\n";
        return;
    }

    string nama;
    cout << "Masukkan nama operator yang ingin dihapus: ";
    cin.ignore();
    getline(cin, nama);

    Node* temp = Head;
    Node* prev = nullptr;


    if (temp != nullptr && temp->nama == nama) {
        Head = temp->next;  
        delete temp;
        cout << "Operator berhasil dihapus!\n";
        return;
    }

    // Mencari node yang sesuai
    while (temp != nullptr && temp->nama != nama) {
        prev = temp;
        temp = temp->next;
    }

    // Jika operator tidak ditemukan
    if (temp == nullptr) {
        cout << "Operator dengan nama " << nama << " tidak ditemukan.\n";
        return;
    }

    prev->next = temp->next;
    delete temp;
    cout << "Operator berhasil dihapus!\n";
}

// Menu utama
int main() {
    int pilihan;
    Node* Head = nullptr;  

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
                tambahOperator(Head);  
                break;
            case 2:
                tampilkanOperator(Head);
                break;
            case 3:
                editOperator(Head);
                break;
            case 4:
                hapusOperator(Head);  
                break;
            case 5:
                cout << "Terima kasih sudah menggunakan Manajemen Operator Arknights\n";
                break;
            default:
                cout << "Pilihan tidak ada\n";
        }
    } while (pilihan != 5);
      
    return 0;
}
