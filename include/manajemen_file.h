#ifndef MANAJEMEN_FILE_H
#define MANAJEMEN_FILE_H

#include "structs.h" // Diperlukan untuk BSTNodeField

// --- Fungsi untuk Memuat Data Jurnal dari File ---
int muatDataDariMasterFile(const char* nama_file, BSTNodeField** root_bst_ptr);

#endif // MANAJEMEN_FILE_H