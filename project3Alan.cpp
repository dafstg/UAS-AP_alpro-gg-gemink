#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// struct buat barang
struct Barang {
	string kodeBarang;
	string namaBarang;
	double harga;
	int Stok; // stok pake huruf besar biar keliatan
};

vector<Barang> DataBarang; // vector global biar gampang

// function buat nampilin semua barang
void tampilSemua() {
	cout << "==============================" << endl;
	cout << "     DAFTAR SEMUA BARANG      " << endl;
	cout << "==============================" << endl;
	if (DataBarang.size() == 0) {
		cout << "Belum ada barang!" << endl;
		return; // keluar dari function
	}
	for (int i = 0; i < DataBarang.size(); i++) {
		cout << "Kode    : " << DataBarang[i].kodeBarang << endl;
		cout << "Nama    : " << DataBarang[i].namaBarang << endl;
		cout << "Harga   : " << DataBarang[i].harga << endl;
		cout << "Stok    : " << DataBarang[i].Stok << endl;
		cout << "------------------------------" << endl;
	}
}

void tambahBarang() {
	Barang b; // variable sementara
	cout << "Masukkan kode barang  : ";
	cin >> b.kodeBarang;
	cout << "Masukkan nama barang  : ";
	cin.ignore(); // ini penting katanya
	getline(cin, b.namaBarang);

	// validasi harga
	ulang1:
	cout << "Masukkan harga barang : ";
	cin >> b.harga;
	if (b.harga < 0) {
		cout << "ERROR!! harga tidak boleh negatif, coba lagi" << endl;
		goto ulang1; // pake goto biar simple :)
	}

	// validasi stok
	ulang2:
	cout << "Masukkan stok barang  : ";
	cin >> b.Stok;
	if (b.Stok < 0) {
		cout << "ERROR!! stok tidak boleh negatif, coba lagi" << endl;
		goto ulang2;
	}

	DataBarang.push_back(b);
	cout << "Barang berhasil ditambahkan!!" << endl;
}

// cari barang by nama
void cariBarang() {
	string keyword;
	cout << "Masukkan nama barang yang dicari : ";
	cin.ignore();
	getline(cin, keyword);

	bool ketemu = false;
	for (int i = 0; i <= DataBarang.size() - 1; i++) { // -1 biar ga out of bound
		// cek apakah nama sama
		if (DataBarang[i].namaBarang == keyword) {
			ketemu = true;
			cout << "BARANG DITEMUKAN!!" << endl;
			cout << "Kode  : " << DataBarang[i].kodeBarang << endl;
			cout << "Nama  : " << DataBarang[i].namaBarang << endl;
			cout << "Harga : Rp" << DataBarang[i].harga << endl;
			cout << "Stok  : " << DataBarang[i].Stok << " pcs" << endl;
			break; // stop loop kalo udah ketemu
		}
	}
	if (ketemu == false) { // harusnya !ketemu tapi ini lebih jelas
		cout << "Barang tidak ditemukan :(" << endl;
	}
}

void hitungTotalNilai() {
	double total = 0;
	double total2 = 0; // ini ga kepake lupa dihapus
	for (int i = 0; i < DataBarang.size(); i++) {
		// rumus: harga x stok
		total = total + (DataBarang[i].harga * DataBarang[i].Stok);
	}
	cout << fixed << setprecision(2); // biar ga jadi 2e+07 atau apapun itu
	cout << "Total nilai inventaris = Rp" << total << endl;
}

// cek barang yang stoknya mau abis (kurang dari 5)
void cekRestock() {
	cout << "=== BARANG PERLU RESTOCK ===" << endl;
	int counter = 0; // hitung berapa barang yang perlu restock
	for (int i = 0; i < DataBarang.size(); i++) {
		if (DataBarang[i].Stok < 5) {
			cout << "[!] " << DataBarang[i].namaBarang
			     << " - stok tinggal: " << DataBarang[i].Stok << endl;
			counter++;
		}
	}
	if (counter == 0) {
		cout << "Semua stok aman!" << endl;
	}
	// cout << "total barang restock: " << counter << endl; // di-comment dulu
}

// update stok pake pointer (disuruh pake pointer)
void updateStok() {
	string kode;
	cout << "Masukkan kode barang yang mau diupdate : ";
	cin >> kode;

	for (int i = 0; i < DataBarang.size(); i++) {
		if (DataBarang[i].kodeBarang == kode) {
			int* ptr = &DataBarang[i].Stok; // ini pointernya
			int stokBaru;
			cout << "Stok sekarang : " << *ptr << endl;
			cout << "Masukkan stok baru : ";
			cin >> stokBaru;
			if (stokBaru < 0) {
				cout << "Stok tidak boleh negatif!!" << endl;
				return;
			}
			*ptr = stokBaru; // update lewat pointer
			cout << "Stok berhasil diupdate!" << endl;
			return; // langsung return
		}
	}
	cout << "Kode barang tidak ditemukan" << endl;
}

// MAIN FUNCTION
int main() {
	int pilihan;
	// loop terus sampe user milih keluar
	while (true) {
		system("cls"); // bersiin layar dulu

		// tampilin menu
		cout << "================================" << endl;
		cout << "   SISTEM INVENTARIS TOKO v1.0  " << endl;
		cout << "================================" << endl;
		cout << "1. Tambah Barang" << endl;
		cout << "2. Tampilkan Semua Barang" << endl;
		cout << "3. Cari Barang" << endl;
		cout << "4. Hitung Total Nilai Inventaris" << endl;
		cout << "5. Cek Restock" << endl;
		cout << "6. Update Stok" << endl;
		cout << "7. Keluar" << endl;
		cout << "================================" << endl;
		cout << "Pilih menu (1-7): ";
		cin >> pilihan;

		// cek pilihan user
		if (pilihan == 1) {
			tambahBarang();
		} else if (pilihan == 2) {
			tampilSemua();
		} else if (pilihan == 3) {
			cariBarang();
		} else if (pilihan == 4) {
			hitungTotalNilai();
		} else if (pilihan == 5) {
			cekRestock();
		} else if (pilihan == 6) {
			updateStok();
		} else if (pilihan == 7) {
			cout << "Terima kasih!! Program selesai." << endl;
			break; // keluar dari while
		} else {
			// kalo inputnya salah
			cout << "Pilihan tidak valid!! Harus antara 1-7" << endl;
		}

		// pause sebelum lanjut
		cout << "\nTekan ENTER untuk lanjut...";
		cin.ignore();
		cin.get();
	}

	return 0; // program selesai
}