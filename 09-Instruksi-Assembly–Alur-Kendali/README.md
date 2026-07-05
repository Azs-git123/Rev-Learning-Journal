# Assembly Instructions - Control Flow

## Tujuan Pembelajaran

Pada materi ini saya mempelajari berbagai instruksi yang digunakan untuk mengendalikan alur eksekusi program. Instruksi control flow sangat penting dalam Reverse Engineering karena digunakan untuk membentuk percabangan, perulangan, dan pemanggilan fungsi.

## Instruksi Perbandingan

### CMP

Instruksi `CMP` digunakan untuk membandingkan dua nilai. Instruksi ini akan melakukan pengurangan secara internal dan mengatur nilai flag tanpa menyimpan hasilnya.

Contoh:

```asm
cmp eax, 10
je equal
```

Instruksi ini sering digunakan untuk memeriksa nilai variabel maupun melakukan validasi.

### TEST

Instruksi `TEST` melakukan operasi AND tanpa menyimpan hasilnya.

Contoh:

```asm
test eax, eax
jz is_zero
```

Instruksi ini sering digunakan untuk:

- Mengecek apakah register bernilai nol.
- Mengecek bit tertentu.
- Mengecek nilai hasil fungsi.

## Instruksi Percabangan

### JMP

`JMP` digunakan untuk berpindah ke alamat lain tanpa syarat.

```asm
jmp target
```

### Conditional Jump

Beberapa conditional jump yang dipelajari:

| Instruksi | Fungsi |
|-----------|--------|
| JE/JZ | Jump jika sama |
| JNE/JNZ | Jump jika tidak sama |
| JG | Lebih besar (signed) |
| JL | Lebih kecil (signed) |
| JA | Lebih besar (unsigned) |
| JB | Lebih kecil (unsigned) |

Conditional jump digunakan untuk membentuk struktur `if`, `if-else`, dan loop.

## CALL dan RET

Instruksi `CALL` digunakan untuk memanggil fungsi.

```asm
call function
```

Ketika `CALL` dijalankan, alamat instruksi berikutnya akan disimpan ke stack sebagai return address.

Sedangkan `RET` digunakan untuk kembali ke fungsi pemanggil.

```asm
ret
```

## Struktur Kontrol dalam Assembly

Compiler akan menerjemahkan struktur kontrol pada bahasa tingkat tinggi menjadi kombinasi instruksi `CMP`, `TEST`, dan `Jcc`.

Contoh:

### If-Else

```c
if (x > 10)
```

biasanya akan diterjemahkan menjadi:

```asm
cmp eax, 10
jle else_block
```

### While Loop

Loop biasanya ditandai dengan adanya lompatan ke alamat sebelumnya (backward jump).

### For Loop

Struktur `for` umumnya terdiri dari:

- Inisialisasi.
- Pengecekan kondisi.
- Body loop.
- Increment.
- Backward jump.

## Praktik

Pada materi ini saya membuat program sederhana yang berisi percabangan (`if-else`) dan perulangan (`for`) untuk mempelajari bagaimana compiler menerjemahkan struktur kontrol ke dalam assembly.

Source code dapat dilihat pada:

```text
samples/control_flow_demo.c
```

---

### 1. Melihat Disassembly Menggunakan objdump

Untuk melihat instruksi assembly yang dihasilkan compiler, saya menggunakan:

```bash
objdump -d -M intel control_flow_demo
```

Dari hasil disassembly terlihat berbagai instruksi control flow seperti:

- `cmp`
- `test`
- `je`
- `jle`
- `jmp`
- `call`

Screenshot:

```text
screenshots/objdump-control-flow.png
```

---

### 2. Analisis Fungsi Menggunakan GDB

Saya menggunakan GDB untuk melihat bagaimana struktur `if-else` dan `for` diterjemahkan ke dalam assembly.

Perintah yang digunakan:

```gdb
break main
run
disassemble main
```

Pada hasil disassembly terlihat bahwa:

```c
if (value > 10)
```

diterjemahkan menjadi:

```asm
cmpl $0xa,-0x4(%rbp)
jle ...
```

Selain itu, loop:

```c
for(int i=0; i<5; i++)
```

diterjemahkan menjadi kombinasi instruksi:

```asm
mov
add
cmp
jle
jmp
```

Screenshot:

```text
screenshots/gdb-disassemble-main.png
```

---

### 3. Melakukan Single Stepping

Untuk memahami alur eksekusi program, saya menjalankan instruksi satu per satu menggunakan:

```gdb
ni
```

Kemudian saya mengamati instruksi yang akan dieksekusi menggunakan:

```gdb
x/10i $rip
```

Melalui teknik ini saya dapat memahami bagaimana CPU berpindah antar instruksi selama program berjalan.

Screenshot:

```text
screenshots/single-step-branch.png
```

---

## Hasil Pengamatan

Berdasarkan praktik yang dilakukan, saya memperoleh beberapa pemahaman:

- Instruksi `cmp` dan `test` digunakan untuk menentukan kondisi percabangan.
- Conditional jump seperti `je`, `jle`, dan `jne` digunakan untuk membentuk struktur `if` dan loop.
- Struktur `for` pada bahasa C diterjemahkan menjadi kombinasi instruksi inisialisasi, perbandingan, increment, dan lompatan bersyarat.
- Instruksi `call` digunakan untuk memanggil fungsi, sedangkan `ret` digunakan untuk kembali ke pemanggil.
- GDB sangat membantu untuk memahami alur eksekusi program secara dinamis.
