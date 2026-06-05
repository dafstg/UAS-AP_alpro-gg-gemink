#include "TebakKata.h"

int main()
{
    srand(time(NULL));

    char ulang;

    cout << "====================================\n";
    cout << "         GAME TEBAK KATA\n";
    cout << "====================================\n";

    do
    {
        KataGame game;
        int tingkat;

        pilihKesulitan(&game, &tingkat);

        inisialisasiGame(&game);

        char tebakanSalah[26];
        int jumlahSalah = 0;

        bool hintDipakai = false;

        while(game.nyawa > 0 && !cekMenang(game))
        {
            tampilkanGame(
                &game,
                tebakanSalah,
                jumlahSalah,
                hintDipakai
            );

            cout << "\nPetunjuk:\n";
            cout << "- Ketik huruf A-Z untuk menebak\n";
            cout << "- Ketik ? untuk menggunakan hint\n";

            string input;

            cout << "\nHURUF SELANJUTNYA : ";
            cin >> input;

            if(input == "?")
            {
                gunakanHint(
                    &game,
                    &hintDipakai
                );

                continue;
            }

            if(input.length() != 1)
            {
                tampilError();
                continue;
            }

            char huruf = tolower(input[0]);

            if(!isalpha(huruf))
            {
                tampilError();
                continue;
            }

            if(
                sudahDitebak(
                    huruf,
                    game.statusTebakan,
                    tebakanSalah,
                    jumlahSalah
                )
            )
            {
                tampilHurufSudahDitebak();
                continue;
            }

            prosesTebakan(
                &game,
                huruf,
                tebakanSalah,
                &jumlahSalah
            );
        }

        if(cekMenang(game))
        {
            cout << "\n====================================\n";
            cout << "      SELAMAT ANDA MENANG !!!\n";
            cout << "====================================\n";

            cout << "Kata yang berhasil ditebak : "
                    << game.kataAsli
                    << endl;

            string nama;

            cout << "\nMasukkan Nama : ";
            cin >> nama;

            int skor =
                hitungSkor(
                    game.nyawa,
                    tingkat
                );

            cout << "\nSkor Anda : "
                    << skor
                    << endl;

            simpanLeaderboard(
                nama,
                skor
            );
        }
        else
        {
            cout << "\n====================================\n";
            cout << "          ANDA KALAH !!!\n";
            cout << "====================================\n";

            cout << "Kata yang benar adalah : "
                    << game.kataAsli
                    << endl;
        }

        tampilLeaderboard();

        while(true)
        {
            cout << "\nMain Lagi? (Y/N) : ";

            cin >> ulang;

            ulang = toupper(ulang);

            if(
                ulang == 'Y' ||
                ulang == 'N'
            )
            {
                break;
            }

            tampilError();
        }

    }
    while(ulang == 'Y');

    cout << "\n====================================\n";
    cout << "TERIMA KASIH TELAH BERMAIN\n";
    cout << "         SAMPAI JUMPA\n";
    cout << "====================================\n";

    return 0;
}