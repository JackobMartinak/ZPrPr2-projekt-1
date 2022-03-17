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
                    // vypise nazov prednasky s limitom 150 znakov
                    printf("Nazov prednasky: %.150s\n", sp);
                } if (count % 6 == 2){
                    // vypise prednasatela s limitom 100 znakov
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
                printf("Nazov prednasky: %.150s\n", (*nazov_p)[i]);
                printf("Prednasatel: %.100s\n", (*prednasatel_p)[i]);
                printf("Typ prednasky: %s\n", (*typPrednasky_p)[i]);
                printf("Cas prednasok: %c%c-%c%c\n", (*casPrednasky_p)[i][0],(*casPrednasky_p)[i][1],(*casPrednasky_p)[i][2],(*casPrednasky_p)[i][3]);
                printf("Datum prednasky: %s\n", (*datumPrednasky_p)[i]);
                printf("\n");
            }
        }
            
    } else {
        *organized_stuff = fopen("OrganizacnePodujatia.txt", "r");
        printf("SUBOR OTVORENY!\n");
    }

}

// Funkcia N alokuje polia
void funkcia_n(FILE** organized_stuff, char***nazov_p, char***prednasatel_p, char***typPrednasky_p, char***casPrednasky_p, char***datumPrednasky_p, int *flag, int *count_p){
    /* Dynamicky vytvori polia pre jednotlive polozky
        // 1. Nazov prispevku 2. mena autorov 3. Typ prezentovania
        // 4. Cas prezentovania 5. Datum prezentacie
        // Zapisu sa v takom poradi ako su v subore
        // Ak polia u6 boli predtym vytvorene tak sa dealokuju a vytvoria nanovo
        // Po uspesnom nacitani hodnot sa vypise "Nacitane data.
        // Ak subor este nie je otvoreny, vypise spravu "Neotvoreny subor" */
    char line[1024];
    char *sp;
    int count = 0, counts = 0; 
    // Kontrola otvoreneho suboru
    if(*organized_stuff == NULL){  // Kontroluje ci subor bol otvoreny
        printf("Neotvoreny subor\n");
    } else {
        // Ak je otvoreny, nacita pocet riadkov a reallocuje pamat
        rewind(*organized_stuff); // ak uz bol otvoreny nastavi kurzor na zaciatok suboru
        while (fgets(line, 1024, *organized_stuff) != NULL) // citanie riadkov kym nie je na konci suboru EOF
        {
            sp = strtok(line, "");   // Nacitanie noveho riadku
            count++; // line + 1
            while(sp != NULL){ // Kym nie je koniec riadku
                sp = strtok(NULL, "");  // Nastavenie konca riadku 
            }
        }
        count += 1;

        if(*flag == 1) { // Ak uz boli polia raz vytvorene tak nasleduje uvolenie a znovu alokovanie poli
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
        // Alokovanie poli
        *count_p = count;
        *nazov_p = (char**)malloc((*count_p/6)*sizeof(char*));
        *prednasatel_p = (char**)malloc((*count_p/6)*sizeof(char*));
        *typPrednasky_p = (char**)malloc((*count_p/6)*sizeof(char*));
        *casPrednasky_p = (char**)malloc((*count_p/6)*sizeof(char*));
        *datumPrednasky_p = (char**)malloc((*count_p/6)*sizeof(char*));

        for(int i = 0; i < *count_p/6; i++){
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
                sp[strcspn(sp, "\n")] = 0; // Nacita sa string bez znaku \n
                if(counts % 6 == 1){
                    strcpy((*nazov_p)[j], sp);
                    j++;
                } if (counts % 6 == 2){
                    strcpy((*prednasatel_p)[k], sp);
                    k++;
                } if (counts % 6 == 3){
                    strcpy((*typPrednasky_p)[l], sp);
                    l++;
                } if (counts % 6 == 4){
                    strcpy((*casPrednasky_p)[m], sp);
                    m++;
                } if (counts % 6 == 5){
                    strcpy((*datumPrednasky_p)[n], sp);
                    n++;
                }
                if (counts % 6 == 0){
                }
                sp = strtok(NULL, "");  // Nastavenie konca riadku
            }
            
        }
        printf("Subor Nacitany\n");
        *flag = 1; // nastavenie flag na 1, indikujuce vytvorenie poli
    }

}

