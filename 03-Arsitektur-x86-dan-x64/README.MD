# x86 dan x64 Architecture Overview

## Tujuan Pembelajaran

Pada materi ini saya mempelajari dasar-dasar arsitektur x86 dan x64 yang menjadi fondasi utama dalam Reverse Engineering. Pemahaman mengenai CPU sangat penting karena seluruh instruksi assembly dieksekusi oleh prosesor.

## Komponen Utama CPU

CPU terdiri dari beberapa komponen utama, antara lain:

- **Arithmetic Logic Unit (ALU)** yang bertugas melakukan operasi aritmatika dan logika.
- **Control Unit** yang mengatur jalannya eksekusi instruksi.
- **Register** yang berfungsi sebagai media penyimpanan data berkecepatan tinggi.

Dalam proses Reverse Engineering, register merupakan komponen yang paling sering digunakan ketika melakukan debugging maupun analisis assembly.

## Siklus Eksekusi Instruksi

Setiap instruksi yang dijalankan CPU akan melalui tiga tahapan utama:

1. **Fetch** → mengambil instruksi dari memori.
2. **Decode** → menerjemahkan instruksi.
3. **Execute** → menjalankan instruksi.

Pemahaman mengenai proses ini membantu saya memahami bagaimana sebuah program dieksekusi oleh prosesor.

## Register pada x64

Arsitektur x64 memiliki beberapa register umum seperti:

- RAX
- RBX
- RCX
- RDX
- RSI
- RDI
- RSP
- RBP
- RIP

Register-register tersebut sering digunakan untuk menyimpan data, parameter fungsi, maupun alamat instruksi.

## Perbedaan x86 dan x64

Beberapa perbedaan utama antara arsitektur x86 dan x64:

| x86 | x64 |
|------|------|
| Register 32-bit | Register 64-bit |
| Maksimal RAM sekitar 4 GB | Mendukung memori jauh lebih besar |
| 8 General Purpose Register | 16 General Purpose Register |

## Privilege Ring

CPU memiliki beberapa tingkat hak akses yang disebut privilege ring.

- **Ring 0** digunakan oleh kernel dan memiliki akses penuh terhadap sistem.
- **Ring 3** digunakan oleh aplikasi biasa dengan hak akses terbatas.

Konsep ini penting untuk memahami bagaimana sistem operasi menjaga keamanan sistem.

## Calling Convention

Calling convention menentukan bagaimana parameter fungsi dikirim ke sebuah fungsi.

Pada Linux x64, enam parameter pertama biasanya dikirim melalui register:

```text
RDI, RSI, RDX, RCX, R8, dan R9
```

Sedangkan nilai hasil fungsi biasanya dikembalikan melalui register `RAX`.

## Praktik

Pada materi ini saya mencoba melihat informasi CPU pada sistem Linux menggunakan beberapa perintah berikut:

```bash
lscpu
cat /proc/cpuinfo
grep "flags" /proc/cpuinfo | head -1
```

Dari hasil pengamatan, saya dapat mengetahui:

- Arsitektur CPU yang digunakan.
- Jumlah core dan thread.
- Fitur prosesor yang tersedia.
- Dukungan virtualisasi.

## Praktik

Pada materi ini saya melakukan beberapa pengamatan terhadap arsitektur CPU pada sistem Linux yang digunakan.

### 1. Mengidentifikasi Informasi CPU

Perintah yang digunakan:

```bash
lscpu
```

Berdasarkan hasil pengamatan, sistem yang digunakan memiliki arsitektur `x86_64` dengan prosesor **AMD Ryzen 7 5800HS**. Selain itu, sistem juga mendukung virtualisasi melalui teknologi **AMD-V**.

Screenshot:

```text
screenshots/lscpu-output.png
```

---

### 2. Mengamati Informasi Detail CPU

Perintah:

```bash
cat /proc/cpuinfo
```

Informasi yang diperoleh antara lain:

- Vendor CPU: AuthenticAMD
- Jumlah core: 8
- Jumlah thread: 16
- Ukuran cache: 512 KB
- Address size: 48-bit physical dan 48-bit virtual

Screenshot:

```text
screenshots/cpuinfo-output.png
```

---

### 3. Mengidentifikasi Fitur CPU

Perintah:

```bash
grep "flags" /proc/cpuinfo | head -1
```

Dari hasil pengamatan ditemukan beberapa fitur CPU seperti:

- SSE
- SSE2
- AVX
- AVX2
- AES
- SMEP
- Virtualization Extension (SVM)

Fitur-fitur tersebut sangat penting dalam Reverse Engineering karena beberapa malware maupun mekanisme proteksi memanfaatkan instruksi-instruksi khusus tersebut.

Screenshot:

```text
screenshots/cpuflags-output.png
```

---

### 4. Melihat Register Menggunakan GDB

Saya membuat program sederhana dan menjalankannya menggunakan GDB untuk melihat isi register saat program dieksekusi.

Perintah:

```bash
gdb ./cpu_demo
```

Di dalam GDB:

```gdb
break main
run
info registers
```

Melalui praktik ini saya dapat melihat isi register seperti:

- RAX
- RBX
- RCX
- RDX
- RSP
- RBP
- RIP

Screenshot:

```text
screenshots/gdb-output.png
```

