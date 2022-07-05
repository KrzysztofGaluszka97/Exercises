#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#define max 255
char wd[max];

int help(){
    printf(" Microshell \n");
    printf(" Autor programu : Krzysztof Galuszka. \n");
    printf(" ls - wyswieltanie zawartosci katalogu \n");
    printf(" cd - sluzy do przemieszczania sie miedzy katalogami\n 'cd nazwa_pliku' przenosi nas do katalogu w ktorym chcemy sie znajdowac,a \n 'c..' przenosi nas do katalogu nadrzednego' \n");
    printf(" exit - zakonczenie dzialania programu powloki \n");
    printf(" help - wyswietlanie autora projektu i oferowanych przez niego uslug \n");
    printf(" touch - tworzenie nowego pliku 'touch nazwa_pliku' \n");
    printf(" Wypisanie komunikatu bledu, przy niepoprawnym wpisaniu polecenia. \n");  
}

void path(){
    wd[max-1] = '\0';
    if(getcwd(wd, max-1) != NULL){
        printf("[{%s}]$ ", wd);
    }
}

void ls(char *par){
	DIR *kat;
	struct dirent *pot;
	char a[max];
	if(par==NULL) 
	{
	    getcwd(a,max);
	    kat=opendir(a);
	}
	else kat=opendir(par);
	if(kat!=NULL)
	{
	    while(pot=readdir(kat)) {
		printf("%s\n",pot->d_name);
		}	
	    closedir(kat);
	}
}

void cd (char *par){
	if(par==NULL){
		chdir(getenv("HOME"));
	}
	else {
		chdir(par);
	}
}

void touch(char * par) {
    FILE * plik = fopen(par, "a");
    fclose(plik);
}
int main()
{
    char napis[max];
    char * kom;
    char * par;
    fflush(stdout);
    help();
    while(1){
        path();
        fgets(napis, max, stdin);
        kom=strtok(napis," \n");
        par=strtok(NULL," \n");
        if (strcmp(napis,"exit")==0) exit(0);
        else if (strcmp(napis,"help")==0) help();
        else if (strcmp(napis,"ls")==0) ls(par);
  	else if (strcmp(napis,"cd")==0) cd(par);
  	else if (strcmp(napis,"touch")==0) touch(par);
  	else printf("Nieprawidlowe polecenie\n"); 
    };
    return 0;
}
