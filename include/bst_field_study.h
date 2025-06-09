#ifndef BST_FIELD_STUDY_H
#define BST_FIELD_STUDY_H

#include "structs.h" // Diperlukan untuk tipe BSTNodeField dan JurnalData

// --- Fungsi untuk Membuat Node BST Field of Study Baru ---
BSTNodeField* buatBSTNodeField(const char* field_of_study);

// --- Fungsi untuk Menyisipkan Node ke BST Field of Study ---
BSTNodeField* sisipkanBSTNodeField(BSTNodeField* root, const char* field_of_study);

// --- Fungsi untuk Mencari Node di BST Field of Study ---
BSTNodeField* cariBSTNodeField(BSTNodeField* root, const char* field_of_study);

// --- Fungsi BARU: Membangun BST yang seimbang dari array string yang sudah diurutkan ---
BSTNodeField* bangunBSTSeimbang(char** fields_array, int start_index, int end_index);

// --- Fungsi untuk Menambahkan JurnalData ke BSTNodeField yang Tepat ---
void tambahkanJurnalKeBST(BSTNodeField** root_bst, JurnalData data_jurnal);

// --- Fungsi untuk Menampilkan BST (misal: InOrder traversal untuk debugging) ---
void tampilkanBSTInOrder(BSTNodeField* root); // Akan menampilkan field_of_study saja

// --- Fungsi untuk Menghapus (Dealokasi Memori) Keseluruhan BST ---
// Membebaskan memori semua BSTNodeField dan juga semua linked list paper di dalamnya.
void hapusBST(BSTNodeField* root);

#endif // BST_FIELD_STUDY_H