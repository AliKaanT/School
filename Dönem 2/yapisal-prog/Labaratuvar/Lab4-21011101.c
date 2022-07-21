#include <stdio.h>

int main() {
    char Names[10] = {};
    int Times[10][2] = {{0}};
    int N, i;

    printf("Kac farkli isleminiz bulunmaktadir : ");
    scanf("%d", &N);

    printf("\n");
    for (i = 0; i < N; i++) {
        isimAl(i, Names);
        printf("\n");  // Farklı harfe gecince bosluk geribildirimi
    }

    printf("\nIslemler assagidaki gibidir.\n");
    for (i = 0; i < N; i++) {
        printf("%c ", Names[i]);
    }

    printf("\n\n************************\n");

    for (i = 0; i < N; i++) {
        printf("\n");
        zamanAl(i, Times, Names);
    }

    printf("\n******* GANTT TABLOSU *******\n\n");

    for (i = 0; i < N; i++) {
        GanttDraw(i, Times, Names);
        printf("\n");  // Farklı harfe gecince bosluk geribildirimi
    }
    return 0;
}

void isimAl(int i, char Names[]) {
    int j = 0;

    printf("%d. islemi giriniz : ", i + 1);
    scanf("%s", &Names[i]);

    while (Names[j] != Names[i] && j < i) {
        j++;
    }
    if (j < i || Names[i] > 122 || Names[i] < 97) {  // Yalnız kucuk harfler
        isimAl(i, Names);
    }
}

void zamanAl(int i, int Times[][2], char Names[]) {
    printf("- %c - baslangic : ", Names[i]);
    scanf("%d", &Times[i][0]);

    do {
        printf("- %c - bitis     : ", Names[i]);
        scanf("%d", &Times[i][1]);
    } while (Times[i][1] < Times[i][0]);
}

void GanttDraw(int i, int Times[][2], char Names[]) {
    int baslangic = Times[i][0];  // okunabilirlik acisindan 2 yeni degisken
    int bitis = Times[i][1];
    int j;

    for (j = 1; j < baslangic; j++) {
        printf("_");
    }
    while (j <= bitis) {
        printf("%c", Names[i]);
        j++;
    }
}