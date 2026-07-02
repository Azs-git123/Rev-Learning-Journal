# Memory Layout and Segments

## Tujuan Pembelajaran

Pada materi ini saya mempelajari bagaimana sistem operasi mengatur memori untuk setiap proses yang berjalan. Pemahaman mengenai layout memori sangat penting dalam Reverse Engineering karena seluruh kode, data, stack, dan heap sebuah program ditempatkan pada area memori yang berbeda.

## Virtual Memory

Sistem operasi modern menggunakan konsep virtual memory, yaitu setiap proses memiliki ruang alamat virtual sendiri.

Virtual memory memberikan beberapa keuntungan:

- Isolasi antar proses.
- Mempermudah pengelolaan memori.
- Mendukung penggunaan memori melebihi kapasitas RAM melalui swap.

Pada arsitektur x64, setiap proses memiliki ruang alamat virtual yang sangat besar sehingga memungkinkan banyak proses berjalan secara bersamaan.

## Layout Memori Proses

Sebuah proses umumnya memiliki beberapa area memori utama:

### .text

Segmen `.text` berisi instruksi mesin hasil kompilasi program.

Karakteristik:

- Berisi kode program.
- Bersifat Read + Execute (R-X).
- Tidak dapat ditulis secara langsung.

### .rodata

Segmen `.rodata` menyimpan data konstan seperti string literal.

Contoh:

```c
const char *msg = "Hello World";
```

### .data

Segmen `.data` menyimpan variabel global atau static yang telah diinisialisasi.

Contoh:

```c
int counter = 10;
```

### .bss

Segmen `.bss` digunakan untuk menyimpan variabel global atau static yang belum diinisialisasi.

Contoh:

```c
int global_var;
```

### Heap

Heap digunakan untuk alokasi memori secara dinamis.

Contoh:

```c
char *buffer = malloc(100);
```

Heap tumbuh ke arah alamat memori yang lebih tinggi.

### Stack

Stack digunakan untuk menyimpan:

- Variabel lokal.
- Parameter fungsi.
- Return address.

Stack tumbuh ke arah alamat memori yang lebih rendah.

## ASLR (Address Space Layout Randomization)

ASLR merupakan mekanisme keamanan yang melakukan randomisasi alamat memori setiap kali program dijalankan.

Tujuannya adalah mempersulit eksploitasi karena alamat memori menjadi tidak dapat diprediksi.

## NX (No Execute)

NX merupakan mekanisme keamanan yang mencegah eksekusi kode pada area memori tertentu seperti stack dan heap.

Dengan adanya NX, serangan buffer overflow menjadi lebih sulit dilakukan.

## Praktik

Pada materi ini saya membuat sebuah program sederhana untuk mengamati tata letak memori sebuah proses saat dijalankan.

Program tersebut berisi:

- Variabel global yang telah diinisialisasi.
- Variabel global yang belum diinisialisasi.
- String konstan.
- Variabel lokal.
- Alokasi memori dinamis menggunakan `malloc()`.

### Program yang Digunakan

Source code dapat ditemukan pada folder:

```text
samples/memory_demo.c
```

---

### 1. Mengamati Layout Memori Saat Runtime

Program dijalankan menggunakan:

```bash
./memory_demo
```

Program menampilkan alamat memori dari beberapa objek seperti:

- Fungsi `main` (.text)
- Variabel global (.data)
- Variabel global tanpa inisialisasi (.bss)
- String konstan (.rodata)
- Variabel lokal (stack)
- Alokasi dinamis (heap)

Dari hasil pengamatan terlihat bahwa setiap jenis data ditempatkan pada area memori yang berbeda.

Screenshot:

```text
screenshots/memory-layout.png
```

---

### 2. Melihat Section pada Binary ELF

Untuk melihat struktur section pada binary ELF, saya menggunakan:

```bash
readelf -S memory_demo
```

Hasilnya menunjukkan berbagai section yang dimiliki oleh binary seperti:

- `.text`
- `.rodata`
- `.data`
- `.bss`

Section tersebut memiliki fungsi yang berbeda-beda dalam proses eksekusi program.

Screenshot:

```text
screenshots/readelf-sections.png
```

---

### 3. Mengamati Memory Mapping Menggunakan GDB

Saya menggunakan GDB untuk melihat bagaimana sistem operasi memetakan memori sebuah proses.

Perintah yang digunakan:

```gdb
break main
run
info proc mappings
```

Melalui perintah tersebut saya dapat melihat:

- Alamat awal dan akhir setiap region memori.
- Hak akses memori (Read, Write, Execute).
- Library yang dimuat ke dalam proses.
- Lokasi stack dan shared library.

Screenshot:

```text
screenshots/gdb-memory-maps.png
```

---

## Hasil Pengamatan

Berdasarkan praktik yang dilakukan, saya memperoleh beberapa pemahaman:

- Kode program disimpan pada segmen `.text`.
- Variabel global berada pada segmen `.data` atau `.bss`.
- String konstan disimpan pada `.rodata`.
- Variabel lokal berada pada stack.
- Alokasi menggunakan `malloc()` ditempatkan pada heap.
- Sistem operasi memberikan hak akses yang berbeda untuk setiap region memori.

