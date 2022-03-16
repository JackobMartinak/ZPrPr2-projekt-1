#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funkcia V otvori subor
void funkcia_v(FILE** organized_stuff, int *flag,char***nazov_p, char***prednasatel_p, char***typPrednasky_p, char***casPrednasky_p, char***datumPrednasky_p, int* counts ){
    char line[200];
    int count = 0;
    char *sp;
    if(*organized_stuff != NULL){
        // Zistit ci uz boli vytvorene dynamicke polia        
        if(*flag == 0){
            while (fgets(line, 200, *organized_stuff) != NULL) // citanie riadkov kym nie je na konci suboru EOF
        {
            sp = strtok(line, "");   // Nacitanie noveho riadku
            count++; // line + 1
            while(sp != NULL){      // Kym nie je koniec riadku
              sp[strcspn(sp, "\n")] = 0; // Nacita sa string bez znaku \n
                if(count % 6 == 1){
                    printf("Nazov prednasky: %.150s\n", sp);
                } if (count % 6 == 2){
                    printf("Prednasatel: %.100s\n", sp);
                } if (count % 6 == 3){
                    printf("Typ prednasky: %s\n", sp);
                } if (count % 6 == 4){
                    printf("Cas prednasok: %c%c-%c%c\n",sp[0],sp[1],sp[2],sp[3]);
                } if (count % 6 == 5){
                    printf("Datum prednasky: %s\n", sp);
                } if (count % 6 == 0){
                    printf("\n");
                }
                sp = strtok(NULL, "");  // Nastavenie konca riadku 
            }
        }
          // Ak ano tak -> Vypisat jednotlive zaznamy z poli
        } 
        if(*flag==1) {
            for(int i = 0; i < (*counts / 6); i++){
                // printf("I: %d\n", i);
                printf("Nazov prednasky: %.150s\n", (*nazov_p)[i]);
                printf("Prednasatel: %.100s\n", (*prednasatel_p)[i]);
                printf("Typ prednasky: %s\n", (*typPrednasky_p)[i]);
                printf("Cas prednasok: %c%c-%c%c\n", (*casPrednasky_p)[i][0],(*casPrednasky_p)[i][1],(*casPrednasky_p)[i][2],(*casPrednasky_p)[i][3]);
                printf("Datum prednasky: %s\n", (*datumPrednasky_p)[i]);
                printf("\n");
            }
        }
                // Inak Vypisat jednotlive zaznamy zo suboru
            
    } else {
        *organized_stuff = fopen("OrganizacnePodujatia.txt", "r");
        printf("SUBOR OTVORENY!\n");
    }

}

