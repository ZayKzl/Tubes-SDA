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

void tampilkanListPaperFilteredByAuthorPrefix(PaperNode* head, const char* prefix) {
    if (head == NULL) {
        printf("   (List paper kosong)\n");
        return;
    }
    PaperNode* current = head;
    int i = 1;
    int prefix_len = strlen(prefix);
    int found = 0;
    while (current != NULL) {
        if (strncasecmp(current->data.nama_penulis, prefix, prefix_len) == 0) {
            found = 1;
            printf("   %d. Penulis : %s\n", i, current->data.nama_penulis);
            printf("      Judul    : %s\n", current->data.judul);
            printf("      Tahun    : %d\n", current->data.tahun_terbit);
            printf("      InCitations: %d\n", current->data.jumlah_incitations);
            printf("      --------------------------------------------------\n");
            i++;
        }
        current = current->next;
    }
    if (!found) {
        printf("   Tidak ditemukan penulis dengan prefix '%s'.\n", prefix);
    }
}

// Fungsi helper baru untuk memilih jurnal dari list yang ditampilkan terbalik
// Fungsi ini harus ditambahkan ke fitur_aplikasi.c atau linked_list_paper.c
PaperNode* pilihJurnalDariListReverse(PaperNode* tail, int nomor_pilihan) {
    if (nomor_pilihan <= 0) return NULL;
    PaperNode* current = tail;
    int i = 1;
    while (current != NULL) {
        if (i == nomor_pilihan) {
            return current;
        }
        current = current->prev; // Traversal mundur
        i++;
    }
    return NULL; // Pilihan tidak valid
}


// --- FUNGSI KELOLA OPSI URUTAN YANG SUDAH DIREVISI ---
void kelolaOpsiUrutan(BSTNodeField* node_bst_field) {
    if (node_bst_field == NULL) {
        printf("Data field of study tidak ditemukan.\n");
        tungguEnter();
        return;
    }

    int pilihan_menu;
    
    // Gunakan enum atau int untuk melacak mode urutan saat ini.
    // 1=Tahun Terbaru, 2=Tahun Terlama, 3=Popularitas, 4=Judul, 6=Penulis
    int mode_urutan_aktif = 1; // Default: Tahun Terbaru Dulu

    // Pointer ke list SLL yang aktif (untuk non-tahun)
    PaperNode* active_sll_head = NULL; 

    do {
        bersihkanLayar();
        printf("=========================================\n");
        printf("   Hasil Pencarian untuk: %s\n", node_bst_field->field_of_study);
        
        // Tentukan string urutan aktif dan tampilkan list yang sesuai
        const char* urutan_aktif_str;
        switch (mode_urutan_aktif) {
            case 1:
                urutan_aktif_str = "Tahun Terbit (Terbaru Dulu)";
                printf("   Urutan Saat Ini: %s\n", urutan_aktif_str);
                printf("-----------------------------------------\n");
                tampilkanListPaperReverse(node_bst_field->year_list_tail);
                break;
            case 2:
                urutan_aktif_str = "Tahun Terbit (Terlama Dulu)";
                printf("   Urutan Saat Ini: %s\n", urutan_aktif_str);
                printf("-----------------------------------------\n");
                tampilkanListPaper(node_bst_field->year_list_head);
                break;
            case 3:
                urutan_aktif_str = "Popularitas (InCitations Terbanyak)";
                active_sll_head = node_bst_field->list_by_incitations_head;
                printf("   Urutan Saat Ini: %s\n", urutan_aktif_str);
                printf("-----------------------------------------\n");
                tampilkanListPaper(active_sll_head);
                break;
            case 4:
                urutan_aktif_str = "Judul (A-Z)";
                active_sll_head = node_bst_field->list_by_title_head;
                printf("   Urutan Saat Ini: %s\n", urutan_aktif_str);
                printf("-----------------------------------------\n");
                tampilkanListPaper(active_sll_head);
                break;
            case 6:
                urutan_aktif_str = "Penulis (A-Z)";
                active_sll_head = node_bst_field->list_by_author_head;
                printf("   Urutan Saat Ini: %s\n", urutan_aktif_str);
                printf("-----------------------------------------\n");
                // Untuk kasus penulis, kita mungkin ingin menampilkan list penuh setelah filter
                tampilkanListPaper(active_sll_head);
                break;
        }

        printf("-----------------------------------------\n");
        printf("Pilihan Aksi:\n");
        printf("1. Urutkan berdasarkan Tahun Terbit (Terbaru Dulu)\n");
        printf("2. Urutkan berdasarkan Tahun Terbit (Terlama Dulu)\n");
        printf("3. Urutkan berdasarkan Popularitas (Jumlah InCitations Terbanyak)\n");
        printf("4. Urutkan berdasarkan Judul (A-Z)\n");
        printf("5. Lihat Abstrak Jurnal\n");
        printf("6. Cari berdasarkan Nama Penulis\n");
        printf("0. Kembali ke Menu Utama\n");
        printf("Pilihan Urutan/Aksi: ");
        
        if (scanf("%d", &pilihan_menu) != 1) {
            pilihan_menu = -1;
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        switch (pilihan_menu) {
            case 1: mode_urutan_aktif = 1; break;
            case 2: mode_urutan_aktif = 2; break;
            case 3: mode_urutan_aktif = 3; break;
            case 4: mode_urutan_aktif = 4; break;
            case 6: // Logika filter penulis (tidak mengubah urutan global)
                {
                    char prefix[MAX_PENULIS];
                    bersihkanLayar();
                    printf("Masukkan prefix nama penulis untuk difilter: ");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    if (fgets(prefix, MAX_PENULIS, stdin) != NULL) {
                        prefix[strcspn(prefix, "\n")] = 0;
                        tampilkanListPaperFilteredByAuthorPrefix(node_bst_field->list_by_author_head, prefix);
                    }
                    tungguEnter();
                    // Setelah filter, mode urutan tetap sama seperti sebelumnya
                }
                break;
            case 5: // Lihat Abstrak
                {
                    printf("Masukkan nomor jurnal yang ingin dilihat abstraknya: ");
                    int no_jurnal;
                    if (scanf("%d", &no_jurnal) == 1) {
                        PaperNode* jurnal_pilihan = NULL;
                        // Tentukan cara memilih berdasarkan mode urutan aktif
                        if (mode_urutan_aktif == 1) { // Terbaru dulu (mundur)
                            jurnal_pilihan = pilihJurnalDariListReverse(node_bst_field->year_list_tail, no_jurnal);
                        } else if (mode_urutan_aktif == 2) { // Terlama dulu (maju)
                            jurnal_pilihan = pilihJurnalDariList(node_bst_field->year_list_head, no_jurnal);
                        } else { // Urutan SLL lainnya (maju)
                            jurnal_pilihan = pilihJurnalDariList(active_sll_head, no_jurnal);
                        }

                        if (jurnal_pilihan != NULL) {
                            lihatAbstrakJurnal(jurnal_pilihan->data);
                        } else {
                            printf("Nomor jurnal tidak valid.\n");
                        }
                    } else {
                        printf("Input nomor tidak valid.\n");
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);
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