
#include <stdlib.h>
#include <time.h>
#include <ctype.h> // toupper() için

// Sabitler
#define MAX_DURUM 100
#define MIN_DURUM 0
#define SIFRE 'Z' 

// Durum değişkenleri
int saglik = 100;       // Sağlık (0-100)
int enerji = 100;       // Enerji (0-100)
int yemek_sayisi = 5;   // Yemek sayısı
int siginak_var = 0;    // Sığınak bulunup bulunmadığı (0: Yok, 1: Var)

// Fonksiyon prototipleri
void envanter_goruntule();
void avlan();
void dinlen();
void siginak_ara();
void tehlike_serisi();
void sifreli_ilerleme();
void durumu_guncelle();
void temizle_giris_tamponu(); 

int main() {
    char komut; // Oyuncu komutu
    
    // Rastgele sayı üreticiyi başlat
    srand(time(NULL));

    printf("--- KARAKTER TABANLI HAYATTA KALMA SIMULATORU ---\n");
    printf("Hayatta kalma mucadelen basliyor! Tek karakterli komutlari kullan.\n");

    // Ana Komut Dinleme Döngüsü (DO-WHILE zorunlu)
    do {
        envanter_goruntule();

        printf("\nKOMUT GİR (A/S/R/E/F/P/X): ");

        if (scanf(" %c", &komut) != 1) { 
            temizle_giris_tamponu(); 
            printf("Hatali giriş algilandi, lütfen tek bir harf girin.\n");
            continue;
        }
        temizle_giris_tamponu(); 

        komut = toupper(komut);

        // Komut Sistemi (SWITCH-CASE zorunlu)
        switch (komut) {
            case 'A': // Avlan
                avlan();
                break;
            case 'S': // Sığınak ara
                siginak_ara();
                break;
            case 'R': // Dinlen
                dinlen();
                break;
            case 'E': // Envanteri görüntüle
                printf("Envanter güncel durumu gösterildi.\n");
                break;
            case 'F': // Tehlike serisi simülasyonu (FOR döngüsü)
                tehlike_serisi();
                break;
            case 'P': // Şifreli ilerleme (DO-WHILE döngüsü)
                sifreli_ilerleme();
                break;
            case 'X': // Çıkış
                printf("Simülasyondan cıkılıyor. Görüsmek üzere!\n");
                break;
            default:
                printf("Gecersiz komut. Lütfen A, S, R, E, F, P veya X girin.\n");
                break;
        }

        // Oyun Sonu Kontrolü
        if (saglik <= MIN_DURUM) {
            printf("\n!!! HAYATTA KALAMADIN. OYUN BİTTİ. !!!\n");
            komut = 'X'; 
        } else if (enerji <= MIN_DURUM && saglik < 30) {
            printf("\n!!! ENERJİN BİTTİ VE ÇOK ZAYİFSİN. OYUN BİTTİ. !!!\n");
            komut = 'X'; 
        }

    } while (komut != 'X'); // Oyuncu 'X' komutunu vermedikçe simülasyon devam eder

    return 0;
}

// --- Yardımcı Fonksiyonlar ---

void temizle_giris_tamponu() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void durumu_guncelle() {
    if (saglik > MAX_DURUM) saglik = MAX_DURUM;
    if (saglik < MIN_DURUM) saglik = MIN_DURUM;
    if (enerji > MAX_DURUM) enerji = MAX_DURUM;
    if (enerji < MIN_DURUM) enerji = MIN_DURUM;
    if (yemek_sayisi < 0) yemek_sayisi = 0; 
}

void envanter_goruntule() {
    printf("\n--- DURUM ---\n");
    printf("Saglik: %d/%d\n", saglik, MAX_DURUM);
    printf("Enerji: %d/%d\n", enerji, MAX_DURUM);
    printf("Yemek Sayisi: %d\n", yemek_sayisi);
    printf("Siginak Durumu: %s\n", siginak_var ? "Bulundu" : "Yok");
    printf("-------------\n");
}

// --- Komut Fonksiyonları ---

// A Komutu: Avlan (Enerji azalır, yemek kazanma ihtimali IF ile değerlendirilir)
void avlan() {
    if (enerji <= 15) {
        printf("cok yorgunsun, avlanmak için yeterli enerjin yok!\n");
        return;
    }

    int sans = rand() % 100;
    int enerji_kaybi = 10 + (rand() % 5); // Aritmetik Operatörler
    enerji -= enerji_kaybi; 
    durumu_guncelle();

    printf("Avlanmaya cıktın. %d Enerji kaybettin.\n", enerji_kaybi);

    // Yemek Kazanma/Yaralanma Şansı (Mantıksal Operatörler &&, || ve IF-ELSE)
    if (sans > 60 && enerji > 20) { // Enerji ve şans yüksekse (VE)
        yemek_sayisi += 2;
        printf("Basarılı bir av oldu! 2 Yemek kazandın.\n");
    }
    else if (sans < 15 || enerji < 10) { // Şans düşük VEYA enerji kritikse (VEYA)
        int hasar = rand() % 10 + 5;
        saglik -= hasar;
        printf("Av sırasında yaralandın. %d Saglık kaybettin!\n", hasar);
    }
    else {
        printf("Avlanma başarısız oldu, elin bos döndün.\n");
    }
    durumu_guncelle();
}

