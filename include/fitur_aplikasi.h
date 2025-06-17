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

void tambahPaperKeAuthor(AuthorPaperNode* author_node, PaperNode* paper);

AuthorPaperNode* cariAtauTambahAuthor(AuthorPaperNode** head, const char* author_name);

void hapusDaftarAuthor(AuthorPaperNode* head);

int stringStartsWithIgnoreCase(const char* str, const char* prefix);

void traverseBSTAndCollectAuthors(BSTNodeField* root, const char* search_str, AuthorPaperNode** author_list_head);

int tampilkanAuthorDanPapers(AuthorPaperNode* author_list_head, int halaman_sekarang, int item_per_hal);

// --- Fungsi untuk Mengelola Pilihan Urutan Tampilan ---
void kelolaOpsiUrutan(BSTNodeField* node_bst_field);

// --- Fungsi untuk Mengelola Pilihan Urutan Berdasarkan Author ---
void kelolaOpsiUrutanAuthor(BSTNodeField* root_bst_field);


#endif // FITUR_APLIKASI_H