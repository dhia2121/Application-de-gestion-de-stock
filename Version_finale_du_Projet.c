#include<stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<time.h>

struct produit{
    int ref;              // référence
    char nom[15];
    int prix;
    int qte;              // quantité
};

struct date{
    int j;
    int m;
    int a;
};

typedef struct produit produit;
typedef struct date date;

void tri_croissant(produit * tab, int n) {
    //trier les produits par ordre croissant selon leurs prix
  int i, j;
  produit aux;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (tab[j].prix > tab[j + 1].prix) {
        aux = tab[j];
        tab[j] = tab[j + 1];
        tab[j + 1] = aux;
      }
    }
  }
}
void tri_decroissant(produit * tab, int n) {
     //trier les produits par ordre decroissant selon leurs prix
  int i, j;
  produit aux;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (tab[j].prix < tab[j + 1].prix) {
        aux = tab[j];
        tab[j] = tab[j + 1];
        tab[j + 1] = aux;
      }
    }
  }
}

void tri_croissantr(produit * tab, int n) {
      //trier les produits par ordre croissant selon leurs references
  int i, j;
  produit aux;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (tab[j].ref > tab[j + 1].ref) {
        aux = tab[j];
        tab[j] = tab[j + 1];
        tab[j + 1] = aux;
      }
    }
  }
}
void tri_decroissantr(produit * tab, int n) {
  //trier les produits par ordre decroissant selon leurs references
  int i, j;
  produit aux;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (tab[j].ref < tab[j + 1].ref) {
        aux = tab[j];
        tab[j] = tab[j + 1];
        tab[j + 1] = aux;
      }
    }
  }
}



int recherche_indice(produit * tab , int n , int x) /*l'entrée x est la référence du produit*/
{   //fonction qui renvoie l'indice du produit dans le tableau d'apres sa reference
    for (int i = 0; i <= n ; i++)
    {
        if (tab[i].ref == x)
        {
            return i;
        }
    }
    return -1;
}

void getDate(date *d)
{    //permet d'obtenir la date actuelle du systeme et l'affecter a la structure date
      time_t now;
    time(&now);
    struct tm *local = localtime(&now);
        d->j=local->tm_mday;
        d->m=local->tm_mon +1;
        d->a=local->tm_year + 1900;
}
void AJOUTER_AU_FICHIER_DES_HISTORIQUES(char nom_fichier[15],char E_ou_S,produit x,date d){
    //ajouter toutes les instructions dans le fichier des historiques
    FILE * fichier;
    fichier=fopen(nom_fichier,"a");
    fprintf(fichier,"%c %d %s %d %d %d/%d/%d\n", E_ou_S, x.ref, x.nom, x.prix, x.qte, d.j, d.m, d.a);
    fclose(fichier);
}
int NOMBRE_DES_LIGNES(char nom_fichier[15]){
    //fonction qui retourne le nombre des lignes d'un fichier
    FILE *fichier;
    char ch[256];
    int i=0;
    fichier = fopen(nom_fichier,"r");

    while ((fgets (ch,256,fichier)) != NULL){
        i++;
    }
    fclose(fichier);
    return i;
}
int AJOUTER(produit * tab,int  n){
    //fonction qui ajoute le produit voulu

      int i,x;
      date d;
     printf("Donner la reference du produit a ajouter :");
     scanf("%d",&(x));
     i=recherche_indice(tab,n,x);
     if (i!= -1 ) {
        printf("Produit existant. \n");
        return n;
    }
    else{
        i=n;
        tab[i].ref=x;
        printf("Donner le nom du produit a ajouter : ");
        scanf("%s",&tab[i].nom);
        printf("Donner le prix du produit a ajouter : ");
        scanf("%d",&tab[i].prix);
        printf("Donner la quantite du produit a ajouter : ");
        scanf("%d",&tab[i].qte);
        getDate(&d);

        AJOUTER_AU_FICHIER_DES_HISTORIQUES("historiques.txt",'E',tab[i],d);
        printf("\nAjout effectuee avec succes. \n");
        return n+1;
        }
}

