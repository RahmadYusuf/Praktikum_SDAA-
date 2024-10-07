#include <iostream>
#include <limits>
using namespace std;

// Struct Linked List
struct Operator {
    string nama;
    string role;  // sniper, guard, caster, vanguard
    int rarity;   // 1-6 bintang
    string faction;
    Operator* next;   // Pointer ke node berikutnya
};

// Stack 
struct Stack {
    Operator* top = nullptr;
    
    bool isEmpty() {
        return top == nullptr;
    }
    
    void push(string nama, string role, int rarity, string faction) {
        Operator* newNode = new Operator();
        newNode->nama = nama;
        newNode->role = role;
        newNode->rarity = rarity;
        newNode->faction = faction;
        newNode->next = top;
        top = newNode;
        cout << "Operator berhasil ditambahkan ke stack!\n";
    }
    
    void pop() {
        if (isEmpty()) {
            cout << "Stack kosong!\n";
            return;
        }
        Operator* temp = top;
        top = top->next;
        delete temp;
        cout << "Operator berhasil dihapus dari stack!\n";
    }
    
    void displaystack() {
        if (isEmpty()) {
            cout << "Stack kosong!\n";
            return;
        }
        Operator* temp = top;
        while (temp != nullptr) {
            cout << "\nNama: " << temp->nama << endl;
            cout << "Role: " << temp->role << endl;
            cout << "Rarity: ";
            for (int i = 0; i < temp->rarity; ++i) {
                cout << "*";  
            }
            cout << endl;
            cout << "Faction: " << temp->faction << endl;
            cout << "--------------------------\n";
            temp = temp->next;
        }
    }
};

// Queue 
struct Queue {
    Operator* front = nullptr;
    Operator* rear = nullptr;
    
    bool isEmpty() {
        return front == nullptr;
    }
    
    void enqueue(string nama, string role, int rarity, string faction) {
        Operator* newNode = new Operator();
        newNode->nama = nama;
        newNode->role = role;
        newNode->rarity = rarity;
        newNode->faction = faction;
        newNode->next = nullptr;
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        cout << "Operator berhasil ditambahkan ke queue!\n";
    }
    
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue kosong!\n";
            return;
        }
        Operator* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;  // Jika queue kosong
        delete temp;
        cout << "Operator berhasil dihapus dari queue!\n";
    }
    
    void displayqueue() {
        if (isEmpty()) {
            cout << "Queue kosong!\n";
            return;
        }
        Operator* temp = front;
        while (temp != nullptr) {
            cout << "\nNama: " << temp->nama << endl;
            cout << "Role: " << temp->role << endl;
            cout << "Rarity: ";
            for (int i = 0; i < temp->rarity; ++i) {
                cout << "*";  
            }
            cout << endl;
            cout << "Faction: " << temp->faction << endl;
            cout << "--------------------------\n";
            temp = temp->next;
        }
    }
};

// Fungsi tambahan operator ke Stack/Queue
void tambahOperatorKeStack(Stack& s) {
    string nama, role, faction;
    int rarity;
    
    cout << "Masukkan nama operator: ";
    cin.ignore();
    getline(cin, nama);
    
    cout << "Masukkan role operator : ";
    getline(cin, role);
    
    cout << "Masukkan rarity (1-6): ";
    while (!(cin >> rarity) || rarity < 1 || rarity > 6) {
        cout << "Rarity tidak valid, masukkan angka antara 1 hingga 6: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cin.ignore();
    cout << "Masukkan faction: ";
    getline(cin, faction);
    
    s.push(nama, role, rarity, faction);
}

void tambahOperatorKeQueue(Queue& q) {
    string nama, role, faction;
    int rarity;
    
    cout << "Masukkan nama operator: ";
    cin.ignore();
    getline(cin, nama);
    
    cout << "Masukkan role operator : ";
    getline(cin, role);
    
    cout << "Masukkan rarity (1-6): ";
    while (!(cin >> rarity) || rarity < 1 || rarity > 6) {
        cout << "Rarity tidak valid, masukkan angka antara 1 hingga 6: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cin.ignore();
    cout << "Masukkan faction: ";
    getline(cin, faction);
    
    q.enqueue(nama, role, rarity, faction);
}

// Menu utama
int main() {
    int pilihan;
    Operator* Head = nullptr;  // Linked List
    Stack s;               // Stack
    Queue q;               // Queue

    do {
        cout << "\n=== Manajemen Operator Arknights ===\n";
        cout << "1. Tambah Operator ke Stack\n";
        cout << "2. Tambah Operator ke Queue\n";
        cout << "3. Tampilkan Stack\n";
        cout << "4. Tampilkan Queue\n";
        cout << "5. Pop Stack\n";
        cout << "6. Dequeue Queue\n";
        cout << "7. Keluar\n";
        cout << "Pilih opsi (1-7): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahOperatorKeStack(s);
                break;
            case 2:
                tambahOperatorKeQueue(q);
                break;
            case 3:
                s.displaystack();
                break;
            case 4:
                q.displayqueue();
                break;
            case 5:
                s.pop();
                break;
            case 6:
                q.dequeue();
                break;
            case 7:
                cout << "Terima kasih sudah menggunakan Manajemen Operator Arknights\n";
                break;
            default:
                cout << "Pilihan tidak ada\n";
        }
    } while (pilihan != 7);

    return 0;
}
