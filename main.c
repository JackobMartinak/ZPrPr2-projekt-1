#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* funkcia_v(FILE* organized_stuff){
    if(organized_stuff != NULL){
                // TODO: Zistit ci uz boli vytvorene dynamicke polia
                // Ak ano tak -> Vypisat jednotlive zaznamy z poli
                // Inak Vypisat jednotlive zaznamy zo suboru
            } else {
                    organized_stuff = fopen("./OrganizacnePodujatia.txt", "r");
                    printf("SUBOR OTVORENY!\n");
                    return organized_stuff;
                if(organized_stuff == NULL) {
                    printf("Neotvoreny Subor\n");
                } else {
                    // TODO: Zistit ci uz boli vytvorene dynamicke polia
                    // Ak ano tak -> Vypisat jednotlive zaznamy z poli
                    // Inak Vypisat jednotlive zaznamy zo suboru
                }
            }
}

void funkcia_n(FILE* organized_stuff){
     // TODO: Spocita pocet zaznamov v subore
            char riadok[1024];
            char *sp, *nazovPrednasky, *prednasatel, *typPrednasky, *casPrednasky, *datumPrednasky;
            int count = 0;
            if(organized_stuff == NULL){
                printf("Neotvoreny subor");
            } else {
                while (fgets(riadok, 1024, organized_stuff) != NULL)
                {
                    sp = strtok(riadok, "");
                    while(sp != NULL){
                        
                        sp = strtok(NULL, "");
                    }
                    count++;
                    
                }
                nazovPrednasky = (char*)malloc((count/ 5) * sizeof(char) + 1);
                prednasatel = (char*)malloc((count/ 5) * sizeof(char) +1);
                typPrednasky = (char*)malloc((count/ 5) * sizeof(char)+1);
                casPrednasky = (char*)malloc((count/ 5) * sizeof(char)+1);
                datumPrednasky = (char*)malloc((count/ 5) * sizeof(char)+1);
                
                printf("pocet riadkov: %d \n", count / 5);
            }
            // Dynamicky vytvori polia pre jednotlive polozky
            // 1. Nazov prispevku 2. mena autorov 3. Typ prezentovania
            // 4. Cas prezentovania 5. Datum prezentacie
            // Zapisu sa v takom poradi ako su v subore
            // Ak polia u6 boli predtym vytvorene tak sa dealokuju a vytvoria nanovo
            // Po uspesnom nacitani hodnot sa vypise "Nacitane data.
            // Ak subor este nie je otvoreny, vypise spravu "Neotvoreny subor"

}

int main(){
    
        FILE *organized_stuff = NULL;
        char operative;

    while(1){
        scanf("%c", &operative);
        if(operative == 'v'){
            printf("Prikaz V");
            organized_stuff = funkcia_v(organized_stuff);
            continue;
        } else if(operative == 'o'){
            // TODO: nacita datum(rrrrmmdd) a vypise zozname prispevkov s rovnakym
            // Datumom zoradene podla casoveho harmonogramu a typu prezentovania, kde
            // UP a UD bude predstavovat jeden zoznam a PP a PD bude predstavovat druhy
            // casovo zoradeny zoznam/ Tento prikaz vypise na obrazovku aj v pripade
            // Ak prikaz n este nebol aktivovany, ale prikaz v ano (iba v ma moznost otvorit subor)
        } else if(operative == 'n'){
            // printf("n");
            funkcia_n(organized_stuff);
        } else if (operative == 's'){
            // TODO: Nacita datum(rrrrmmdd) a typ prezentovania vo formate
            // {PD, UD, PP, UP}, vypise polozky "Cas prezentovania", "Prezenter"
            // a "Nazov prispevku" z dynamickych poli
            // Ak nie su vytvorene vypise sa "Polia nie su vytvorene\n"
            // AK pre dany vstup neexistuje zaznam vypise sa "Pre dany vystup neexistuju zaznamy"
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
            // TODO: Dealokuju sa vsetky polia, ak boli vytvorene
            // Ak je subor otvoreny, tak sa zavrie a nasledne 
            // Program skonci
            if(organized_stuff != NULL){
                fclose(organized_stuff);
            }
            break;
        }
    }
    
    return 0;
}