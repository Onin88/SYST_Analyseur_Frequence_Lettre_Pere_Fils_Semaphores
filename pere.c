#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include "mes_semaphores.h"

/*
1 Processus :   
                real    0m0.306s
                user    0m0.271s
                sys     0m0.035s        

2 Processus :   
                real    0m0.186s
                user    0m0.294s
                sys     0m0.043s

4 Processus :   
                real    0m0.135s
                user    0m0.403s
                sys     0m0.042s  

8 Processus :   
                real    0m0.142s
                user    0m0.665s
                sys     0m0.143s

Real : temps réel
User : Le temps que le CPU a passé en user mode
Syst : temps que le CPU a passé dans le core du processus

Plus on augmente le nombre de processus plus ça va vite,
sauf si le nombre de processus dépasse le nombre de coeurs de la machine.
*/

int main(int argc, char* argv[]){
    int status;
    FILE* fichierCorpus;

    pid_t pid;

    int nbligneatraiter;
    nbligneatraiter = 0;

    char nblignChar[1024];
    char lignStart[1024];
    
    char chaine[1024];

    float pourcentage;
    long long nbCarac;
    int* tableau;
    int nbProcessus;
    nbProcessus = atoi(argv[3]);
    int ligneDepart;
    ligneDepart = 0;
    int nbLignes;

    key_t key = ftok(".", 'k');
    int tabID = shmget(key, 26*(sizeof(int)), IPC_CREAT|0666); //création mémoire partagée
    int* tab = (int*)shmat(tabID, NULL, 0) ; //attachement au segment mémoire partagée, variable partagée
    if(tab == NULL){
        perror("Erreur d'attachement au segment memoire partagé");
        exit(2);
    }
    *tab = 0;

    if (tabID == -1){
        perror("Erreur creation segment memoire partagé");
        exit(1);
    }

    if (argc != 4) {
        printf("usage : %s <nom ficher txt à explorer> <nom fichier à générer> <nombre de processus>\n", argv[0]) ;
        exit(1) ;
    }

    fichierCorpus = fopen(argv[1], "r");
    if (!fichierCorpus) {
        printf("erreur à l'ouverture du fichier %s\n", argv[1]) ;
        exit(2);
    }

    nbLignes = 0;
    while (fgets(chaine, 1024, fichierCorpus)) {
        nbLignes++;
    }

    printf("nbLignes : %d\n" , nbLignes);

    if(nbProcessus>1){
        nbligneatraiter = nbLignes/nbProcessus;
    }else{
        nbligneatraiter = nbLignes;
    }

    
    sprintf(nblignChar, "%d", nbligneatraiter);
    sprintf(lignStart, "%d", ligneDepart);

    printf("nbLigneATraiter PERE : %d\n", nbligneatraiter);
    printf("ligne de départ PERE : %d\n", ligneDepart);

    for(int i = 0; i < nbProcessus; i++){
        if(i>0){
            ligneDepart += nbligneatraiter;
            sprintf(lignStart, "%d", ligneDepart);
            printf("ligneDepart [%d] : %d\n", i, ligneDepart);
        }
        pid = fork();
        switch (pid){
            case -1 :
                exit(1);

            case 0 :
                if(execl("./fils", "./fils", argv[1], argv[2], lignStart, nblignChar, NULL)){
                    perror("Erreur dans la création du fils");
                    return EXIT_FAILURE;
                }
                exit(1);

            default :
                break;
        }
    }

    while((pid = wait(&status)) > 0);

    nbCarac = 0;
    for(int i = 0; i<26; i++){
        nbCarac += tab[i]; // Nombre de caractères en tout récuperé
        printf("Tab : %d\n", tab[i]);
    }
    printf("nbcarac : %lld \n", nbCarac);
    for(int j = 0; j<26; j++){
        float tabN = (float) tab[j];
        //printf("float tab:%f\n", tabN);
        float nombreCarac = (float) nbCarac;
        //printf("float nbCarac:%f\n", nombreCarac);
        float division = tabN/nombreCarac;
        //printf("division : %f\n", division);
        pourcentage = (division)*100; // Pourcentage d'apparition de chaque variable
        printf("%c : %.2f %c\n", j+97, pourcentage, '%');
    }

    //Suppression partage
    shmdt(tab);
    shmctl(tabID, IPC_RMID, 0);
    return 0;
}

//./pere ExtraitLeMonde2002.txt res 2