// Funkcia O vypise specialny vypis podla casu 
void funkcia_o(FILE** organized_stuff, char***nazov_p, char***prednasatel_p, char***typPrednasky_p, char***casPrednasky_p, char***datumPrednasky_p, int *flag, int *count_p ) {
    /*!!!WARNING!!! funkcia_o funguje len polovicne, zo suboru to nevie vypisat spravne a z poli vypise ale neusporiada podla casu !!!! */
    
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
                        strcpy(nazov, sp);
                    } if (count % 6 == 2){
                        strcpy(pred, sp);
                    } if (count % 6 == 3){
                        strcpy(typ, sp);
                    } if (count % 6 == 4){
                        strcpy(cas, sp);
                    } if (count % 6 == 5){
                        strcpy(datum_a, sp);
                    } if (count % 6 == 0){
                    }
                }
                if(strcmp(datum_a, datum) == 0){
                    printf("%s %2s %2s %2s\n", cas, typ, pred, nazov);
                }
            }
        }
    }
}

// Funkcia S vypise vypis podla datumu a typu prednasky
void funkcia_s(FILE** organized_stuff, char***nazov_p, char***prednasatel_p, char***typPrednasky_p, char***casPrednasky_p, char***datumPrednasky_p, int *flag, int *count_p ) {
    if(*flag == 0){
        printf("Polia nie su vytvorene\n");
    } else {
        char datum[64], typ[64]; 
        int flag_vstup = 0; // premena pre vstup  ci existuju zaznamy
        printf("Zadajte datum(rrrrmmdd) a typ: ");
        scanf("%s %s",datum,  typ);
        datum[strcspn(datum, "\n")] = 0; // odstranenie \n zo vstupu ak sa tam \n nachadza
        typ[strcspn(typ, "\n")] = 0; // odstranenie \n zo vstupu ak sa tam \n nachadza

        
        for(int c = 0; c < (*count_p / 6); c++){
            // Kontrola ci sa datum a typ prednasky nachadzaju v poliach
            if(strcmp((*datumPrednasky_p)[c], datum) == 0 && strcmp((*typPrednasky_p)[c], typ) == 0){
                printf("%s\t %s\t %s\n", (*casPrednasky_p)[c], (*prednasatel_p)[c], (*nazov_p)[c]);
                flag_vstup = 1;
            }
        }
        if(flag_vstup == 0){
            printf("Pre dany vstup neexistuju zaznamy\n");
        }
    }
}

// Funkcia P prida zaznam do dynamickych poli
void funkcia_p(FILE** organized_stuff, char***nazov_p, char***prednasatel_p, char***typPrednasky_p, char***casPrednasky_p, char***datumPrednasky_p, int *flag, int *count_p ) {
    if(*flag == 0){
        printf("Polia nie su vytvorene\n");
    } else {
        int indexovanie_poli;
        *count_p += 6;
        indexovanie_poli = (*count_p/6) - 1;
        // Realocovanie poli o novej velkosti
        *nazov_p = (char**)realloc(*nazov_p,(indexovanie_poli)*sizeof(char*)+sizeof(char *));
        *prednasatel_p = (char**)realloc(*prednasatel_p,(indexovanie_poli)*sizeof(char*)+sizeof(char *));
        *typPrednasky_p = (char**)realloc(*typPrednasky_p,(indexovanie_poli)*sizeof(char*)+sizeof(char *));
        *casPrednasky_p = (char**)realloc(*casPrednasky_p, (indexovanie_poli)*sizeof(char*)+ sizeof(char *));
        *datumPrednasky_p = (char**)realloc(*datumPrednasky_p, (indexovanie_poli)*sizeof(char*)+ sizeof(char *));
        (*nazov_p)[indexovanie_poli] = (char*)malloc(60 * sizeof(char));
        (*prednasatel_p)[indexovanie_poli] = (char*)malloc(60 * sizeof(char));
        (*typPrednasky_p)[indexovanie_poli] = (char*)malloc(60 * sizeof(char));
        (*casPrednasky_p)[indexovanie_poli] = (char*)malloc(60 * sizeof(char));
        (*datumPrednasky_p)[indexovanie_poli] = (char*)malloc(60 * sizeof(char));

        char st[150], tmp;
        for(int v = 1; v < 6; v++){
            printf("Zadajte sem: ");
            scanf("%c", &tmp); // cistenie buffera
            scanf("%[^\n]s", st); // citanie vstupu po \n
            st[strcspn(st, "\n")] = 0; // ak sa \n nacita tak sa odstrani
            // priradzovanie noveho prvku
            if(v % 6 == 1){
                strcpy((*nazov_p)[indexovanie_poli], st);
            } else if(v % 6 == 2){
                strcpy((*prednasatel_p)[indexovanie_poli], st);
            } else if(v % 6 == 3){
                strcpy((*typPrednasky_p)[indexovanie_poli], st);
            } else if(v % 6 == 4){

                strcpy((*casPrednasky_p)[indexovanie_poli], st);
                
            } else if(v % 6 == 5) {
                strcpy((*datumPrednasky_p)[indexovanie_poli], st);
            }
        }
    }
}

