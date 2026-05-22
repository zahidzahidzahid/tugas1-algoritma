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

// ================= LOAD FILE =================
void loadFile() {
    FILE *file = fopen("lelele.csv", "r");

    // Error handling file
    if (file == NULL) {
        cout << "File tidak ditemukan, data baru akan dibuat.\n";
        return;
    }

    n = 0;

    while (fscanf(file, " %[^,],%f,%[^,],%d",
        arr[n].nama,
        &arr[n].harga,
        arr[n].kategori,
        &arr[n].stok) != EOF) {

        // Error handling overflow array
        if (n >= 100) {
            cout << "Data melebihi kapasitas array!\n";
            break;
        }

        n++;
    }

    fclose(file);
}

// ================= SAVE FILE =================
void saveFile() {
    FILE *file = fopen("lelele.csv", "w");

    // Error handling file
    if (file == NULL) {
        cout << "Gagal membuka file untuk menyimpan data!\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%s,%.1f,%s,%d\n",
            arr[i].nama,
            arr[i].harga,
            arr[i].kategori,
            arr[i].stok);
    }

    fclose(file);
}

// ================= TAMBAH PRODUK =================
void tambahProduk() {

    // Overflow handling
    if (n >= 100) {
        cout << "Array penuh! Tidak bisa menambahkan produk lagi.\n";
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

// ================= TAMPIL DATA =================
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

// ================= BUBBLE SORT ASC =================
void bubbleSort() {

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (strcmp(arr[j].nama, arr[j + 1].nama) > 0) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    cout << "Data berhasil diurutkan secara ASCENDING (A-Z) berdasarkan nama.\n";
}

// ================= QUICK SORT DESC =================
void quickSort(int low, int high) {

    int i = low;
    int j = high;

    float pivot = arr[(low + high) / 2].harga;

    while (i <= j) {

        while (arr[i].harga > pivot) i++;
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

// Fungsi tambahan agar pesan tidak muncul berkali-kali
void sortHargaDesc() {

    quickSort(0, n - 1);

    cout << "Data berhasil diurutkan secara DESCENDING (terbesar ke terkecil) berdasarkan harga.\n";
}

// ================= SEQUENTIAL SEARCH =================
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

    if (!found) {
        cout << "Produk tidak ditemukan!\n";
    }
}

// ================= BINARY SEARCH =================
void binarySearch(char cari[]) {

    int l = 0;
    int r = n - 1;

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
        cout << "3. Sort Nama (Bubble ASC)\n";
        cout << "4. Sort Harga (Quick DESC)\n";
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
            sortHargaDesc();
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

            // Binary search harus data terurut
            bubbleSort();

            binarySearch(cari);

            break;

        case 0:
            cout << "Program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilih != 0);

    return 0;
}
