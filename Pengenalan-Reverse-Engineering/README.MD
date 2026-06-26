# Latihan: Analisis Awal Binary

## Target

Pada latihan ini saya memilih binary `/usr/bin/whoami` sebagai objek analisis.

## Tujuan

Melakukan pengumpulan informasi dasar terhadap sebuah binary sebelum memasuki tahap analisis yang lebih mendalam.

## Tools yang Digunakan

* file
* strings
* readelf
* sha256sum
* ldd

## Langkah Analisis

### Mengidentifikasi tipe file

```bash
file /usr/bin/whoami
```

### Menampilkan string yang terdapat pada binary

```bash
strings /usr/bin/whoami | head -20
```

### Melihat informasi ELF Header

```bash
readelf -h /usr/bin/whoami
```

### Mengidentifikasi library yang digunakan

```bash
ldd /usr/bin/whoami
```

### Menghasilkan hash file

```bash
sha256sum /usr/bin/whoami
```

## Temuan

* Binary menggunakan format ELF.
* Binary ditujukan untuk arsitektur x86-64.
* Binary menggunakan beberapa shared library sistem.
* Ditemukan beberapa string yang berkaitan dengan penggunaan program.

## Kesimpulan

Tahap reconnaissance memberikan gambaran awal mengenai karakteristik binary yang akan dianalisis sehingga dapat membantu proses analisis berikutnya.

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
