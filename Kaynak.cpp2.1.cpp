#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Hasta s�n�f�
class Hasta {
public:
    string ad_soyad;
    int yas;
    bool hayati_tehlike;
    bool travma;
    bool solunum_problemleri;
    bool zehirlenme;
    bool enfeksiyon;
    bool psikiyatrik_kriz;
    bool kronik_hastalik;
    int kanama_derecesi; // Yeni �zellik: Kanama derecesi
    double oncelik;

    Hasta(string ad_soyad, int yas, bool hayati_tehlike, bool travma, bool solunum_problemleri, bool zehirlenme, bool enfeksiyon, bool psikiyatrik_kriz, bool kronik_hastalik, int kanama_derecesi) {
        this->ad_soyad = ad_soyad;
        this->yas = yas;
        this->hayati_tehlike = hayati_tehlike;
        this->travma = travma;
        this->solunum_problemleri = solunum_problemleri;
        this->zehirlenme = zehirlenme;
        this->enfeksiyon = enfeksiyon;
        this->psikiyatrik_kriz = psikiyatrik_kriz;
        this->kronik_hastalik = kronik_hastalik;
        this->kanama_derecesi = kanama_derecesi;
        this->oncelik = hesapla_oncelik();
    }

    double hesapla_oncelik() const {
        double oncelik = 0.0;

        // Her fakt�re a��rl�k verilerek �ncelik puan� hesaplan�r
        if (hayati_tehlike) oncelik += 50.0;
        if (travma) oncelik += 30.0;
        if (solunum_problemleri) oncelik += 25.0;
        if (zehirlenme) oncelik += 20.0;
        if (enfeksiyon) oncelik += 15.0;
        if (psikiyatrik_kriz) oncelik += 10.0;
        if (kronik_hastalik) oncelik += 5.0;

        // Ya�a g�re a��rl�k eklenir
        if (yas > 70) oncelik += 20.0;
        else if (yas > 60) oncelik += 10.0;
        else if (yas < 18) oncelik += 15.0;

        // Kanama derecesi logaritmik olarak eklenir
        oncelik += log2(kanama_derecesi + 1) * 10.0;

        // Kombinasyon bonuslar�
        if (hayati_tehlike && solunum_problemleri) oncelik += 10.0;
        if (travma && solunum_problemleri) oncelik += 8.0;
        if (zehirlenme && enfeksiyon) oncelik += 6.0;

        return -oncelik; // K���k olan daha y�ksek �ncelik anlam�na gelir
    }

    bool operator<(const Hasta& other) const {
        return this->oncelik < other.oncelik;
    }
};

// HastaneOtomasyonu s�n�f�
class HastaneOtomasyonu {
private:
    priority_queue<Hasta> kuyruk;

public:
    void hasta_ekle(const Hasta& hasta) {
        kuyruk.push(hasta);
        cout << hasta.ad_soyad << " adl� hasta kuyru�a eklendi." << endl;
        kuyruk_goster();
    }

    void hasta_cikar() {
        if (!kuyruk.empty()) {
            Hasta en_yuksek_oncelikli_hasta = kuyruk.top();
            kuyruk.pop();
            cout << en_yuksek_oncelikli_hasta.ad_soyad << " adl� hasta tedavi i�in ��kar�ld�." << endl;
            kuyruk_goster();
        }
        else {
            cout << "Kuyrukta hasta yok." << endl;
        }
    }

    void kuyruk_goster() {
        if (kuyruk.empty()) {
            cout << "Kuyrukta hasta yok." << endl;
            return;
        }

        // T�m hastalar� g�stermek i�in ge�ici bir kuyruk kullanaca��z
        priority_queue<Hasta> temp_kuyruk = kuyruk;
        cout << "Kuyruktaki hastalar:" << endl;
        while (!temp_kuyruk.empty()) {
            Hasta hasta = temp_kuyruk.top();
            temp_kuyruk.pop();
            cout << "Ad Soyad: " << hasta.ad_soyad << ", Ya�: " << hasta.yas << ", �ncelik: " << -hasta.oncelik << endl;
        }
    }

    void cikis() {
        cout << "Otomasyondan ��k�l�yor." << endl;
        exit(0);
    }
};

