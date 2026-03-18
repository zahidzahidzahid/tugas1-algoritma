#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Produk {
    char nama[50];
    float harga;
    char kategori[30];
    int stok;
};

Produk arr[100];
int n = 0;

// ================= FILE HANDLING =================
void loadFile() {
    FILE *file = fopen("lelele.csv", "r");
    if (file == NULL) return;

    n = 0;
    while (fscanf(file, " %[^,],%f,%[^,],%d",
        arr[n].nama,
        &arr[n].harga,
        arr[n].kategori,
        &arr[n].stok) != EOF) {
        n++;
    }
    fclose(file);
}

void saveFile() {
    FILE *file = fopen("lelele.csv", "w");
    for (int i = 0; i < n; i++) {
        fprintf(file, "%s,%.1f,%s,%d\n",
            arr[i].nama,
            arr[i].harga,
            arr[i].kategori,
            arr[i].stok);
    }
    fclose(file);
}

// ================= CRUD =================
void tambahProduk() {
    if (n >= 100) {
        cout << "Data penuh!\n";
        return;
    }

    cin.ignore();
    cout << "Nama: ";
    cin.getline(arr[n].nama, 50);

    cout << "Harga: ";
    cin >> arr[n].harga;

    while (true) {
        cout << "Kategori (makanan/minuman): ";
        cin >> arr[n].kategori;

        if (strcmp(arr[n].kategori, "makanan") == 0 ||
            strcmp(arr[n].kategori, "minuman") == 0) {
            break;
        }
        cout << "Kategori salah! ulangi.\n";
    }

    cout << "Stok: ";
    cin >> arr[n].stok;

    n++;
    saveFile();

    cout << "Produk berhasil ditambahkan!\n";
}

void tampil() {
    if (n == 0) {
        cout << "Data kosong!\n";
        return;
    }

    cout << "\n=== DAFTAR PRODUK ===\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". "
             << arr[i].nama << " | "
             << arr[i].harga << " | "
             << arr[i].kategori << " | "
             << arr[i].stok << endl;
    }
}

// ================= SORTING =================
void bubbleSort() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j].nama, arr[j + 1].nama) > 0) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    cout << "Sorting nama (ASC) selesai!\n";
}

void quickSort(int low, int high) {
    int i = low, j = high;
    float pivot = arr[(low + high) / 2].harga;

    while (i <= j) {
        while (arr[i].harga > pivot) i++;   // DESC
        while (arr[j].harga < pivot) j--;

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (low < j) quickSort(low, j);
    if (i < high) quickSort(i, high);
}

// ================= SEARCHING =================
void sequentialSearch(char cari[]) {
    bool found = false;

    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].nama, cari) == 0) {
            cout << "\nDitemukan:\n";
            cout << arr[i].nama << " | "
                 << arr[i].harga << " | "
                 << arr[i].kategori << " | "
                 << arr[i].stok << endl;
            found = true;
        }
    }

    if (!found) cout << "Produk tidak ditemukan!\n";
}

void binarySearch(char cari[]) {
    int l = 0, r = n - 1;

    while (l <= r) {
        int mid = (l + r) / 2;
        int cmp = strcmp(arr[mid].nama, cari);

        if (cmp == 0) {
            cout << "\nDitemukan:\n";
            cout << arr[mid].nama << " | "
                 << arr[mid].harga << " | "
                 << arr[mid].kategori << " | "
                 << arr[mid].stok << endl;
            return;
        } else if (cmp < 0) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << "Produk tidak ditemukan!\n";
}

// ================= MAIN =================
int main() {
    int pilih;
    char cari[50];

    loadFile();

    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Tambah Produk\n";
        cout << "2. Tampilkan Produk\n";
        cout << "3. Sort Nama (Bubble)\n";
        cout << "4. Sort Harga (Quick)\n";
        cout << "5. Search Sequential\n";
        cout << "6. Search Binary\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
        case 1:
            tambahProduk();
            break;

        case 2:
            tampil();
            break;

        case 3:
            bubbleSort();
            tampil();
            break;

        case 4:
            quickSort(0, n - 1);
            tampil();
            break;

        case 5:
            cin.ignore();
            cout << "Cari nama: ";
            cin.getline(cari, 50);
            sequentialSearch(cari);
            break;

        case 6:
            cin.ignore();
            cout << "Cari nama: ";
            cin.getline(cari, 50);
            bubbleSort(); // wajib sort dulu
            binarySearch(cari);
            break;
        }

    } while (pilih != 0);

    return 0;
}