#ifndef BST_FIELD_STUDY_H
#define BST_FIELD_STUDY_H

#include "structs.h" // Diperlukan untuk tipe BSTNodeField dan JurnalData

// --- Fungsi untuk Membuat Node BST Field of Study Baru ---
BSTNodeField* buatBSTNodeField(const char* field_of_study);

// --- Fungsi untuk Menyisipkan Node ke BST Field of Study (DENGAN LOGIKA AVL) ---
BSTNodeField* sisipkanBSTNodeField(BSTNodeField* root, const char* field_of_study);

// --- Fungsi untuk Mencari Node di BST Field of Study ---
BSTNodeField* cariBSTNodeField(BSTNodeField* root, const char* field_of_study);

// --- Fungsi untuk Menambahkan JurnalData ke BSTNodeField yang Tepat ---
void tambahkanJurnalKeBST(BSTNodeField** root_bst, JurnalData data_jurnal);

// --- Fungsi untuk Menampilkan BST (InOrder traversal) ---
void tampilkanBSTInOrder(BSTNodeField* root);

// --- Fungsi untuk Menghapus (Dealokasi Memori) Keseluruhan BST ---
void hapusBST(BSTNodeField* root);

// --- FUNGSI-FUNGSI BARU UNTUK IMPLEMENTASI AVL ---
// Mengembalikan tinggi sebuah node. Tinggi node NULL adalah -1.
int getHeight(BSTNodeField* node);

// Fungsi bantu untuk mendapatkan nilai maksimum.
int max(int a, int b);

// Melakukan rotasi kanan pada subtree yang berakar pada node 'y'.
BSTNodeField* rightRotate(BSTNodeField* y);

// Melakukan rotasi kiri pada subtree yang berakar pada node 'x'.
BSTNodeField* leftRotate(BSTNodeField* x);

// Mendapatkan faktor keseimbangan sebuah node (tinggi_kiri - tinggi_kanan).
int getBalanceFactor(BSTNodeField* node);

// (Opsional) Fungsi untuk memeriksa apakah seluruh BST seimbang (untuk debugging/verifikasi)
int isBalanced(BSTNodeField* root);


#endif // BST_FIELD_STUDY_H