void RECHERCHER(produit* tab,int n){
    //chercher si le produit existe deja ou non
    int x;
    int indice;

    printf("Donner la reference ");
    scanf("%d",&(x));
    indice=recherche_indice(tab,n,x);

    if (indice != -1 ) {
        printf("Produit existant \n");
        printf("Quantite : %d \n",tab[indice].qte);
    }
    else{
        printf("Produit inexistant \n");

    }

}


int SUPPRIMER(produit * tab,int n){
    // fonction qui supprime un produit donné
     int i,x,k;
      date d;

     printf("Donner la reference du produit a supprimer ");
     scanf("%d",&(x));
     i=recherche_indice(tab,n,x);
     if (i== -1 ) {
        printf("Reference invalide.\n");
        return n;
    }
    else{
         getDate(&d);
         AJOUTER_AU_FICHIER_DES_HISTORIQUES("historiques.txt",'S',tab[i],d);
         for (int k=i; k<n; k++)
         {
             tab[k]=tab[k+1];
         }
         printf("Suppression effectuee avec succes. \n");
         return n-1;
    }
}


void MODIFIER(produit * tab,int n){
    //fonction qui modifie un produit donné
    int i,x;
    date d;

    getDate(&d);
    printf("Donner la reference du produit a modifier : ");
    scanf("%d",&x);
    i=recherche_indice(tab,n,x);
    if(i!=-1){
        printf("Le produit a modifier : \n");
        printf("Reference : %d \n",tab[i].ref);
        printf("Nom : %s \n",tab[i].nom);
        printf("Prix : %d \n",tab[i].prix);
        printf("Qantite : %d \n\n",tab[i].qte);
        AJOUTER_AU_FICHIER_DES_HISTORIQUES("historiques.txt",'S',tab[i],d);

        printf("Donner la nouvelle reference : ");
        scanf("%d",&(tab[i].ref));
        printf("Donner le nouveau nom : ");
        scanf("%s",&(tab[i].nom));
        printf("Donner le nouveau prix : ");
        scanf("%d",&(tab[i].prix));
        printf("Donner la nouvelle qantite : ");
        scanf("%d",&(tab[i].qte));
        printf("%n");

        printf("\nModification effectuee avec succes. \n");

        AJOUTER_AU_FICHIER_DES_HISTORIQUES("historiques.txt",'E',tab[i],d);
    }else{
        printf("Produit inexistant \n");
    }


}


void AFFICHER_LA_DESCRIPTION(produit * tab, int n){
    int i,x;
    printf("Donner la reference du produit : ");
    scanf("%d",&x);
    i=recherche_indice(tab,n,x);
    if(i!=-1){
        printf("Le nom du produit est %s. ",tab[i].nom);
        printf("Son prix est de %d dinars. ",tab[i].prix);
        printf("Sa quantite est %d. \n",tab[i].qte);
    }else{
        printf("Reference invalide. \n");
    }

}

void AFFICHER_TOUS_LES_PRODUITS(produit * tab, int n)
{   //affichage du stock ayant tous les produits existants
    int i,c=0;
    produit aux[20];
    int tri;

    for(i=0;i<n;i++)
    {
        aux[i]=tab[i];
    }

        if(n!=0){
            printf("(1) Affichage croissant selon le prix \n");
            printf("(2) Affichage decroissant selon le prix \n");
            printf("(3) Affichage croissant selon la reference \n");
            printf("(4) Affichage decroissant selon la reference \n\n");

            printf("Votre Choix :");
            scanf("%d",&tri);
            if (tri==1){
                tri_croissant(aux,n);
                c=1;
            }
            if(tri==2){
                tri_decroissant(aux,n);
                c=1;
            }
            if (tri==3){
                tri_croissantr(aux,n);
                c=1;
            }
            if(tri==4){
                tri_decroissantr(aux,n);
                c=1;
            }
            if(c==1){
                printf("\nREFERENCE           |NOM              |PRIX      |QUANTITE        ");
                printf("\n--------------------+-----------------+----------+----------\n");
                for(i=0;i<n;i++){
                    printf("%-20d|%-17s|%-10d|%-10d\n",aux[i].ref,aux[i].nom,aux[i].prix,aux[i].qte);
                    printf("--------------------+-----------------+----------+----------\n");

                }
            }
            printf("\n");

            }else
            {
                printf("Le stock est vide. \n");
            }

}


