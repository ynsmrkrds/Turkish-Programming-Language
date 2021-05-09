#include<stdlib.h>
#include<stdio.h>
#include"parsing.c"

/*------------------------------------------*/
//main fonksiyonu
int main()
{	
	//TPL diliyle yazilmis kodu acar ve lexical analiz yapar
	if(dosyaAc() == false)
	{
		printf("HATA : dosya bulunamadi.\n");
	}
	else 
	{
		getChar();
		do 
		{
			lex();
			if(nextToken == EOF && hataVarmi == false)
			{
				ekranaBas(94);
			}
			else if(hataVarmi == true)
			{
				ekranaBas(93);
				ekranaBas(95);
			}
		} 
		while(nextToken != EOF);
				
		if(hataVarmi == false)
		{
			dosyaAc();

			program();
		}
	}
	
	return 0;
}
