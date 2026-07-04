# Assembly Instructions - Data Movement and Arithmetic

## Tujuan Pembelajaran

Pada materi ini saya mempelajari berbagai instruksi dasar pada arsitektur x86/x64 yang sering dijumpai saat melakukan Reverse Engineering. Instruksi-instruksi ini digunakan untuk memindahkan data, melakukan operasi aritmatika, manipulasi bit, serta mengendalikan alur eksekusi program.

## Instruksi Data Movement

### MOV

Instruksi `MOV` digunakan untuk memindahkan data dari sumber ke tujuan.

Contoh:

```asm
mov eax, 1
mov rbx, rax
```

Instruksi ini merupakan instruksi yang paling sering muncul pada hasil disassembly.

### LEA

`LEA` (Load Effective Address) digunakan untuk menghitung alamat memori tanpa membaca isi memori tersebut.

Contoh:

```asm
lea rax, [rbp-0x10]
```

Instruksi ini sering digunakan compiler untuk melakukan optimasi aritmatika maupun perhitungan alamat array.

### PUSH dan POP

Instruksi ini digunakan untuk berinteraksi dengan stack.

```asm
push rbp
pop rbp
```

- `PUSH` akan menambahkan data ke stack.
- `POP` akan mengambil data dari stack.

## Instruksi Aritmatika

Beberapa instruksi aritmatika yang dipelajari:

### ADD

Digunakan untuk penjumlahan.

```asm
add eax, ebx
```

### SUB

Digunakan untuk pengurangan.

```asm
sub eax, ebx
```

### INC dan DEC

Digunakan untuk menambah atau mengurangi nilai sebesar satu.

```asm
inc eax
dec ecx
```

Instruksi ini sering digunakan pada loop.

## Instruksi Bitwise

### AND

Digunakan untuk melakukan operasi bitwise AND.

```asm
and eax, 0xFF
```

### OR

Digunakan untuk melakukan operasi bitwise OR.

```asm
or eax, 1
```

### XOR

Instruksi `XOR` merupakan salah satu instruksi yang paling sering ditemui dalam Reverse Engineering.

```asm
xor eax, eax
```

Instruksi di atas biasanya digunakan untuk mengosongkan register.

Selain itu, XOR juga banyak digunakan pada malware untuk proses encoding maupun decoding data.

### TEST

Instruksi `TEST` digunakan untuk memeriksa suatu nilai tanpa mengubah operand.

Contoh:

```asm
test eax, eax
jz failed
```

Instruksi ini sering digunakan untuk memeriksa apakah suatu register bernilai nol.

## Sign Extension dan Zero Extension

Pada materi ini saya juga mempelajari:

- `MOVZX` untuk zero extension.
- `MOVSX` untuk sign extension.

Instruksi ini membantu menentukan apakah suatu data diperlakukan sebagai signed atau unsigned.

## Praktik

Pada materi ini saya membuat program sederhana yang melakukan operasi aritmatika dasar seperti penjumlahan, pengurangan, dan perkalian.

Source code dapat dilihat pada:

```text
samples/instruction_demo.c
```

---

### 1. Melihat Disassembly Menggunakan objdump

Untuk melihat instruksi assembly yang dihasilkan compiler, saya menggunakan:

```bash
objdump -d -M intel instruction_demo
```

Melalui hasil disassembly, saya dapat mengamati berbagai instruksi yang umum digunakan seperti:

- `mov`
- `add`
- `sub`
- `call`
- `test`
- `ret`

Instruksi-instruksi tersebut merupakan fondasi utama dalam analisis binary.

Screenshot:

```text
screenshots/objdump-disassembly.png
```

---

### 2. Menganalisis Fungsi Menggunakan GDB

Saya juga menggunakan GDB untuk melihat instruksi assembly pada fungsi `main`.

Perintah yang digunakan:

```gdb
break main
run
disassemble main
```

Dari hasil analisis terlihat bahwa compiler menerjemahkan operasi:

```c
sum = a + b;
diff = a - b;
mul = a * b;
```

menjadi instruksi:

```asm
add
sub
imul
```

Selain itu terlihat pula prologue dan epilogue fungsi:

```asm
push rbp
mov rbp, rsp
sub rsp, 0x20
...
leave
ret
```

Screenshot:

```text
screenshots/gdb-disassembly.png
```

---

## Hasil Pengamatan

Berdasarkan praktik yang dilakukan, saya memperoleh beberapa pemahaman:

- Instruksi `mov` digunakan untuk memindahkan data antar register maupun memori.
- Instruksi `add`, `sub`, dan `imul` digunakan untuk operasi aritmatika.
- Compiler menghasilkan prologue dan epilogue fungsi secara otomatis.
- Setiap operasi pada bahasa C akan diterjemahkan menjadi satu atau beberapa instruksi assembly.
- GDB dan objdump sangat membantu dalam memahami bagaimana compiler menghasilkan kode mesin.

