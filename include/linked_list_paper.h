#ifndef LINKED_LIST_PAPER_H
#define LINKED_LIST_PAPER_H

#include "structs.h"
#include <stdbool.h> // Untuk tipe bool jika Anda menggunakannya

PaperNode* buatPaperNode(JurnalData data_jurnal);

// Fungsi sisip DLL (asumsi sudah benar dan mengelola head & tail)
void sisipkanDLLUrutTahunAsc(PaperNode** head_ptr, PaperNode** tail_ptr, JurnalData data_jurnal);
void sisipkanDLLUrutIncitationsDesc(PaperNode** head_ptr, PaperNode** tail_ptr, JurnalData data_jurnal);
void sisipkanDLLUrutJudulAsc(PaperNode** head_ptr, PaperNode** tail_ptr, JurnalData data_jurnal);
// Tambahkan deklarasi untuk sisip Author jika Anda menggunakannya dan itu DLL
// void sisipkanDLLUrutAuthorAsc(PaperNode** head_ptr, PaperNode** tail_ptr, JurnalData data_jurnal);


// --- PERUBAHAN UNTUK PAGINASI ---
// Fungsi tampilan sekarang menerima halaman dan item per halaman
// dan mengembalikan total item dalam list tersebut.
// Parameter ke-5 (nomor_urut_awal_di_halaman) digunakan untuk memberi tahu pemanggil
// nomor urut global dari item pertama yang ditampilkan di halaman itu.
int tampilkanListPaper(PaperNode* head, const char* list_name, int halaman_sekarang, int item_per_halaman, int* nomor_urut_awal_di_halaman);
int tampilkanListPaperReverse(PaperNode* tail, const char* list_name, int halaman_sekarang, int item_per_halaman, int* nomor_urut_awal_di_halaman);

// Fungsi helper untuk menghitung total item dalam list
int hitungTotalItemDiList(PaperNode* head);

// Fungsi pilih jurnal sekarang juga butuh info paginasi untuk menghitung indeks absolut
// nomor_pilihan_di_halaman adalah nomor yang dipilih pengguna (1-20) di halaman saat ini.
PaperNode* pilihJurnalDariList(PaperNode* head, int nomor_pilihan_di_halaman, int halaman_sekarang, int item_per_halaman);
PaperNode* pilihJurnalDariListReverse(PaperNode* tail, int nomor_pilihan_di_halaman, int halaman_sekarang, int item_per_halaman); 

void hapusListPaper(PaperNode** head_ptr, PaperNode** tail_ptr); // Asumsi Anda punya implementasi yang benar untuk DLL

#endif // LINKED_LIST_PAPER_H