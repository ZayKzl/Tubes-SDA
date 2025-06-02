#include <stdio.h>
#include <stdlib.h> // Untuk EXIT_SUCCESS, EXIT_FAILURE
#include "../include/structs.h"
#include "../include/manajemen_file.h"
#include "../include/bst_field_study.h"
#include "../include/fitur_aplikasi.h"

// Deklarasi eksternal untuk tungguEnter jika belum ada di header
// Atau pastikan sudah ada di fitur_aplikasi.h
extern void tungguEnter(); 
extern void tampilkanMenuUtama();
extern void jalankanFiturPencarianJurnal(BSTNodeField* root_bst);


int main() {
    BSTNodeField* root_bst = NULL;
    // GANTI NAMA FILE KE FILE JSON ANDA
    // Ini sudah benar, menggunakan path relatif dari root proyek
    const char *master_file_path = "dataset/jurnals_output.json"; 

    // PERBAIKAN DI SINI: Gunakan 'master_file_path' sebagai argumen
    printf("Memuat data dari master file JSON: %s...\n", master_file_path); 
    if (!muatDataDariMasterFile(master_file_path, &root_bst)) { // PERBAIKAN DI SINI: Gunakan 'master_file_path'
        printf("Gagal memuat data. Aplikasi mungkin tidak berfungsi dengan benar atau akan keluar.\n");
        // Anda bisa memilih untuk keluar jika data gagal dimuat:
        // return EXIT_FAILURE; 
    } else {
        printf("Data berhasil dimuat dari JSON.\n");
    }
    
    // Panggil tungguEnter() setelah pesan agar pengguna sempat baca
    tungguEnter();


    int pilihan_menu;
    do {
        tampilkanMenuUtama(); 
        if (scanf("%d", &pilihan_menu) != 1) {
            pilihan_menu = -1; 
            int c_buff;
            while ((c_buff = getchar()) != '\n' && c_buff != EOF); // Membersihkan buffer input
        }

        switch (pilihan_menu) {
            case 1:
                jalankanFiturPencarianJurnal(root_bst); 
                break;
            case 0:
                printf("Keluar dari aplikasi...\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                tungguEnter();
        }
    } while (pilihan_menu != 0);

    printf("Membersihkan memori...\n");
    hapusBST(root_bst); 
    root_bst = NULL;    
    printf("Aplikasi ditutup. Sampai jumpa!\n");

    return EXIT_SUCCESS;
}