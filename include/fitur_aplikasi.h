#ifndef FITUR_APLIKASI_H
#define FITUR_APLIKASI_H

#include "structs.h" // Untuk BSTNodeField
#include "stack_search_history.h" // Untuk SearchHistoryStack

// --- Fungsi untuk Menampilkan Menu Utama ---
void tampilkanMenuUtama();

void tampilkanSemuaFieldOfStudy(BSTNodeField* root);


// --- Fungsi untuk Menjalankan Fitur Pencarian Jurnal ---
void jalankanFiturPencarianJurnal(BSTNodeField* root_bst, SearchHistoryStack *history);

// --- Fungsi untuk Menjalankan Fitur Melihat Abstrak ---
void lihatAbstrakJurnal(JurnalData data_jurnal);

// --- Fungsi untuk Mengelola Pilihan Urutan Tampilan ---
void kelolaOpsiUrutan(BSTNodeField* node_bst_field);

// --- Fungsi untuk Mengelola Pilihan Urutan Berdasarkan Author ---
void kelolaOpsiUrutanAuthor(BSTNodeField* root_bst_field);


#endif // FITUR_APLIKASI_H