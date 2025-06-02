#ifndef MANAJEMEN_FILE_H
#define MANAJEMEN_FILE_H

#include "structs.h" // Diperlukan untuk BSTNodeField

// --- Fungsi untuk Memuat Data Jurnal dari File ---
// Membaca data jurnal dari file yang ditentukan (nama_file).
// Data yang dibaca akan dimasukkan ke dalam struktur BST.
// Mengembalikan 1 jika berhasil, 0 jika gagal.
// root_bst_ptr adalah pointer ke pointer root BST agar bisa diinisialisasi/diubah.
int muatDataDariMasterFile(const char* nama_file, BSTNodeField** root_bst_ptr);

// Mungkin ada fungsi lain terkait manajemen file, misalnya:
// int simpanDataKeFile(const char* nama_file, BSTNodeField* root_bst); // Jika ada fitur simpan

#endif // MANAJEMEN_FILE_H