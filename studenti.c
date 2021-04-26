#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define dim_rand_fisier 50
#define dim_nume 25
#define dim_lista
typedef struct student
{
    char *nume;
    int clasa;
    char *materie;
    int *note;
} student;
typedef struct lista
{
    student stud;
    struct lista *prev, *next;
} lista;
lista *lista_studenti; ///am creat o lista si initiallizata cu null
int main()
{

    FILE *fisier = fopen("studenti.txt", "r");

    if (fisier == NULL)
    {
        printf("Eroare la deschiderea fisierlui cu studenti!");
        exit(1);
    }
    //lista_studenti = (lista *)malloc(dim_lista * sizeof(lista));
    while (!feof(fisier))
    {
        char *s;
        s = (char *)malloc(dim_rand_fisier * sizeof(char));
        fgets(s, dim_rand_fisier, fisier);
        fflush(stdin);
        //    printf("%s", s);
        int n = strlen(s);
        char *p = strtok(s, ",\n");
        char nume[dim_nume];
        strcpy(nume, p); ///primul nume
        strcat(nume, " ");
        p = strtok(NULL, ",\n");
        bool ok = false, ok2 = true; /*presupun ca nu am adaugat inca al doilea nume si
                                     sa pot adauga doar o singura data numele*/
        int nr = 1;                  //va retine al catelea tip de informatie este acum pe linia curenta
        while (p)
        {
            // daca am ajuns la al doilea nume
            nr++;
            if (ok == false)
            { //al doilea tips
                strcat(nume, p);
                strcat(nume, "\0");
                ok = true;
                printf("Nume: %s\n ", nume);
            }
            int nota, clasa;
            char materie[dim_nume];
            if (nr == 3)
            {
                clasa = atoi(p);
                printf("Clasa:%d \n", clasa);
            }
            else if (nr == 4)
            {

                strcpy(materie, p);
                /*strcat(materie, '\0');*/
                printf("Materia: %s\n ", materie);
            }
            else if (nr == 5)
            {
                nota = atoi(p);
                printf("Nota:%d\n", nota);
            }
            p = strtok(NULL, ",\n");
        }
    }
}