# Introduction to Assembly Language

## Tujuan Pembelajaran

Pada materi ini saya mempelajari dasar-dasar bahasa Assembly pada arsitektur x86-64. Assembly merupakan representasi yang lebih mudah dibaca manusia dari machine code yang dieksekusi secara langsung oleh CPU.

Dalam Reverse Engineering, assembly merupakan bahasa utama yang digunakan untuk memahami cara kerja sebuah program ketika source code tidak tersedia.

## Apa Itu Assembly Language?

Assembly language merupakan bahasa tingkat rendah yang memiliki hubungan sangat dekat dengan instruksi mesin.

Contoh instruksi assembly:

```asm
mov eax, 1
```

Instruksi di atas memindahkan nilai `1` ke register `EAX`.

Assembly terdiri dari beberapa komponen:

| Komponen | Penjelasan |
|-----------|------------|
| Mnemonic | Nama instruksi seperti MOV, ADD, JMP |
| Operand | Data atau register yang digunakan |
| Opcode | Representasi biner dari instruksi |
| Instruction | Kombinasi mnemonic dan operand |

## Peran Assembler

Assembler bertugas menerjemahkan source code assembly menjadi machine code.

Contoh assembler yang sering digunakan:

- NASM
- GAS
- MASM
- FASM

Pada materi ini saya menggunakan NASM.

## Intel Syntax dan AT&T Syntax

Arsitektur x86 memiliki dua jenis sintaks utama:

### Intel Syntax

```asm
mov eax, 1
```

### AT&T Syntax

```asm
movl $1, %eax
```

Sebagian besar tool Reverse Engineering seperti IDA Pro, Ghidra, dan x64dbg menggunakan Intel Syntax.

## Struktur Program Assembly

Program assembly umumnya terdiri dari tiga section utama:

### .text

Berisi kode program yang akan dieksekusi.

### .data

Berisi data yang telah diinisialisasi.

### .bss

Berisi data yang belum diinisialisasi.

Contoh:

```asm
section .data
    msg db "Hello", 0x0a

section .text
    global _start

_start:
    mov rax, 60
    xor rdi, rdi
    syscall
```

## Linux Syscall

Pada Linux x86-64, syscall digunakan untuk berkomunikasi dengan kernel.

Contoh syscall:

| Syscall | Nomor |
|----------|-------|
| read | 0 |
| write | 1 |
| open | 2 |
| exit | 60 |

Register yang digunakan:

| Register | Fungsi |
|-----------|---------|
| RAX | Nomor syscall |
| RDI | Argumen 1 |
| RSI | Argumen 2 |
| RDX | Argumen 3 |

## Praktik

Pada materi ini saya membuat program sederhana "Hello World" menggunakan NASM.

Source code program dapat dilihat pada:

```text
samples/hello.asm
```

### 1. Assemble dan Linking

Program assembly dikompilasi menggunakan NASM kemudian di-link menggunakan LD.

Perintah:

```bash
nasm -f elf64 hello.asm -o hello.o
ld hello.o -o hello
```

Setelah proses build selesai, program dapat dijalankan secara langsung.

```bash
./hello
```

Program berhasil menampilkan pesan:

```text
Hello, Reverse Engineering!
```

Screenshot:

```text
screenshots/hello-output.png
```

---

### 2. Melihat Disassembly Program

Untuk melihat instruksi assembly yang terdapat pada binary, saya menggunakan:

```bash
objdump -d -M intel hello
```

Hasil disassembly memperlihatkan bahwa instruksi assembly telah diterjemahkan menjadi machine code yang dapat dieksekusi oleh CPU.

Beberapa instruksi yang terlihat antara lain:

- `mov`
- `lea`
- `xor`
- `syscall`

Selain itu juga terlihat representasi machine code dalam bentuk byte hexadecimal.

Screenshot:

```text
screenshots/objdump-disassembly.png
```

---

## Hasil Pengamatan

Berdasarkan praktik yang dilakukan, saya memperoleh beberapa pemahaman:

- Program assembly harus melalui proses assemble dan linking sebelum dapat dijalankan.
- NASM menerjemahkan source code assembly menjadi object file.
- Instruksi assembly memiliki representasi machine code dalam bentuk byte.
- Program Linux x86-64 berinteraksi dengan kernel menggunakan syscall.
