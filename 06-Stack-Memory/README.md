# The Stack - How It Works

## Tujuan Pembelajaran

Pada materi ini saya mempelajari konsep stack sebagai salah satu struktur data terpenting dalam eksekusi program. Stack digunakan untuk menyimpan return address, variabel lokal, parameter fungsi, serta informasi yang dibutuhkan selama pemanggilan fungsi.

## Apa Itu Stack?

Stack merupakan area memori yang bekerja menggunakan prinsip LIFO (Last In First Out). Artinya, data yang terakhir masuk ke stack akan menjadi data pertama yang keluar.

Pada arsitektur x86 dan x64, posisi paling atas stack ditunjukkan oleh register:

- ESP (x86)
- RSP (x64)

Operasi utama pada stack adalah:

- `PUSH` → menambahkan data ke stack.
- `POP` → mengambil data dari stack.

Selain itu, instruksi seperti `CALL` dan `RET` juga menggunakan stack secara otomatis.

## Arah Pertumbuhan Stack

Pada arsitektur x86 dan x64, stack tumbuh ke arah alamat memori yang lebih rendah.

Artinya:

- `PUSH` akan mengurangi nilai RSP.
- `POP` akan menambah nilai RSP.

Pemahaman mengenai arah pertumbuhan stack sangat penting dalam analisis buffer overflow.

## Stack Frame

Setiap kali sebuah fungsi dipanggil, sistem akan membuat sebuah stack frame.

Stack frame umumnya berisi:

- Return address.
- Saved base pointer.
- Variabel lokal.
- Parameter fungsi.
- Register yang disimpan sementara.

Dalam proses Reverse Engineering, stack frame membantu memahami alur eksekusi suatu fungsi.

## Register RSP dan RBP

Register `RSP` selalu menunjuk ke bagian paling atas stack.

Sedangkan `RBP` digunakan sebagai acuan tetap selama fungsi berjalan sehingga mempermudah akses ke variabel lokal dan parameter fungsi.

Pola prologue fungsi yang sering dijumpai adalah:

```asm
push rbp
mov rbp, rsp
sub rsp, 0x20
```

Sedangkan epilogue fungsi biasanya berupa:

```asm
leave
ret
```

## Calling Convention

Calling convention menentukan bagaimana parameter fungsi dikirim.

Pada Linux x64, enam parameter pertama dikirim melalui register:

```text
RDI, RSI, RDX, RCX, R8, dan R9
```

Sedangkan nilai return biasanya disimpan pada register `RAX`.

## Buffer Overflow

Salah satu kerentanan klasik yang memanfaatkan stack adalah buffer overflow.

Buffer overflow terjadi ketika data yang ditulis melebihi ukuran buffer sehingga dapat menimpa data lain pada stack seperti:

- Saved RBP.
- Return Address.

Apabila return address berhasil dimodifikasi, maka alur eksekusi program dapat dikendalikan.

## Praktik

Pada materi ini saya menggunakan GDB untuk mengamati bagaimana stack digunakan selama eksekusi program.

Program yang digunakan dapat dilihat pada folder:

```text
samples/stack_demo.c
```

---

### 1. Mengamati Register Stack

Untuk melihat register yang berkaitan dengan stack, saya menggunakan perintah:

```gdb
info registers rsp rbp rip
```

Dari hasil pengamatan:

- `RSP` menunjuk ke bagian paling atas stack.
- `RBP` digunakan sebagai acuan tetap untuk stack frame saat fungsi berjalan.
- `RIP` menunjukkan alamat instruksi yang sedang dieksekusi.

Screenshot:

```text
screenshots/stack-registers.png
```

---

### 2. Melihat Isi Stack

Untuk melihat isi stack secara langsung, saya menggunakan:

```gdb
x/20gx $rsp
```

Perintah tersebut menampilkan 20 buah nilai memori mulai dari alamat yang ditunjuk oleh register `RSP`.

Dari hasil pengamatan terlihat berbagai data yang tersimpan di stack seperti:

- Return address.
- Saved frame pointer.
- Variabel lokal.
- Argumen fungsi.

Screenshot:

```text
screenshots/stack-memory.png
```

---

### 3. Mengamati Stack Frame

Untuk melihat informasi detail mengenai stack frame suatu fungsi, saya menggunakan:

```gdb
info frame
```

Informasi yang ditampilkan antara lain:

- Alamat frame saat ini.
- Return address yang tersimpan.
- Lokasi argumen fungsi.
- Lokasi variabel lokal.
- Saved register.

Screenshot:

```text
screenshots/info-frame.png
```

Melalui perintah ini saya dapat memahami bagaimana sebuah fungsi menyimpan informasi yang dibutuhkan selama eksekusi.

---

### 4. Melihat Backtrace

Untuk melihat urutan pemanggilan fungsi, saya menggunakan:

```gdb
bt
```

Perintah ini menampilkan seluruh fungsi yang sedang aktif pada call stack.

Pada program yang diuji, terlihat bahwa fungsi `main()` memanggil fungsi `greet()`.

Screenshot:

```text
screenshots/backtrace.png
```

Backtrace sangat membantu dalam proses debugging maupun analisis crash.

---

## Hasil Pengamatan

Berdasarkan praktik yang dilakukan, saya memperoleh beberapa pemahaman:

- Stack bekerja menggunakan prinsip LIFO (Last In First Out).
- Setiap pemanggilan fungsi akan membuat stack frame baru.
- Register `RSP` dan `RBP` berperan penting dalam pengelolaan stack.
- Return address disimpan pada stack dan digunakan oleh instruksi `RET`.
- Call stack dapat digunakan untuk melacak alur eksekusi program.
