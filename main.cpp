#include <Arduino.h>

// 1. Deklarasi Konstanta Pin
const int PIN_BUZZER = 7;
const int PIN_HIJAU  = 8;   // Jarak >30 cm (Kosong)
const int PIN_KUNING = 9;   // Jarak 10-30 cm (Hampir Penuh)
const int PIN_MERAH  = 10;  // Jarak <10 cm (Penuh)

// Fungsi untuk mematikan semua indikator
void semuaMati() {
  digitalWrite(PIN_HIJAU, LOW);
  digitalWrite(PIN_KUNING, LOW);
  digitalWrite(PIN_MERAH, LOW);
  noTone(PIN_BUZZER);
}

// Fungsi evaluasi jarak sampah dengan percabangan If-Else
void periksaJarakSampah(int jarak) {
  semuaMati(); // Bersihkan indikator sebelumnya

  Serial.print("Jarak terdeteksi: ");
  Serial.print(jarak);
  Serial.print(" cm -> ");

  // Logika Percabangan If-Else
  if (jarak > 30) {
    // Jarak Makin Jauh (>30 cm): Sampah masih sedikit / Kosong
    Serial.println("Sampah Kosong (LED Hijau Menyala)");
    digitalWrite(PIN_HIJAU, HIGH);
  } 
  else if (jarak >= 10 && jarak <= 30) {
    // Jarak Sedang (10-30 cm): Sampah mulai terisi / Hampir Penuh
    Serial.println("Sampah Hampir Penuh (LED Kuning Menyala)");
    digitalWrite(PIN_KUNING, HIGH);
  } 
  else {
    // Jarak Dekat (<10 cm): Sampah sudah tinggi / Penuh
    Serial.println("SAMPAH PENUH! (LED Merah & Buzzer Aktif)");
    digitalWrite(PIN_MERAH, HIGH);
    tone(PIN_BUZZER, 1000); // Buzzer berbunyi
  }
}

void setup() {
  // Atur pin indikator sebagai OUTPUT
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_HIJAU, OUTPUT);
  pinMode(PIN_KUNING, OUTPUT);
  pinMode(PIN_MERAH, OUTPUT);

  // Inisialisasi Serial Monitor
  Serial.begin(9600);
  Serial.println("==========================================");
  Serial.println("  SIMULASI SENSOR JARAK TEMPAT SAMPAH     ");
  Serial.println("  Ketik angka jarak (cm) di Serial Monitor");
  Serial.println("  Contoh: 35 (Hijau), 20 (Kuning), 5 (Merah)");
  Serial.println("==========================================");
}

void loop() {
  // Mengecek apakah ada input angka dari pengguna lewat Serial Monitor
  if (Serial.available() > 0) {
    int jarakInput = Serial.parseInt(); // Membaca angka yang diketik
    periksaJarakSampah(jarakInput);     // Evaluasi nilainya
  }
}