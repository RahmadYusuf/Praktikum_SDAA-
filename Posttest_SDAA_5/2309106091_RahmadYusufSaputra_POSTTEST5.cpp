#include <iostream>
#include <limits>
using namespace std;

// Struktur untuk Linked List
struct Operator {
    string nama;      
    string role;       // Role operator: sniper, guard, caster, vanguard
    int rarity;        // Rarity: 1-6 bintang
    string faction;    
    Operator* next;    // Pointer ke node berikutnya
};

// Struktur untuk Stack
struct Stack {
    Operator* top = nullptr;  
    

    bool isEmpty() {
        return top == nullptr;
    }
    
    // Menambahkan operator ke stack
    void push(string nama, string role, int rarity, string faction) {
        Operator* newNode = new Operator();
        newNode->nama = nama;
        newNode->role = role;
        newNode->rarity = rarity;
        newNode->faction = faction;
        newNode->next = top;  // Node baru Mengarah ke top saat ini
        top = newNode;        // Update top Menjadi node baru
        cout << "Operator berhasil ditambahkan ke stack!\n";
    }
    
    // Menghapus operator dari stack
    void pop() {
        if (isEmpty()) {
            cout << "Stack kosong!\n";
            return;
        }
        Operator* temp = top; // Menyimpan node teratas
        top = top->next;      // Memindahkan top ke node berikutnya
        delete temp;         // Menghapus node teratas
        cout << "Operator berhasil dihapus dari stack!\n";
    }
    
    // Menampilkan isi stack
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
            temp = temp->next;  // Pindah ke node berikutnya
        }
    }

    // Merge Sort untuk urutan ascending
    Operator* mergeSort(Operator* head) {
        if (!head || !head->next) return head; // Jika list kosong atau hanya ada satu node

        Operator* mid = getMid(head);          
        Operator* left = mergeSort(head);     
        Operator* right = mergeSort(mid);     

        return merge(left, right);     // Menggabungkan kedua bagian yang sudah diurutkan
    }

    // Mendapatkan node tengah dari list
    Operator* getMid(Operator* head) {
        Operator* slow = head;
        Operator* fast = head->next;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;                 
            fast = fast->next->next;          
        } 
        Operator* mid = slow->next;          
        slow->next = nullptr;   // Memisahkan list
        return mid;
    }

    // Menggabungkan dua list yang sudah terurut
    Operator* merge(Operator* left, Operator* right) {
        if (!left) return right;              
        if (!right) return left;              

        if (left->rarity < right->rarity) {
            left->next = merge(left->next, right);
            return left;
        } else {
            right->next = merge(left, right->next); 
            return right;
        }
    }

    // Memanggil merge sort
    void Mergesort() {
        top = mergeSort(top);                  
    }
};

// Struktur untuk Queue
struct Queue {
    Operator* front = nullptr; 
    Operator* rear = nullptr; 
    
    bool isEmpty() {
        return front == nullptr;
    }
    
    // Menambahkan operator ke queue
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
    
    // Menghapus operator dari queue
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue kosong!\n";
            return;
        }
        Operator* temp = front;  
        front = front->next;     
        if (front == nullptr) rear = nullptr;  
        delete temp;            
        cout << "Operator berhasil dihapus dari queue!\n";
    }
    
    // Menampilkan isi queue
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

    // Shell Sort untuk urutan descending
    void shellSort() {
        if (isEmpty()) return;

        
        int n = 0;
        Operator* temp = front;
        while (temp) {
            n++;  
            temp = temp->next;
        } 

        // Pengurutan Menggunakan metode shell
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                Operator* current = getNodeAt(i);
                Operator* j = getNodeAt(i - gap);
                
                while (j != nullptr && j->rarity < current->rarity) {
                    j = j->next;
                }
                if (j != nullptr) {
                    swapOperators(current, j);
                }
            }
        }
    }

    // Mendapatkan node pada indeks tertentu
    Operator* getNodeAt(int index) {
        Operator* temp = front;
        for (int i = 0; i < index && temp != nullptr; i++) {
            temp = temp->next;
        }
        return temp;
    }

    // Menukar data dari dua operator
    void swapOperators(Operator* a, Operator* b) {
        string tempName = a->nama;
        string tempRole = a->role;
        int tempRarity = a->rarity;
        string tempFaction = a->faction;

        a->nama = b->nama;
        a->role = b->role;
        a->rarity = b->rarity;
        a->faction = b->faction;

        b->nama = tempName;
        b->role = tempRole;
        b->rarity = tempRarity;
        b->faction = tempFaction;
    }
};

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
    
    s.push(nama, role, rarity, faction); // Menambahkan operator ke stack
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
    
    q.enqueue(nama, role, rarity, faction); // Menambahkan operator ke queue
}

// Menu utama
int main() {
    int pilihan;
    Stack s;               
    Queue q;               
    do {
        cout << "\n=== Manajemen Operator Arknights ===\n";
        cout << "1. Tambah Operator ke Stack\n";
        cout << "2. Tambah Operator ke Queue\n";
        cout << "3. Tampilkan Stack\n";
        cout << "4. Tampilkan Queue\n";
        cout << "5. Pop Stack\n";
        cout << "6. Dequeue Queue\n";
        cout << "7. Tampilkan Merge Sort Stack (Ascending)\n";
        cout << "8. Tampilkan Shell Sort Queue (Descending)\n";
        cout << "9. Keluar\n";
        cout << "Pilih opsi (1-9): ";
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
                s.Mergesort(); 
                cout << "Stack berhasil diurutkan Menggunakan merge sort secara ascending berdasarkan rarity.\n";
                break;
            case 8:
                q.shellSort(); // Mengurutkan queue Menggunakan shell sort
                cout << "Queue berhasil diurutkan Menggunakan shell sort secara descending berdasarkan rarity.\n";
                break;
            case 9:
                cout << "Terima kasih sudah Menggunakan Manajemen Operator Arknights\n";
                break;
            default:
                cout << "Pilihan tidak ada\n";
        }
    } while (pilihan != 9);

    return 0;
}
