#ifndef FITUR_APLIKASI_H
#define FITUR_APLIKASI_H

#include "structs.h" // Untuk BSTNodeField

// --- Fungsi untuk Menampilkan Menu Utama ---
void tampilkanMenuUtama();

// --- Fungsi untuk Menjalankan Fitur Pencarian Jurnal ---
// root_bst adalah root dari keseluruhan struktur data.
// Meminta input field_of_study dari pengguna.
// Menampilkan hasil pencarian (awal urut tahun) dan opsi untuk melihat abstrak/mengurutkan.
void jalankanFiturPencarianJurnal(BSTNodeField* root_bst);

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


// (Fitur "Popularitas Jurnal" [cite: 1] seperti yang dideskripsikan di dokumen analisis
// ("Pengguna dapat melihat popularitas jurnal yang ia cari berdasarkan berapa kali jurnal tersebut disitasi") [cite: 1]
// sudah terintegrasi dengan adanya field 'jumlah_incitations' pada JurnalData
// dan kemampuan untuk mengurutkan berdasarkan 'jumlah_incitations' melalui kelolaOpsiUrutan.)

#endif // FITUR_APLIKASI_H