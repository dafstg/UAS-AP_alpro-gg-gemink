#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

main () 
{
int skor = 0;
int indeks,hilang,posisi;
string jawaban,clue,tebakan;    
char ulang;
vector<string> negara = {"indonesia", "japan", "brunei", "singapore", "thailand", "england", "germany", "france"};

srand(time(0));

do 
{
    indeks = rand() % negara.size();

    jawaban = negara[indeks];
    clue = jawaban;

    hilang = jawaban.length() / 2;

    for (int i = 0; i < hilang; i++)
    {
        posisi = rand() % jawaban.length();
        clue[posisi] = '_';
    }

    cout << "Tebak negara : " << clue <<endl;
    cout << "Negara apakah yang dimaksud? : ";
    cin >> tebakan;

    if (tebakan == jawaban)
    {
        cout << "Selamat! Anda benar."<<endl;
        skor++;
    }
    else
    {
        cout << "Maaf, jawaban Anda salah. Coba lagi."<<endl;
    }

    cout << "Skor Anda : " << skor <<endl;

    cout << "Ingin bermain lagi? (y/n) : ";
    cin >> ulang;

} while (ulang == 'Y' || ulang == 'y');

cout << "Game Selesai :D";
}