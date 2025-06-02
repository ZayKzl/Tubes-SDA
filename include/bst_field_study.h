#ifndef BST_FIELD_STUDY_H
#define BST_FIELD_STUDY_H

#include "structs.h" // Diperlukan untuk tipe BSTNodeField dan JurnalData

// --- Fungsi untuk Membuat Node BST Field of Study Baru ---
// Mengalokasikan memori untuk BSTNodeField baru dan menginisialisasi field_of_study.
// Pointer list paper diinisialisasi ke NULL.
// Mengembalikan pointer ke node baru, atau NULL jika gagal.
BSTNodeField* buatBSTNodeField(const char* field_of_study);

// --- Fungsi untuk Menyisipkan Node ke BST Field of Study ---
// Menyisipkan node baru atau mengembalikan node yang sudah ada jika field_of_study sama.
// Root adalah pointer ke root BST.
// Mengembalikan root baru dari BST tersebut.
BSTNodeField* sisipkanBSTNodeField(BSTNodeField* root, const char* field_of_study);

// --- Fungsi untuk Mencari Node di BST Field of Study ---
// Mencari node berdasarkan field_of_study.
// Mengembalikan pointer ke node yang ditemukan, atau NULL jika tidak ada.
BSTNodeField* cariBSTNodeField(BSTNodeField* root, const char* field_of_study);

// --- Fungsi untuk Menambahkan JurnalData ke BSTNodeField yang Tepat ---
// Fungsi ini akan dipanggil setelah membaca satu JurnalData dari file.
// 1. Cari/Sisipkan BSTNodeField berdasarkan JurnalData.field_of_study.
// 2. Jika BSTNodeField ditemukan/dibuat, panggil fungsi sisipkanPaperUrut... 
//    dari linked_list_paper.h untuk memasukkan JurnalData ke 3 list paper.
// Perhatikan: root_bst adalah pointer ke pointer agar bisa diubah jika root awal NULL.
void tambahkanJurnalKeBST(BSTNodeField** root_bst, JurnalData data_jurnal);

// --- Fungsi untuk Menampilkan BST (misal: InOrder traversal untuk debugging) ---
void tampilkanBSTInOrder(BSTNodeField* root); // Akan menampilkan field_of_study saja

// --- Fungsi untuk Menghapus (Dealokasi Memori) Keseluruhan BST ---
// Membebaskan memori semua BSTNodeField dan juga semua linked list paper di dalamnya.
void hapusBST(BSTNodeField* root);

#endif // BST_FIELD_STUDY_H