#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 3

void random_matris(int A[][3]);
void minor(int A[][MAX], int M[][MAX], int x, int y);
int determinant(int B[]);
void yazdir(int C[][MAX]);

int main() {
    int A[MAX][MAX];  // Matris
    int M[MAX][MAX];  // Minor matris

    random_matris(A);

    yazdir(A);

    printf("\n\n*******************\n\n");

    minor(A, M, 0, 0);  // Baslangic olarak 0,0 gönderildi.

    yazdir(M);

    return 0;
}

void random_matris(int A[][MAX]) {
    srand(time(NULL));
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            A[i][j] = rand() % 10;
        }
    }
}

int determinant(int B[]) { return (B[0] * B[3]) - (B[1] * B[2]); }

void minor(int A[][MAX], int M[][MAX], int x, int y) {
    // x,y minoru bulunacak degerin koordinatı

    int B[4]; /* B dizisi minoru bulunacak degerin satir ve sutunlar silindikten
                 sonra olusan 2x2 matrisin sirasiyla (0,0)-(0,1)-(1,0)-(1,1)
                 degerlerini saklar.*/

    int i, j, k = 0;    //k B matrisinin indisini tutar.

    for (i = 0; i < 3; i++) {
        if (i != x) {
            for (j = 0; j < 3; j++) {
                if (j != y) {
                    B[k] = A[i][j];
                    k++;
                }
            }
        }
    }

    M[x][y] = determinant(B);
    y++;
    if (y == 3 && x == 2) {
        // done
    } else if (y == 3) {
        y = 0;
        x++;
        minor(A, M, x, y);
    } else {
        minor(A, M, x, y);
    }
}

void yazdir(int C[][MAX]) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d\t", C[i][j]);
        }
        printf("\n");
    }
}