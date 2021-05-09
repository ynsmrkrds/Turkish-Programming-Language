// Karakter Siniflari
#define HARF 0
#define SAYI 1
#define BILINMEYEN 99

//Token Kodlari
#define ISE 11 //if
#define YADA 12 //else if
#define DEGILSE 13	//else
#define BOYLEYKEN 14 //while
#define TAM 21 //int
#define ONDALIK 22 //float
#define SIMGE 23 //char
#define MANTIK 24 //boolean
#define TUTAC 25 //degisken, sabit isimleri vs 
#define TAM_SAYI 26//10,47,98 gibi
#define ONDALIK_SAYI 27//4,4 , 78,78 gibi
#define DOGRU 28 //true
#define YANLIS 29 //false
#define TOPLA 31 //iki degeri toplama fonksiyonu
#define CIKAR 32 //iki degeri cikarma fonksiyonu
#define CARP 33 //iki degeri carpma fonksiyonu
#define BOL 34 //iki degeri bolme fonksiyonu
#define VE 38 //parametreleri birbirinden ayırmak icin kullanılır 
#define ATAMA 39 //degiskene atama yaparken -> kullanilir
#define BASLA 41 //TPL dilinde kod yazmaya baslamak icin <: kullanılır
#define BITIR 42 //TPL dilinde kod yazılan kodu bitirmek icin :> kullanılır
#define SOL_PARAN 51 // ( isareti parametre icin kullanılır
#define SAG_PARAN 52 // ) isareti parametre icin kullanılır
#define SOL_KOSELI 53 // [ dizilerin baslangıctaki degerlerini girmek icin kullanilir
#define SAG_KOSELI 54 // ] dizilerin baslangıctaki degerlerini girmek icin kullanilir
#define EGIK 55 // / dizi icin boyut belirtirken kullanılır
#define TERS_EGIK 56 // \ dizi icin boyut belirtirken kullanılır
#define NOKTA 57 //TPL dilinde satır bitirirken . kullanılır
#define VIRGUL 58 //ondalik sayilar icin virgul kullanılır
#define TIRE 59 //char icin ilk deger verme
#define KUCUKTUR 61 //mantiksal islenmelerde < isareti
#define KUCUK_ESITTIR 62 //mantiksal islenmelerde <= isareti
#define BUYUKTUR 63 //mantiksal islenmelerde > isareti
#define BUYUK_ESITTIR 64 //mantiksal islenmelerde >= isareti
#define ESITTIR 65 //mantiksal islenmelerde == isareti
#define ESIT_DEGILDIR 66 //mantiksal islenmelerde != isareti