int REMPLIRE_LE_TABLEAU(char nom_fichier[15],produit * tab){              //fonction qui remplie le tableau du stock en cours et retourne sa taille
    FILE * fichier;
    int n,i;

    fichier=fopen(nom_fichier,"a");
    fclose(fichier);
    n=NOMBRE_DES_LIGNES(nom_fichier);
    fichier=fopen(nom_fichier,"r");
    if (fichier != NULL){
        for(i=0;i<n;i++){
            fscanf(fichier,"%d %s %d %d\n",&(tab[i].ref),&(tab[i].nom),&(tab[i].prix),&(tab[i].qte));
        }
        fclose(fichier);
    }
    return n;
}

void AJOUTER_AU_FICHIER_TABLEAU(char nom_fichier[15],produit * tab,int n){           // n = la taille du tableau à la fin
    FILE * fichier;
    int i;

    if(n>0){
        fichier=fopen(nom_fichier,"w");
        for(i=0;i<n;i++){
            fprintf(fichier,"%d %s %d %d\n",(tab[i].ref),(tab[i].nom),(tab[i].prix),(tab[i].qte));
        }
        fclose(fichier);
    }else{
        remove(nom_fichier);
    }

}


void AFFICHER_LES_HISTORIQUES(char nom_fichier[15]){
    //affichage des actions faites pour les produits entrants et sortant
    FILE * fichier;
    char c[15],a;
    int n,i;
    int b,d,e,f,g,h;

    n=NOMBRE_DES_LIGNES(nom_fichier);
    if(n!=0){
        fichier=fopen(nom_fichier,"r");
        printf("\nENTRE/SORTIE  |REFERENCE         |NOM              |PRIX      |QUANTITE  |DATE    ");
        printf("\n--------------+------------------+-----------------+----------+----------+------------\n");
        for(i=0;i<n;i++){
            fscanf(fichier,"%c %d %s %d %d %d/%d/%d\n",&a,&b,&c,&d,&e,&f,&g,&h);
            printf("%-14c|%-18d|%-17s|%-10d|%-10d|%d/%d/%d\n",a,b,c,d,e,f,g,h);
            printf("--------------+------------------+-----------------+----------+----------+------------\n");
        }
    }else{
        printf("Pas d'historiques.\n");
    }

}

void SETTINGS(){
        char choix[5],choix2[5];

    printf("(1) Changer le couleur du texte au blanc \n");
    printf("(2) Changer le couleur du texte au bleu \n");
    printf("(3) Changer le couleur du texte au rouge \n");
    printf("(4) Changer le couleur du texte au vert \n");
    printf("(5) Changer le couleur du texte au noir \n");
    printf("Votre Choix :");
    scanf("%s",&choix);

    printf("\n(1) Changer le couleur de l'arriere-plan au blanc \n");
    printf("(2) Changer le couleur de l'arriere-plan au bleu \n");
    printf("(3) Changer le couleur de l'arriere-plan au rouge \n");
    printf("(4) Changer le couleur de l'arriere-plan au vert \n");
    printf("(5) Changer le couleur de l'arriere-plan au noir \n");
    printf("Votre Choix :");
    scanf("%s",&choix2);

    switch(atoi(choix)){
    case 1 :
        {
            switch(atoi(choix2)){
            case 2 :
            {
                system("COLOR 97");
                break;
            }
            case 3 :
            {
                system("COLOR 47");
                break;
            }
            case 4 :
            {
                system("COLOR 27");
                break;
            }
            case 5 :
            {
                system("COLOR 07");
                break;
            }
            }
            break;
        }
    case 2 :
        {
            switch(atoi(choix2)){
            case 1 :
            {
                system("COLOR 79");
                break;
            }
            case 3 :
            {
                system("COLOR 49");
                break;
            }
            case 4 :
            {
                system("COLOR 29");
                break;
            }
            case 5 :
            {
                system("COLOR 09");
                break;
            }
            }
            break;
        }
    case 3 :
        {
            switch(atoi(choix2)){
            case 1 :
            {
                system("COLOR 74");
                break;
            }
            case 2 :
            {
                system("COLOR 94");
                break;
            }
            case 4 :
            {
                system("COLOR 24");
                break;
            }
            case 5 :
            {
                system("COLOR 04");
                break;
            }
            }
            break;
        }
    case 4 :
        {
            switch(atoi(choix2)){
            case 1 :
            {
                system("COLOR 72");
                break;
            }
            case 2 :
            {
                system("COLOR 92");
                break;
            }
            case 3 :
            {
                system("COLOR 42");
                break;
            }
            case 5 :
            {
                system("COLOR 02");
                break;
            }
            }
            break;
        }
    case 5 :
        {
            switch(atoi(choix2)){
            case 1 :
            {
                system("COLOR 70");
                break;
            }
            case 2 :
            {
                system("COLOR 90");
                break;
            }
            case 3 :
            {
                system("COLOR 40");
                break;
            }
            case 4 :
            {
                system("COLOR 20");
                break;
            }

            }
            break;
        }
    }
}





