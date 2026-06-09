#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;


struct Barang {
	string kodeBarang;
	string namaBarang;
	double harga;
	int Stok; 
};

vector<Barang> DataBarang; 


void tampilSemua() {
	cout << "==============================" << endl;
	cout << "     DAFTAR SEMUA BARANG      " << endl;
	cout << "==============================" << endl;
	if (DataBarang.size() == 0) {
		cout << "Belum ada barang!" << endl;
		return; 
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
	Barang b; 
	cout << "Masukkan kode barang  : ";
	cin >> b.kodeBarang;
	cout << "Masukkan nama barang  : ";
	cin.ignore();
	getline(cin, b.namaBarang);


	ulang1:
	cout << "Masukkan harga barang : ";
	cin >> b.harga;
	if (b.harga < 0) {
		cout << "ERROR!! harga tidak boleh negatif, coba lagi" << endl;
		goto ulang1; 
	}


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


void cariBarang() {
	string keyword;
	cout << "Masukkan nama barang yang dicari : ";
	cin.ignore();
	getline(cin, keyword);

	bool ketemu = false;
	for (int i = 0; i <= DataBarang.size() - 1; i++) { 
	
		if (DataBarang[i].namaBarang == keyword) {
			ketemu = true;
			cout << "BARANG DITEMUKAN!!" << endl;
			cout << "Kode  : " << DataBarang[i].kodeBarang << endl;
			cout << "Nama  : " << DataBarang[i].namaBarang << endl;
			cout << "Harga : Rp" << DataBarang[i].harga << endl;
			cout << "Stok  : " << DataBarang[i].Stok << " pcs" << endl;
			break; 
		}
	}
	if (ketemu == false) { 
		cout << "Barang tidak ditemukan :(" << endl;
	}
}

void hitungTotalNilai() {
	double total = 0;
	double total2 = 0; 
	for (int i = 0; i < DataBarang.size(); i++) {
		
		total = total + (DataBarang[i].harga * DataBarang[i].Stok);
	}
	cout << fixed << setprecision(2); 
	cout << "Total nilai inventaris = Rp" << total << endl;
}


void cekRestock() {
	cout << "=== BARANG PERLU RESTOCK ===" << endl;
	int counter = 0; 
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
	
}


void updateStok() {
	string kode;
	cout << "Masukkan kode barang yang mau diupdate : ";
	cin >> kode;

	for (int i = 0; i < DataBarang.size(); i++) {
		if (DataBarang[i].kodeBarang == kode) {
			int* ptr = &DataBarang[i].Stok;
			int stokBaru;
			cout << "Stok sekarang : " << *ptr << endl;
			cout << "Masukkan stok baru : ";
			cin >> stokBaru;
			if (stokBaru < 0) {
				cout << "Stok tidak boleh negatif!!" << endl;
				return;
			}
			*ptr = stokBaru; 
			cout << "Stok berhasil diupdate!" << endl;
			return;
		}
	}
	cout << "Kode barang tidak ditemukan" << endl;
}


int main() {
	int pilihan;

	while (true) {
		system("cls"); 

		
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
			break; 
		} else {
		
			cout << "Pilihan tidak valid!! Harus antara 1-7" << endl;
		}


		cout << "\nTekan ENTER untuk lanjut...";
		cin.ignore();
		cin.get();
	}

	return 0; 
}
