#include<stdio.h>
#include<ctype.h>
#include<stdbool.h>
#include<string.h>
#include"tokens.c"

//Global Tanımlamalar

//Degiskenler
char nextChar; //getChar fonksiyonu ile okunan bir sonraki char degerini bu degiskende tutacagiz
char lexeme [100]; //getChar fonksiyonu ile okunan mantikli char'lari lexeme degiskeninde tutacagiz
int charClass; //HARF,SAYI,EOF,BILINMEYEN degerlerini tutacak
int lexLenght; //okunan lexeme uzunlugunu tutmak icin degisken
int token; 
int nextToken; //okunan ifadelerin token isimlerini tutacak
bool hataVarmi = false;

// Fonksiyon Prototipleri
void addChar(); //lexeme dizisinin icine okunan simgeleri ekler
void getChar(); //nextChar cinsinin harf mi sayi mi yada baska bise mi oldugunu charClass degiskenine aktarir
void getNonBlank(); //bosluklari siler(atlar)
int lookup(char ch); //karakterler icin lookup fonksiyonu
int lex(); //lexical analiz fonksiyonu
bool dosyaAc();
void ekranaBas(int token);
void lookuprw(char lexeme[]);

FILE *in_fp; //yazilan kod textini okumak icin gerekli olan pointer

//lookup fonksiyonu dile ait olan operatorleri ve kelimeleri bulan fonksiyondur
int lookup(char ch)
{
	switch(ch)
	{
		case '(':
			addChar();
			nextToken = SOL_PARAN;
			break;
			
		case ')':
			addChar();
			nextToken = SAG_PARAN;
			break;
			
		case '[':
			addChar();
			nextToken = SOL_KOSELI;
			break;
			
		case ']':
			addChar();
			nextToken = SAG_KOSELI;
			break;
			
		case '/':
			addChar();
			nextToken = EGIK;
			break;
			
		case '\\':
			addChar();
			nextToken = TERS_EGIK;
			break;
			
		case '.':
			addChar();
			nextToken = NOKTA;
			break;
			
			
		case '<':
			addChar();
			getChar();
			
			if(nextChar == ':')
			{
				addChar();
				nextToken = BASLA;
			}
			else if(nextChar == '=')
			{
				addChar();
				nextToken = KUCUK_ESITTIR;
			}
			else
			{
				nextToken = KUCUKTUR;
			}
			break;
		case '>':
			addChar();
			getChar();
			
			if(nextChar == '=')
			{
				addChar();
				nextToken = BUYUK_ESITTIR;
			}
			else if('>')
			{
				addChar();
				nextToken = TIRE;
			}
			else
			{
				nextToken = BUYUKTUR;
			}
			break;
			
		case '=':
			addChar();
			getChar();
			
			if(nextChar == '=')
			{
				addChar();
				nextToken = ESITTIR;
			}
			break;
		case '!':
			addChar();
			getChar();
			
			if(nextChar == '=')
			{
				addChar();
				nextToken = ESIT_DEGILDIR;
			}
			break;
		case ':':
			addChar();
			getChar();
			
			if(nextChar == '>')
			{
				addChar();
				nextToken = BITIR;
			}
			break;	
		
		default:
			addChar();
			nextToken = EOF;
			hataVarmi = true;
			break;
	}
	
	return nextToken;
}

void lookuprw(char lexeme[])
{
	if(strcmp(lexeme, "ise") == 0)
	{
		nextToken = ISE;
	}
	else if(strcmp(lexeme, "yada") == 0)
	{
		nextToken = YADA;
	}
	else if(strcmp(lexeme, "degilse") == 0)
	{
		nextToken = DEGILSE;
	}
	else if(strcmp(lexeme, "boyleyken") == 0)
	{
		nextToken = BOYLEYKEN;
	}
	else if(strcmp(lexeme, "tam") == 0)
	{
		nextToken = TAM;
	}
	else if(strcmp(lexeme, "ondalik") == 0)
	{
		nextToken = ONDALIK;
	}
	else if(strcmp(lexeme, "simge") == 0)
	{
		nextToken = SIMGE;
	}
	else if(strcmp(lexeme, "mantik") == 0)
	{
		nextToken = MANTIK;
	}
	else if(strcmp(lexeme, "DOGRU") == 0)
	{
		nextToken = DOGRU;
	}
	else if(strcmp(lexeme, "YANLIS") == 0)
	{
		nextToken = YANLIS;
	}
	else if(strcmp(lexeme, "ve") == 0)
	{
		nextToken = VE;
	}
	else if(strcmp(lexeme, "topla") == 0)
	{
		nextToken = TOPLA;
	}
	else if(strcmp(lexeme, "cikar") == 0)
	{
		nextToken = CIKAR;
	}
	else if(strcmp(lexeme, "carp") == 0)
	{
		nextToken = CARP;
	}
	else if(strcmp(lexeme, "bol") == 0)
	{
		nextToken = BOL;
	}
	else if(strcmp(lexeme, "ata") == 0)
	{
		nextToken = ATAMA;
	}
	else
	{
		nextToken = TUTAC;								
	}
}

