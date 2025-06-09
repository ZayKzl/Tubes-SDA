#include <stdio.h>
#include <stdlib.h> // Untuk EXIT_SUCCESS, EXIT_FAILURE
#include "../include/structs.h"
#include "../include/manajemen_file.h"
#include "../include/bst_field_study.h"
#include "../include/fitur_aplikasi.h"
#include "../include/stack_search_history.h" 

// Deklarasi eksternal untuk fungsi tungguEnter jika belum ada di header
extern void tungguEnter(); 

// Deklarasi global untuk search history stack
SearchHistoryStack searchHistory; 

int main() {
    BSTNodeField* root_bst = NULL;
    // GANTI NAMA FILE KE FILE JSON ANDA
    const char* nama_master_file = "dataset/jurnals_output.json"; // atau nama file JSON lain dari Python Anda

    // Inisialisasi search history stack di awal program
    initSearchHistoryStack(&searchHistory);

    printf("Memuat data dari master file JSON: %s...\n", nama_master_file);
    if (!muatDataDariMasterFile(nama_master_file, &root_bst)) {
        printf("Gagal memuat data. Aplikasi mungkin tidak berfungsi dengan benar atau akan keluar.\n");
        // Anda bisa memilih untuk keluar jika data gagal dimuat:
        // return EXIT_FAILURE; 
    } else {
        printf("Data berhasil dimuat dari JSON.\n");
    }
    
    // Panggil tungguEnter() setelah pesan agar pengguna sempat baca
    // Ini akan memanggil fungsi dari fitur_aplikasi.c, pastikan di-link dengan benar.
    // Jika tidak mau ada dependensi ke fitur_aplikasi.c di main, buat fungsi tungguEnter lokal.
    // Untuk sementara kita panggil dari sana.
    extern void tungguEnter(); // Deklarasi eksternal jika belum ada di header
    tungguEnter();


    int pilihan_menu;
    do {
        tampilkanMenuUtama(); // Dari fitur_aplikasi.h/.c
        if (scanf("%d", &pilihan_menu) != 1) {
            pilihan_menu = -1; 
            int c_buff;
            while ((c_buff = getchar()) != '\n' && c_buff != EOF);
        }

        switch (pilihan_menu) {
            case 1:
                tampilkanSemuaFieldOfStudy(root_bst);
                break;
            case 2:
                jalankanFiturPencarianJurnal(root_bst, &searchHistory); // Dari fitur_aplikasi.h/.c
                break;
            case 3: 
                displaySearchHistory(&searchHistory);
                tungguEnter();
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
    clearSearchHistory(&searchHistory);   
    printf("Aplikasi ditutup. Sampai jumpa!\n");

    return EXIT_SUCCESS;
}