#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100000

int main() {
    srand(time(NULL));

    int i, j;
    int A[MAX];  //{4, 15, 14, 3, 9, 7, 12, 17, 8, 5, 16, 11, 1, 2, 10, 6}
    int N = 256;

    random(A, N);
    diziYaz(A, N);  // Sirali olmayan diziyi yaz.

    clock_t start, end;
    double gecen_zaman;
    start = clock();

    // Zaman hesabi baslangici

    // Zaman hesabi yapabilmek icin diziyi 500 kez karistirip siraladim.
    // Aksi takdirde dizi boyutunu buyutsem bile cok kisa suruyor.
    // Dizi boyutu cok buyuk olursa recrusive fonksiyonlarin cok birikmesi sebebi ile program duruyor.

    random(A, N);        // Random dizi olusturur.
    sorter(A, N, 0, 1);  // Artan yonde siralar.}

    // Zaman hesabi sonu

    end = clock();
    gecen_zaman = ((double)(end - start)) / CLOCKS_PER_SEC;

    diziYaz(A, N);  // Sirali diziyi yaz.

    printf("%g sn gecti", gecen_zaman);
    return 0;
}

// artan parametresi = 1 icin artan dizi, = 0 icin azalan dizi olsuturur.
void sorter(int A[], int N, int konum, int artan) {
    if (N != 2) {  // Diziyi once artan sonra azalan sekline getirir. Kisaca bitonic dizi olsuturur.

        sorter(A, N / 2, konum, 1);          // ilk yarisini artan yonde sirala
        sorter(A, N / 2, konum + N / 2, 0);  // ikinci yarisini azalan yonde sirala
    }

    swapper(A, N, konum, artan);  // Ust fonksiyonu ile ayni yonde(artan-azalan) swapper cagir.
}

void swapper(int A[], int N, int konum, int artan) {
    int i, tmp;

    for (i = 0; i < N / 2; i++) {
        if (!((A[konum + i] > A[konum + i + N / 2]) ^ (artan == 1))) {  // Xor gate ile swap gerekli mi kontrolu.
            tmp = A[konum + i];
            A[konum + i] = A[konum + i + N / 2];
            A[konum + i + N / 2] = tmp;
        }
    }
    if (N != 2) {
        swapper(A, N / 2, konum, artan);          // Ust fonksiyonu ile ayni yonde swap islemi uygula
        swapper(A, N / 2, konum + N / 2, artan);  // Ust fonksiyonu ile ayni yonde ikinci bolume swap islemi uygula
    }
}

void diziYaz(int A[], int N) {  // Dizi yazdirma
    int i;
    for (i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void random(int A[], int N) {
    int i;
    for (i = 0; i < N; i++) {  // Random dizi olustur.
        A[i] = rand() % N + 1;
    }
}
