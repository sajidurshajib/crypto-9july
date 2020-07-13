#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

void boot();
void file_write(char a[100], char b[100]);
void file_read(char c[100]);
char numToChar(int a);
int charToNum(char a);
int random(int a);
char randomChar();
void encryption(char str[1000]);
void decryption(char st[10000]);


char encrypted[10000]="\0";
char decrypted[10000]="\0";
char justText[10000]="\0";

int main()
{
    // Initializer for random number function
    srand(time(NULL));

    label:
    system("cls");
    boot();

    int op;

    printf("\n\n");
    printf("\t[.] Choose option: \n\n");
    printf("\t[1] Encryption \n");
    printf("\t[2] Decryption \n\n");
    printf("\t[Note] : For intput and output use /data/IO.txt file... \n\n");
    printf("\t#=> ");
    scanf("%d",&op);
    getchar();

    if(op==1)
    {
        printf("\n\t[=] PlainText: ");

        file_read("data/IO.txt");
        printf("%s",justText);

        encryption(justText);
        file_write("data/IO.txt",encrypted);

        printf("\n\n");
        printf("\t[#] Encrypted: ");

        printf("%s",encrypted);

    }
    else if(op==2)
    {
        printf("\n\t[#] EncryptedText: ");

        file_read("data/IO.txt");
        printf("%s",justText);

        decryption(justText);
        file_write("data/IO.txt",decrypted);

        printf("\n\n");
        printf("\t[#] Decrypted: ");

        printf("%s",decrypted);
    }


    printf("\n\n\t[R] For restart, insert just 1: ");
    int r;
    scanf("%d",&r);
    if(r==1)
        goto label;
    printf("\n\n");
    return 0;
}



void file_write(char a[10000], char b[10000])
{
    FILE *fw;
    fw = fopen(a,"w");
    fprintf(fw,b);
    fclose(fw);
}

void file_read(char c[10000])
{
    FILE *fr;
    fr = fopen(c,"r");
    char st[10000];
    fgets(st,10000,fr);
    strcpy(justText,st);
    //printf("%s",st);
    fclose(fr);
}

void boot()
{
    //Banner
    printf("\n");
    printf("\t+-------------------------------------------+\n");
    printf("\t|                  kryptos                  |\n");
    printf("\t|       Developed by Sajidur Rahman         |\n");
    printf("\t+-------------------------------------------+\n");

    if(!opendir("data"))
    {
        system("mkdir data");

    }

    if(access("data/IO.txt",F_OK )==-1 )
    {
        file_write("data/IO.txt","");
    }

}



// Number to Character converter
char numToChar(int a)
{
    char c = a;
    return c;
}

// Char to Number converter
int charToNum(char a)
{
    int n = a;
    return n;
}

// Random number generator with range
// 0 to < range
int random(int a)
{
    int r = rand();
    if(r>a)
        r = r%a;
    return r;
}

// Random character maker
char randomChar()
{
    char c;
    int r = random(130);
    if(r<33)
        r=r+33;
    c=numToChar(r);
    return c;
}


//Encryption
void encryption(char str[1000])
{
    //Final string
    char strfinal[10000]="\0";//Null string needed
    int finalCount=0;
    //............

    int length = strlen(str);
    int i;
    //Work with every character
    for(i=0; i<length; i++)
    {
        char publicKey = randomChar();
        int numPublicKey = (publicKey%4)+1; //1,2,3,4

        int front=numPublicKey-1;
        int rear=4-numPublicKey;

        // Public key
        //printf("%c",publicKey);
        strfinal[finalCount]=publicKey;
        finalCount++;
        // Fake front key
        int j;
        for(j=1; j<=front; j++)
        {
            //printf("%c",randomChar());
            strfinal[finalCount]=randomChar();
            finalCount++;
        }
        //Main key
        //printf("%c",str[i]+numPublicKey);
        char mainKey = numToChar(str[i]+numPublicKey);
        strfinal[finalCount]=mainKey;
        finalCount++;
        // Fake rear key
        for(j=1; j<=rear; j++)
        {
            //printf("%c",randomChar());
            strfinal[finalCount]=randomChar();
            finalCount++;
        }

    }
    //puts(strfinal);
    strcpy(encrypted,strfinal);
}


// Decryption
void decryption(char str[10000])
{
    char mainStr[1000]="\0"; //Without null string get some problems.
    int mainStrCount=0;

    int length = strlen(str);
    int charCount = 0;

    while(charCount < length)
    {
        int publicKey = (charToNum(str[charCount]) % 4)+1;
        int mainKeyPos = charCount + publicKey;

        char mainKey = charToNum(str[mainKeyPos])-publicKey;
        mainStr[mainStrCount]= mainKey;
        mainStrCount++;
        charCount = charCount+5;

    }

    //puts(mainStr);
    strcpy(decrypted,mainStr);

}