// Funkcia H vypise histogram 
void funkcia_h(FILE** organized_stuff, char***nazov_p, char***prednasatel_p, char***typPrednasky_p, char***casPrednasky_p, char***datumPrednasky_p, int *flag, int *count_p) {
    if(*flag == 0){
        printf("Polia nie su vytvorene\n");
    } else {
        // pocitadla pre jednotlive casy
        int up810 = 0,ud810 = 0,pp810 =0, pd810 =0, up1012=0, ud1012 = 0, pp1012 = 0, pd1012=0,up1214=0,ud1214=0,pp1214=0,pd1214=0,up1416=0,ud1416=0,pp1416=0,pd1416=0,up1618=0,ud1618=0,pp1618=0,pd1618=0,up1820=0,ud1820=0,pp1820=0,pd1820=0;
        int cas=0;
        
        // pocitanie jednotlivych casov
        for(int r=0; r< (*count_p/6); r++){
        if(strcmp((*typPrednasky_p)[r], "UP") == 0) {
            cas = atoi((*casPrednasky_p)[r]);
            if(800<=cas && cas<1000) {up810+=1;}
            else if(1000 <=cas && cas <1200) {up1012++;}
            else if(1200<=cas && cas<1400) {up1214++;}
            else if(1400<=cas && cas<1600) {up1416++;}
            else if(1600<=cas && cas<1800) {up1618++;}
            else if(1800<=cas && cas<2000) {up1820++;}
            }
        if(strcmp((*typPrednasky_p)[r], "UD") == 0) {
            cas = atoi((*casPrednasky_p)[r]);
            if(800<=cas && cas<1000) {ud810+=1;}
            else if(1000 <=cas && cas<1200) {ud1012++;}
            else if(1200<=cas && cas<1400) {ud1214++;}
            else if(1400<=cas && cas<1600) {ud1416++;}
            else if(1600<=cas && cas<1800) {ud1618++;}
            else if(1800<=cas && cas<2000) {ud1820++;}
            }
        if(strcmp((*typPrednasky_p)[r], "PP") == 0) {
            cas = atoi((*casPrednasky_p)[r]);
            if(800<=cas && cas<1000) {pp810+=1;}
            else if(1000 <=cas && cas<1200) {pp1012++;}
            else if(1200<=cas && cas<1400) {pp1214++;}
            else if(1400<=cas && cas<1600) {pp1416++;}
            else if(1600<=cas && cas<1800) {pp1618++;}
            else if(1800<=cas && cas<2000) {pp1820++;}
            }
        if(strcmp((*typPrednasky_p)[r], "PD") == 0) {
            cas = atoi((*casPrednasky_p)[r]);
            if(800<=cas && cas<1000) {pd810+=1;}
            else if(1000 <=cas && cas<1200) {pd1012++;}
            else if(1200<=cas && cas<1400) {pd1214++;}
            else if(1400<=cas && cas<1600) {pd1416++;}
            else if(1600<=cas && cas<1800) {pd1618++;}
            else if(1800<=cas && cas<2000) {pd1820++;}
            }
        }
        // vypisanie histogramu
        printf(" hodina\t\tUP\tUD\tPP\tPD\n");
        printf("08:00-09:59 :\t%d\t%d\t%d\t%d\n", up810, ud810, pp810, pd810);
        printf("10:00-11:59 :\t%d\t%d\t%d\t%d\n", up1012, ud1012, pp1012, pd1012);
        printf("12:00-13:59 :\t%d\t%d\t%d\t%d\n", up1214, ud1214,pp1214,pd1214);
        printf("14:00-15:59 :\t%d\t%d\t%d\t%d\n", up1416,ud1416,pp1416,pd1416);
        printf("16:00-17:59 :\t%d\t%d\t%d\t%d\n", up1618,ud1618,pp1618,pd1618);
        printf("18:00-19:59 :\t%d\t%d\t%d\t%d\n", up1820,ud1820,pp1820,pd1820);
        
    }
}

