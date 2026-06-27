# Pengenalan Reverse Engineering

## Tujuan Pembelajaran

Pada materi pertama ini, saya mempelajari konsep dasar Reverse Engineering, alasan mengapa bidang ini penting dalam dunia keamanan siber, serta tahapan umum yang dilakukan saat menganalisis sebuah program.

## Apa itu Reverse Engineering?

Reverse Engineering adalah proses mempelajari dan memahami cara kerja suatu program atau sistem tanpa melihat kode sumber aslinya. Proses ini dilakukan dengan menganalisis file binary yang sudah dikompilasi.

Dalam bidang keamanan siber, Reverse Engineering banyak digunakan untuk menganalisis malware, mencari kerentanan pada perangkat lunak, memahami mekanisme proteksi suatu aplikasi, serta mempelajari perilaku sebuah program.

## Mengapa Reverse Engineering Penting?

Reverse Engineering memiliki banyak manfaat, terutama dalam bidang keamanan informasi. Beberapa di antaranya adalah:

* Menganalisis malware untuk mengetahui perilaku dan dampaknya.
* Menemukan kerentanan pada aplikasi atau sistem.
* Membantu proses pengembangan exploit dalam lingkungan penelitian.
* Memahami mekanisme perlindungan perangkat lunak.
* Membangun kompatibilitas antar perangkat lunak atau sistem.

## Tahapan Umum Reverse Engineering

Dalam melakukan Reverse Engineering, terdapat beberapa tahapan yang biasanya dilakukan secara berurutan.

### 1. Reconnaissance

Tahap awal yang bertujuan untuk mengumpulkan informasi dasar mengenai file target, seperti jenis file, arsitektur yang digunakan, hash file, serta string yang tersimpan di dalam binary.

Tools yang umum digunakan:

* file
* strings
* readelf
* sha256sum

### 2. Static Analysis

Static analysis merupakan proses menganalisis binary tanpa menjalankannya. Pada tahap ini, analis akan mempelajari struktur program, fungsi-fungsi yang ada, serta alur eksekusi program.

Beberapa tools yang sering digunakan antara lain:

* Ghidra
* IDA Pro
* radare2
* objdump

### 3. Dynamic Analysis

Dynamic analysis dilakukan dengan menjalankan program dalam lingkungan yang terkontrol untuk mengamati perilakunya secara langsung.

Melalui teknik ini, analis dapat melihat aktivitas program, seperti akses file, komunikasi jaringan, maupun perubahan yang terjadi pada sistem.

Tools yang umum digunakan:

* GDB
* x64dbg
* strace
* ltrace
* Process Monitor

### 4. Pengujian Hipotesis

Setelah memperoleh hasil analisis, analis akan membuat dugaan mengenai fungsi atau perilaku tertentu, kemudian melakukan pengujian untuk memastikan apakah dugaan tersebut benar.

### 5. Dokumentasi

Seluruh proses analisis perlu didokumentasikan dengan baik agar hasilnya dapat dipelajari kembali dan mempermudah analisis lanjutan di masa mendatang.

## Perbedaan Static Analysis dan Dynamic Analysis

Static analysis dilakukan tanpa menjalankan program, sehingga lebih aman dan memungkinkan analis melihat keseluruhan kode program. Namun, teknik ini terkadang sulit digunakan ketika binary menggunakan teknik obfuscation atau packing.

Sementara itu, dynamic analysis dilakukan dengan menjalankan program secara langsung. Teknik ini memungkinkan analis melihat perilaku program saat runtime, tetapi memiliki risiko lebih tinggi sehingga harus dilakukan pada lingkungan yang terisolasi.

## Aspek Hukum dan Etika

Kegiatan Reverse Engineering harus dilakukan secara bertanggung jawab dan tetap memperhatikan aturan yang berlaku. Analisis sebaiknya hanya dilakukan pada sistem yang dimiliki sendiri, memiliki izin resmi, atau digunakan dalam konteks pembelajaran dan penelitian.

## Praktik: Analisis Awal Binary

Pada materi ini saya membuat sebuah program sederhana bernama `simple_auth` untuk mempelajari tahapan awal dalam Reverse Engineering.

Program ini berfungsi untuk melakukan validasi password sederhana.

### Source Code

Source code dan file binary dapat ditemukan pada folder `samples/`.

### Langkah Analisis

Untuk memperoleh informasi awal mengenai binary, saya menggunakan beberapa tools berikut:

```bash
file simple_auth
strings simple_auth
readelf -h simple_auth
ldd simple_auth
sha256sum simple_auth
```

### Hasil Analisis

#### Identifikasi Tipe File

Berdasarkan hasil perintah `file`, diketahui bahwa `simple_auth` merupakan file executable berformat ELF 64-bit untuk arsitektur x86-64. Binary ini menggunakan dynamic linking dan masih menyimpan simbol debugging (not stripped).

#### Analisis String

Melalui perintah `strings`, ditemukan beberapa string penting seperti:

* `Masukkan password:`
* `admin`
* `Akses Diterima`
* `Akses Ditolak`

Keberadaan string tersebut menunjukkan bahwa informasi sensitif terkadang dapat ditemukan tanpa perlu melakukan debugging atau disassembly.

#### Analisis Dependensi

Berdasarkan hasil `ldd`, program menggunakan library standar Linux seperti `libc.so.6` untuk menjalankan fungsi-fungsi dasar.

#### Analisis Struktur Binary

Dengan bantuan `readelf`, saya dapat melihat informasi tambahan mengenai struktur ELF, arsitektur yang digunakan, serta metadata binary.

### Kesimpulan

Tahap reconnaissance memberikan banyak informasi awal mengenai karakteristik sebuah binary. Informasi seperti tipe file, arsitektur, string penting, dan library yang digunakan sangat membantu sebelum memasuki tahap analisis yang lebih mendalam.


