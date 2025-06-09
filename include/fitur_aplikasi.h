#ifndef FITUR_APLIKASI_H
#define FITUR_APLIKASI_H

#include "structs.h" // Untuk BSTNodeField
#include "stack_search_history.h" // Untuk SearchHistoryStack

// --- Fungsi untuk Menampilkan Menu Utama ---
void tampilkanMenuUtama();

void tampilkanSemuaFieldOfStudy(BSTNodeField* root);


// --- Fungsi untuk Menjalankan Fitur Pencarian Jurnal ---
// root_bst adalah root dari keseluruhan struktur data.
// Meminta input field_of_study dari pengguna.
// Menampilkan hasil pencarian (awal urut tahun) dan opsi untuk melihat abstrak/mengurutkan.
// Menambahkan parameter SearchHistoryStack *history
void jalankanFiturPencarianJurnal(BSTNodeField* root_bst, SearchHistoryStack *history);

// --- Fungsi untuk Menjalankan Fitur Melihat Abstrak ---
// Ini mungkin lebih baik dipanggil dari dalam jalankanFiturPencarianJurnal
// setelah daftar jurnal ditampilkan dan pengguna memilih salah satu.
// Menerima PaperNode spesifik atau JurnalData.
void lihatAbstrakJurnal(JurnalData data_jurnal);

// --- Fungsi untuk Mengelola Pilihan Urutan Tampilan ---
// Fungsi ini akan dipanggil setelah hasil pencarian untuk field_of_study ditampilkan.
// Pengguna bisa memilih untuk melihat daftar terurut berdasarkan kriteria lain.
// node_bst_field adalah node BST untuk field of study yang sedang aktif.
void kelolaOpsiUrutan(BSTNodeField* node_bst_field);

// --- Fungsi untuk Mengelola Pilihan Urutan Berdasarkan Author ---
// Fungsi ini akan memunculkan author berdasarkan input karakter awal dan menampilkan paper yang dibuat author tersebut.
// Fitur ini adalah fitur nomor 8.
void kelolaOpsiUrutanAuthor(BSTNodeField* root_bst_field);


#endif // FITUR_APLIKASI_H