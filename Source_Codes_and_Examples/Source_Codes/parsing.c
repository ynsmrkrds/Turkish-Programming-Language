#include<stdio.h>
#include<ctype.h>
#include<stdbool.h>
#include<string.h>
#include"lex.c"

void stmtList();
void stmt();
void iseStmt();
void ise();
void yada();
void degilse();
void boyleykenStmt();
void logicExpr();
void expr();
void topla();
void cikar();
void carp();
void bol();
void aritmetik();
void ata();
void simgeDizi();
void tamSayiDizi();
void degiskenler();
void simge();
bool solParanVarmi();
bool sagParanVarmi();
bool baslaVarmi();
bool bitirVarmi();
bool veVarmi();

//<program> --> <: <stmtList> :>
void program()
{
	 getChar();
	
	 if(baslaVarmi())
	 {
		printf("Program basladi.\n");
		stmtList();
		
		if(nextToken == BITIR)
		{
			ekranaBas(95);
			printf("Program bitti.\n");
			
			lex();
						
			if(nextToken == EOF && hataVarmi == false)
			{
				ekranaBas(95);
				ekranaBas(91);
			}	
			else if(nextToken == EOF && hataVarmi == true)
			{
				ekranaBas(95);
				ekranaBas(92);
			}
		}
		else
		{
			ekranaBas(BITIR);
		}
	 }
	 else
	 {
		ekranaBas(BASLA);
	 }	 
}

//<stmtList> --> <stmt> {<stmtList>}
void stmtList()
{
	stmt();
	
	if(nextToken != BITIR)
	{
		stmtList();
	}
}

//<stmt> --> <iseStmt> | <boyleykenStmt> | <degiskenler> | <ata>
void stmt()
{
	lex();
	
	if(nextToken != BITIR)
	{
		switch(nextToken)
		{
			case ISE:
				ekranaBas(95);
				iseStmt();
				break;
				
			case BOYLEYKEN:
				ekranaBas(95);
				boyleykenStmt();
				break;
				
			case ATAMA:
				ekranaBas(95);
				ata();
				break;
			
			case TAM:
				ekranaBas(95);
				degiskenler();
				break;
				
			case ONDALIK:
				ekranaBas(95);
				degiskenler();
				break;
				
			case MANTIK:
				ekranaBas(95);
				degiskenler();
				break;
			
			case SIMGE:
				ekranaBas(95);
				degiskenler();
				break;
				
			default:
				ekranaBas(92);
				break;
		}
	}	
}

//<iseStmt> --> <ise> {<yada>}{<degilse>}
void iseStmt()
{	
	ise();
	
	lex();
	
	if(nextToken == YADA)
	{
		yada();
				
		if(nextToken == DEGILSE)
		{
			ekranaBas(95);
			degilse();
		}
	}
	else if(nextToken == DEGILSE)
	{
		degilse();	
	}
}

//<ise> --> ise(<logicExpr>) <: <stmtList> :>
void ise()
{	
	if(solParanVarmi())
	{
		logicExpr();
		
		if(sagParanVarmi())
		{			
			if(baslaVarmi())
			{
				stmtList();
				
				if(nextToken == BITIR)
				{
					ekranaBas(95);
					printf("ise fonksiyonu basariyla gerceklesti.\n");
				}	
				else
				{
					ekranaBas(BITIR);
				}			
			}
			else
			{
				ekranaBas(BASLA);
			}
		}
		else
		{
			ekranaBas(SAG_PARAN);
		}
	}
	else
	{
		ekranaBas(SOL_PARAN);
	}
}

//<yada> --> yada(<logicExpr>) <: <stmtList> :> {<yada>}
void yada()
{
	while(nextToken == YADA)
	{
		ekranaBas(95);
		if(solParanVarmi())
		{
			logicExpr();
			
			if(sagParanVarmi())
			{
				if(baslaVarmi())
				{
					stmtList();
					
					if(nextToken == BITIR)
					{
						ekranaBas(95);
						printf("yada fonksiyonu basariyla gerceklesti.\n");
						
						lex();
						yada();
					}	
					else
					{
						ekranaBas(BITIR);
					}
				}
				else
				{
					ekranaBas(BASLA);
				}
			}
			else
			{
				ekranaBas(SAG_PARAN);
			}
		}
		else
		{
			ekranaBas(SOL_PARAN);
		}
	}
}

