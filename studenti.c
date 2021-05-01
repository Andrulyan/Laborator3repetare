/*
am o problema ca nu imi tine capul listelor de note si materii pt fiecare student
va rog sa imi dati feedback dupa aceea
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define dim_rand_fisier 50
#define dim_nume 25
#define dim_lista 100
#define nr_note_materii 20
typedef struct student
{
    ///in aceasta lista voi retine materia si nota pentru un student dar si un pointer catre urmatorul element
    char *materie;
    int nota;
    struct student *next;
} student;
typedef struct lista
{
    /*aceasta structura va contine: - numele studentului si clasa din care face parte
                                    - o lista simplu inlantuita care va retine materiile si notele studentului curent
                                    - pointeri catre nodul urmator si nodul precedent
    */
    student *stud_materii_note; ///va pointa catre structura student, care retine materia si nota
    int clasa;
    char *nume;
    struct lista *prev, *next;
} lista;
lista *lista_studenti_head = NULL; ///am creat pointeri catre inceputul si sfarsitul listei de studenti.
lista *lista_studenti_last = NULL;
/*student *creeare_nod(char *materie, int nota)
{
    student *nota_materie;
    nota_materie = (student *)malloc(sizeof(student)); ///declar un nod de tip student pt a stoca cele doua informatii (materia+nota)
    nota_materie->materie = (char *)malloc(dim_nume * sizeof(char));
    strcpy(nota_materie->materie, materie);
    nota_materie->nota = nota;
    nota_materie->next = NULL;
    return nota_materie;
}*/
student *inserare_nod_student(student *head, char *materie, int nota)
{
    if (head == NULL)
    {
        student *nota_materie;
        nota_materie = (student *)malloc(sizeof(student)); ///declar un nod de tip student pt a stoca cele doua informatii (materia+nota)
        nota_materie->materie = (char *)malloc(dim_nume * sizeof(char));
        strcpy(nota_materie->materie, materie);
        nota_materie->nota = nota;
        nota_materie->next = NULL;
        head = nota_materie;
    }
    else
    {

        student *index = head;

        while (index->next)
        {
            index = index->next;
        }
        student *nota_materie;
        nota_materie = (student *)malloc(sizeof(student)); ///declar un nod de tip student pt a stoca cele doua informatii (materia+nota)
        nota_materie->materie = (char *)malloc(dim_nume * sizeof(char));
        strcpy(nota_materie->materie, materie);
        nota_materie->nota = nota;
        nota_materie->next = NULL;

        index->next = nota_materie;
    }
    return head;
}
lista *verificare_student(lista *lista_studenti_head, char *nume)
{
    ///daca exista deja numele in lista voi returna 0 altfel 1; apoi voi afla pozitia pe care se afla acesst student
    lista *aux = lista_studenti_head;
    while (aux)
    {
        if (strcmp(aux->nume, nume) == 0)
        {
            //pozitie = aux; /// retin pointerul catre acel student care deja se afla in lista :)
            return aux;
            // return false;
        }
        aux = aux->next;
    }
    return NULL;
}
lista *inserare_nod(lista *lista_studenti_head, char *nume, int clasa, char *materie, int nota)
{
    lista *new_node;
    new_node = (lista *)malloc(sizeof(lista));
    new_node->nume = (char *)malloc(dim_nume * sizeof(char));
    strcpy(new_node->nume, nume);
    new_node->clasa = clasa;

    if (lista_studenti_head == NULL)
    {
        lista_studenti_head = new_node;
        lista_studenti_head->next = NULL;
        lista_studenti_head->prev = NULL;
        lista_studenti_last = lista_studenti_head;
        lista_studenti_head->stud_materii_note = malloc(sizeof(lista));
        lista_studenti_head->stud_materii_note = NULL;
        lista_studenti_head->stud_materii_note = inserare_nod_student(lista_studenti_head->stud_materii_note, materie, nota);
    }
    else
    {
        lista *poz = (lista *)malloc(sizeof(lista));
        poz = verificare_student(lista_studenti_head, nume); ///-NULL daca nu exista studentul
                                                             /// altfel pointerul acelui student care exista deja
        if (poz == NULL)
        {
            lista_studenti_last->next = new_node;
            new_node->prev = lista_studenti_last;
            lista_studenti_last = new_node;
            lista_studenti_last->next = NULL;
            lista_studenti_last->stud_materii_note = inserare_nod_student(lista_studenti_last->stud_materii_note, materie, nota);
        }
        else
        {
            ///am inserat o noua materie(+nota) pentru studentul aflat la adresa poz din lista dubla inlantuita de studenti

            poz->stud_materii_note = inserare_nod_student(poz->stud_materii_note, materie, nota);
        }
    }

    return lista_studenti_head;
}
void afisare_note_materii(student *note_materii)
{
    student *i = note_materii;
    while (note_materii)
    {
        printf("Materie: %s ---- nota: %d\n", note_materii->materie, note_materii->nota);
        note_materii = note_materii->next;
    }
}
void afisare_lista(lista *lista_studenti_head)
{
    printf("\n");
    lista *nod = lista_studenti_head; ///voi parcurge lista de la stanga la dreapta cu variabila pointer nod
    while (nod != NULL)
    {
        printf("Nume: %s\n ", nod->nume);
        printf("Clasa:%d \n", nod->clasa);
        // printf("Materiile + note:\n");
        afisare_note_materii(nod->stud_materii_note);
        printf("\n");
        nod = nod->next;
    }
}

int main()
{

    FILE *fisier = fopen("studenti.txt", "r");
    if (fisier == NULL)
    {
        printf("Eroare la deschiderea fisierlui cu studenti!");
        exit(1);
    }
    //lista_studenti_head = (lista *)malloc(dim_lista*sizeof(lista));
    while (!feof(fisier))
    {

        char *s;
        s = (char *)malloc(dim_rand_fisier * sizeof(char));
        fgets(s, dim_rand_fisier, fisier);
        fflush(stdin);
        //printf("%s\n", s);

        char *nume, *materie;
        nume = (char *)malloc(dim_nume * sizeof(char));
        materie = (char *)malloc(dim_nume * sizeof(char));
        int nota, clasa;

        char *p = strtok(s, ",\n");
        strcpy(nume, p); ///primul nume
        strcat(nume, " ");
        p = strtok(NULL, ",\n");
        int nr = 1; //va retine al catelea tip de informatie este acum pe linia curenta
        while (p)
        {
            // daca am ajuns la al doilea nume
            nr++;
            if (nr == 2)
            { //al doilea tips
                strcat(nume, p);
                strcat(nume, "\0");
            }
            if (nr == 3)
            {
                clasa = atoi(p);
            }
            else if (nr == 4)
            {

                strcpy(materie, p);
                /*strcat(materie, '\0');*/
            }
            else if (nr == 5)
            {
                nota = atoi(p);
            }
            p = strtok(NULL, ",\n");
        }
        //fflush(stdout);
        // printf("Nume: %s\n ", nume);
        // printf("Clasa:%d \n", clasa);
        // printf("Materia: %s\n ", materie);
        // printf("Nota:%d\n\n", nota);

        lista_studenti_head = inserare_nod(lista_studenti_head, nume, clasa, materie, nota);
        ///vom adauga informatiile tocmai extrase in structurile noastre
    }
    afisare_lista(lista_studenti_head);
    lista *copie_lista = lista_studenti_head;
}