void funkcia_n(FILE** organized_stuff, char***nazov_p, char***prednasatel_p, char***typPrednasky_p, char***casPrednasky_p, char***datumPrednasky_p, int *flag, int *count_p){
    // Dynamicky vytvori polia pre jednotlive polozky
    // 1. Nazov prispevku 2. mena autorov 3. Typ prezentovania
    // 4. Cas prezentovania 5. Datum prezentacie
    // Zapisu sa v takom poradi ako su v subore
    // Ak polia u6 boli predtym vytvorene tak sa dealokuju a vytvoria nanovo
    // Po uspesnom nacitani hodnot sa vypise "Nacitane data.
    // Ak subor este nie je otvoreny, vypise spravu "Neotvoreny subor"
    // TODO: Spocita pocet zaznamov v subore
    char line[1024];
    char *sp;
    
    // *pomocnePole, *vsetkyPolia[] = {&nazovPrednasky, &prednasatel, &casPrednasky, &datumPrednasky, &pomocnePole};
    int count = 0, counts = 0; 
    // Kontrola otvoreneho suboru
    if(*organized_stuff == NULL){
        printf("Neotvoreny subor\n");
    } else {
        // Ak je otvoreny, nacita pocet riadkov a reallocuje pamat
        rewind(*organized_stuff);
        while (fgets(line, 1024, *organized_stuff) != NULL) // citanie riadkov kym nie je na konci suboru EOF
        {
            sp = strtok(line, "");   // Nacitanie noveho riadku
            count++; // line + 1
            while(sp != NULL){ // Kym nie je koniec riadku
                sp = strtok(NULL, "");  // Nastavenie konca riadku 
            }
        }
        count += 1;
        // char *nazovPrednasky[count / 6], *prednasatel[count / 6], *typPrednasky[count / 6], *casPrednasky[count / 6], *datumPrednasky[count/6];
        if(*flag == 1) {
            for(int x = 0; x < count/6; x++){
                free((*nazov_p)[x]);
                free((*prednasatel_p)[x]);
                free((*typPrednasky_p)[x]);
                free((*casPrednasky_p)[x]);
                free((*datumPrednasky_p)[x]);
            }
                free(*nazov_p);
                free(*prednasatel_p);
                free(*typPrednasky_p);
                free(*datumPrednasky_p);
                free(*casPrednasky_p);

        }

        printf("pocet riadkov: %d \n", count);
        *count_p = count;

        // for(int i = 0; i < count / 6; i++){
        //     nazov_p[i] = (char*)malloc(sizeof(char) * 1024);
        //     prednasatel_p[i] = (char*)malloc(sizeof(char) * 1024);
        //     typPrednasky_p[i] = (char*)malloc(sizeof(char) * 1024);
        //     casPrednasky_p[i] = (char*)malloc(sizeof(char) * 1024);
        //     datumPrednasky_p[i] = (char*)malloc(sizeof(char) * 1024);
        // }
        *nazov_p = (char**)malloc((count/6)*sizeof(char*));
        *prednasatel_p = (char**)malloc((count/6)*sizeof(char*));
        *typPrednasky_p = (char**)malloc((count/6)*sizeof(char*));
        *casPrednasky_p = (char**)malloc((count/6)*sizeof(char*));
        *datumPrednasky_p = (char**)malloc((count/6)*sizeof(char*));

        for(int i = 0; i < count/6; i++){
            (*nazov_p)[i] = (char*)malloc(60 * sizeof(char));
            (*prednasatel_p)[i] = (char*)malloc(60 * sizeof(char));
            (*typPrednasky_p)[i] = (char*)malloc(60 * sizeof(char));
            (*casPrednasky_p)[i] = (char*)malloc(60 * sizeof(char));
            (*datumPrednasky_p)[i] = (char*)malloc(60 * sizeof(char));
        }
        int j = 0, k=0 , l=0, m=0, n=0, o=0;
        // int i = 0;
        rewind(*organized_stuff); // Vratenie kurzora na zaciatok suboru
        
        while (fgets(line, 1024,* organized_stuff) != NULL) // citanie riadkov kym nie je na konci suboru EOF
        {
            sp = strtok(line, "");   // Nacitanie noveho riadku
            counts++;
            while(sp != NULL){      // Kym nie je koniec riadku
                // /// // // // // // strcpy(pomocnePole, sp);
                sp[strcspn(sp, "\n")] = 0; // Nacita sa string bez znaku \n
                if(counts % 6 == 1){
                    strcpy((*nazov_p)[j], sp);
                    
                    // printf("Nazov prednasky %d : %s\n",j ,(*nazov_p)[j]);
                    j++;
                } if (counts % 6 == 2){
                    strcpy((*prednasatel_p)[k], sp);
                    // printf("Prednasatel %d: %s\n", k, (*prednasatel_p)[k]);
                    k++;
                } if (counts % 6 == 3){
                    strcpy((*typPrednasky_p)[l], sp);
                    // printf("Typ prednasky %d: %s\n", l , (*typPrednasky_p)[l]);
                    l++;
                } if (counts % 6 == 4){
                    strcpy((*casPrednasky_p)[m], sp);
                    // printf("Cas prednasok %d: %s\n", m , (*casPrednasky_p)[m]);
                    m++;
                } if (counts % 6 == 5){
                    // printf("AAAAAAA\n");
                    strcpy((*datumPrednasky_p)[n], sp);
                    // printf("Datum prednasky %d: %s\n", n, (*datumPrednasky_p)[n]);
                    n++;
                }
                if (counts % 6 == 0){
                    // printf("Prazdny riadok \n");
                }
                sp = strtok(NULL, "");  // Nastavenie konca riadku v
              // printf("%s", prednasatel_p[2]);
            }
            
        }
        printf("Subor Nacitany\n");
        // printf("=========%s\n", (*prednasatel_p)[1]);
        *flag = 1;
    }

}

void funkcia_o(FILE** organized_stuff, char***nazov_p, char***prednasatel_p, char***typPrednasky_p, char***casPrednasky_p, char***datumPrednasky_p, int *flag, int *count_p ) {
    char datum[9];
    if(*organized_stuff == NULL){
        printf("SUBOR ESTE NEBOL OTVORENY\n");
    } else{
        printf("Zadaj datum: ");
        scanf("%s", datum);
      // printf("%s", datum);
        if(*flag==1){
            datum[strcspn(datum, "\n")] = 0; // Nacita sa string bez znaku \n
            for(int f=0; f < (*count_p / 6); f++){
                if(strcmp((*datumPrednasky_p)[f], datum)==0){
                    printf("%s %2s %2s %2s\n", (*casPrednasky_p)[f],(*typPrednasky_p)[f],(*prednasatel_p)[f], (*nazov_p)[f]);
                }
            }
        } else {
            char line[1024],nazov[200],pred[200],typ[200],cas[200] ,datum_a[200];
            char* sp;
            int count = 0;
            while(fgets(line, 1024, *organized_stuff)){
              sp = strtok(line, "");
              count++;
              while(sp != NULL){
                sp[strcspn(sp, "\n")] = 0;
                  if(count % 6 == 1){
                    // printf("Nazov prednasky: %.150s\n", sp);
                    strcpy(nazov, sp);
                } if (count % 6 == 2){
                    // printf("Prednasatel: %.100s\n", sp);
                    strcpy(pred, sp);
                } if (count % 6 == 3){
                    // printf("Typ prednasky: %s\n", sp);
                    strcpy(typ, sp);
                } if (count % 6 == 4){
                    // printf("Cas prednasok: %c%c-%c%c\n",sp[0],sp[1],sp[2],sp[3]);
                    strcpy(cas, sp);
                } if (count % 6 == 5){
                    // printf("Datum prednasky: %s\n", sp);
                    strcpy(datum_a, sp);
                } if (count % 6 == 0){
                    // printf("\n");
                }
              }
              if(strcmp(datum_a, datum) == 0){
                 printf("%s %2s %2s %2s\n", cas, typ, pred, nazov);
              }
            }
        }
    }
}

