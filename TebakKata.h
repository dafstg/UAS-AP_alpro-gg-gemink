#ifndef TEBAKKATA_H
#define TEBAKKATA_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

struct KataGame
{
    string kataAsli;
    string statusTebakan;
    int nyawa;
};

struct Leaderboard
{
    string nama;
    int skor;
};

string daftarKata[15] =
{
    "komputer",
    "algoritma",
    "variabel",
    "pointer",
    "database",
    "internet",
    "keyboard",
    "monitor",
    "program",
    "struktur",
    "fungsi",
    "operator",
    "compiler",
    "jaringan",
    "aplikasi"
};

Leaderboard top5[5] =
{
    {"---",0},
    {"---",0},
    {"---",0},
    {"---",0},
    {"---",0}
};

void tampilError()
{
    cout << "\n====================================\n";
    cout << "ERROR, SILAHKAN MASUKKAN SESUAI KETENTUAN\n";
    cout << "BIPBIPBIP - MOROS\n";
    cout << "SILAHKAN PILIH ULANG DAN IKUTI OPSI YANG TERSEDIA\n";
    cout << "====================================\n";
}

void tampilHurufSudahDitebak()
{
    cout << "\n====================================\n";
    cout << "HURUF SUDAH PERNAH DITEBAK\n";
    cout << "SILAHKAN COBA HURUF LAIN\n";
    cout << "====================================\n";
}

int inputMenu(int min, int max)
{
    int pilihan;

    while(true)
    {
        cin >> pilihan;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000,'\n');
            tampilError();
            continue;
        }

        if(pilihan < min || pilihan > max)
        {
            tampilError();
            continue;
        }

        return pilihan;
    }
}

void pilihKesulitan(KataGame *game, int *tingkat)
{
    cout << "\n===== PILIH KESULITAN =====\n";
    cout << "1. Easy   (8 Nyawa)\n";
    cout << "2. Medium (6 Nyawa)\n";
    cout << "3. Hard   (4 Nyawa)\n";
    cout << "Pilihan : ";

    int pilih = inputMenu(1,3);

    if(pilih == 1)
    {
        game->nyawa = 8;
        *tingkat = 1;
    }
    else if(pilih == 2)
    {
        game->nyawa = 6;
        *tingkat = 2;
    }
    else
    {
        game->nyawa = 4;
        *tingkat = 3;
    }
}

void inisialisasiGame(KataGame *game)
{
    int index = rand() % 15;

    game->kataAsli = daftarKata[index];
    game->statusTebakan = "";

    for(int i = 0; i < game->kataAsli.length(); i++)
    {
        game->statusTebakan += "_";
    }
}

bool cekMenang(KataGame game)
{
    return game.kataAsli == game.statusTebakan;
}

void tampilkanGame(
    KataGame *game,
    char tebakanSalah[],
    int jumlahSalah,
    bool hintDipakai)
{
    cout << "\n====================================\n";
    cout << "Kata  : " << game->statusTebakan << endl;
    cout << "Nyawa : " << game->nyawa << endl;

    cout << "Huruf Salah : ";

    for(int i = 0; i < jumlahSalah; i++)
    {
        cout << tebakanSalah[i] << " ";
    }

    cout << endl;

    if(hintDipakai)
    {
        cout << "HINT ANDA SUDAH HABIS\n";
    }

    cout << "====================================\n";
}

bool sudahDitebak(
    char huruf,
    string status,
    char tebakanSalah[],
    int jumlahSalah)
{
    for(char c : status)
    {
        if(c == huruf)
        {
            return true;
        }
    }

    for(int i = 0; i < jumlahSalah; i++)
    {
        if(tebakanSalah[i] == huruf)
        {
            return true;
        }
    }

    return false;
}

void prosesTebakan(
    KataGame *game,
    char huruf,
    char tebakanSalah[],
    int *jumlahSalah)
{
    bool ditemukan = false;

    for(int i = 0; i < game->kataAsli.length(); i++)
    {
        if(game->kataAsli[i] == huruf)
        {
            game->statusTebakan[i] = huruf;
            ditemukan = true;
        }
    }

    if(ditemukan)
    {
        cout << "\nTebakan benar!\n";
    }
    else
    {
        tebakanSalah[*jumlahSalah] = huruf;
        (*jumlahSalah)++;

        game->nyawa--;

        cout << "\nHuruf tidak ditemukan!\n";
    }
}

void gunakanHint(
    KataGame *game,
    bool *hintDipakai)
{
    if(*hintDipakai)
    {
        return;
    }

    int posisi;

    do
    {
        posisi = rand() % game->kataAsli.length();
    }
    while(game->statusTebakan[posisi] != '_');

    char hurufHint = game->kataAsli[posisi];

    game->statusTebakan[posisi] = hurufHint;

    game->nyawa--;

    *hintDipakai = true;

    cout << "\n====================================\n";
    cout << "HINT YANG KAMU PEROLEH ADALAH HURUF '";
    cout << hurufHint;
    cout << "'\n";
    cout << "GUNAKAN PETUNJUK INI DENGAN BIJAK!\n";
    cout << "Nyawa berkurang 1 poin.\n";
    cout << "====================================\n";
}

int hitungSkor(int nyawa, int tingkat)
{
    if(tingkat == 1)
    {
        return nyawa * 10;
    }

    if(tingkat == 2)
    {
        return nyawa * 20;
    }

    return nyawa * 30;
}

void simpanLeaderboard(string nama, int skor)
{
    for(int i = 0; i < 5; i++)
    {
        if(skor > top5[i].skor)
        {
            for(int j = 4; j > i; j--)
            {
                top5[j] = top5[j - 1];
            }

            top5[i].nama = nama;
            top5[i].skor = skor;
            break;
        }
    }
}

void tampilLeaderboard()
{
    cout << "\n===== TOP 5 LEADERBOARD =====\n";

    for(int i = 0; i < 5; i++)
    {
        cout << i + 1 << ". "
                << top5[i].nama
                << " - "
                << top5[i].skor
                << endl;
    }
}

#endif