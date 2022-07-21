#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 50

void get_polinom(double P[]);                             // P(x) fonksiyonu alır.
double Polinom_calc(double P[], double x);                // P(x) fonksiyonunu hesaplar.
void turev_al(double P[], double T[]);                    // Turev fonksiyon olusturur.
void matris_al(double M[][MAX], int n, int m);            // n*m matris alir.
void dizi_al(double M[], int n);                          // n elemanli dizi alir.
void matris_yaz(double A[][MAX], int n, int m);           // Matrisi ekrana yazar.
void satirdegis(double Z[][MAX], int m, int x1, int x2);  // x1 ve x2 satirini yer degistirir.
double det(double A[][MAX], int n);                       // determinant alir.
double kof(double A[][MAX], int n, int x, int y);         // kofaktor alir
double factorial(int a);                                  // Faktoriyel hesabi yapar.
double floatperm(double a, int b);                        // Virguluu a sayisi icin permutasyon
double floatcomb(double a, int b);                        // Virguluu a sayisi icin permutasyon

void bisection();      // Bisection yontemini calistirir
void regula_falsi();   // Regula-falsi yontemini calistitir
void new_raph();       // Newton-Raphson yontemini calistirir
void ters_matris();    // Matrisin tersini alir.
void gauss_elim();     // Gauss eliminasyon yontemini calistirir
void seidal();         // Gauss-Seidal yontemini calistirir.
void say_turev();      // Sayısal türev alma yontemini calistirir.
void trapez();         // Trapez integral yontemini calistirir.
void simpson();        // Simpson 1/3 yontemini calistirir.
void enterpolasyon();  // Enterpolasyon yontemini calistirir.

int main() {
    int yontem = 1, bitir;
    while (yontem != 0) {
        printf("0  : Programi sonlandir\n");
        printf("1  : Bisection\n");
        printf("2  : Regula-falsi\n");
        printf("3  : Newton-Raphson\n");
        printf("4  : NxN matrisin tersi\n");
        printf("5  : Gauss Eliminasyon\n");
        printf("6  : Gauss Seidal Iterasyon\n");
        printf("7  : Sayisal turev\n");
        printf("8  : Simpson yontemi\n");
        printf("9  : Trapez yontemi\n");
        printf("10 : Enterpolasyon yontemi\n");

        printf("\nKullanmak istediginiz yontemi seciniz : ");
        scanf("%d", &yontem);
        system("cls");

        if (yontem == 0) {
            printf("--Program sonlandirildi--");
            return 0;
        } else if (yontem == 1)
            bisection();
        else if (yontem == 2)
            regula_falsi();
        else if (yontem == 3)
            new_raph();
        else if (yontem == 4)
            ters_matris();
        else if (yontem == 5)
            gauss_elim();
        else if (yontem == 6)
            seidal();
        else if (yontem == 7)
            say_turev();
        else if (yontem == 8)
            simpson();
        else if (yontem == 9)
            trapez();
        else if (yontem == 10)
            enterpolasyon();
        else {
            system("cls");
            printf("Hatali giris yaptiniz !!\n\n");
        }

        printf("\n\n0 : Programi sonlandir\n1 : Yeniden kullan\n");
        scanf("%d", &bitir);
        if (bitir == 0) {
            return 0;
        } else {
            system("cls");
            main();
        }
    }
}

void bisection() {
    double a, b, x, tolerans;
    int iterasyon = 1;  //  2^iterasyon sayısını saklar.

    double F[MAX];
    get_polinom(F);

    printf("Kokun bulundugunu dusundugunuz bir aralik giriniz.\n");
    printf("a : ");
    scanf("%lf", &a);
    printf("b : ");
    scanf("%lf", &b);

    while (Polinom_calc(F, a) * Polinom_calc(F, b) > 0) {
        printf("Tekrar giriniz...\n");
        printf("a : ");
        scanf("%lf", &a);
        printf("b : ");
        scanf("%lf", &b);
    };

    printf("\nBir tolerans degeri giriniz (Ex: 0.0001) : ");
    scanf("%lf", &tolerans);
    tolerans = fabs(tolerans);

    // Islem kismi baslangic

    do {
        x = (a + b) / 2;
        if (Polinom_calc(F, x) == 0) {
            a = x;
            b = x;
        } else if (Polinom_calc(F, x) * Polinom_calc(F, a) > 0) {
            a = x;
        } else {
            b = x;
        }

        iterasyon *= 2;
    } while (((fabs(a - b)) / iterasyon) > tolerans);

    // Islem kismi bitis

    printf("\nKok : %g\n\n", x);
}

