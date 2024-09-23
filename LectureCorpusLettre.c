#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


#define TAILLE 1024
#define TAILLE_NB_LETTRE 26

/* Fonction d'�critue de l'histogramme dans un fichier */
void ecrireFichier(char *nomFichier, long int cpt, int h[]) {

  FILE *fichOut ;
  int j ;

  
  fichOut = fopen(nomFichier, "w") ;
  if (!fichOut) {
    printf("erreur � l'ouverture du fichier %s\n", nomFichier) ;
    exit(2) ;
  }
  
  //printf("�criture du fichier %s\n", nomFichier) ;
  fprintf(fichOut, "nombre de caract�res lus : %ld\n", cpt) ;
  for (j = 0 ; j < 26 ; j++) {
    fprintf(fichOut, "%c : %d\n", j + 'a', h[j]) ;
  }
  fclose(fichOut) ;
}

/********************
* 
* Calcul de la fr�quence d'apparition des lettres dans un fichier texte.
* (g�n�ration de fichiers de progression)
*
******************/


int main(int argc, char* argv[]) 
{
  FILE *fichierCorpus ;
  char nomFichierGenere[100] ;
  int i, car, nbLignes, cptFichier ;
  long int nbCar ;
  char chaine[TAILLE] ;
  int nbLignesFichier=0;

  int numLigneStart;
  int nbLigneTraite;
  numLigneStart = atoi(argv[3]); //Numéro de la ligne par laquelle on doit commencer
  nbLigneTraite = atoi(argv[4]); //Nombre de lignes à traiter
  
  /* Tableau pour l'histogramme*/
  int histo[TAILLE_NB_LETTRE] = {0} ;
  
  
  if (argc != 5) {
    printf("usage : %s <fichier a traiter> <nom generique fichiers resultats> <Numero de ligne de départ> <Nombre de lignes a traiter>\n", argv[0]) ;
    exit(1) ;
  }

  fichierCorpus = fopen(argv[1], "r") ;
  if (!fichierCorpus) {
    printf("erreur a l'ouverture du fichier %s\n", argv[1]) ;
    exit(2) ;
  }
  
  while (fgets(chaine, TAILLE, fichierCorpus)) {
    nbLignesFichier++;
  }

  fseek(fichierCorpus, 0, SEEK_SET); //On replace au début

  for(int i = 0; i < numLigneStart; i++){
    fgets(chaine, TAILLE, fichierCorpus);
  }
  
  if(nbLigneTraite == 0){
    nbLigneTraite = nbLignesFichier;
  }
  
  nbCar = 0 ;
  nbLignes = 0 ;
  cptFichier = 0 ;

  /* Traitement ligne par ligne */
  while (fgets(chaine, TAILLE, fichierCorpus) && nbLignes < nbLigneTraite) {
    /* D�compte des lettres (minuscules)*/
    for (i = 0 ; i < strlen(chaine) ; i++) {
      car = chaine[i] - 'a' ;
      if ((car >= 0) && (car < 26)) {
        histo[car] ++ ;
        nbCar++ ;
      }
    }

    /* G�n�ration du fichier de d�compte */
    nbLignes++ ;
    if (nbLignes % 10000 == 0) {
      sprintf(nomFichierGenere, "%s_%d_%d.txt", argv[2], getpid(), cptFichier) ;
      ecrireFichier(nomFichierGenere, nbCar, histo) ;	
      printf(".");fflush(stdout);
      cptFichier++ ;
    }

  }
  printf("\n");
  
  /* Ecriture dans le dernier fichier */
  sprintf(nomFichierGenere, "%s_%d_final.txt", argv[2], getpid()) ;
  ecrireFichier(nomFichierGenere, nbCar, histo) ;
  printf("Dernier fichier genere : %s [nombre de caracteres traites : %ld, nb lignes traitees : %d sur %d]\n", nomFichierGenere, nbCar, nbLignes, nbLignesFichier) ;

   
  fclose(fichierCorpus) ;
  return(0) ;
}
