#include <iostream>
#include <limits>
#include <cmath> 

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
    // Fibonacci Search untuk mencari berdasarkan rarity
    int fibSearch(int rarity) {
        if (top == nullptr) return -1; // Jika list kosong

        // Inisialisasi dua angka Fibonacci pertama
        int fib2 = 0;  // (m-2)'th Fibonacci
        int fib1 = 1;  // (m-1)'th Fibonacci
        int fibM = fib1 + fib2; // m'th Fibonacci

        // Hitung ukuran list
        int size = 0;
        Operator* temp = top;
        while (temp) {
            size++;
            temp = temp->next;
        }

        // Cari nilai fibonacci yang terbesar dan lebih kecil atau sama dengan size
        while (fibM < size) {
            fib2 = fib1;
            fib1 = fibM;
            fibM = fib1 + fib2;
        }

        // Penanda untuk membatasi pencarian
        int offset = -1;

        Operator* nodeAtI = top; // Node pertama
        while (fibM > 1) {
            // Indeks yang akan diperiksa
            int i = min(offset + fib2, size - 1);

            nodeAtI = top;
            for (int j = 0; j < i; j++) nodeAtI = nodeAtI->next;

            if (nodeAtI->rarity < rarity) {
                fibM = fib1;
                fib1 = fib2;
                fib2 = fibM - fib1;
                offset = i;
            } else if (nodeAtI->rarity > rarity) {
                fibM = fib2;
                fib1 = fib1 - fib2;
                fib2 = fibM - fib1;
            } else {
                cout << "Operator ditemukan dengan rarity " << rarity << " di posisi " << i << "\n";
                return i;
            }
        }

        if (fib1 && top->rarity == rarity) {
            cout << "Operator ditemukan dengan rarity " << rarity << "\n";
            return 0;
        }

        cout << "Operator dengan rarity " << rarity << " tidak ditemukan!\n";
        return -1;
    }

    // Jump Search untuk mencari berdasarkan rarity
    int jumpSearch(Operator* head, int rarity) {
        if (head == nullptr) return -1; // Jika list kosong

    // Hitung ukuran list
    int size = 0;
    Operator* temp = head;
    while (temp) {
        size++;
        temp = temp->next;
    }

    // Tentukan langkah (jump) berdasarkan akar kuadrat dari ukuran list
    int step = sqrt(size);
    int prev = 0;

    // Lakukan jumping hingga rarity lebih besar atau sama dengan rarity di node tertentu
    Operator* node = head;
    while (node && node->rarity < rarity) {
        prev = min(step, size) - 1;

        // Pindah ke node pada posisi prev
        for (int i = 0; i < step && node; i++) node = node->next;

        step += sqrt(size); // Menambah langkah untuk jumping berikutnya
        if (!node || prev >= size) return -1;
    }

    // Linear search dari prev ke node yang sesuai
    node = head;
    for (int i = 0; i < prev; i++) node = node->next;

    while (node && prev < size && node->rarity <= rarity) {
        if (node->rarity == rarity) {
            cout << "Operator ditemukan dengan rarity " << rarity << " di posisi " << prev << "\n";
            return prev;
        }
        node = node->next;
        prev++;
    }

    cout << "Operator dengan rarity " << rarity << " tidak ditemukan!\n";
    return -1;
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

// Fibonacci Search untuk data integer (rarity)
int fibSearch(Operator* head, int rarity) {
    if (head == nullptr) return -1; // Jika list kosong

    // Inisialisasi dua angka Fibonacci pertama
    int fib2 = 0;  // (m-2)'th Fibonacci
    int fib1 = 1;  // (m-1)'th Fibonacci
    int fibM = fib1 + fib2; // m'th Fibonacci

    // Hitung ukuran list
    int size = 0;
    Operator* temp = head;
    while (temp) {
        size++;
        temp = temp->next;
    }

    // Cari nilai fibonacci yang terbesar dan lebih kecil atau sama dengan size
    while (fibM < size) {
        fib2 = fib1;
        fib1 = fibM;
        fibM = fib1 + fib2;
    }

    // Penanda untuk membatasi pencarian
    int offset = -1;

    Operator* nodeAtI = head; // Node pertama
    while (fibM > 1) {
        // Indeks yang akan diperiksa
        int i = min(offset + fib2, size - 1);

        nodeAtI = head;
        for (int j = 0; j < i; j++) nodeAtI = nodeAtI->next;

        if (nodeAtI->rarity < rarity) {
            fibM = fib1;
            fib1 = fib2;
            fib2 = fibM - fib1;
            offset = i;
        } else if (nodeAtI->rarity > rarity) {
            fibM = fib2;
            fib1 = fib1 - fib2;
            fib2 = fibM - fib1;
        } else {
            cout << "Operator ditemukan dengan rarity " << rarity << " di posisi " << i << "\n";
            return i;
        }
    }

    if (fib1 && head->rarity == rarity) {
        cout << "Operator ditemukan dengan rarity " << rarity << "\n";
        return 0;
    }

    cout << "Operator dengan rarity " << rarity << " tidak ditemukan!\n";
    return -1;
}

// Jump Search untuk data integer (rarity)
int jumpSearch(Operator* head, int rarity) {
    if (head == nullptr) return -1; // Jika list kosong

    // Hitung ukuran list
    int size = 0;
    Operator* temp = head;
    while (temp) {
        size++;
        temp = temp->next;
    }

    // Tentukan langkah (jump) berdasarkan akar kuadrat dari ukuran list
    int step = sqrt(size);
    int prev = 0;

    // Lakukan jumping hingga rarity lebih besar atau sama dengan rarity di node tertentu
    Operator* node = head;
    while (node && node->rarity < rarity) {
        prev = min(step, size) - 1;

        // Pindah ke node pada posisi prev
        for (int i = 0; i < step && node; i++) node = node->next;

        step += sqrt(size); // Menambah langkah untuk jumping berikutnya
        if (!node || prev >= size) return -1;
    }

    // Linear search dari prev ke node yang sesuai
    node = head;
    for (int i = 0; i < prev; i++) node = node->next;

    while (node && prev < size && node->rarity <= rarity) {
        if (node->rarity == rarity) {
            cout << "Operator ditemukan dengan rarity " << rarity << " di posisi " << prev << "\n";
            return prev;
        }
        node = node->next;
        prev++;
    }

    cout << "Operator dengan rarity " << rarity << " tidak ditemukan!\n";
    return -1;
}


// Boyer-Moore untuk data string (nama)
void boyerMooreSearch(Operator* head, const string& pattern) {
    if (head == nullptr) {
        cout << "Stack kosong!" << endl;
        return;
    }

    // Buat tabel pergeseran untuk Boyer-Moore
    int patLen = pattern.length();
    int badChar[256];

    for (int i = 0; i < 256; i++) badChar[i] = -1;
    for (int i = 0; i < patLen; i++) badChar[(int)pattern[i]] = i;

    int pos = 0;
    Operator* node = head;
    while (node != nullptr) {
        const string& text = node->nama;
        int txtLen = text.length();
        int shift = 0;

        while (shift <= (txtLen - patLen)) {
            int j = patLen - 1;

            while (j >= 0 && pattern[j] == text[shift + j])
                j--;

            if (j < 0) {
                // Tampilkan semua data saat ditemukan
                cout << "Operator ditemukan:\n";
                cout << "Nama: " << node->nama << "\n";
                cout << "Role: " << node->role << "\n"; 
                cout << "Rarity: " << node->rarity << "\n"; 
                cout << "faction: " << node->faction << "\n"; 
                return;
            } else {
                shift += max(1, j - badChar[(int)text[shift + j]]);
            }
        }

        node = node->next;
        pos++;
    }

    cout << "Operator dengan nama " << pattern << " tidak ditemukan!\n";
}




// Menu utama
int main() {
    int pilihan;
    string nama;
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
        cout << "9. Searching Stack Fibo Rarity\n";
        cout << "10. Jump Search berdasarkan rarity\n";
        cout << "11. Boyer-Moore Search berdasarkan nama\n";
        cout << "12. Keluar\n";
        cout << "Pilih opsi (1-12): ";
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
                q.shellSort(); 
                cout << "Queue berhasil diurutkan Menggunakan shell sort secara descending berdasarkan rarity.\n";
                break;
            case 9:
                int rarity;
                cout << "Masukkan rarity yang ingin dicari: ";
                cin >> rarity;
                s.fibSearch(rarity);
                break;
            case 10:
                cout << "Masukkan rarity yang ingin dicari: ";
                cin >> rarity;
                jumpSearch(s.top, rarity);
                break;
            case 11:
                cout << "Masukkan nama yang ingin dicari: ";
                cin.ignore();
                getline(cin, nama);
                boyerMooreSearch(s.top, nama);
                break;
            case 12:
                cout << "Terima kasih sudah menggunakan Manajemen Operator Arknights\n";
                break;
            default:
                cout << "Pilihan tidak ada\n";
        }
    } while (pilihan != 12);

    return 0;
}