void regula_falsi() {
    double a, b, x, tolerans;
    int iterasyon = 1;  //  2^iterasyon sayısını saklar.

    double F[MAX];
    get_polinom(F);

    printf("Kokun bulundugunu dusundugunuz bir aralik giriniz.\n");
    printf("a : ");
    scanf("%lf", &a);
    printf("b : ");
    scanf("%lf", &b);

    while (Polinom_calc(F, a) * Polinom_calc(F, b) > 0) {
        printf("Tekrar giriniz...\n");
        printf("a : ");
        scanf("%lf", &a);
        printf("b : ");
        scanf("%lf", &b);
    };

    printf("\nBir tolerans degeri giriniz (Ex: 0.0001) : ");
    scanf("%lf", &tolerans);
    tolerans = fabs(tolerans);

    // Islem kismi baslangic

    do {
        x = Polinom_calc(F, a) * (b - a) /
                (Polinom_calc(F, a) - Polinom_calc(F, b)) +
            a;
        if (Polinom_calc(F, x) == 0) {
            a = x;
            b = x;
        } else if (Polinom_calc(F, x) * Polinom_calc(F, a) > 0) {
            a = x;
        } else {
            b = x;
        }

        iterasyon *= 2;
    } while (((fabs(a - b)) / iterasyon) > tolerans);

    // Islem kismi bitis

    printf("\nKok : %g\n\n", x);
}

void new_raph() {
    double a, x, tolerans;

    double F[MAX];
    double T[MAX];

    get_polinom(F);
    turev_al(F, T);

    printf("Bir baslangic noktasi seciniz : ");
    scanf("%lf", &a);

    printf("\nBir tolerans degeri giriniz (Ex: 0.01) : ");
    scanf("%lf", &tolerans);

    x = a;
    do {
        a = x;
        x = a - (Polinom_calc(F, a) / Polinom_calc(T, a));
    } while (fabs(a - x) > tolerans);

    printf("\nKok : %g\n\n", x);
}

void ters_matris() {
    int i, j, n;
    double A[MAX][MAX];
    double M[MAX][MAX];
    printf("Matristeki satir ve sutun sayisini (kare matris) giriniz : ");
    scanf("%d", &n);
    printf("\n");
    matris_al(A, n, n);

    double determinant = det(A, n);

    if (determinant == 0) {
        printf("Matrisin tersi yoktur.");
    } else {
        // ADJONIST MATRIS / det(A)
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                M[i][j] = kof(A, n, j, i) / determinant;
            }
        }
        printf("\nTers matris :\n\n");
        matris_yaz(M, n, n);
    }
}

void gauss_elim() {
    double A[MAX][MAX];
    double Answer[MAX];
    int n, m;
    int i, j, k;
    double tmp;

    printf("Matristeki satir ve sutun sayisini (kare matris) giriniz : ");
    scanf("%d", &n);
    m = n + 1;
    printf("Katsayilar matrisini giriniz !! \n");
    matris_al(A, n, n);
    printf("\nEsitlik vektorunu giriniz !!\n");
    dizi_al(Answer, n);

    for (i = 0; i < n; i++) {  //  Matrisleri birlestirmek.
        A[i][m - 1] = Answer[i];
    }

    printf("\n");

    matris_yaz(A, n, m);

    printf("\n\n-****************-\n\n");

    for (i = 0; i < n; i++) {
        if (A[i][i] == 0) {  // 0'a bolme hatasi cozme
            j = i + 1;
            while (A[j][j] == 0 && j < n) {
                j++;
            }
            satirdegis(A, m, i, j);
        }

        //////////

        k = 0;
        while (i != k) {
            tmp = A[i][k];
            for (j = k; j < m; j++) {
                A[i][j] -= A[k][j] * tmp;
            }
            k++;
        }
        tmp = A[i][k];
        for (j = 0; j < m; j++) {
            A[i][j] = A[i][j] / tmp;
        }

        //////////////
    }

    Answer[n - 1] = A[n - 1][m - 1];
    for (i = n - 2; i >= 0; i--) {
        m - 1 - i;
        j = m - 2;
        tmp = 0;
        while (j > i) {
            tmp += A[i][j] * Answer[j];
            j--;
        }
        Answer[i] = A[i][m - 1] - tmp;
    }

    for (i = 0; i < m - 1; i++) {
        printf("x%d : %g\n", i + 1, Answer[i]);
    }
}

