# CPU Registers Deep Dive

## Tujuan Pembelajaran

Pada materi ini saya mempelajari berbagai jenis register yang terdapat pada arsitektur x86 dan x64. Register merupakan tempat penyimpanan tercepat di dalam CPU dan hampir setiap instruksi assembly akan membaca atau menulis data ke register.

## General Purpose Registers

Register umum digunakan untuk menyimpan data, alamat memori, maupun parameter fungsi.

Beberapa register yang sering dijumpai:

| Register | Fungsi Umum |
|----------|-------------|
| RAX | Menyimpan nilai return dan operasi aritmatika |
| RBX | General purpose register |
| RCX | Counter dan parameter fungsi |
| RDX | Data register dan parameter fungsi |
| RSI | Source Index |
| RDI | Destination Index |
| RSP | Stack Pointer |
| RBP | Base/Frame Pointer |
| RIP | Menunjuk instruksi berikutnya |

Pada arsitektur x64 terdapat register tambahan yaitu R8 hingga R15.

## Stack Pointer dan Frame Pointer

`RSP` menunjuk ke bagian paling atas stack, sedangkan `RBP` biasanya digunakan sebagai acuan untuk mengakses variabel lokal dan parameter fungsi.

Dalam proses debugging, kedua register ini sangat penting untuk memahami struktur stack sebuah program.

## Calling Convention

Calling convention menentukan bagaimana parameter fungsi dikirim.

Pada Linux x64, enam parameter pertama dikirim melalui register:

```text
RDI, RSI, RDX, RCX, R8, dan R9
```

Sedangkan nilai return biasanya disimpan pada register `RAX`.

## Segment Registers

Selain register umum, CPU juga memiliki segment register seperti:

- CS
- DS
- SS
- FS
- GS

Pada sistem modern, register `FS` dan `GS` masih banyak digunakan, terutama untuk Thread Local Storage (TLS) maupun struktur internal sistem operasi.

## Flags Register

Flags register menyimpan informasi hasil operasi yang dilakukan CPU.

Beberapa flag yang sering dijumpai:

| Flag | Fungsi |
|-------|--------|
| CF | Carry Flag |
| ZF | Zero Flag |
| SF | Sign Flag |
| OF | Overflow Flag |
| IF | Interrupt Flag |

Flag ini sangat penting karena menentukan alur percabangan program.

Contoh:

```asm
cmp eax, ebx
je  equal
```

Instruksi `je` akan dijalankan apabila Zero Flag (ZF) bernilai 1.

## Instruction Pointer

Register `RIP` menyimpan alamat instruksi berikutnya yang akan dieksekusi CPU.

Mengendalikan nilai RIP berarti mengendalikan alur eksekusi program.

## Praktik

Pada materi ini saya menggunakan GDB untuk mengamati dan memanipulasi register CPU saat program dijalankan.

### Menampilkan Seluruh Register

Perintah yang digunakan:

```gdb
info registers
```

Perintah tersebut menampilkan seluruh register CPU seperti:

- RAX
- RBX
- RCX
- RDX
- RSP
- RBP
- RIP
- EFLAGS

Melalui hasil pengamatan, saya dapat melihat nilai setiap register serta alamat instruksi yang sedang dieksekusi oleh program.

Screenshot:

```text
screenshots/info-registers.png
```

### Menampilkan Nilai Register Tertentu

Untuk melihat isi register `RAX` dalam format hexadecimal, saya menggunakan:

```gdb
p/x $rax
```

Hasilnya menunjukkan nilai register `RAX` saat breakpoint tercapai.

### Memodifikasi Register

GDB juga memungkinkan perubahan nilai register secara langsung.

Contoh:

```gdb
set $rax = 100
```

Fitur ini sangat berguna dalam Reverse Engineering untuk:

- Mengubah alur eksekusi program.
- Melakukan bypass terhadap validasi tertentu.
- Melakukan eksperimen selama proses debugging.

Screenshot:

```text
screenshots/rax-modification.png
```