// Ana fonksiyon
int main() {
    setlocale(LC_ALL, "Turkish");
    HastaneOtomasyonu otomasyon;
    int secim;
    Hasta hasta1("Ahmet Y�lmaz", 45, false, true, false, true, false, false, false, 3);
    otomasyon.hasta_ekle(hasta1);

    while (true) {

        cout << "\n1. Hasta Ekle\n";
        cout << "2. En Y�ksek �ncelikli Hastay� Tedavi Et\n";
        cout << "3. �IKI�\n";
        cout << "Se�iminizi yap�n: ";
        cin >> secim;

        if (secim == 1) {
            string ad_soyad;
            int yas;
            int hayati_tehlike, travma, solunum_problemleri, zehirlenme, enfeksiyon, psikiyatrik_kriz, kronik_hastalik, kanama_derecesi;

            cout << "Ad Soyad: ";
            cin.ignore(); // Bu sat�r, getline'dan �nceki newline karakterini temizler
            getline(cin, ad_soyad);
            cout << "Ya�: ";
            cin >> yas;
            cout << "Hayati Tehlike (1-Evet, 0-Hay�r): ";
            cin >> hayati_tehlike;
            while (hayati_tehlike != 0 && hayati_tehlike != 1) {
                cout << "L�tfen sadece 1 (Evet) veya 0 (Hay�r) de�erlerinden birini girin: ";
                cin >> hayati_tehlike;
            }

            cout << "Travma (1-Evet, 0-Hay�r): ";
            cin >> travma;
            while (travma != 0 && travma != 1) {
                cout << "L�tfen sadece 1 (Evet) veya 0 (Hay�r) de�erlerinden birini girin: ";
                cin >> travma;
            }

            cout << "Solunum Problemleri (1-Evet, 0-Hay�r): ";
            cin >> solunum_problemleri;
            while (solunum_problemleri != 0 && solunum_problemleri != 1) {
                cout << "L�tfen sadece 1 (Evet) veya 0 (Hay�r) de�erlerinden birini girin: ";
                cin >> solunum_problemleri;
            }

            cout << "Zehirlenme (1-Evet, 0-Hay�r): ";
            cin >> zehirlenme;
            while (zehirlenme != 0 && zehirlenme != 1) {
                cout << "L�tfen sadece 1 (Evet) veya 0 (Hay�r) de�erlerinden birini girin: ";
                cin >> zehirlenme;
            }

            cout << "Ciddi Enfeksiyon (1-Evet, 0-Hay�r): ";
            cin >> enfeksiyon;
            while (enfeksiyon != 0 && enfeksiyon != 1) {
                cout << "L�tfen sadece 1 (Evet) veya 0 (Hay�r) de�erlerinden birini girin: ";
                cin >> enfeksiyon;
            }

            cout << "Psikiyatrik Kriz (1-Evet, 0-Hay�r): ";
            cin >> psikiyatrik_kriz;
            while (psikiyatrik_kriz != 0 && psikiyatrik_kriz != 1) {
                cout << "L�tfen sadece 1 (Evet) veya 0 (Hay�r) de�erlerinden birini girin: ";
                cin >> psikiyatrik_kriz;
            }

            cout << "Kronik Hastal�k (1-Evet, 0-Hay�r): ";
            cin >> kronik_hastalik;
            while (kronik_hastalik != 0 && kronik_hastalik != 1) {
                cout << "L�tfen sadece 1 (Evet) veya 0 (Hay�r) de�erlerinden birini girin: ";
                cin >> kronik_hastalik;
            }

            cout << "Kanama Derecesi (0-9 aras� bir say�): ";
            cin >> kanama_derecesi;

            Hasta yeni_hasta(ad_soyad, yas, hayati_tehlike, travma, solunum_problemleri, zehirlenme, enfeksiyon, psikiyatrik_kriz, kronik_hastalik, kanama_derecesi);
            otomasyon.hasta_ekle(yeni_hasta);

        }
        else if (secim == 2) {
            otomasyon.hasta_cikar();
        }
        else if (secim == 3) {
            otomasyon.cikis();
        }
        else {
            cout << "Ge�ersiz se�im. L�tfen tekrar deneyin." << endl;
        }
    }

    return 0;
}
