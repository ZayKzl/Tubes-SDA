#ifndef LINKED_LIST_PAPER_H
#define LINKED_LIST_PAPER_H

#include "structs.h" // Diperlukan untuk tipe PaperNode dan JurnalData

// --- Fungsi untuk Membuat Node Paper Baru ---
// Mengalokasikan memori untuk PaperNode baru dan mengisinya dengan JurnalData.
// Mengembalikan pointer ke node baru, atau NULL jika gagal.
PaperNode* buatPaperNode(JurnalData data_jurnal);

// --- Fungsi untuk Menyisipkan Paper ke Linked List Terurut ---
// Catatan: Kita akan membuat tiga fungsi sisip terpisah untuk kejelasan,
// atau satu fungsi generik dengan parameter pembanding.
// Untuk sekarang, kita deklarasikan yang terpisah.

// Menyisipkan paper ke list yang diurutkan berdasarkan TAHUN (menurun: terbaru dulu).
// Menerima head dari list yang ada dan data jurnal baru.
// Mengembalikan head baru dari list tersebut.
void sisipkanPaperUrutTahunDLL(PaperNode** head_ptr, PaperNode** tail_ptr, JurnalData data_jurnal);

// Menyisipkan paper ke list yang diurutkan berdasarkan JUMLAH INCITATIONS (menurun: terbanyak dulu).
// Menerima head dari list yang ada dan data jurnal baru.
// Mengembalikan head baru dari list tersebut.
PaperNode* sisipkanPaperUrutIncitations(PaperNode* head, JurnalData data_jurnal);

// Menyisipkan paper ke list yang diurutkan berdasarkan JUDUL (abjad A-Z).
// Menerima head dari list yang ada dan data jurnal baru.
// Mengembalikan head baru dari list tersebut.
PaperNode* sisipkanPaperUrutJudul(PaperNode* head, JurnalData data_jurnal);

// --- Fungsi untuk Menampilkan Isi Linked List Paper ---
// Menerima head dari list dan menampilkan informasi dasar jurnal (misal: judul, tahun, penulis).
void tampilkanListPaper(PaperNode* head);

// --- Fungsi untuk Menghapus (Dealokasi Memori) Linked List Paper ---
// Menerima head dari list dan membebaskan memori semua node di dalamnya.
void hapusListPaper(PaperNode* head);
void tampilkanListPaperReverse(PaperNode* tail);

// Menyisipkan paper ke list yang diurutkan berdasarkan NAMA PENULIS (abjad A-Z).
// Menerima head dari list yang ada dan data jurnal baru.
// Mengembalikan head baru dari list tersebut.
PaperNode* sisipkanPaperUrutAuthor(PaperNode* head, JurnalData data_jurnal);

#endif // LINKED_LIST_PAPER_H
