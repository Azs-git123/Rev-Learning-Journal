# Number Systems and Data Representation

## Tujuan Pembelajaran

Pada materi ini saya mempelajari berbagai sistem bilangan yang digunakan komputer serta bagaimana data direpresentasikan di dalam memori. Pemahaman mengenai konsep ini sangat penting karena proses Reverse Engineering selalu berhubungan dengan pembacaan data biner, heksadesimal, maupun struktur data di memori.

## Sistem Bilangan pada Komputer

Komputer bekerja menggunakan sistem bilangan biner (base 2) yang hanya terdiri dari angka 0 dan 1. Namun, dalam praktik Reverse Engineering, analis lebih sering menggunakan bilangan heksadesimal (base 16) karena lebih ringkas dan mudah dibaca.

Beberapa sistem bilangan yang umum digunakan:

* Biner (base 2)
* Desimal (base 10)
* Heksadesimal (base 16)

## Heksadesimal dalam Reverse Engineering

Bilangan heksadesimal merupakan representasi yang paling sering ditemui saat melakukan analisis binary.

Contoh nilai heksadesimal yang sering muncul:

| Nilai Hex  | Keterangan       |
| ---------- | ---------------- |
| 0x00       | NULL byte        |
| 0x41       | Karakter 'A'     |
| 0x90       | Instruksi NOP    |
| 0xCC       | Breakpoint       |
| 0x7F454C46 | Magic Number ELF |
| 0x4D5A     | Magic Number PE  |

## Signed dan Unsigned Integer

CPU tidak membedakan apakah sebuah nilai merupakan signed atau unsigned. Interpretasi nilai bergantung pada instruksi yang digunakan.

Sebagai contoh:

* `0xFF` dapat bernilai 255 jika dianggap unsigned.
* `0xFF` dapat bernilai -1 jika dianggap signed.

Untuk merepresentasikan bilangan negatif, prosesor modern menggunakan metode Two's Complement.

## Endianness

Endianness menentukan bagaimana data multi-byte disimpan di memori.

### Little Endian

Byte dengan nilai paling rendah disimpan terlebih dahulu.

Contoh:

```text
0xDEADBEEF

EF BE AD DE
```

Arsitektur x86 dan x64 menggunakan format little-endian.

### Big Endian

Byte dengan nilai paling tinggi disimpan terlebih dahulu.

```text
0xDEADBEEF

DE AD BE EF
```

## Representasi Karakter

Karakter pada komputer direpresentasikan menggunakan standar seperti ASCII dan Unicode.

Contoh:

| Karakter | Hex  |
| -------- | ---- |
| A        | 0x41 |
| a        | 0x61 |
| 0        | 0x30 |

## Operasi Bit

Operasi bit merupakan dasar dari banyak teknik obfuscation, enkripsi, dan manipulasi data.

Operasi yang umum digunakan:

* AND
* OR
* XOR
* NOT
* Shift
* Rotate

XOR merupakan operasi yang sangat sering dijumpai pada malware maupun software protection karena sifatnya yang reversible.

## Layout Data di Memori

Data di dalam program disimpan dalam berbagai bentuk, seperti:

* Array
* String
* Struct

Memahami bagaimana data disusun di memori sangat membantu saat menganalisis binary menggunakan debugger maupun decompiler.