// S Komutu: Sığınak ara (Başarı ihtimali mantıksal operatörlerle değerlendirilir)
void siginak_ara() {
    if (siginak_var) {
        printf("Zaten bir sıgınagın var.\n");
        return;
    }
    if (enerji < 15) {
        printf("Sıgınak aramak için cok yorgunsun.\n");
        return;
    }
    enerji -= 15; // Aritmetik Operatör
    durumu_guncelle();

    int sans = rand() % 100;
    
    // IF-ELSE IF-ELSE yapılarıyla farklı koşullara göre değerlendirme
    if (enerji > 50 && saglik > 60 && sans > 40) { // Mükemmel sığınak
        siginak_var = 1;
        printf("Mükemmel bir sıgınak buldun!\n");
    }
    else if (saglik > 30 && sans > 60) { // Basit sığınak
        siginak_var = 1;
        printf("Basit ama is görecek bir sıgınak buldun.\n");
    }
    else { // Başarısız
        printf("Cevreyi aradın ama güvenli bir yer bulamadın.\n");
    }
    durumu_guncelle();
}

// R Komutu: Dinlen (Enerji artışı, sağlık kontrolü)
void dinlen() {
    // Dinlenme sırasında yemek tüketimi ve sağlık/enerji artışı (Aritmetik Operatörler)
    if (yemek_sayisi > 0) {
        yemek_sayisi--; 
        printf("Dinlenirken 1 yemek tükettin.\n");
    } else {
        printf("Yemegin kalmadıgı için ac dinleniyorsun!\n");
        saglik -= 5; // Aç kalma cezası
    }
    
    int enerji_artisi = 20 + (rand() % 10); 
    // Sığınak varsa daha çok iyileşme (Aritmetik işlem)
    int saglik_artisi = siginak_var ? 15 : 8; 

    enerji += enerji_artisi; 
    saglik += saglik_artisi; 

    durumu_guncelle(); 

    printf("Dinleniyorsun. Enerji +%d, Saglık +%d kazandin.\n", enerji_artisi, saglik_artisi);
}

// F Komutu: Bölgedeki tehlike serisi (FOR döngüsü zorunlu)
void tehlike_serisi() {
    int tehlike_sayisi = 5; 
    
    // Dev-C++ hatası düzeltildi: 'i' for döngüsünden önce tanımlandı.
    int i; 

    printf("\n!!! BÖLGEDE TEHLİKE SERİSİ BASLADİ (%d TUR) !!!\n", tehlike_sayisi);
    enerji -= 10; // Başlangıç yorgunluğu

    // FOR Döngüsü zorunlu
    for (i = 1; i <= tehlike_sayisi; i++) {
        int sans = rand() % 100;
        printf("--- Tur %d (Saglık: %d, Enerji: %d) ---\n", i, saglik, enerji);
        
        // Oyuncunun durumuna bağlı olarak koşullu sonuçlar
        if (siginak_var && sans > 30) {
            printf("Sıgınağın sayesinde tehlikeyi atlattın.\n");
            enerji -= 2; 
        } else if (sans < 20) {
            int hasar = rand() % 10 + 10;
            saglik -= hasar;
            printf("Ciddi bir tehlikeye yakalandİn! %d Saglık kaybettin.\n", hasar); 
        } else if (sans < 50) {
            enerji -= 15;
            printf("Tehlikeden kacarken yoruldun. %d Enerji kaybettin.\n", 15); 
        } else {
            printf("Zamaninda reaksiyon gösterdin ve tehlikeden kactın.\n"); 
        }

        durumu_guncelle();
        if (saglik <= MIN_DURUM) {
            printf("Sağlıgın tükendigi icin seri yarida kesildi.\n");
            break; 
        }
    }
    printf("!!! TEHLİKE SERİSİ SONA ERDİ !!!\n");
}

// P Komutu: Şifreli ilerleme (DO-WHILE doğrulama döngüsü zorunlu)
void sifreli_ilerleme() {
    char girilen_karakter;
    int deneme_sayisi = 0;

    printf("\n--- ŞİFRELİ GEÇİŞ NOKTASI ---\n");
    printf("Engeli aşmak için dogru karakteri (bir harf) bulmalısın.\n");
    
    // DO-WHILE Döngüsü zorunlu
    do {
        printf("Sifre Tahminin (Tek Harf Gir): ");
        if (scanf(" %c", &girilen_karakter) != 1) {
             temizle_giris_tamponu();
             printf("Gecersiz giris. Lütfen sadece bir harf girin.\n");
             continue; 
        }
        temizle_giris_tamponu();
        
        girilen_karakter = toupper(girilen_karakter);
        deneme_sayisi++;

        if (girilen_karakter != SIFRE) {
            printf("Yanlıs sifre. Tekrar dene.\n");
            if (deneme_sayisi >= 3) {
                enerji -= 5;
                printf("Cok fazla denedin, yoruldun. 5 Enerji kaybettin.\n");
                durumu_guncelle();
            }
        }
    } while (girilen_karakter != SIFRE); // Doğru karakteri girene kadar döngü devam

    printf("Tebrikler! Doğru sifreyi ('%c') buldun ve engeli aştın. +5 Saglık kazandın.\n", SIFRE);
    saglik += 5;
    durumu_guncelle();
}
