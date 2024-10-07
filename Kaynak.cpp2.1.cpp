#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Hasta sýnýfý
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
    int kanama_derecesi; // Yeni özellik: Kanama derecesi
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

        // Her faktöre aðýrlýk verilerek öncelik puaný hesaplanýr
        if (hayati_tehlike) oncelik += 50.0;
        if (travma) oncelik += 30.0;
        if (solunum_problemleri) oncelik += 25.0;
        if (zehirlenme) oncelik += 20.0;
        if (enfeksiyon) oncelik += 15.0;
        if (psikiyatrik_kriz) oncelik += 10.0;
        if (kronik_hastalik) oncelik += 5.0;

        // Yaþa göre aðýrlýk eklenir
        if (yas > 70) oncelik += 20.0;
        else if (yas > 60) oncelik += 10.0;
        else if (yas < 18) oncelik += 15.0;

        // Kanama derecesi logaritmik olarak eklenir
        oncelik += log2(kanama_derecesi + 1) * 10.0;

        // Kombinasyon bonuslarý
        if (hayati_tehlike && solunum_problemleri) oncelik += 10.0;
        if (travma && solunum_problemleri) oncelik += 8.0;
        if (zehirlenme && enfeksiyon) oncelik += 6.0;

        return -oncelik; // Küçük olan daha yüksek öncelik anlamýna gelir
    }

    bool operator<(const Hasta& other) const {
        return this->oncelik < other.oncelik;
    }
};

// HastaneOtomasyonu sýnýfý
class HastaneOtomasyonu {
private:
    priority_queue<Hasta> kuyruk;

public:
    void hasta_ekle(const Hasta& hasta) {
        kuyruk.push(hasta);
        cout << hasta.ad_soyad << " adlý hasta kuyruða eklendi." << endl;
        kuyruk_goster();
    }

    void hasta_cikar() {
        if (!kuyruk.empty()) {
            Hasta en_yuksek_oncelikli_hasta = kuyruk.top();
            kuyruk.pop();
            cout << en_yuksek_oncelikli_hasta.ad_soyad << " adlý hasta tedavi için çýkarýldý." << endl;
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

        // Tüm hastalarý göstermek için geçici bir kuyruk kullanacaðýz
        priority_queue<Hasta> temp_kuyruk = kuyruk;
        cout << "Kuyruktaki hastalar:" << endl;
        while (!temp_kuyruk.empty()) {
            Hasta hasta = temp_kuyruk.top();
            temp_kuyruk.pop();
            cout << "Ad Soyad: " << hasta.ad_soyad << ", Yaþ: " << hasta.yas << ", Öncelik: " << -hasta.oncelik << endl;
        }
    }

    void cikis() {
        cout << "Otomasyondan çýkýlýyor." << endl;
        exit(0);
    }
};

// Ana fonksiyon
int main() {
    setlocale(LC_ALL, "Turkish");
    HastaneOtomasyonu otomasyon;
    int secim;
    Hasta hasta1("Ahmet Yýlmaz", 45, false, true, false, true, false, false, false, 3);
    otomasyon.hasta_ekle(hasta1);

    while (true) {

        cout << "\n1. Hasta Ekle\n";
        cout << "2. En Yüksek Öncelikli Hastayý Tedavi Et\n";
        cout << "3. ÇIKIÞ\n";
        cout << "Seçiminizi yapýn: ";
        cin >> secim;

        if (secim == 1) {
            string ad_soyad;
            int yas;
            int hayati_tehlike, travma, solunum_problemleri, zehirlenme, enfeksiyon, psikiyatrik_kriz, kronik_hastalik, kanama_derecesi;

            cout << "Ad Soyad: ";
            cin.ignore(); // Bu satýr, getline'dan önceki newline karakterini temizler
            getline(cin, ad_soyad);
            cout << "Yaþ: ";
            cin >> yas;
            cout << "Hayati Tehlike (1-Evet, 0-Hayýr): ";
            cin >> hayati_tehlike;
            while (hayati_tehlike != 0 && hayati_tehlike != 1) {
                cout << "Lütfen sadece 1 (Evet) veya 0 (Hayýr) deðerlerinden birini girin: ";
                cin >> hayati_tehlike;
            }

            cout << "Travma (1-Evet, 0-Hayýr): ";
            cin >> travma;
            while (travma != 0 && travma != 1) {
                cout << "Lütfen sadece 1 (Evet) veya 0 (Hayýr) deðerlerinden birini girin: ";
                cin >> travma;
            }

            cout << "Solunum Problemleri (1-Evet, 0-Hayýr): ";
            cin >> solunum_problemleri;
            while (solunum_problemleri != 0 && solunum_problemleri != 1) {
                cout << "Lütfen sadece 1 (Evet) veya 0 (Hayýr) deðerlerinden birini girin: ";
                cin >> solunum_problemleri;
            }

            cout << "Zehirlenme (1-Evet, 0-Hayýr): ";
            cin >> zehirlenme;
            while (zehirlenme != 0 && zehirlenme != 1) {
                cout << "Lütfen sadece 1 (Evet) veya 0 (Hayýr) deðerlerinden birini girin: ";
                cin >> zehirlenme;
            }

            cout << "Ciddi Enfeksiyon (1-Evet, 0-Hayýr): ";
            cin >> enfeksiyon;
            while (enfeksiyon != 0 && enfeksiyon != 1) {
                cout << "Lütfen sadece 1 (Evet) veya 0 (Hayýr) deðerlerinden birini girin: ";
                cin >> enfeksiyon;
            }

            cout << "Psikiyatrik Kriz (1-Evet, 0-Hayýr): ";
            cin >> psikiyatrik_kriz;
            while (psikiyatrik_kriz != 0 && psikiyatrik_kriz != 1) {
                cout << "Lütfen sadece 1 (Evet) veya 0 (Hayýr) deðerlerinden birini girin: ";
                cin >> psikiyatrik_kriz;
            }

            cout << "Kronik Hastalýk (1-Evet, 0-Hayýr): ";
            cin >> kronik_hastalik;
            while (kronik_hastalik != 0 && kronik_hastalik != 1) {
                cout << "Lütfen sadece 1 (Evet) veya 0 (Hayýr) deðerlerinden birini girin: ";
                cin >> kronik_hastalik;
            }

            cout << "Kanama Derecesi (0-9 arasý bir sayý): ";
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
            cout << "Geçersiz seçim. Lütfen tekrar deneyin." << endl;
        }
    }

    return 0;
}
