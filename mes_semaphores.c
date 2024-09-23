#include "mes_semaphores.h"

int sem_creation(int * semid, int nombre_semaphores){
    *semid = semget(IPC_PRIVATE, nombre_semaphores, IPC_CREAT|0660|IPC_EXCL);
    if(*semid == -1){
        return -1;
    }
    return 0;
}

int sem_initialisation(int semid, int num_semaphore, int nbr_jetons){
    semval initsem;
    initsem.val = nbr_jetons; //= le nombre de jeton
    semctl(semid, num_semaphore, SETVAL, initsem);
    return 0;
}

int P(int semid, int num_semaphore){
    struct sembuf tab_op;
    tab_op.sem_num = num_semaphore;
    tab_op.sem_flg = 0;
    tab_op.sem_op = -1;

    semop(semid, &tab_op, 1);
    return 0;
}

int V(int semid, int num_semaphore){
    struct sembuf tab_op;
    tab_op.sem_num = num_semaphore;
    tab_op.sem_flg = 0;
    tab_op.sem_op = 1;

    semop(semid, &tab_op, 1);
    return 0;
}

int sem_destruction(int semid){
    semctl(semid, IPC_RMID, 0);
    return 0;
}

int sem_recup(int * semid, int nb_semaphores){
    *semid = semget(IPC_PRIVATE, nb_semaphores, 0);
    if(*semid == -1){
        return -1;
    }
    return 0;
}