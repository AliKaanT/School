#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

int main()
{

    time_t time1;
    srand((unsigned)time(&time1));

    int difficulty;
    int hafizaBuyukluk; // Bilgisayarin hatirladigi kart sayisi
    int tabloBuyukluk;  // Tablonun NxN degeri.
    int kartsayisi;     // Tablodaki kart sayisi

    int sira = 0;      // 0 ise sira kullanicida 1 ise bilgisayarda
    int tablo[9][9];   // tablodaki degerleri saklar
    int durum[9][9];   // Kart gizli ise 0, gorunur olmasi gerekiyorsa 1, bulunduysa 2
    int hafiza[16][3]; // 0 = x | 1 = y | 2 = deger
    int i, j, k = 1;
    int kullaniciPuan = 0, bilgisayarPuan = 0, kullanicihamle = 0, bilgisayarhamle = 0;
    int x1, x2, y1, y2, x, y;
    int card1, card2;
    int kontrol, kontrol2, kontrol3;
    int m, kon;

    printf("Bir zorluk seviyesi secerek numarasini giriniz\n1 : kolay\n2 : normal\n3 : zor\n");
    scanf("%d", &difficulty);
    kontrol = 0;
    while (kontrol == 0) // Zorluk secme
    {
        if (difficulty - 1 == 0)
        {
            hafizaBuyukluk = 2;
            tabloBuyukluk = 5;
            kartsayisi = 16;
            printf("\nOyun kolay modda baslatiliyor\n\n");
            kontrol = 1;
        }
        else if (difficulty - 1 == 1)
        {
            hafizaBuyukluk = 6;
            tabloBuyukluk = 7;
            kartsayisi = 36;
            printf("\nOyun normal modda baslatiliyor\n\n");
            kontrol = 1;
        }
        else if (difficulty - 1 == 2)
        {
            hafizaBuyukluk = 16;
            tabloBuyukluk = 9;
            kartsayisi = 64;
            printf("\nOyun zor modda baslatiliyor\n\n");
            kontrol = 1;
        }
        else
        {
            printf("Hatali girdiniz\n1: kolay\n2 : normal\n3 : zor\n");
            scanf("%d", &difficulty);
        }
    }

    for (i = 1; i < tabloBuyukluk; i++) // durumlari gorunur yapma islemi
    {
        for (j = 1; j < tabloBuyukluk; j++)
        {
            durum[i][j] = 1;
            tablo[i][j] = 0;
        }
    }

    for (i = 0; i < 16; i++) // hafiza sıfırlama ve ilk satir sutun ayarlama islemi
    {
        for (j = 0; j < 3; j++)
        {
            hafiza[i][j] = 0;
        }
    }

    i = 2;
    while (i <= kartsayisi + 1) // Tabloyu doldurna islemi
    {
        x = (rand() % (tabloBuyukluk - 1)) + 1;
        y = (rand() % (tabloBuyukluk - 1)) + 1;

        if (tablo[x][y] == 0)
        {
            tablo[x][y] = i / 2;
            i++;
        }
    }

    void tabloyazdir(int mod) // Tablo yazdirma fonksiyonu
    {
        printf("\n");
        for (i = 0; i < tabloBuyukluk; i++) // Tabloyu ekrana yazdiran kod parcasi
        {
            for (j = 0; j < tabloBuyukluk; j++)
            {

                if (i != 0 && j != 0)
                {
                    if (durum[i][j] == 0)
                    {
                        printf("%s\t", " *");
                    }
                    else if (durum[i][j] == 1)
                    {
                        printf("|%d|\t", tablo[i][j]);
                    }
                    else
                    {
                        printf("%s\t", " -");
                    }

                    // Menu bolumu

                    if (i == ((tabloBuyukluk - 1) / 2) && j == tabloBuyukluk - 1)
                    {

                        printf("Kullanici puani : \t%d", kullaniciPuan);
                    }
                    if (i == ((tabloBuyukluk - 1) / 2 + 1) && j == tabloBuyukluk - 1)
                    {
                        printf("Bilgisayar puani : \t%d", bilgisayarPuan);
                    }
                }
                else // Tablo daki ilk satır ve sutun
                {
                    printf(" %d\t", i + j);

                    if (mod == 1)
                    {
                        if (j == tabloBuyukluk - 1)
                        {
                            if (sira == 1)
                            {
                                printf("Oynama sirasi : Bilgisayar");
                            }
                            else
                            {
                                printf("Oynama sirasi : Kullanici");
                            }
                        }
                    }
                }
            }
            printf("\n");
        }
        printf("\n");
    }

    void gecikme(int saniye, char mesaj[50], int yazdir) // gecikme ekleyen fonksiyon
    {
        int a;

        int mili_saniye = 1000 * saniye;
        clock_t baslangic = clock();

        while (clock() < baslangic + mili_saniye)
        {
            if (clock() % 1000 == 0)
            {
                if (a == 0)
                {
                    if (yazdir == 1)
                    {
                        printf("%d%s\n", saniye - (clock() - baslangic) / 1000, mesaj);
                        a = 1;
                    }
                }
            }
            else
            {
                a = 0;
            }
        };
    }

gecikme(1," ",0);
    tabloyazdir(0);

    gecikme(5, "...", 1);
    system("cls");

    for (i = 1; i < tabloBuyukluk; i++) // durumlari sifirlama islemi
    {
        for (j = 1; j < tabloBuyukluk; j++)
        {
            durum[i][j] = 0;
        }
    }

    k = 0;
    while ((kullaniciPuan < kartsayisi / 4 + 1) && (bilgisayarPuan < kartsayisi / 4 + 1) && (kullaniciPuan + bilgisayarPuan < kartsayisi / 2))
    {
        if (sira == 0) // Kullanici girisi
        {
            kullanicihamle++;
            tabloyazdir(1);

            printf("\nBirinci karti seciniz\n");

            kontrol2 = 1;

            while (kontrol2 == 1) // Kart sectirme 1
            {

                printf("satir : ");
                scanf("%d", &x1);
                printf("sutun : ");
                scanf("%d", &y1);

                if (x1 >= 1 && x1 <= tabloBuyukluk - 1 && y1 >= 1 && y1 <= tabloBuyukluk - 1)
                {

                    if (durum[x1][y1] == 0)
                    {
                        kontrol2 = 0;
                    }
                    else if (durum[x1][y1] == 1)
                    {
                        printf("Ayni karti sectiniz!! Lutfen tekrar seciniz.\n");
                    }
                    else if (durum[x1][y1] == 2)
                    {
                        printf("Daha once bulunmus bir kart sectiniz!! Lutfen tekrar seciniz.\n");
                    }
                }
                else
                {
                    printf("Tabloda olmayan bir sayi sectiniz!! Lutfen tekrar seciniz.\n");
                }
            }

            printf("\n%s%d\n\n", "Secilen kart : ", tablo[x1][y1]);

            card1 = tablo[x1][y1];
            durum[x1][y1] = 1;

            //    *********************************************************  //

            printf("Ikinci karti seciniz\n");

            kontrol2 = 1;

            while (kontrol2 == 1) // Kart seçtirme 2
            {
                printf("satir : ");
                scanf("%d", &x2);
                printf("sutun : ");
                scanf("%d", &y2);

                if (x2 >= 1 && x2 <= tabloBuyukluk - 1 && y2 >= 1 && y2 <= tabloBuyukluk - 1)
                {

                    if (durum[x2][y2] == 0)
                    {
                        kontrol2 = 0;
                    }
                    else if (durum[x2][y2] == 1)
                    {
                        printf("Ayni karti sectiniz!! Lutfen tekrar seciniz!!\n");
                    }
                    else if (durum[x2][y2] == 2)
                    {
                        printf("Daha once bulunmus bir kart sectiniz!! Lutfen tekrar seciniz!!\n");
                    }
                }
                else
                {
                    printf("Tabloda olmayan bir sayi sectiniz.\n");
                }
            }

            printf("\n%s%d\n", "Secilen kart : ", tablo[x2][y2]);

            card2 = tablo[x2][y2];
            durum[x2][y2] = 1;

            if (card1 == card2)
            {
                kullaniciPuan++;
            }

            tabloyazdir(0);

            if (card1 == card2)
            {
                printf("\nDogru karti buldunuz !! \n");
                durum[x1][y1] = 2;
                durum[x2][y2] = 2;
                sira = 0;

                kontrol2 = 0;
                i = 0;
                while (kontrol2 != 2 && i < hafizaBuyukluk)
                {

                    if ((hafiza[i][0] == x1 && hafiza[i][1] == y1))
                    {

                        for (j = i; j < 15; j++)
                        {
                            hafiza[j][0] = hafiza[j + 1][0];
                            hafiza[j][1] = hafiza[j + 1][1];
                            hafiza[j][2] = hafiza[j + 1][2];
                        }
                        hafiza[15][0] = 0;
                        hafiza[15][1] = 0;
                        hafiza[15][2] = 0;

                        i--;
                        kontrol2++;

                        if (k == 0)
                        {
                            k = hafizaBuyukluk - 1;
                        }
                        else
                        {
                            k--;
                        }
                    }

                    if ((hafiza[i][0] == x2 && hafiza[i][1] == y2))
                    {

                        for (j = i; j < 15; j++)
                        {
                            hafiza[j][0] = hafiza[j + 1][0];
                            hafiza[j][1] = hafiza[j + 1][1];
                            hafiza[j][2] = hafiza[j + 1][2];
                        }

                        hafiza[15][0] = 0;
                        hafiza[15][1] = 0;
                        hafiza[15][2] = 0;

                        i--;
                        kontrol2++;

                        if (k == 0)
                        {
                            k = hafizaBuyukluk - 1;
                        }
                        else
                        {
                            k--;
                        }
                    }
                    i++;
                }
            }
            else
            {
                { // Kartlari hafizaya yazdirdik.

                    kontrol3 = 0;
                    i = 0;
                    j = 0;
                    while (kontrol3 == 0 && i < hafizaBuyukluk)
                    {
                        if (hafiza[i][0] == x1 && hafiza[i][1] == y1)
                        {

                            for (j = i; j < 15; j++)
                            {

                                hafiza[j][0] = hafiza[j + 1][0];
                                hafiza[j][1] = hafiza[j + 1][1];
                                hafiza[j][2] = hafiza[j + 1][2];
                            }

                            hafiza[15][0] = 0;
                            hafiza[15][1] = 0;
                            hafiza[15][2] = 0;

                            if (hafiza[k][0] == 0 && k != 0)
                            {
                                k--;
                            }
                            else
                            {
                                k = hafizaBuyukluk - 1;
                            }

                            kontrol3 = 1;
                        }
                        i++;
                    }

                    kontrol3 = 0;
                    i = 0;
                    j = 0;
                    while (kontrol3 == 0 && i < hafizaBuyukluk)
                    {
                        if (hafiza[i][0] == x2 && hafiza[i][1] == y2)
                        {

                            for (j = i; j < 15; j++)
                            {
                                hafiza[j][0] = hafiza[j + 1][0];
                                hafiza[j][1] = hafiza[j + 1][1];
                                hafiza[j][2] = hafiza[j + 1][2];
                            }
                            hafiza[15][0] = 0;
                            hafiza[15][1] = 0;
                            hafiza[15][2] = 0;

                            if (hafiza[k][0] == 0 && k != 0)
                            {
                                k--;
                            }
                            else
                            {
                                k = hafizaBuyukluk - 1;
                            }

                            kontrol3 = 1;
                        }
                        i++;
                    }

                    hafiza[k][0] = x1;
                    hafiza[k][1] = y1;
                    hafiza[k][2] = tablo[x1][y1];
                    k++;
                    if (k >= hafizaBuyukluk)
                    {
                        k = 0;
                    }

                    hafiza[k][0] = x2;
                    hafiza[k][1] = y2;
                    hafiza[k][2] = tablo[x2][y2];
                    k++;
                    if (k >= hafizaBuyukluk)
                    {

                        k = 0;
                    }
                }

                printf("Bulamadiniz !! \n\n");
                durum[x1][y1] = 0;
                durum[x2][y2] = 0;
                sira = 1;
            };
            gecikme(2, " ", 0);
            gecikme(3, " saniye sonra ekran temizlenecek!!", 1);
            system("cls");
        }

        //    *********************************************************  //
        //    *********************************************************  //
        //    *********************************************************  //
        //    ***************** BILGISAYAR SIRASI *********************  //
        //    *********************************************************  //
        //    *********************************************************  //
        //    *********************************************************  //

        else // Bilgisayar girisi
        {

            bilgisayarhamle++;
            tabloyazdir(1);

            kontrol = 0;
            i = 0;
            while (i < hafizaBuyukluk - 1 && kontrol == 0) // Bilgisayar eslesebilen bir ikili biliyormu.
            {
                j = i + 1;
                while (j < hafizaBuyukluk && kontrol == 0)
                {
                    if (hafiza[i][2] == hafiza[j][2] && (hafiza[i][0] != hafiza[j][0] || hafiza[i][1] != hafiza[j][1]))
                    {
                        kontrol = 1;

                        x1 = hafiza[j][0];
                        y1 = hafiza[j][1];
                        x2 = hafiza[i][0];
                        y2 = hafiza[i][1];
                    }
                    j++;
                }
                i++;
            }

            kontrol2 = 1;

            if (kontrol == 0)
            {
                while (kontrol2 == 1) // Bilgisayar ilk sayi secimi
                {

                    kontrol2 = 0;
                    x1 = (rand() % (tabloBuyukluk - 1)) + 1;
                    y1 = (rand() % (tabloBuyukluk - 1)) + 1;

                    if (durum[x1][y1] != 0)
                    {
                        kontrol2 = 1;
                    }
                    for (i = 0; i < hafizaBuyukluk; i++)
                    {
                        if (x1 == hafiza[i][0] && y1 == hafiza[i][1])
                        {
                            kontrol2 = 1;
                        }
                    }
                }
            }

            durum[x1][y1] = 1;

            card1 = tablo[x1][y1];

            printf("Bilgisayar secim yapiyor...\n\n");

            gecikme(1, " ", 0);

            printf("Bilgisayarin sectigi birinci sayi :\n\nsatir : %d sutun : %d\t DEGER : |%d|\n\n", x1, y1, tablo[x1][y1]);

            gecikme(1, " ", 0);

            //  ***  // // Bilgisayar ikinci sayi secimi

            if (kontrol == 0)
            {
                kontrol2 = 1;
                i = 0;
                while (kontrol2 == 1 && i < hafizaBuyukluk)
                {
                    if (tablo[x1][y1] == hafiza[i][2])
                    {
                        x2 = hafiza[i][0];
                        y2 = hafiza[i][1];
                        kontrol2 = 0;
                    }
                    i++;
                }

                while (kontrol2 == 1) 
                {
                    kontrol2 = 0;
                    x2 = (rand() % (tabloBuyukluk - 1)) + 1;
                    y2 = (rand() % (tabloBuyukluk - 1)) + 1;

                    if (durum[x2][y2] != 0)
                    {
                        kontrol2 = 1;
                    }
                    for (i = 0; i < hafizaBuyukluk; i++)
                    {
                        if (x2 == hafiza[i][0] && y2 == hafiza[i][1])
                        {
                            kontrol2 = 1;
                        }
                    }
                }
            }

            durum[x2][y2] = 1;

            card2 = tablo[x2][y2];

            printf("Bilgisayarin sectigi ikinci sayi :\n\nsatir : %d sutun : %d\t DEGER : |%d|\n\n", x2, y2, tablo[x2][y2]);

            gecikme(1, " ", 0);

            if (card1 == card2)
            {
                bilgisayarPuan++;
            }

            tabloyazdir(0);

            if (card1 == card2)
            {
                printf("Bilgisayar dogru karti buldu.\n\n");
                sira = 1;
                durum[x1][y1] = 2;
                durum[x2][y2] = 2;

                kontrol2 = 0;
                i = 0;
                while (kontrol2 == 0 && i < hafizaBuyukluk)
                {

                    if (hafiza[i][0] == x1 && hafiza[i][1] == y1)
                    {

                        for (j = i; j < 15; j++)
                        {
                            hafiza[j][0] = hafiza[j + 1][0];
                            hafiza[j][1] = hafiza[j + 1][1];
                            hafiza[j][2] = hafiza[j + 1][2];
                        }

                        hafiza[15][0] = 0;
                        hafiza[15][1] = 0;
                        hafiza[15][2] = 0;

                        if (hafiza[k][0] == 0 && k != 0)
                        {
                            k--;
                        }
                        else
                        {
                            k = hafizaBuyukluk - 1;
                        }

                        kontrol2 = 1;
                    }
                    i++;
                }

                kontrol2 = 0;
                i = 0;
                while (kontrol2 == 0 && i < hafizaBuyukluk)
                {

                    if (hafiza[i][0] == x2 && hafiza[i][1] == y2)
                    {

                        for (j = i; j < 15; j++)
                        {
                            hafiza[j][0] = hafiza[j + 1][0];
                            hafiza[j][1] = hafiza[j + 1][1];
                            hafiza[j][2] = hafiza[j + 1][2];
                        }
                        hafiza[15][0] = 0;
                        hafiza[15][1] = 0;
                        hafiza[15][2] = 0;

                        if (hafiza[k][0] == 0 && k != 0)
                        {
                            k--;
                        }
                        else
                        {
                            k = hafizaBuyukluk - 1;
                        }

                        kontrol2 = 1;
                    }
                    i++;
                }
            }
            else
            {
                printf("Bilgisayar bilemedi\n\n");
                sira = 0;
                durum[x1][y1] = 0;
                durum[x2][y2] = 0;

                { // Kartlari hafizaya yazdirdik.

                    kontrol3 = 0;
                    i = 0;
                    j = 0;
                    while (kontrol3 == 0 && i < hafizaBuyukluk)
                    {
                        if (hafiza[i][0] == x1 && hafiza[i][1] == y1)
                        {

                            for (j = i; j < 15; j++)
                            {

                                hafiza[j][0] = hafiza[j + 1][0];
                                hafiza[j][1] = hafiza[j + 1][1];
                                hafiza[j][2] = hafiza[j + 1][2];
                            }

                            hafiza[15][0] = 0;
                            hafiza[15][1] = 0;
                            hafiza[15][2] = 0;

                            if (hafiza[k][0] == 0 && k != 0)
                            {
                                k--;
                            }
                            else
                            {
                                k = hafizaBuyukluk - 1;
                            }

                            kontrol3 = 1;
                        }
                        i++;
                    }

                    kontrol3 = 0;
                    i = 0;
                    j = 0;
                    while (kontrol3 == 0 && i < hafizaBuyukluk)
                    {
                        if (hafiza[i][0] == x2 && hafiza[i][1] == y2)
                        {

                            for (j = i; j < 15; j++)
                            {
                                hafiza[j][0] = hafiza[j + 1][0];
                                hafiza[j][1] = hafiza[j + 1][1];
                                hafiza[j][2] = hafiza[j + 1][2];
                            }
                            hafiza[15][0] = 0;
                            hafiza[15][1] = 0;
                            hafiza[15][2] = 0;

                            if (hafiza[k][0] == 0 && k != 0)
                            {
                                k--;
                            }
                            else
                            {
                                k = hafizaBuyukluk - 1;
                            }

                            kontrol3 = 1;
                        }
                        i++;
                    }

                    hafiza[k][0] = x1;
                    hafiza[k][1] = y1;
                    hafiza[k][2] = tablo[x1][y1];
                    k++;
                    if (k >= hafizaBuyukluk)
                    {
                        k = 0;
                    }

                    hafiza[k][0] = x2;
                    hafiza[k][1] = y2;
                    hafiza[k][2] = tablo[x2][y2];
                    k++;
                    if (k >= hafizaBuyukluk)
                    {

                        k = 0;
                    }
                }
            }

            gecikme(5, " ", 0);
            gecikme(3, " saniye sonra ekran temizlenecek!!", 1);
            system("cls");
        }
    } // En büyük while sonu

    if ((kullaniciPuan >= kartsayisi / 4 + 1))
    {
        printf("TEBRIKLER kazandiniz!!!\n\n");
    }
    else if (kullaniciPuan == bilgisayarPuan)
    {
        printf("Oyun berabere bitti!!!\n\n");
    }
    else
    {
        printf("Bilgisayar kazandi!!!\n\n");
    }

    printf("Kullanici puani : %d\nBilgisayar puani : %d\n\n", kullaniciPuan, bilgisayarPuan);
    printf("Kullanicinin hamle sayisi : %d\nBilgisayarin hamle sayisi %d", kullanicihamle, bilgisayarhamle);

    return 0;
}
