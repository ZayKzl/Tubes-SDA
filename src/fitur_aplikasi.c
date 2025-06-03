#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "../include/fitur_aplikasi.h"
#include "../include/bst_field_study.h"   
#include "../include/linked_list_paper.h" 

void bersihkanLayar() {
    // Gunakan system("cls") untuk Windows, system("clear") untuk Linux/macOS
    // Atau cetak banyak baris baru jika ingin portabilitas tanpa panggilan sistem
    // system("cls"); 
    // system("clear");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); // Cara sederhana
}

void tungguEnter() {
    printf("\nTekan Enter untuk melanjutkan...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Bersihkan sisa buffer
    getchar(); // Tunggu satu karakter (Enter)
}

void tampilkanMenuUtama() {
    bersihkanLayar();
    printf("=========================================\n");
    printf("      APLIKASI JURNAL ILMIAH SDA\n");
    printf("=========================================\n");
    printf(" Stakeholder: Civitas Akademika\n"); // Hapus [cite: 1] jika tidak dari file
    printf("-----------------------------------------\n");
    printf("Menu:\n");
    printf("1. Pencarian Jurnal (berdasarkan Field of Study)\n"); // Hapus [cite: 1]
    printf("0. Keluar\n");
    printf("-----------------------------------------\n");
    printf("Pilihan Anda: ");
}

// Fungsi pilihJurnalDariList dan pilihJurnalDariListReverse
// seharusnya diimplementasikan di linked_list_paper.c dan dideklarasikan di .h nya
// Jika masih di sini, pastikan konsisten. Untuk sekarang, kita asumsikan mereka ada di linked_list_paper.c

void lihatAbstrakJurnal(JurnalData data_jurnal) {
    bersihkanLayar();
    printf("=========================================\n");
    printf("             DETAIL & ABSTRAK JURNAL\n");
    printf("=========================================\n");
    printf("ID Paper     : %s\n", data_jurnal.id_paper);
    printf("Judul        : %s\n", data_jurnal.judul);
    printf("Penulis      : %s\n", data_jurnal.nama_penulis);
    printf("Tahun Terbit : %d\n", data_jurnal.tahun_terbit);
    printf("Field of Study: %s\n", data_jurnal.field_of_study);
    printf("InCitations  : %d\n", data_jurnal.jumlah_incitations);
    printf("Sitasi Info  : %s\n", data_jurnal.sitasi_info);
    printf("-----------------------------------------\n");
    printf("Abstrak      :\n%s\n", data_jurnal.abstrak);
    printf("=========================================\n");
    tungguEnter();
}

void kelolaOpsiUrutan(BSTNodeField* node_bst_field) {
    if (node_bst_field == NULL) {
        printf("Data field of study tidak ditemukan.\n");
        tungguEnter();
        return;
    }

    int pilihan_menu_aksi;
    int mode_tampilan_aktif = 1; // Default: Tahun Terbaru Dulu
    int halaman_sekarang = 1;
    const int ITEM_PER_HALAMAN = 20;
    int total_item_di_list_aktif = 0;
    int dummy_nomor_awal; // Untuk parameter fungsi tampilkanList...

    PaperNode* head_list_aktif = NULL; 
    PaperNode* tail_list_aktif = NULL; 

    do {
        bersihkanLayar();
        printf("=========================================\n");
        printf("   Hasil Pencarian untuk: %s\n", node_bst_field->field_of_study);
        
        const char* urutan_aktif_str = "";
        
        switch (mode_tampilan_aktif) {
            case 1: 
                urutan_aktif_str = "Tahun Terbit (Terbaru Dulu)";
                tail_list_aktif = node_bst_field->year_list_tail;
                head_list_aktif = NULL; 
                total_item_di_list_aktif = tampilkanListPaperReverse(tail_list_aktif, "Tahun (Terbaru)", halaman_sekarang, ITEM_PER_HALAMAN, &dummy_nomor_awal);
                break;
            case 2: 
                urutan_aktif_str = "Tahun Terbit (Terlama Dulu)";
                head_list_aktif = node_bst_field->year_list_head;
                tail_list_aktif = NULL;
                total_item_di_list_aktif = tampilkanListPaper(head_list_aktif, "Tahun (Terlama)", halaman_sekarang, ITEM_PER_HALAMAN, &dummy_nomor_awal);
                break;
            case 3: 
                urutan_aktif_str = "Popularitas (InCitations Terbanyak)";
                head_list_aktif = node_bst_field->incitations_list_head;
                tail_list_aktif = NULL;
                total_item_di_list_aktif = tampilkanListPaper(head_list_aktif, "Incitations (Terbanyak)", halaman_sekarang, ITEM_PER_HALAMAN, &dummy_nomor_awal);
                break;
            case 4: 
                urutan_aktif_str = "Popularitas (InCitations Tersedikit)";
                tail_list_aktif = node_bst_field->incitations_list_tail;
                head_list_aktif = NULL;
                total_item_di_list_aktif = tampilkanListPaperReverse(tail_list_aktif, "Incitations (Tersedikit)", halaman_sekarang, ITEM_PER_HALAMAN, &dummy_nomor_awal);
                break;
            case 5: 
                urutan_aktif_str = "Judul (A-Z)";
                head_list_aktif = node_bst_field->title_list_head;
                tail_list_aktif = NULL;
                total_item_di_list_aktif = tampilkanListPaper(head_list_aktif, "Judul (A-Z)", halaman_sekarang, ITEM_PER_HALAMAN, &dummy_nomor_awal);
                break;
            case 6: 
                urutan_aktif_str = "Judul (Z-A)";
                tail_list_aktif = node_bst_field->title_list_tail;
                head_list_aktif = NULL;
                total_item_di_list_aktif = tampilkanListPaperReverse(tail_list_aktif, "Judul (Z-A)", halaman_sekarang, ITEM_PER_HALAMAN, &dummy_nomor_awal);
                break;
        }
        
        int total_halaman = (total_item_di_list_aktif > 0) ? (total_item_di_list_aktif + ITEM_PER_HALAMAN - 1) / ITEM_PER_HALAMAN : 1;

        printf("   Urutan Saat Ini: %s (Halaman %d / %d dari total %d jurnal)\n", urutan_aktif_str, halaman_sekarang, total_halaman, total_item_di_list_aktif);
        printf("-----------------------------------------\n");

        printf("Pilihan Aksi:\n");
        printf("1. Tahun (Terbaru)         2. Tahun (Terlama)\n");
        printf("3. Popularitas (Terbanyak)  4. Popularitas (Tersedikit)\n");
        printf("5. Judul (A-Z)              6. Judul (Z-A)\n");
        printf("7. Lihat Abstrak Jurnal\n");
        if (total_item_di_list_aktif > 0) { // Hanya tampilkan navigasi jika ada item
            if (halaman_sekarang < total_halaman) {
                printf("8. Halaman Berikutnya (Next)\n");
            }
            if (halaman_sekarang > 1) {
                printf("9. Halaman Sebelumnya (Prev)\n");
            }
        }
        printf("0. Kembali ke Menu Utama\n");
        printf("Pilihan Urutan/Aksi: ");
        
        if (scanf("%d", &pilihan_menu_aksi) != 1) {
            pilihan_menu_aksi = -1; 
            int c;
            while ((c = getchar()) != '\n' && c != EOF); 
        }

        switch (pilihan_menu_aksi) {
            case 1: case 2: case 3: case 4: case 5: case 6:
                if (mode_tampilan_aktif != pilihan_menu_aksi) {
                    mode_tampilan_aktif = pilihan_menu_aksi; 
                    halaman_sekarang = 1; 
                }
                break;
            case 7: // Lihat Abstrak
                { 
                    if (total_item_di_list_aktif == 0) {
                        printf("Tidak ada jurnal untuk dilihat.\n");
                        tungguEnter();
                        break; 
                    }
                    
                    printf("Masukkan nomor jurnal (1-%d) yang tampil di halaman ini: ", 
                           (total_item_di_list_aktif - ((halaman_sekarang - 1) * ITEM_PER_HALAMAN) < ITEM_PER_HALAMAN) ? 
                           (total_item_di_list_aktif % ITEM_PER_HALAMAN == 0 ? ITEM_PER_HALAMAN : total_item_di_list_aktif % ITEM_PER_HALAMAN) : 
                           ITEM_PER_HALAMAN);
                    
                    int no_jurnal_di_halaman_input; 
                    
                    int c_buf; 
                    while ((c_buf = getchar()) != '\n' && c_buf != EOF); 

                    if (scanf("%d", &no_jurnal_di_halaman_input) == 1) {
                        // Validasi input nomor di halaman
                        int max_item_di_halaman_ini = total_item_di_list_aktif - ((halaman_sekarang - 1) * ITEM_PER_HALAMAN);
                        if (max_item_di_halaman_ini > ITEM_PER_HALAMAN) max_item_di_halaman_ini = ITEM_PER_HALAMAN;

                        if (no_jurnal_di_halaman_input < 1 || no_jurnal_di_halaman_input > max_item_di_halaman_ini ) {
                             printf("Nomor pilihan di halaman tidak valid.\n");
                        } else {
                            // Hitung nomor GLOBAL berdasarkan input nomor di halaman
                            int nomor_pilihan_global;
                            if (mode_tampilan_aktif == 1 || mode_tampilan_aktif == 4 || mode_tampilan_aktif == 6) { // Tampilan mundur
                                // Untuk tampilan mundur, item ke-1 di halaman adalah item global terbesar di halaman itu
                                int item_terakhir_global_di_halaman = total_item_di_list_aktif - ((halaman_sekarang - 1) * ITEM_PER_HALAMAN);
                                nomor_pilihan_global = item_terakhir_global_di_halaman - no_jurnal_di_halaman_input + 1;
                            } else { // Tampilan maju
                                nomor_pilihan_global = ((halaman_sekarang - 1) * ITEM_PER_HALAMAN) + no_jurnal_di_halaman_input;
                            }
                            
                            PaperNode* jurnal_pilihan = NULL;
                            if (mode_tampilan_aktif == 1 || mode_tampilan_aktif == 4 || mode_tampilan_aktif == 6) { 
                                jurnal_pilihan = pilihJurnalDariListReverse(tail_list_aktif, nomor_pilihan_global);
                            } else { 
                                jurnal_pilihan = pilihJurnalDariList(head_list_aktif, nomor_pilihan_global);
                            }

                            if (jurnal_pilihan != NULL) {
                                lihatAbstrakJurnal(jurnal_pilihan->data);
                            } else {
                                printf("Nomor jurnal (global %d) tidak ditemukan setelah konversi.\n", nomor_pilihan_global);
                            }
                        }
                    } else {
                         printf("Input nomor jurnal tidak valid.\n");
                         int c_err;
                         while ((c_err = getchar()) != '\n' && c_err != EOF); 
                    }
                    tungguEnter();
                }
                break; 
            case 8: 
                if (halaman_sekarang < total_halaman) {
                    halaman_sekarang++;
                } else {
                    printf("Anda sudah di halaman terakhir.\n");
                    tungguEnter();
                }
                break;
            case 9: 
                if (halaman_sekarang > 1) {
                    halaman_sekarang--;
                } else {
                    printf("Anda sudah di halaman pertama.\n");
                    tungguEnter();
                }
                break;
            case 0: 
                printf("Kembali ke menu utama...\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
                tungguEnter();
        } 
    } while (pilihan_menu_aksi != 0); 
}

void jalankanFiturPencarianJurnal(BSTNodeField* root_bst) {
    char input_fos[MAX_FIELD_STUDY];
    bersihkanLayar();
    printf("=========================================\n");
    printf("           PENCARIAN JURNAL\n");
    printf("=========================================\n");
    printf("Masukkan Field of Study yang dicari: ");
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    
    if (fgets(input_fos, MAX_FIELD_STUDY, stdin) != NULL) {
        input_fos[strcspn(input_fos, "\n")] = 0;
    } else {
        printf("Gagal membaca input.\n");
        tungguEnter();
        return;
    }

    BSTNodeField* node_ditemukan = cariBSTNodeField(root_bst, input_fos);

    if (node_ditemukan == NULL) {
        printf("Field of Study '%s' tidak ditemukan.\n", input_fos);
        tungguEnter();
    } else {
        kelolaOpsiUrutan(node_ditemukan);
    }
}