void addChar()
{
	if (lexLenght <= 98)
    {
		lexeme[lexLenght++] = nextChar;
		lexeme[lexLenght] = 0;
	}
	else
	{
		printf("Error - lexeme is too long \n");
	}
}

void getChar() 
{
	if((nextChar = getc(in_fp)) != EOF) 
	{
		if(isalpha(nextChar))
		{
			charClass = HARF;
		}
		else if(isdigit(nextChar))
		{
			charClass = SAYI;
		}
		else 
		{
			charClass = BILINMEYEN;
		}
	}	
	else
	{	
		charClass = EOF;
	}
}

void getNonBlank()
{
	while (isspace(nextChar))
	{
		getChar();
	}
}

int lex()
{
	lexLenght = 0;
	getNonBlank();
	bool kontrol = false;
	
	switch (charClass) 
	{
		case HARF:
			addChar();
			getChar();
					
			while(charClass == HARF || charClass == SAYI)
			{
				addChar();
				getChar();
			}
			
			lookuprw(lexeme);
			
			break;
			
		case SAYI:
			addChar();
			getChar();
			
			nextToken = TAM_SAYI;
			
			if(nextChar == ',' && kontrol == false)
			{
				addChar();
				getChar();
				
				if(nextChar == ',')
				{
					charClass = BILINMEYEN;
				}
				
				nextToken = ONDALIK_SAYI;
				kontrol = true;
			}		
			
			while(charClass == SAYI)
		    {				
				addChar();
				getChar();
				
				if(nextChar == ',' && kontrol == false)
				{
					addChar();
					getChar();
					
					if(nextChar == ',')
					{
						nextToken = EOF;
					}
					else
					{
						nextToken = ONDALIK_SAYI;
						kontrol = true;
					}					
				}									
			}
										
			break;
			
		case BILINMEYEN:
			lookup(nextChar);
			getChar();
			
			break;
			
		case EOF:
			nextToken = EOF;
			lexeme[0] = 'E';
			lexeme[1] = 'O';
			lexeme[2] = 'F';
			lexeme[3] = 0;
			break;
	}
	
	return nextToken;
}

void ekranaBas(int token)
{	
	switch(token)
    {
        case ISE:
	    	printf("ise komutu bulunamadi\n");
	    	hataVarmi = true;
	    	ekranaBas(95);
			break;

        case YADA:
			printf("yada komutu bulunamadi\n");
		    hataVarmi = true;
		    ekranaBas(95);
			break;

        case DEGILSE:
			printf("degilse komutu bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case BOYLEYKEN:
			printf("boyleyken komutu bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;
			
        case TUTAC:
			printf("Deger icin tutac bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case TAM_SAYI:
			printf("Tam sayi bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case ONDALIK_SAYI:
			printf("Ondalik sayı bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;
			
        case TOPLA:
			printf("topla komutu bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;  

        case CIKAR:
			printf("cikar komutu bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case CARP:
			printf("carp komutu bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case BOL:
			printf("bol komutu bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case ATAMA:
			printf("ata komutu bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case VE:
			printf("ve komutu bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case BASLA:
			printf("basla komutu bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break; 

        case BITIR:
			printf("bitir komutu bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case SOL_PARAN:
			printf("( simgesi bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case SAG_PARAN:
			printf(") simgesi bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break; 

        case SAG_KOSELI:
			printf("] simgesi bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case SOL_KOSELI:
			printf("[ simgesi bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break; 
        
        case EGIK:
			printf("/ simgesi bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case TERS_EGIK:
			printf("\\ simgesi bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case NOKTA:
			printf(". simgesi bulunamadi\n");
			ekranaBas(95);
			hataVarmi = true;
			break; 

        case VIRGUL:
			printf("Ondalik sayi bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case TIRE:
			printf("Tire simgesi bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case KUCUKTUR:
			printf("< simgesi bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case KUCUK_ESITTIR:
			printf("<= simgesi bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case BUYUKTUR:
			printf("'>' simgesi bulunamadi\n");
			hataVarmi = true;
			break;

        case BUYUK_ESITTIR:
			printf(">= simgesi bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case ESITTIR:
			printf("== simgesi bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case ESIT_DEGILDIR:
			printf("!= simgesi bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;
			
		case DOGRU:
            printf("DOGRU komutu bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;
			
		case YANLIS:
            printf("YANLIS komutu bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;

        case 90:
			printf("Degisken tipi bulunamadi\n");
			hataVarmi = true;
			ekranaBas(95);
			break;
			
		case 91:
			printf("Program basariyla derlendi.\n");
			break;
			
		case 92:
			printf("Program basariyla derlenemedi.\n");
			break;
			
		case 93:
			printf("Programda bilinmeyen karakter tespit edildi.\n");
			break;
			
		case 94:
			printf("Program lookup tablosuna uygun.\n");
			break;
			
		case 95:
			printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
			break;
        
        default:
			printf("Hata algilanamadi\n");
			break;
	}   
}

bool dosyaAc()
{			
	//TPL diliyle yazilmis kodu acar ve lexical analiz yapar
	if((in_fp = fopen("filename.txt", "r")) == NULL)
	{
		return false;
	}
	
	return true;
}
