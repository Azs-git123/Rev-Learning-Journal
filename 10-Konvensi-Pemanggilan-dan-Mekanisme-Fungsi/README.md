# Calling Conventions and Function Mechanics

## Tujuan Pembelajaran

Pada materi ini saya mempelajari berbagai calling convention yang digunakan pada arsitektur x86 dan x64. Calling convention merupakan aturan yang menentukan bagaimana argumen fungsi dikirim, bagaimana nilai dikembalikan, serta bagaimana stack dikelola selama pemanggilan fungsi.

Pemahaman mengenai calling convention sangat penting dalam Reverse Engineering karena membantu dalam mengidentifikasi fungsi, parameter, serta memahami alur program.

## Apa Itu Calling Convention?

Calling convention adalah sekumpulan aturan yang mengatur:

- Bagaimana argumen fungsi dikirim.
- Di mana nilai return disimpan.
- Siapa yang membersihkan stack.
- Register mana yang harus dipertahankan.

## Calling Convention pada x86

### cdecl

Karakteristik:

- Argumen dikirim melalui stack dari kanan ke kiri.
- Caller bertanggung jawab membersihkan stack.
- Nilai return disimpan pada register EAX.

Ciri khas:

```asm
push arg2
push arg1
call func
add esp, 8
```

## stdcall

Karakteristik:

- Argumen dikirim melalui stack.
- Callee membersihkan stack.
- Banyak digunakan oleh Windows API.

Ciri khas:

```asm
push arg2
push arg1
call func

ret 8
```

## fastcall

Karakteristik:

- Argumen pertama menggunakan ECX.
- Argumen kedua menggunakan EDX.
- Sisanya dikirim melalui stack.

## Calling Convention pada x64

### System V AMD64 ABI (Linux)

Enam argumen pertama dikirim melalui register:

| Argumen | Register |
|----------|----------|
| 1 | RDI |
| 2 | RSI |
| 3 | RDX |
| 4 | RCX |
| 5 | R8 |
| 6 | R9 |

Nilai return disimpan pada register `RAX`.

### Microsoft x64 ABI

Empat argumen pertama menggunakan:

| Argumen | Register |
|----------|----------|
| 1 | RCX |
| 2 | RDX |
| 3 | R8 |
| 4 | R9 |

Windows juga menggunakan shadow space sebelum pemanggilan fungsi.

## Function Prologue

Sebagian besar fungsi dimulai dengan prologue:

```asm
push rbp
mov rbp, rsp
sub rsp, 0x20
```

Tujuannya adalah:

- Menyimpan frame pointer sebelumnya.
- Membuat stack frame baru.
- Mengalokasikan ruang untuk variabel lokal.

## Function Epilogue

Fungsi biasanya diakhiri dengan:

```asm
leave
ret
```

atau

```asm
mov rsp, rbp
pop rbp
ret
```

## Praktik

Pada materi ini saya membuat fungsi sederhana untuk mengamati bagaimana argumen dikirim ke fungsi pada sistem Linux x64.

Source code dapat dilihat pada:

```text
samples/calling_demo.c
```

---

### 1. Melihat Disassembly Fungsi

Untuk melihat instruksi assembly yang dihasilkan compiler, saya menggunakan:

```bash
objdump -d -M intel calling_demo
```

Dari hasil disassembly terlihat adanya instruksi:

- `call`
- `mov`
- `push`
- `ret`

Instruksi tersebut digunakan selama proses pemanggilan fungsi.

Screenshot:

```text
screenshots/objdump-function.png
```

---

### 2. Mengamati Prologue dan Epilogue Fungsi

Saya menggunakan GDB untuk melihat isi fungsi `add()`.

Perintah yang digunakan:

```gdb
break add
run
disassemble add
```

Pada hasil disassembly terlihat function prologue:

```asm
push rbp
mov rbp, rsp
```

dan function epilogue:

```asm
pop rbp
ret
```

Compiler juga memindahkan argumen dari register ke stack frame menggunakan instruksi:

```asm
mov edi,-0x4(%rbp)
mov esi,-0x8(%rbp)
mov edx,-0xc(%rbp)
```

Screenshot:

```text
screenshots/function-prologue.png
```

---

### 3. Mengamati Argumen Fungsi

Ketika eksekusi berhenti pada fungsi `add()`, saya memeriksa register:

```gdb
info registers rdi rsi rdx
```

Hasilnya:

- `RDI` berisi nilai `10`.
- `RSI` berisi nilai `20`.
- `RDX` berisi nilai `30`.

Hal ini menunjukkan bahwa Linux x64 menggunakan register untuk mengirim argumen fungsi sesuai dengan aturan System V AMD64 ABI.

Screenshot:

```text
screenshots/function-arguments.png
```

---

## Hasil Pengamatan

Berdasarkan praktik yang dilakukan, saya memperoleh beberapa pemahaman:

- Linux x64 menggunakan register `RDI`, `RSI`, `RDX`, `RCX`, `R8`, dan `R9` untuk mengirim argumen fungsi.
- Nilai hasil fungsi biasanya dikembalikan melalui register `RAX`.
- Function prologue digunakan untuk membuat stack frame baru.
- Function epilogue digunakan untuk mengembalikan kondisi stack sebelum fungsi dipanggil.
- Calling convention sangat membantu dalam memahami fungsi ketika melakukan Reverse Engineering.