void funkcia_s(FILE** organized_stuff, char***nazov_p, char***prednasatel_p, char***typPrednasky_p, char***casPrednasky_p, char***datumPrednasky_p, int *flag, int *count_p ) {
  if(*flag == 0){
    printf("Polia nie su vytvorene\n");
  } else {
    char datum[64], typ[64];
    int flag_vstup = 0;
    printf("Zadajte datum(rrrrmmdd) a typ: ");
    scanf("%s %s",datum,  typ);
    datum[strcspn(datum, "\n")] = 0;
    typ[strcspn(typ, "\n")] = 0;
    // printf("%s", datum);
    // printf("%s", typ);
    
    for(int c = 0; c < (*count_p / 6); c++){
      if(strcmp((*datumPrednasky_p)[c], datum) == 0 && strcmp((*typPrednasky_p)[c], typ) == 0){
        printf("%s\t %s\t %s\n", (*casPrednasky_p)[c], (*prednasatel_p)[c], (*nazov_p)[c]);
        flag_vstup = 1;
        // printf("%d", flag_vstup);
      }
    }
    // printf("%d", flag_vstup);
    if(flag_vstup == 0){
      printf("Pre dany vstup neexistuju zaznamy\n");
    }
  }
}

int main(){
    
        FILE *organized_stuff = NULL;
        int counts = 0;
        int *count_p;
        char operative;
        char** nazov = NULL, **prednasatel = NULL, **typPrednasky = NULL;
        char**casPrednasky = NULL; 
        char **datumPrednasky = NULL;
        int flag = 0;
        int *flag_p = &flag;
        count_p = &counts;
    while(1){
        scanf("%c", &operative);
        if(operative == 'v'){
            funkcia_v(&organized_stuff, flag_p , &nazov, &prednasatel, &typPrednasky, &casPrednasky, &datumPrednasky, count_p);
            continue;
        } else if(operative == 'o'){
            funkcia_o(&organized_stuff, &nazov, &prednasatel, &typPrednasky, &casPrednasky, &datumPrednasky, flag_p, count_p);
        } else if(operative == 'n'){
            funkcia_n(&organized_stuff, &nazov, &prednasatel, &typPrednasky, &casPrednasky, &datumPrednasky, flag_p, count_p);
        } else if (operative == 's'){
          funkcia_s(&organized_stuff, &nazov, &prednasatel, &typPrednasky, &casPrednasky, &datumPrednasky, flag_p, count_p);
        } else if (operative == 'h') {
            // TODO: Vypise sa histogram pre typ prezentovania a hodinu v
            // 2-hodinovom intervale
            // Ak dynamicke polia nie su vytvorene, vypise spravu
            // Polia nie su vytvorene \n
        } else if (operative == 'z'){
            // TODO: Nacita nazov prispevku a zaznam/zaznamy s rovnakym
            // Nazvom sa vymazu z dynamickych poli. 
            // Po vymazani sa vypise hlaska kolko zaznamov bolo vymazanych
            // Ak polia nie su vytvorene, vypise "Polia nie su vytvorene"
            // Sprava je nasledovana koncom riadku
        } else if (operative == 'p') {
            // TODO: Nacitat vsetky udaje z klavesnice a pridat 
            // zaznam do dynamickych poli na koniec
            // Po pridani sa vypise "Zaznam sa podarilo pridat"
            // Ak polia nie su vytvorene vypise sa "Pola nie su vytvorene"
            // Sprava je nasledovana koncom riadku
        } else if (operative == 'k'){
            if(organized_stuff != NULL){
                fclose(organized_stuff);
            }

            if(flag == 1){
              for(int i = 0; i < 6; i++){
                
                free(nazov[i]);
                free(prednasatel[i]);
                free(typPrednasky[i]);
                free(casPrednasky[i]);
                free(datumPrednasky[i]);
              }
              free(nazov);
              free(prednasatel);
              free(typPrednasky);
              free(casPrednasky);
              free(datumPrednasky);
            }      
            break;
        }
    }
    
    return 0;
}