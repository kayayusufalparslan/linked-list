#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct n node;
struct n{
    char word[50];
    int x;
    struct n * next;
};


void bastir(node * r)
{
    while(r != NULL)
    {
        printf("Kelime: %s    |   Tekrar Sayisi: %d\n", r -> word, r->x );
        r = r -> next;
    }
}

node * basaEkle (node * r, int x, char kelime[50])
{
    r = (node *)malloc(sizeof(node));
        r -> next = NULL;
        r -> x = x;
        strcpy(r->word, kelime);
        return r;
}

node * rootDegistir ( node * r, int x, char kelime[50])
{
        node * temp = (node *)malloc(sizeof(node));
        temp -> x = x;
        temp -> next = r;
        strcpy(temp->word, kelime);
        return temp;
}

node * arayaVeSonaEkle ( node * r, int x, char kelime[50] )
{
    node * iter = r;
    while( iter -> next != NULL && iter -> next -> x > x){
        iter = iter -> next;
    }

    node * temp = (node *)malloc(sizeof(node));
    temp -> next = iter -> next;
    iter -> next = temp;
    temp -> x = x;
    strcpy(temp->word, kelime);
    return r;
}

node * ekleSirali(node * r, int x, char kelime[50])
{
    if( r==NULL) //linklist bos ise;
    {
        return basaEkle(r, x, kelime);
    }
    if( r -> x < x) // ilk elemeandan kucukse, root degisir;
    {
        return rootDegistir(r, x, kelime);
    }
    //Ekleyecegimiz degerden kucuk en buyuk degeri bulana kadar devam edip oraya ekleme metodu.
    return arayaVeSonaEkle(r, x, kelime);
}

int tekrar( char y[50]){
    FILE *f2;
    f2 = fopen("C:\\Users\\h\\Desktop\\prolab.txt","r");
    char x[50];
    //node * root;
    //root = NULL;
    int tekrar = 0;
    while( fscanf(f2, " %s ", x) != EOF)
    {
        for(int i = 0; x[i]; i++){
            x[i] = tolower(x[i]);
        }
        if(strcmp(x, y)==0){
            tekrar++;
        }
    }
    fclose(f2);
    return tekrar;
}

node * read_words (FILE *f ) {

    char x[50];
    node * root;
    root = NULL;
    int sayac=0;
    while( fscanf(f, " %s ", x) != EOF)
    {
        for(int i = 0; x[i]; i++){
            x[i] = tolower(x[i]);
        }
        sayac = tekrar(x);
        root = ekleSirali(root, sayac, x);
    }
    return root;
}

void silKopya(node * root)
{
    node * iter1, * iter2, * kopya;
    iter1 = root;

    //Elemanlari tek tek dongumuze aliyoruz;
    while (iter1 != NULL && iter1->next != NULL)
    {
        iter2 = iter1;

        //Secilen elemani, tum liste ile karsilastiriyoruz;
        while (iter2->next != NULL)
        {
            //Ayni kelimeye sahip elemanlari siliyoruz.
            if (strcmp(iter1->word, iter2->next->word)==0 )
            {
                kopya = iter2->next;
                iter2->next = iter2->next->next;
                //bellekte bosa yer kaplamamasi icin o alani bos birakiyoruz, siliyoruz;
                free(kopya);
            }
            else //Kelimeler ayni degilse eger listemizi taramaya devam etmesini soyluyoruz;
                iter2 = iter2->next;
        }
        iter1 = iter1->next;
    }
}

int main() {
    FILE *pointFile;
    pointFile = fopen("C:\\Users\\h\\Desktop\\prolab.txt","r");
    node * kelime;
    kelime = NULL;
    kelime = read_words(pointFile);
    silKopya(kelime);
    bastir(kelime);
    fclose(pointFile);

	return 0;
}
