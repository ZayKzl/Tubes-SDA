#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Untuk system("cls") atau system("clear") jika dipakai
#include "../include/fitur_aplikasi.h"
#include "../include/bst_field_study.h"   // Untuk cariBSTNodeField
#include "../include/linked_list_paper.h" // Untuk tampilkanListPaper

void bersihkanLayar() {
    // Gunakan system("cls") untuk Windows, system("clear") untuk Linux/macOS
    // Atau cetak banyak baris baru jika ingin portabilitas tanpa panggilan sistem
    // system("cls"); 
    // system("clear");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); // Cara sederhana
}

void tungguEnter() {
    printf("\nTekan Enter untuk melanjutkan...");
    // Mengosongkan buffer input sebelum getchar()
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar(); // Menunggu Enter
}

void tampilkanMenuUtama() {
    bersihkanLayar();
    printf("=========================================\n");
    printf("      APLIKASI JURNAL ILMIAH SDA\n");
    printf("=========================================\n");
    printf(" Stakeholder: Civitas Akademika [cite: 1]\n");
    printf("-----------------------------------------\n");
    printf("Menu:\n");
    printf("1. Pencarian Jurnal (berdasarkan Field of Study) [cite: 1]\n");
    printf("0. Keluar\n");
    printf("-----------------------------------------\n");
    printf("Pilihan Anda: ");
}

PaperNode* pilihJurnalDariList(PaperNode* head, int nomor_pilihan) {
    if (nomor_pilihan <= 0) return NULL;
    PaperNode* current = head;
    int i = 1;
    while (current != NULL) {
        if (i == nomor_pilihan) {
            return current;
        }
        current = current->next;
        i++;
    }
    return NULL; // Pilihan tidak valid
}

void lihatAbstrakJurnal(JurnalData data_jurnal) {
    bersihkanLayar();
    printf("=========================================\n");
    printf("             DETAIL & ABSTRAK JURNAL\n");
    printf("=========================================\n");
    printf("Judul        : %s\n", data_jurnal.judul);
    printf("Penulis      : %s\n", data_jurnal.nama_penulis);
    printf("Tahun Terbit : %d\n", data_jurnal.tahun_terbit);
    printf("Field of Study: %s\n", data_jurnal.field_of_study);
    printf("InCitations  : %d\n", data_jurnal.jumlah_incitations);
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

    int pilihan_urut;
    PaperNode* selected_list_head = node_bst_field->list_by_year_head; // Default
    const char* urutan_aktif = "Tahun Terbit (Terbaru Dulu)";

    do {
        bersihkanLayar();
        printf("=========================================\n");
        printf("   Hasil Pencarian untuk: %s\n", node_bst_field->field_of_study);
        printf("   Urutan Saat Ini: %s\n", urutan_aktif);
        printf("-----------------------------------------\n");
        tampilkanListPaper(selected_list_head);
        printf("-----------------------------------------\n");
        printf("Pilihan Aksi:\n");
        printf("1. Urutkan berdasarkan Tahun Terbit (Terbaru Dulu)\n");
        printf("2. Urutkan berdasarkan Tahun Terbit (Terlama Dulu)\n");
        printf("3. Urutkan berdasarkan Popularitas (Jumlah InCitations Terbanyak)\n");
        printf("4. Urutkan berdasarkan Judul (A-Z)\n");
        printf("5. Lihat Abstrak Jurnal\n");
        printf("0. Kembali ke Menu Utama\n");
        printf("Pilihan Urutan/Aksi: ");
        
        if (scanf("%d", &pilihan_urut) != 1) {
            pilihan_urut = -1; // Input tidak valid
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // Bersihkan buffer
        }


        switch (pilihan_urut) {
            case 1:
                selected_list_head = node_bst_field->list_by_year_head;
                urutan_aktif = "Tahun Terbit (Terbaru Dulu)";
                break;
            case 2:
                selected_list_head = node_bst_field->list_by_year_asc_head;
                urutan_aktif = "Tahun Terbit (Terlama Dulu)";
                break;
            case 3:
                selected_list_head = node_bst_field->list_by_incitations_head;
                urutan_aktif = "Popularitas (InCitations Terbanyak)";
                break;
            case 4:
                selected_list_head = node_bst_field->list_by_title_head;
                urutan_aktif = "Judul (A-Z)";
                break;
            case 5: // Lihat Abstrak
                if (selected_list_head == NULL) {
                    printf("Tidak ada jurnal untuk dilihat abstraknya.\n");
                } else {
                    printf("Masukkan nomor jurnal yang ingin dilihat abstraknya: ");
                    int no_jurnal;
                    if (scanf("%d", &no_jurnal) == 1) {
                        PaperNode* jurnal_pilihan = pilihJurnalDariList(selected_list_head, no_jurnal);
                        if (jurnal_pilihan != NULL) {
                            lihatAbstrakJurnal(jurnal_pilihan->data);
                        } else {
                            printf("Nomor jurnal tidak valid.\n");
                        }
                    } else {
                        printf("Input nomor tidak valid.\n");
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF); // Bersihkan buffer
                    }
                }
                tungguEnter(); // Beri jeda setelah lihat abstrak atau pesan error
                break;
            case 0:
                printf("Kembali ke menu utama...\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
                tungguEnter();
        }
    } while (pilihan_urut != 0);
}


void jalankanFiturPencarianJurnal(BSTNodeField* root_bst) {
    char input_fos[MAX_FIELD_STUDY];
    bersihkanLayar();
    printf("=========================================\n");
    printf("           PENCARIAN JURNAL\n");
    printf("=========================================\n");
    printf("Masukkan Field of Study yang dicari: ");
    
    // Menggunakan fgets untuk input string yang aman
    // Bersihkan buffer dulu jika ada sisa newline dari input sebelumnya
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    
    if (fgets(input_fos, MAX_FIELD_STUDY, stdin) != NULL) {
        // Hapus newline karakter jika ada dari fgets
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
        // Langsung panggil kelolaOpsiUrutan, karena defaultnya sudah urut tahun
        kelolaOpsiUrutan(node_ditemukan);
    }
}