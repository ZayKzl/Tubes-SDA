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
    if (nomor_pilihan <= 0 || head == NULL) {
        return NULL;
    }
    PaperNode* current = head;
    int i = 1;
    while (current != NULL) {
        // printf("  DEBUG PILIH_MAJU: Iterasi %d, Target %d, Judul: %.30s\n", i, nomor_pilihan, current->data.judul);
        if (i == nomor_pilihan) {
            // printf("  DEBUG PILIH_MAJU: Jurnal DITEMUKAN!\n");
            return current;
        }
        current = current->next;
        i++;
    }
    // printf("  DEBUG PILIH_MAJU: Jurnal TIDAK ditemukan setelah %d iterasi.\n", i-1);
    return NULL; 
}

// ***IMPLEMENTASI BARU ATAU YANG PERLU DIPASTIKAN ADA***
PaperNode* pilihJurnalDariListReverse(PaperNode* tail, int nomor_pilihan) {
    if (nomor_pilihan <= 0 || tail == NULL) {
        // printf("DEBUG PILIH_REVERSE: Input tidak valid atau tail NULL (Nomor: %d, Tail: %p)\n", nomor_pilihan, (void*)tail);
        return NULL;
    }
    PaperNode* current = tail;
    int i = 1; // Nomor pilihan dimulai dari 1, sesuai dengan yang dilihat pengguna
    while (current != NULL) {
        // printf("  DEBUG PILIH_REVERSE: Iterasi %d, Target %d, Judul: %.30s\n", i, nomor_pilihan, current->data.judul);
        if (i == nomor_pilihan) {
            // printf("  DEBUG PILIH_REVERSE: Jurnal DITEMUKAN!\n");
            return current;
        }
        current = current->prev; // Bergerak mundur menggunakan pointer prev
        i++;
    }
    // printf("  DEBUG PILIH_REVERSE: Jurnal TIDAK ditemukan setelah %d iterasi.\n", i-1);
    return NULL; // Pilihan tidak valid atau di luar jangkauan
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

    int pilihan_menu;
    // 1=Tahun Terbaru (mundur dari year_list_tail)
    // 2=Tahun Terlama (maju dari year_list_head)
    // 3=Popularitas Terbanyak (maju dari incitations_list_head)
    // 4=Popularitas Tersedikit (mundur dari incitations_list_tail)
    // 5=Judul A-Z (maju dari title_list_head)
    // 6=Judul Z-A (mundur dari title_list_tail)
    int mode_tampilan_aktif = 1; // Default: Tahun Terbaru Dulu

    PaperNode* head_untuk_abstrak = NULL; // Untuk memilih jurnal saat maju
    PaperNode* tail_untuk_abstrak = NULL; // Untuk memilih jurnal saat mundur

    do {
        bersihkanLayar();
        printf("=========================================\n");
        printf("   Hasil Pencarian untuk: %s\n", node_bst_field->field_of_study);
        
        const char* urutan_aktif_str = "";
        head_untuk_abstrak = NULL; // Reset
        tail_untuk_abstrak = NULL; // Reset

        switch (mode_tampilan_aktif) {
            case 1: // Tahun Terbaru Dulu
                urutan_aktif_str = "Tahun Terbit (Terbaru Dulu)";
                printf("   Urutan Saat Ini: %s\n", urutan_aktif_str);
                printf("-----------------------------------------\n");
                tampilkanListPaperReverse(node_bst_field->year_list_tail, "Tahun (Terbaru)");
                tail_untuk_abstrak = node_bst_field->year_list_tail;
                break;
            case 2: // Tahun Terlama Dulu
                urutan_aktif_str = "Tahun Terbit (Terlama Dulu)";
                printf("   Urutan Saat Ini: %s\n", urutan_aktif_str);
                printf("-----------------------------------------\n");
                tampilkanListPaper(node_bst_field->year_list_head, "Tahun (Terlama)");
                head_untuk_abstrak = node_bst_field->year_list_head;
                break;
            case 3: // Popularitas Terbanyak
                urutan_aktif_str = "Popularitas (InCitations Terbanyak)";
                printf("   Urutan Saat Ini: %s\n", urutan_aktif_str);
                printf("-----------------------------------------\n");
                tampilkanListPaper(node_bst_field->incitations_list_head, "Incitations (Terbanyak)");
                head_untuk_abstrak = node_bst_field->incitations_list_head;
                break;
            case 4: // Popularitas Tersedikit
                urutan_aktif_str = "Popularitas (InCitations Tersedikit)";
                printf("   Urutan Saat Ini: %s\n", urutan_aktif_str);
                printf("-----------------------------------------\n");
                tampilkanListPaperReverse(node_bst_field->incitations_list_tail, "Incitations (Tersedikit)");
                tail_untuk_abstrak = node_bst_field->incitations_list_tail;
                break;
            case 5: // Judul A-Z
                urutan_aktif_str = "Judul (A-Z)";
                printf("   Urutan Saat Ini: %s\n", urutan_aktif_str);
                printf("-----------------------------------------\n");
                tampilkanListPaper(node_bst_field->title_list_head, "Judul (A-Z)");
                head_untuk_abstrak = node_bst_field->title_list_head;
                break;
            case 6: // Judul Z-A
                urutan_aktif_str = "Judul (Z-A)";
                printf("   Urutan Saat Ini: %s\n", urutan_aktif_str);
                printf("-----------------------------------------\n");
                tampilkanListPaperReverse(node_bst_field->title_list_tail, "Judul (Z-A)");
                tail_untuk_abstrak = node_bst_field->title_list_tail;
                break;
        }

        printf("-----------------------------------------\n");
        printf("Pilihan Aksi:\n");
        printf("1. Tahun Terbit (Terbaru Dulu)         2. Tahun Terbit (Terlama Dulu)\n");
        printf("3. Popularitas (Terbanyak Dulu)        4. Popularitas (Tersedikit Dulu)\n");
        printf("5. Judul (A-Z)                         6. Judul (Z-A)\n");
        printf("7. Lihat Abstrak Jurnal\n");
        printf("0. Kembali ke Menu Utama\n");
        printf("Pilihan Urutan/Aksi: ");
        
        if (scanf("%d", &pilihan_menu) != 1) {
            pilihan_menu = -1; // Input tidak valid
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // Bersihkan buffer
        }

        switch (pilihan_menu) {
            case 1: mode_tampilan_aktif = 1; break;
            case 2: mode_tampilan_aktif = 2; break;
            case 3: mode_tampilan_aktif = 3; break;
            case 4: mode_tampilan_aktif = 4; break;
            case 5: mode_tampilan_aktif = 5; break;
            case 6: mode_tampilan_aktif = 6; break;
            case 7: // Lihat Abstrak
                {
                    // Cek apakah list yang sesuai (head atau tail) memang ada isinya
                    if ((mode_tampilan_aktif == 1 || mode_tampilan_aktif == 4 || mode_tampilan_aktif == 6) && tail_untuk_abstrak == NULL) {
                        printf("List untuk tampilan mundur kosong atau belum dipilih.\n");
                        tungguEnter();
                        break;
                    }
                    if ((mode_tampilan_aktif == 2 || mode_tampilan_aktif == 3 || mode_tampilan_aktif == 5) && head_untuk_abstrak == NULL) {
                        printf("List untuk tampilan maju kosong atau belum dipilih.\n");
                        tungguEnter();
                        break;
                    }

                    printf("Masukkan nomor jurnal yang ingin dilihat abstraknya: ");
                    int no_jurnal;
                    if (scanf("%d", &no_jurnal) == 1) {
                        PaperNode* jurnal_pilihan = NULL;
                        // Tentukan cara memilih berdasarkan mode urutan aktif
                        if (mode_tampilan_aktif == 1 || mode_tampilan_aktif == 4 || mode_tampilan_aktif == 6) { // Tampilan mundur
                            // PERBAIKAN DI SINI:
                            jurnal_pilihan = pilihJurnalDariListReverse(tail_untuk_abstrak, no_jurnal);
                        } else { // Tampilan maju (mode 2, 3, 5)
                            jurnal_pilihan = pilihJurnalDariList(head_untuk_abstrak, no_jurnal);
                        }

                        if (jurnal_pilihan != NULL) {
                            lihatAbstrakJurnal(jurnal_pilihan->data);
                        } else {
                            printf("Nomor jurnal tidak valid untuk urutan saat ini.\n");
                        }
                    } else {
                        printf("Input nomor tidak valid.\n");
                        int c_err;
                        while ((c_err = getchar()) != '\n' && c_err != EOF); 
                    }
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
    } while (pilihan_menu != 0);
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