int main()
{
char choix[5];
produit tab[20];
date d;
int n;
char a[10];

n=REMPLIRE_LE_TABLEAU("tableau.txt",tab);

while(atoi(choix)!=9){                      //atoi() convertir un  string en un integer

    printf("\nGESTION DE STOCK\n\n");
    printf("(1)  Ajouter un produit \n(2)  Modifier un produit \n");
    printf("(3)  Rechercher un produit \n(4)  Supprimer un produit \n");
    printf("(5)  Afficher la description d'un produit \n(6)  Afficher tous les produits \n");
    printf("(7)  Afficher les historiques \n(8)  Settings \n");
    printf("(9)  Quitter le programme \n\n");
    printf("Votre choix: ");
    scanf("%s",&choix);

    while(atoi(choix)<1 || atoi(choix)>9){
        system("cls");              //clear console screen

        printf("\nGESTION DE STOCK\n\n");
        printf("(1)  Ajouter un produit \n(2)  Modifier un produit\n");
        printf("(3)  Rechercher un produit \n(4)  Supprimer un produit \n");
        printf("(5)  Afficher la description d'un produit \n(6)  Afficher tous les produits \n");
        printf("(7)  Afficher les historiques \n(8)  Settings \n");
        printf("(9)  Quitter le programme \n\n");
        printf("Votre choix: ");
        scanf("%s",&choix);
    }

    switch(atoi(choix)){

      case 1 :
      {
          system("cls");

          n=AJOUTER(tab,n);
          AJOUTER_AU_FICHIER_TABLEAU("tableau.txt",tab,n);

          printf("\n(0)  Retour au menu principale\n");
          scanf("%s",&a);
          break;
      }
      case 2 :
      {
          system("cls");

          MODIFIER(tab,n);
          AJOUTER_AU_FICHIER_TABLEAU("tableau.txt",tab,n);

          printf("\n(0)  Retour au menu principale\n");
          scanf("%s",&a);
          break;
      }
      case 3 :
      {
          system("cls");

          RECHERCHER(tab,n);

          printf("\n(0)  Retour au menu principale\n");
          scanf("%s",&a);
          break;
      }
      case 4 :
      {
          system("cls");

          n=SUPPRIMER(tab,n);
          AJOUTER_AU_FICHIER_TABLEAU("tableau.txt",tab,n);

          printf("\n(0)  Retour au menu principale\n");
          scanf("%s",&a);
          break;
      }
      case 5 :
      {
          system("cls");

          AFFICHER_LA_DESCRIPTION(tab,n);

          printf("\n(0)  Retour au menu principale\n");
          scanf("%s",&a);
          break;
      }
      case 6 :
      {
          system("cls");

          AFFICHER_TOUS_LES_PRODUITS(tab,n);

          printf("\n(0)  Retour au menu principale\n");
          scanf("%s",&a);
          break;
      }
      case 7 :
      {
          system("cls");

          AFFICHER_LES_HISTORIQUES("historiques.txt");

          printf("\n(0)  Retour au menu principale\n");
          scanf("%s",&a);
          break;
      }
      case 8 :
      {
          system("cls");

          SETTINGS();

          printf("\n(0)  Retour au menu principale\n");
          scanf("%s",&a);
          break;
      }
    }
    system("cls");
}
printf("Vous avez quitte l'application. ");
AJOUTER_AU_FICHIER_TABLEAU("tableau.txt",tab,n);

getch();
}