//<degilse> --> degilse <: <stmtList> :>
void degilse()
{	
	if(baslaVarmi())
	{
		stmtList();
		
		if(bitirVarmi())
		{
			ekranaBas(95);
			printf("degilse fonksiyonu basariyla gerceklesti.\n");
		}
		else
		{
			ekranaBas(BITIR);
		}
	}
	else
	{
		ekranaBas(BASLA);
	}
}

//<boyleykenStmt> --> boyleyken(<logicExpr>) <: <stmtList> :>
void boyleykenStmt()
{
	if(solParanVarmi())
	{
		logicExpr();
		
		if(sagParanVarmi())
		{
			if(baslaVarmi())
			{
				stmtList();
				
				lex();
				
				if(nextToken == BITIR)
				{
					ekranaBas(95);
					printf("boyleyken fonksiyonu basariyla gerceklesi.\n");
				}
				else
				{
					ekranaBas(BITIR);
				}
			}
			else
			{
				ekranaBas(BASLA);
			}
		}
		else
		{
			ekranaBas(SAG_PARAN);
		}
	}
	else
	{
		ekranaBas(SOL_PARAN);
	}
}

//<logicExpr> --> <expr> {< | > | <= | >= | == | !=}+ <expr>
void logicExpr()
{
	lex();
	
	expr();
	
	lex();
	
	if(nextToken == KUCUKTUR || nextToken == BUYUKTUR || nextToken == KUCUK_ESITTIR || nextToken == BUYUK_ESITTIR || nextToken == ESITTIR || nextToken == ESIT_DEGILDIR)
	{
		ekranaBas(95);
		lex();
		
		expr();
	}
}

//<expr> --> <tutac> | <tamSayi> | <ondalikSayi> | <topla> | <cikar> | <carp> | <bol> | DOGRU | YANLIS 
void expr()
{	
	switch(nextToken)
	{
		case TUTAC:
			ekranaBas(95);
			break;
		
		case TAM_SAYI:
			ekranaBas(95);
			break;
			
		case ONDALIK_SAYI:
			ekranaBas(95);
			break;
		
		case TIRE:
			ekranaBas(95);
			simge();
			
		case DOGRU:
			ekranaBas(95);
			break;
			
		case YANLIS:
			ekranaBas(95);
			break;
			
		case TOPLA:
			ekranaBas(95);
			topla();
			break;
		
		case CIKAR:
			ekranaBas(95);
			cikar();
			break;
			
		case CARP:
			ekranaBas(95);
			carp();
			break;
			
		case BOL:
			ekranaBas(95);
			bol();
			break;
			
		default:
			hataVarmi = true;
			printf("Expression bulunamadi.\n");
	}
}

//<topla> --> topla(<expr> ve <expr>)
void topla()
{
	aritmetik();
}

//<cikar> --> cikar(<expr> ve <expr>)
void cikar()
{
	aritmetik();
}

//<carp> --> carp(<expr> ve <expr>)
void carp()
{
	aritmetik();
}

//<bol> --> bol(<expr> ve <expr>)
void bol()
{
	aritmetik();
}

void aritmetik()
{
	if(solParanVarmi())
	{
		lex();
		
		expr();
		
		lex();
		
		if(nextToken == VE)
		{
			ekranaBas(95);
			
			lex();
			
			expr();
			
			if(sagParanVarmi() == false)
			{
				ekranaBas(SAG_PARAN);
			}
		}
		else
		{
			ekranaBas(VE);
		}
	}
	else
	{
		ekranaBas(SOL_PARAN);
	}
}