// Funkcia Z zmaze zaznam z poli
void funkcia_z(FILE** organized_stuff, char***nazov_p, char***prednasatel_p, char***typPrednasky_p, char***casPrednasky_p, char***datumPrednasky_p, int *flag, int *count_p){
    /* !!!WARNING!!! mazanie funguje len ak sa tam prvok nachadza raz inak sa to rozbije :(*/
    if(*flag == 0){
        printf("Polia nie su vytvorene\n");
    } else {
        char vstup[150], temp;
        int vymazanych = 0;
        int index = 0;
        printf("Zadajte nazov prispevku na vymazanie: ");
        scanf("%c", &temp);
        scanf("%[^\n]s", vstup);
        vstup[strcspn(vstup, "\n")] = 0;
        for(int z = 0; z < (*count_p/6); z++){
            // kontrolovanie ci sa tam vstup na vymazanie nachadza
            if(strcmp((*nazov_p)[z], vstup)== 0){
                // uvolenie samotneho prvku z pola
                printf("%s\n", (*nazov_p)[z]);
                vymazanych++;
                free((*nazov_p)[z]);
                free((*prednasatel_p)[z]);
                free((*typPrednasky_p)[z]);
                free((*casPrednasky_p)[z]);
                free((*datumPrednasky_p)[z]);
                *count_p -= 6;
                // posunutie zvysnych prvkov v poli
                for(int m = 0; m <= (*count_p/6); m++){
                    (*nazov_p)[m] = (*nazov_p)[m+1];
                    (*prednasatel_p)[m] = (*prednasatel_p)[m+1];
                    (*typPrednasky_p)[m] = (*typPrednasky_p)[m+1];
                    (*casPrednasky_p)[m] = (*casPrednasky_p)[m+1];
                    (*datumPrednasky_p)[m] = (*datumPrednasky_p)[m+1];
                }
                // zmensenie velkosti poli
                *nazov_p = (char**)realloc(*nazov_p,((*count_p/6))*sizeof(char*) + sizeof(char*));
                *prednasatel_p = (char**)realloc(*prednasatel_p,((*count_p/6))*sizeof(char*) + sizeof(char*));
                *typPrednasky_p = (char**)realloc(*typPrednasky_p,((*count_p/6))*sizeof(char*) + sizeof(char*));
                *casPrednasky_p = (char**)realloc(*casPrednasky_p,((*count_p/6))*sizeof(char*) + sizeof(char*));
                *datumPrednasky_p = (char**)realloc(*datumPrednasky_p,((*count_p/6))*sizeof(char*) + sizeof(char*));
            }
        }
        printf("Vymazalo sa: %d zaznamov!\n", vymazanych);
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
            funkcia_h(&organized_stuff, &nazov, &prednasatel, &typPrednasky, &casPrednasky, &datumPrednasky, flag_p, count_p);
        } else if (operative == 'z'){
            funkcia_z(&organized_stuff, &nazov, &prednasatel, &typPrednasky, &casPrednasky, &datumPrednasky, flag_p, count_p);
        } else if (operative == 'p') {
            funkcia_p(&organized_stuff, &nazov, &prednasatel, &typPrednasky, &casPrednasky, &datumPrednasky, flag_p, count_p);
        } else if (operative == 'k'){
            if(organized_stuff != NULL){ // ak je subor otvoreny tak ho zavrie
                fclose(organized_stuff);
            }

            if(flag == 1){ // ak boli polia vytvorene uvolnia sa
                for(int i = 0; i < (*count_p/6); i++){
                
                    free(nazov[i]);
                    free(prednasatel[i]);
                    free(typPrednasky[i]);
                    free(casPrednasky[i]);
                    free(datumPrednasky[i]);
                }
                // uvolenenie samotnych pointerov
                free(nazov);
                free(prednasatel);
                free(typPrednasky);
                free(casPrednasky);
                free(datumPrednasky);
            }      
            break; // koniec hlavnej LOOPY
        }
    }
    
    return 0;
}