void seidal() {
    double A[MAX][MAX];
    double Answer[MAX];
    int n, m;
    int i, j, k;
    double tmp, last, tolerans = 0.001;

    printf("Matristeki satir ve sutun sayisini (kare matris) giriniz : ");
    scanf("%d", &n);
    m = n + 1;
    printf("Katsayilar matrisini giriniz !! \n");
    matris_al(A, n, n);
    printf("\nEsitlik vektorunu giriniz !!\n");
    dizi_al(Answer, n);  // Gecici olarak answer dizisi kullanmak.

    for (i = 0; i < n; i++) {  //  Matrisleri birlestirmek.
        A[i][m - 1] = Answer[i];
    }

    printf("\nHer bir degisken icin baslangic degeri verin !!\n");
    dizi_al(Answer, n);

    printf("Bir tolerans degeri giriniz (Ex: 0.0001) : ");
    scanf("%lf", &tolerans);

    for (j = 0; j < m; j++) {  // max sayilar diagonala dizmek.
        tmp = fabs(A[j][j]);
        k = j;
        for (i = j + 1; i < n; i++) {
            if (fabs(A[i][j]) > tmp) {
                tmp = fabs(A[i][j]);
                k = i;
            }
        }
        if (k != j) {
            satirdegis(A, m, j, k);
        }
    }

    do {
        last = Answer[0];
        for (i = 0; i < n; i++) {
            tmp = 0;
            for (j = 0; j < m - 1; j++) {
                tmp += A[i][j] * Answer[j];
            }
            tmp -= A[i][i] * Answer[i];  // Kendisini cıkardik.
            Answer[i] = (A[i][m - 1] - tmp) / A[i][i];
        }
        // for (i = 0; i < n; i++) printf("%g\t", Answer[i]); //adimlari gostermek icin ac
    } while (fabs(last - Answer[0]) > tolerans);
    printf("\n");
    for (i = 0; i < n; i++) printf("x%d : %.4g\n", i + 1, Answer[i]);
}

void say_turev() {
    double a, h, toplam;
    double x1, x2;
    double F[MAX];
    get_polinom(F);

    printf("Hangi noktada turev bulmak istersiniz : ");
    scanf("%lf", &a);

    printf("\nBir adim araligi giriniz : ");
    scanf("%lf", &h);

    // f(a)' = f(a+h) - f(a-h) / 2h

    x1 = Polinom_calc(F, (a + h));
    x2 = Polinom_calc(F, (a - h));
    toplam = (x1 - x2) / (2 * h);

    printf("\nFonksiyonun %g noktasindaki turevi : %g", a, toplam);
}

void trapez() {
    int n, i;
    double F[MAX];
    double a, b, h, toplam = 0, x;

    get_polinom(F);

    printf("ALT sinir giriniz : ");
    scanf("%lf", &a);
    printf("UST sinir giriniz : ");
    scanf("%lf", &b);

    printf("\nAraligin kac parcaya bolunecegini giriniz (tamsayi) : ");
    scanf("%d", &n);

    x = a;
    h = (b - a) / n;

    for (i = 0; i <= n; i++) {
        // 1. ve n. degerleri 1 kez, ara degerleri iki kez topluyor.
        toplam += Polinom_calc(F, x);
        x += h;
        toplam += Polinom_calc(F, x);
    }

    toplam = (h / 2) * toplam;

    printf("\nFonksiyonun alt: %g ve ust:%g sinirlari ile integrali : %g", a, b, toplam);
}

void simpson() {
    int n, i;
    double F[MAX];
    double a, b, h, toplam, x;

    get_polinom(F);

    printf("ALT sinir giriniz : ");
    scanf("%lf", &a);
    printf("UST sinir giriniz : ");
    scanf("%lf", &b);

    printf("\nAraligin kac parcaya bolunecegini giriniz (tamsayi) : ");
    scanf("%d", &n);

    if (n % 2 == 1) n++;

    x = a;
    h = (b - a) / n;

    toplam = Polinom_calc(F, a) + Polinom_calc(F, b);

    for (i = 1; i < n; i++) {
        x += h;
        if (i % 2 == 1) {
            toplam += 4 * (Polinom_calc(F, x));
        } else {
            toplam += 2 * (Polinom_calc(F, x));
        }
    }

    toplam = (h / 3) * toplam;

    printf("\nFonksiyonun alt: %g ve ust:%g sinirlari ile integrali : %g", a, b, toplam);
}
void enterpolasyon() {
    double X[MAX];
    double Y[MAX];
    double D[MAX] = {0};  // Ileri farklar matrisi

    int i, flag = 1, n;
    double tmp = 1, cevap, x, k;

    printf("Fonksiyonun kac farkli degerine sahipsiniz : ");
    scanf("%d", &n);  // gecici olarak n kullandim.

    printf("Bilinen degerleri giriniz!!\n\n");

    for (i = 0; i < n; i++) {
        printf("X%d : ", i);
        scanf("%lf", &X[i]);
        printf("Y%d : ", i);
        scanf("%lf", &Y[i]);
        printf("\n");
    }

    printf("Hangi deger icin fonksiyonu hesaplamak istersiniz : ");
    scanf("%lf", &x);

    n = 0;
    while (tmp != 0) {  // Ileri farkları hesaplar.
        n++;
        tmp = 0;
        for (i = 0; i <= n; i++) {
            tmp += pow(-1, i) * floatcomb(n, i) * Y[n - i];
        }
        D[n] = tmp;
    }

    k = (x - X[0]) / (X[1] - X[0]);  // h = X[1]-X[0]
    tmp = 0;
    for (i = 1; i < n; i++) {
        tmp += floatcomb(k, i) * D[i];
    }
    cevap = Y[0] + tmp;

    printf("F(%g) = %g", x, cevap);
};

