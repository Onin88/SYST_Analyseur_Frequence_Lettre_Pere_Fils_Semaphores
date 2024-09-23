Clean:
	rm res*.txt
	rm pere
	rm fils

compil:
	gcc -o pere pere.c mes_semaphores.c
	gcc -o fils fils.c mes_semaphores.c

lancer1: compil
	./pere ExtraitLeMonde2002.txt res.txt 1

lancer2: compil
	./pere ExtraitLeMonde2002.txt res.txt 2

lancer4: compil
	./pere ExtraitLeMonde2002.txt res.txt 4

lancer8: compil
	./pere ExtraitLeMonde2002.txt res.txt 8