#include <stdio.h>
#include "library.h"
#include "init.h"

int main() {
        system("cls");
        FILE *fp;

        empty();

        fp=fopen("alice.txt", "w");

        printf("Date   : ");
        timeStamp();
        printf("\nStatus : Idle");
        fflush(stdin);
        printf("\n\nPrivate Key : ");
        isDigit = scanf(" %d", &alice);
        if (isDigit != 1) {
                while(1) {
                        system("cls");
                        printf("Date   : ");
                        timeStamp();
                        printf("\nStatus : Idle");
                        fflush(stdin);
                        printf("\n\nPrivate Key : ");
                        isDigit = scanf(" %d", &alice);
                        if (isDigit == 1) {
                                break;
                        }
                }
        }
        putw(alice, fp);
        fclose(fp);

        while(1) {
                pairing();
                fp=fopen("bob.txt", "r");
                bob = getw(fp);
                fclose(fp);
                if (bob > 0) break;
        }

        fax();

        return 0;


}

void header(){
        printf("Date   : ");
        timeStamp();
        printf("\nStatus : Paired");
}

void enigma(){
        printf("\n\nEnter message : \n\n");
        gets(message);
        int msgLen = strlen(message);
        defKey(alice, (int) bob);

        int keyLen = strlen(proKey);
        char newKey[msgLen], newKeyExc[msgLen], encryptedMsg[msgLen], encryptedMsgExc[msgLen], decryptedMsg[msgLen];
        for(i = 0, j = 0; i < msgLen; ++i, ++j) {
                if(j == keyLen)
                        j = 0;

                newKey[i] = proKey[j];
        }

        newKey[i] = '\0';

        FILE *fp;
        fp = fopen("keyExc.txt", "w");
        fprintf(fp, "%s", newKey);
        fclose(fp);

        //encryption
        for(i = 0; i < msgLen; ++i)
                encryptedMsg[i] = (message[i] + newKey[i]);

        encryptedMsg[i] = '\0';

        fp = fopen("encryptedMsg.txt", "w");
        fprintf(fp, "%s", encryptedMsg);
        fclose(fp);

        //TODO use integer as well
        fp = fopen("encryptedSignal.txt", "w");
        sign = 1;
        putw(sign, fp);
        fclose(fp);

        //decryption
        fp = fopen("encryptedMsg.txt", "r");
        fscanf(fp, "%s", encryptedMsgExc);
        fclose(fp);

        fp = fopen("keyExc.txt", "r");
        fscanf(fp, "%s", newKeyExc);

        for(i = 0; i < msgLen; ++i)
                decryptedMsg[i] = (encryptedMsgExc[i] - newKeyExc[i]);

        decryptedMsg[i] = '\0';

        fp = fopen("decryptedMsg.txt", "w");
        fprintf(fp, "%s", decryptedMsg);
        fclose(fp);

        //printf("\nNew Generated Key: %s", newKey);
        system("cls");
        header();
        printf("\n\nEncrypted Message: \n\n%s", encryptedMsg);
        printf("\n\nMessages Sent!");
        printf("\nPress enter to continue  ");
        getchar();
        main();
        //printf("\nDecrypted Message: %s", decryptedMsg);
}

uint64_t defKey(uint64_t a, uint64_t b){
        p = 3;
        q = 17;
        sa = pow(p, a); ssa = sa % q;
        sb = pow(p, b); ssb = sb % q;

        ga = pow(ssb, a); gga = ga % q;
        gb = pow(ssa, b); ggb = gb % q;

        selectKey(gga);
}

void selectKey(int x){
        slen = sizeof(skey) / sizeof(skey[0]);
        srand(time(NULL));
        for (i=0; i<x; i++) {
                z = rand() % 26;
                proKey[i] = skey[z];
        }
}

void pairing(){
        system("cls");
        printf("\n");
        for (i = 1; i < 3; i++) {
                printf("\n");
        }
        printf("                                      Pairing!\n");
        printf("                                    ");
        for (l = 0; l < 11; l++) {
                printf(".");
                Sleep(500);
        }
        printf("\n\n\n\n");
}

void fax(){
        system("cls");
        header();

        FILE *fp;

        while(1) {
                fflush(stdin);
                fp=fopen("fax.txt", "r");
                detect = getw(fp);
                fclose(fp);

                if (detect > 0) {
                        menu = 'R';
                        system("cls");
                        header();
                        break;
                }
                else{
                        while(1) {
                                system("cls");
                                header();
                                printf("\n\n[G] Go\n[E] Exit\nChoose : ");
                                scanf(" %c", &menu);

                                fp=fopen("fax.txt", "r");
                                detect = getw(fp);
                                fclose(fp);

                                if (detect > 0) {
                                        menu = 'R';
                                        break;
                                }

                                if (menu == 'G') {
                                        //sending
                                        fp = fopen("fax.txt", "w");
                                        detect = 1;
                                        putw(detect, fp);
                                        fclose(fp);

                                        fflush(stdin);
                                        system("cls");
                                        header();
                                        enigma();
                                        break;
                                }
                                else if (menu == 'E') exit(0);

                        }
                        break;
                }
        }


        if (menu == 'R') {
                //receiving
                system("cls");
                header();
                int msgLen = strlen(message);
                char showEncrypted[msgLen], showDecrypted[1000];
                printf("\n\nMessage : \n\n");
                while(1) {
                        //TODO change sign  method using integer
                        fp=fopen("encryptedSignal.txt", "r");
                        sign = getw(fp);
                        fclose(fp);
                        if (sign > 0) break;
                }

                fp = fopen("encryptedMsg.txt", "r");
                fscanf(fp, "%s", showEncrypted);
                fclose(fp);
                printf("%s", showEncrypted);
                fflush(stdin);
                printf("\n\nPress enter to decrypt  ");
                getchar();
                yesno = 'y';
                if (yesno == 'y') {
                        fflush(stdin);
                        fp = fopen("decryptedMsg.txt", "r");
                        fscanf(fp, "%[^\n]s", showDecrypted);
                        fclose(fp);
                        system("cls");
                        header();
                        printf("\n\nMessage :\n\n%s", showDecrypted);

                        //TODO press enter to continue
                        printf("\n\nPress enter to continue  ");
                        getchar();
                        showEncrypted[0] = '\0';
                        main();
                }
        }
}

int callback(){
        menu = 'K';
        FILE *fp;
        fp = fopen("fax.txt", "w");
        fprintf(fp, "");
        fclose(fp);
        fax();
}

void empty(){
        FILE *fp;
        menu = 'O';
        fp = fopen("fax.txt", "w");
        fprintf(fp, "");
        fclose(fp);

        fp = fopen("encryptedMsg.txt", "w");
        fprintf(fp, "");
        fclose(fp);

        fp = fopen("decryptedMsg.txt", "w");
        fprintf(fp, "");
        fclose(fp);

        fp = fopen("alice.txt", "w");
        fprintf(fp, "");
        fclose(fp);

        fp = fopen("bob.txt", "w");
        fprintf(fp, "");
        fclose(fp);

        fp = fopen("keyExc.txt", "w");
        fprintf(fp, "");
        fclose(fp);

        fp = fopen("encryptedSignal.txt", "w");
        fprintf(fp, "");
        fclose(fp);
}