/**/

// YARDIMCI FONKSIYONLAR

/**/
double Polinom_calc(double P[], double x) {
    double toplam = 0;
    int i;
    for (i = 1; i <= (P[0] + 1); i++) {
        toplam += P[i] * pow(x, (i - 1));
    }
    return toplam;
};

void get_polinom(double P[]) {
    /*
    Polinom matrisleri 0. indisde polinomun derecesini,
    sonraki indislerde x^0 'dan baslayarak katsayilari tutar.
    Ör : P[4] = {2, 1.5 ,-8 ,3}; ===>  3x^2 - 8x + 1.5
    */

    int i, onay = 0;
    while (onay == 0) {
        printf("Polinomun derecesini giriniz : ");
        scanf("%lf", &P[0]);

        printf("Sirayla katsayilari giriniz\n\n");

        for (i = 1; i <= (P[0] + 1); i++) {
            printf("x^%d : ", i - 1);
            scanf("%lf", &P[i]);
        }

        printf("\n P(x) = ");

        for (i = (P[0] + 1); i >= 1; i--) {
            if (i != 1) {
                printf("%gx^%d + ", P[i], i - 1);
            } else {
                printf("%g", P[i]);
            }
        }
        onay = 1;
        printf("\n\nOnayliyor musunuz?\nEvet : 1 Hayir : 0\n");
        scanf("%d", &onay);
        system("cls");
    }

    printf("\n P(x) = ");

    for (i = (P[0] + 1); i >= 1; i--) {
        if (i != 1) {
            printf("%gx^%d + ", P[i], i - 1);
        } else {
            printf("%g\n\n", P[i]);
        }
    }
}

void turev_al(double P[], double T[]) {
    int i;
    for (i = 1; i < P[0] + 1; i++) {
        T[i] = P[i + 1] * (i);
    }
    T[0] = P[0] - 1;
}

void matris_al(double M[][MAX], int n, int m) {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("A[%d][%d] : ", i + 1, j + 1);
            scanf("%lf", &M[i][j]);
        }
        printf("\n");
    }
}

void satirdegis(double Z[][MAX], int m, int x1, int x2) {
    double tmp;
    int i;

    for (i = 0; i < m; i++) {
        tmp = Z[x1][i];
        Z[x1][i] = Z[x2][i];
        Z[x2][i] = tmp;
    }
}

void dizi_al(double M[], int n) {
    int j;
    for (j = 0; j < n; j++) {
        printf("A[%d] : ", j + 1);
        scanf("%lf", &M[j]);
    }
}

void matris_yaz(double A[][MAX], int n, int m) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%.3g\t", A[i][j]);
        }
        printf("\n");
    }
}

double det(double A[][MAX], int n) {
    int i;
    double tmp = 0;

    if (n == 1) {
        tmp = A[0][0];
    } else if (n == 2) {
        tmp = (A[0][0] * A[1][1]) - (A[0][1] * A[1][0]);
    } else {
        tmp = 0;
        for (i = 0; i < n; i++) {
            tmp += kof(A, n, 0, i) * A[0][i];
        }
    }
    return tmp;
}
double kof(double A[][MAX], int n, int x, int y) {
    double M[MAX][MAX];  // A matrisinin kopyasi
    int i, j, k;
    double tmp;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            M[i][j] = A[i][j];
        }
    }

    for (k = 0; k < n; k++) {  // satiri yok et
        for (i = x; i < n - 1; i++) {
            M[i][k] = M[i + 1][k];
        }
    }
    for (k = 0; k < n; k++) {  // sutunu yok et
        for (i = y; i < n - 1; i++) {
            M[k][i] = M[k][i + 1];
        }
    }

    return det(M, n - 1) * pow(-1, x + y);
}

double factorial(int a) {
    int tmp = 1;
    if (a == 0 || a == 1) return 1;
    for (; a > 1; a--) {
        tmp = tmp * a;
    }
    return tmp;
}

double floatcomb(double a, int b) {
    return floatperm(a, b) / factorial(b);
}

double floatperm(double a, int b) {
    int i;
    double tmp = 1;
    for (i = 0; i < b; i++) {
        tmp *= a;
        a--;
    }
    return tmp;
}
// THE END