//<ata> --> ata(<tutac> ve <expr> | [ <simgeDizi> ] | [ <tamSayiDizi> ]).
void ata()
{	
	if(solParanVarmi())
	{	
		lex();
		
		if(nextToken == TUTAC)
		{
			ekranaBas(95);
		
			if(veVarmi())
			{				
				lex();
				
				if(nextToken == SOL_KOSELI)
				{
					ekranaBas(95);
					lex();
					
					if(nextToken == TIRE)
					{
						ekranaBas(95);
						
						lex();
		
						if(nextToken == TUTAC || nextToken == TAM_SAYI)
						{
							ekranaBas(95);
				
							lex();
			
							if(nextToken == TIRE)
							{
								ekranaBas(95);
							}
							else
							{
								ekranaBas(TIRE);
							}		
						}
						else
						{
							printf("Simge bulunamadi.\n");
						}
						
						simgeDizi();
					}
					else if(nextToken == TAM_SAYI)
					{
						ekranaBas(95);
						
						tamSayiDizi();
					}
					else
					{
						printf("Dizinin icine uygun karakter gelmedi.\n");
					}
											
					if(nextToken == SAG_KOSELI)
					{
						ekranaBas(95);								
					}
					else
					{
						ekranaBas(SAG_KOSELI);
					}
				}
				else if(nextToken == TIRE)
				{
					ekranaBas(95);
					simge();
				}
				else
				{
					expr();
				}				
								
				if(sagParanVarmi())
				{
					lex();
					
					if(nextToken == NOKTA)
					{
						ekranaBas(95);
						printf("Atama islemi basariyla gerceklesti.\n");
					}
					else
					{
						ekranaBas(NOKTA);
					}
				}
				else
				{
					ekranaBas(SAG_PARAN);
				}
			}
			else
			{
				ekranaBas(VE);
			}
		}	
		else
		{
			ekranaBas(TUTAC);
		}
	}
	else
	{
		ekranaBas(SOL_PARAN);
	}
}

//<simgeDizi> --> >> <harfler> >> {ve <simgeDizi>}
void simgeDizi()
{	
	while(veVarmi())
	{
		lex();
		
		if(nextToken == TIRE)
		{
			ekranaBas(95);
			
			lex();
		
			if(nextToken == TUTAC || nextToken == TAM_SAYI)
			{
				ekranaBas(95);
			
				lex();
			
				if(nextToken == TIRE)
				{
					ekranaBas(95);
				}
				else
				{
					ekranaBas(TIRE);
				}		
			}
			else
			{
				printf("Simge bulunamadi.\n");
			}
		}
		else
		{
			ekranaBas(TIRE);
		}
	}
}

//<tamSayiDizi> --> <tamSayi> {ve <tamSayiDizi>}
void tamSayiDizi()
{		
	while(veVarmi())
	{
		lex();
		
		if(nextToken == TAM_SAYI)
		{
			ekranaBas(95);
		}
		else
		{
			ekranaBas(TAM_SAYI);
		}
	}
}

//<degiskenler> --> {tam | ondalik | simge | mantik}+ <tutac> {/ <tamSayi> \} .
void degiskenler()
{	
	lex();
	
	if(nextToken == TUTAC)
	{
		ekranaBas(95);
		
		lex();
			
		if(nextToken == EGIK)
		{
			ekranaBas(95);
			
			lex();
			
			if(nextToken == TAM_SAYI)
			{
				ekranaBas(95);
				
				lex();
					
				if(nextToken == TERS_EGIK)
				{
					ekranaBas(95);
					
					lex();
					
					if(nextToken == NOKTA)
					{
						ekranaBas(95);
						printf("Dizi olusturuldu.\n");
					}
					else
					{
						ekranaBas(NOKTA);
					}
				}
				else
				{
					ekranaBas(TERS_EGIK);
				}
			}
			else
			{
				ekranaBas(TAM_SAYI);
			}
		}	
		else if(nextToken == NOKTA)
		{
			ekranaBas(95);
			printf("Degisken olusturuldu.\n");
		}
		else
		{
			ekranaBas(NOKTA);
		}		
	}
	else
	{
		ekranaBas(TUTAC);
	}
}

void simge()
{
	lex();
	
	if(nextToken == TUTAC)
	{
		ekranaBas(95);
		
		lex();
		
		if(nextToken == TIRE)
		{
			ekranaBas(95);
		}
		else
		{
			ekranaBas(TIRE);
		}
	}
	else
	{
		ekranaBas(TUTAC);
	}
}

bool solParanVarmi()
{
	lex();
	
	if(nextToken == SOL_PARAN)
	{
		ekranaBas(95);
		return true;
	}
	
	return false;
}

bool sagParanVarmi()
{
	lex();
	
	if(nextToken == SAG_PARAN)
	{
		ekranaBas(95);
		return true;
	}
	
	return false;
}

bool baslaVarmi()
{
	lex();
	
	if(nextToken == BASLA)
	{
		ekranaBas(95);
		return true;
	}
	
	return false;
}

bool bitirVarmi()
{
	lex();
	
	if(nextToken == BITIR)
	{
		ekranaBas(95);
		return true;
	}
	
	return false;
}

bool veVarmi()
{
	lex();
	
	if(nextToken == VE)
	{
		ekranaBas(95);
		return true;
	}
	
	return false;
}

