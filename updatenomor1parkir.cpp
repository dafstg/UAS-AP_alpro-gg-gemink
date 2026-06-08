#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;

struct Petugas {
    string nama;
    string id;
};

struct Mobil {
    string plat;
    string merk;
    string warna;
    chrono::time_point<chrono::steady_clock> waktuMasuk;
};

const int MAX_KAPASITAS = 20;

void tampilkanHeader();
void inputPetugas(Petugas* p);
void tampilkanMenuUtama();
void tambahKendaraan(vector<Mobil>& daftarParkir);
void tampilkanKendaraan(const vector<Mobil>& daftarParkir);
void prosesPembayaran(vector<Mobil>& daftarParkir);

int main() {
    system("cls");
    Petugas petugasAktif;
    vector<Mobil> daftarParkir;
    int opsi = 0;

    tampilkanHeader();
    inputPetugas(&petugasAktif);

    cout << "\n=====================================================================\n";
    cout << "Nama Petugas : " << petugasAktif.nama << "\n";
    cout << "ID Petugas   : " << petugasAktif.id << "\n\n";
    cout << "                      TERIMA KASIH ATAS KERJASAMANYA !\n";
    cout << "---------------------- S E L A M A T   B E R T U G A S ----------------------\n";
    cout << "=====================================================================\n";

    do {
        tampilkanMenuUtama();
        cout << "Masukkan opsi : ";
        if (!(cin >> opsi)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input tidak valid! Silakan masukkan angka.\n";
            continue;
        }

        switch (opsi) {
            case 1:
                tambahKendaraan(daftarParkir);
                break;
            case 2:
                tampilkanKendaraan(daftarParkir);
                break;
            case 3:
                prosesPembayaran(daftarParkir);
                break;
            case 4:
                cout << "\nKeluar dari program. Terima kasih!\n";
                break;
            default:
                cout << "Opsi tidak tersedia. Silakan pilih 1-4.\n";
        }
    } while (opsi != 4);

    return 0;
}


void tampilkanHeader() {
    cout << "=====================================================================\n";
    cout << "---------------------- S E L A M A T   D A T A N G ----------------------\n";
    cout << "                       DI PORTAL PARKIR KHUSUS MOBIL\n";
    cout << "                                MALL PRIENAL\n";
    cout << "=====================================================================\n\n";
    cout << "Kami senang Anda telah hadir.\n";
    cout << "Sebelum melanjutkan, silahkan masukkan informasi Anda yang akan bertugas hari ini.\n\n";
}

void inputPetugas(Petugas* p) {
    cout << "Masukkan nama : ";
    cin.ignore();
    getline(cin, p->nama);
    cout << "Masukkan ID   : ";
    getline(cin, p->id);
}

void tampilkanMenuUtama() {
    cout << "\nSilahkan input opsi berikut dalam bentuk angka.\n";
    cout << "1. Tambahkan Daftar Kendaraan\n";
    cout << "2. Tampilkan Daftar Kendaraan\n";
    cout << "3. Pembayaran\n";
    cout << "4. Keluar Program\n";
}

void tambahKendaraan(vector<Mobil>& daftarParkir) {
    int jumlahInput = 0;
    cout << "Masukkan jumlah mobil yang akan di parkirkan : ";
    cin >> jumlahInput;

    if (daftarParkir.size() + jumlahInput > MAX_KAPASITAS) {
        cout << "Maaf, parkiran hanya dapat memuat " << MAX_KAPASITAS << " mobil !\n";
        return;
    }

    cin.ignore();
    for (int i = 0; i < jumlahInput; i++) {
        Mobil mobilBaru;
        cout << "\nMobil ke " << (daftarParkir.size() + 1) << "\n";
        cout << "Masukkan plat mobil  : ";
        getline(cin, mobilBaru.plat);
        cout << "Masukkan merk mobil  : ";
        getline(cin, mobilBaru.merk);
        cout << "Masukkan warna mobil : ";
        getline(cin, mobilBaru.warna);
        
        mobilBaru.waktuMasuk = chrono::steady_clock::now();

        daftarParkir.push_back(mobilBaru);
    }
}

void tampilkanKendaraan(const vector<Mobil>& daftarParkir) {
    cout << "\nDAFTAR MOBIL YANG SUDAH TERPARKIR :\n";
    cout << "=====================================================================\n";

    if (daftarParkir.empty()) {
        cout << "   [ Parkiran Kosong ]\n";
        cout << "=====================================================================\n";
        return;
    }

    auto waktuSekarang = chrono::steady_clock::now();

    for (size_t i = 0; i < daftarParkir.size(); i++) {
        auto durasiDetik = chrono::duration_cast<chrono::seconds>(waktuSekarang - daftarParkir[i].waktuMasuk).count();
        
        long long jam = durasiDetik / 3600;
        long long menit = (durasiDetik % 3600) / 60;
        long long detik = durasiDetik % 60;

        cout << "Mobil ke-" << (i + 1) << "\n";
        cout << "Plat mobil   : " << daftarParkir[i].plat << "\n";
        cout << "Merk mobil   : " << daftarParkir[i].merk << "\n";
        cout << "Warna mobil  : " << daftarParkir[i].warna << "\n";
        cout << "Waktu parkir : " << jam << " jam " << menit << " menit " << detik << " detik\n";
        cout << "---------------------------------------------------------------------\n";
    }
    cout << "=====================================================================\n";
}

void prosesPembayaran(vector<Mobil>& daftarParkir) {
    tampilkanKendaraan(daftarParkir);

    if (daftarParkir.empty()) return;

    cin.ignore();
    string cariPlat;
    cout << "Masukkan plat mobil yang ingin dibayar : ";
    getline(cin, cariPlat);

    int indexDitemukan = -1;
    for (size_t i = 0; i < daftarParkir.size(); i++) {
        if (daftarParkir[i].plat == cariPlat) {
            indexDitemukan = i;
            break;
        }
    }

    if (indexDitemukan == -1) {
        cout << "PLAT TIDAK DITEMUKAN !\n\n";
        cout << "Masukkan plat mobil yang ingin dibayar : ";
        getline(cin, cariPlat);

        for (size_t i = 0; i < daftarParkir.size(); i++) {
            if (daftarParkir[i].plat == cariPlat) {
                indexDitemukan = i;
                break;
            }
        }
    }

    if (indexDitemukan == -1) {
        cout << "Proses pembayaran dibatalkan karena Plat tetap tidak ditemukan.\n";
        return;
    }

    auto waktuKeluar = chrono::steady_clock::now();
    auto totalDetik = chrono::duration_cast<chrono::seconds>(waktuKeluar - daftarParkir[indexDitemukan].waktuMasuk).count();

    long long biayaParkir = 400 + (totalDetik * 3);

    cout << "\nB I A Y A   P A R K I R : Rp" << biayaParkir << "\n";
    cout << "---------------------------------------------------------------------\n";

    daftarParkir.erase(daftarParkir.begin() + indexDitemukan);
}
