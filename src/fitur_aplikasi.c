 #include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "../include/fitur_aplikasi.h"
#include "../include/bst_field_study.h"   
#include "../include/linked_list_paper.h" 
#include "../include/stack_search_history.h"

void bersihkanLayar() {
    // Gunakan system("cls") untuk Windows, system("clear") untuk Linux/macOS
    // Atau cetak banyak baris baru jika ingin portabilitas tanpa panggilan sistem
    // system("cls"); 
    // system("clear");
    printf("\n\n"); // Cara sederhana
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
    printf(" Stakeholder: Civitas Akademika\n");
    printf("-----------------------------------------\n");
    printf("Menu:\n");
    printf("1. Tampilkan Field of Study\n");
    printf("2. Pencarian Jurnal (berdasarkan Field of Study)\n");
    printf("3. Lihat Riwayat Pencarian\n");
    printf("0. Keluar\n");
    printf("-----------------------------------------\n");
    printf("Pilihan Anda: ");
}

void tampilkanSemuaFieldOfStudy(BSTNodeField* root) {
    if (root == NULL) {
        printf("Tidak ada data Field of Study.\n");
        tungguEnter();
        return;
    }

    printf("=========================================\n");
    printf("       DAFTAR FIELD OF STUDY\n");
    printf("=========================================\n");
    tampilkanBSTInOrder(root);
    tungguEnter();
}


void lihatAbstrakJurnal(JurnalData data_jurnal) {
    bersihkanLayar();
    printf("=========================================\n");
    printf("        DETAIL & ABSTRAK JURNAL\n");
    printf("=========================================\n");
    printf("ID Paper       : %s\n", data_jurnal.id_paper);
    printf("Judul          : %s\n", data_jurnal.judul);
    printf("Penulis        : %s\n", data_jurnal.nama_penulis);
    printf("Tahun Terbit   : %d\n", data_jurnal.tahun_terbit);
    printf("Field of Study : %s\n", data_jurnal.field_of_study);
    printf("InCitations    : %d\n", data_jurnal.jumlah_incitations);
    printf("-----------------------------------------\n");
    printf("Abstrak        :\n%s\n", data_jurnal.abstrak);
    printf("=========================================\n");
}


#include <ctype.h> // for tolower

typedef struct AuthorPaperNode {
    char author_name[MAX_PENULIS];
    PaperNode** papers;
    int paper_count;
    int paper_capacity;
    struct AuthorPaperNode* next;
} AuthorPaperNode;

void tambahPaperKeAuthor(AuthorPaperNode* author_node, PaperNode* paper) {
    if (author_node->paper_count == author_node->paper_capacity) {
        int new_capacity = (author_node->paper_capacity == 0) ? 4 : author_node->paper_capacity * 2;
        PaperNode** new_array = realloc(author_node->papers, new_capacity * sizeof(PaperNode*));
        if (new_array == NULL) {
            printf("Gagal mengalokasikan memori untuk paper author.\n");
            return;
        }
        author_node->papers = new_array;
        author_node->paper_capacity = new_capacity;
    }
    author_node->papers[author_node->paper_count++] = paper;
}

AuthorPaperNode* cariAtauTambahAuthor(AuthorPaperNode** head, const char* author_name) {
    AuthorPaperNode* current = *head;
    while (current != NULL) {
        if (strcmp(current->author_name, author_name) == 0) {
            return current;
        }
        current = current->next;
    }
    // Not found, add new
    AuthorPaperNode* new_node = malloc(sizeof(AuthorPaperNode));
    if (new_node == NULL) {
        printf("Gagal mengalokasikan memori untuk author baru.\n");
        return NULL;
    }
    strcpy(new_node->author_name, author_name);
    new_node->papers = NULL;
    new_node->paper_count = 0;
    new_node->paper_capacity = 0;
    new_node->next = *head;
    *head = new_node;
    return new_node;
}

void hapusDaftarAuthor(AuthorPaperNode* head) {
    AuthorPaperNode* current = head;
    while (current != NULL) {
        AuthorPaperNode* next = current->next;
        free(current->papers);
        free(current);
        current = next;
    }
}

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int stringStartsWithIgnoreCase(const char* str, const char* prefix) {
    while (*prefix) {
        if (tolower((unsigned char)*prefix) != tolower((unsigned char)*str)) {
            return 0;
        }
        prefix++;
        str++;
    }
    return 1;
}

void traverseBSTAndCollectAuthors(BSTNodeField* root, const char* search_str, AuthorPaperNode** author_list_head) {
    if (root == NULL) return;

    traverseBSTAndCollectAuthors(root->left_child, search_str, author_list_head);

    // Traverse year_list_head to get all papers in this field
    PaperNode* current_paper = root->year_list_head;
    while (current_paper != NULL) {
        // Parse multiple authors separated by commas or semicolons
        char authors_copy[MAX_PENULIS];
        strncpy(authors_copy, current_paper->data.nama_penulis, MAX_PENULIS);
        authors_copy[MAX_PENULIS - 1] = '\0';

        char* token = strtok(authors_copy, ",;");
        while (token != NULL) {
            // Trim leading spaces
            while (*token == ' ') token++;

            if (stringStartsWithIgnoreCase(token, search_str)) {
                AuthorPaperNode* author_node = cariAtauTambahAuthor(author_list_head, token);
                if (author_node != NULL) {
                    tambahPaperKeAuthor(author_node, current_paper);
                }
            }
            token = strtok(NULL, ",;");
        }
        current_paper = current_paper->next;
    }

    traverseBSTAndCollectAuthors(root->right_child, search_str, author_list_head);
}


int tampilkanAuthorDanPapers(AuthorPaperNode* author_list_head, int halaman_sekarang, int item_per_hal) {
    int total_papers = 0;
    int start_index = (halaman_sekarang - 1) * item_per_hal;
    int end_index = start_index + item_per_hal;

    // Count total papers
    AuthorPaperNode* current_author = author_list_head;
    while (current_author != NULL) {
        total_papers += current_author->paper_count;
        current_author = current_author->next;
    }

    if (total_papers == 0) {
        printf("Tidak ada author dengan kriteria tersebut.\n");
        return 0;
    }

    int paper_index = 0;
    current_author = author_list_head;
    int printed_papers = 0;

    while (current_author != NULL && printed_papers < item_per_hal) {
        printf("%s\n", current_author->author_name);
        for (int i = 0; i < current_author->paper_count; i++) {
            if (paper_index >= start_index && paper_index < end_index) {
                printf("%d. [%s] ", paper_index + 1, current_author->papers[i]->data.judul);
                printed_papers++;
            }
            paper_index++;
            if (printed_papers >= item_per_hal) break;
        }
        printf("\n");
        current_author = current_author->next;
    }

    return total_papers;
}

PaperNode* cariPaperDariNomor(AuthorPaperNode* author_list_head, int nomor) {
    int current_index = 1;
    AuthorPaperNode* current_author = author_list_head;
    while (current_author != NULL) {
        for (int i = 0; i < current_author->paper_count; i++) {
            if (current_index == nomor) {
                return current_author->papers[i];
            }
            current_index++;
        }
        current_author = current_author->next;
    }
    return NULL;
}

void kelolaOpsiUrutanAuthor(BSTNodeField* root_bst_field) {
    if (root_bst_field == NULL) {
        printf("Data field of study tidak ditemukan.\n");
        tungguEnter();
        return;
    }

    char input_str[MAX_PENULIS];
    int pilihan_menu_aksi;
    int halaman_sekarang = 1;
    const int ITEM_PER_HALAMAN = 20;
    int total_papers = 0;

    AuthorPaperNode* author_list_head = NULL;

    while (1) {
        bersihkanLayar();
        printf("=========================================\n");
        printf("   Fitur Pencarian Berdasarkan Author\n");
        printf("=========================================\n");
        printf("Masukkan nama awal atau sebagian nama author (0 untuk kembali): ");

        // Clear input buffer before reading
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (fgets(input_str, sizeof(input_str), stdin) == NULL) {
            printf("Gagal membaca input.\n");
            tungguEnter();
            continue;
        }
        // Remove trailing newline
        input_str[strcspn(input_str, "\n")] = 0;

        if (strcmp(input_str, "0") == 0) {
            break;
        }

        // Build author list
        hapusDaftarAuthor(author_list_head);
        author_list_head = NULL;
        traverseBSTAndCollectAuthors(root_bst_field, input_str, &author_list_head);

        if (author_list_head == NULL) {
            printf("Tidak ada author dengan nama yang cocok '%s'.\n", input_str);
            tungguEnter();
            continue;
        }

        halaman_sekarang = 1;
        do {
            bersihkanLayar();
            printf("=========================================\n");
            printf("   Author dengan nama cocok '%s'\n", input_str);
            printf("=========================================\n");

            total_papers = tampilkanAuthorDanPapers(author_list_head, halaman_sekarang, ITEM_PER_HALAMAN);

            int total_halaman = (total_papers > 0) ? (total_papers + ITEM_PER_HALAMAN - 1) / ITEM_PER_HALAMAN : 1;

            printf("        Halaman %d / %d dari total %d paper\n", halaman_sekarang, total_halaman, total_papers);
            printf("      --------------------------------------------------\n\n");

            printf("Pilihan Aksi:\n");
            printf("7. Lihat Abstrak Jurnal\n");
            if (halaman_sekarang < total_halaman) {
                printf("8. Halaman Berikutnya (Next)\n");
            }
            if (halaman_sekarang > 1) {
                printf("9. Halaman Sebelumnya (Prev)\n");
            }
            printf("0. Kembali ke Menu Sebelumnya\n");
            printf("\nPilihan Urutan/Aksi: ");

            if (scanf("%d", &pilihan_menu_aksi) != 1) {
                pilihan_menu_aksi = -1;
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }

            switch (pilihan_menu_aksi) {
                case 7: {
                    if (total_papers == 0) {
                        printf("Tidak ada jurnal untuk dilihat.\n");
                        tungguEnter();
                        break;
                    }
                    printf("Masukkan nomor jurnal (1-%d) yang tampil di halaman ini: ", 
                        (total_papers - ((halaman_sekarang - 1) * ITEM_PER_HALAMAN) < ITEM_PER_HALAMAN) ? 
                        (total_papers % ITEM_PER_HALAMAN == 0 ? ITEM_PER_HALAMAN : total_papers % ITEM_PER_HALAMAN) : 
                        ITEM_PER_HALAMAN);

                    int no_jurnal_di_halaman_input;
                    int c_buf;
                    while ((c_buf = getchar()) != '\n' && c_buf != EOF);

                    if (scanf("%d", &no_jurnal_di_halaman_input) == 1) {
                        int max_item_di_halaman_ini = total_papers - ((halaman_sekarang - 1) * ITEM_PER_HALAMAN);
                        if (max_item_di_halaman_ini > ITEM_PER_HALAMAN) max_item_di_halaman_ini = ITEM_PER_HALAMAN;

                        if (no_jurnal_di_halaman_input < 1 || no_jurnal_di_halaman_input > max_item_di_halaman_ini) {
                            printf("Nomor pilihan di halaman tidak valid.\n");
                        } else {
                            int nomor_pilihan_global = ((halaman_sekarang - 1) * ITEM_PER_HALAMAN) + no_jurnal_di_halaman_input;
                            PaperNode* jurnal_pilihan = cariPaperDariNomor(author_list_head, nomor_pilihan_global);
                            if (jurnal_pilihan != NULL) {
                                lihatAbstrakJurnal(jurnal_pilihan->data);
                            } else {
                                printf("Nomor jurnal (global %d) tidak ditemukan.\n", nomor_pilihan_global);
                            }
                        }
                    } else {
                        printf("Input nomor jurnal tidak valid.\n");
                        int c_err;
                        while ((c_err = getchar()) != '\n' && c_err != EOF);
                    }
                    tungguEnter();
                    break;
                }
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
                    break;
                default:
                    printf("Pilihan tidak valid!\n");
                    tungguEnter();
            }
        } while (pilihan_menu_aksi != 0);

        hapusDaftarAuthor(author_list_head);
        author_list_head = NULL;
    }
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
                total_item_di_list_aktif = tampilkanListPaperReverse(tail_list_aktif, "Tahun (Terbaru)", halaman_sekarang, ITEM_PER_HALAMAN);
                break;
            case 2: 
                urutan_aktif_str = "Tahun Terbit (Terlama Dulu)";
                head_list_aktif = node_bst_field->year_list_head;
                tail_list_aktif = NULL;
                total_item_di_list_aktif = tampilkanListPaper(head_list_aktif, "Tahun (Terlama)", halaman_sekarang, ITEM_PER_HALAMAN);
                break;
            case 3: 
                urutan_aktif_str = "Popularitas (InCitations Terbanyak)";
                head_list_aktif = node_bst_field->incitations_list_head;
                tail_list_aktif = NULL;
                total_item_di_list_aktif = tampilkanListPaper(head_list_aktif, "Incitations (Terbanyak)", halaman_sekarang, ITEM_PER_HALAMAN);
                break;
            case 4: 
                urutan_aktif_str = "Popularitas (InCitations Tersedikit)";
                tail_list_aktif = node_bst_field->incitations_list_tail;
                head_list_aktif = NULL;
                total_item_di_list_aktif = tampilkanListPaperReverse(tail_list_aktif, "Incitations (Tersedikit)", halaman_sekarang, ITEM_PER_HALAMAN);
                break;
            case 5: 
                urutan_aktif_str = "Judul (A-Z)";
                head_list_aktif = node_bst_field->title_list_head;
                tail_list_aktif = NULL;
                total_item_di_list_aktif = tampilkanListPaper(head_list_aktif, "Judul (A-Z)", halaman_sekarang, ITEM_PER_HALAMAN);
                break;
            case 6: 
                urutan_aktif_str = "Judul (Z-A)";
                tail_list_aktif = node_bst_field->title_list_tail;
                head_list_aktif = NULL;
                total_item_di_list_aktif = tampilkanListPaperReverse(tail_list_aktif, "Judul (Z-A)", halaman_sekarang, ITEM_PER_HALAMAN);
                break;
            case 8: // New feature for author-based display
                kelolaOpsiUrutanAuthor(node_bst_field);
                break;
        }
        
        if (pilihan_menu_aksi == 8) {
            pilihan_menu_aksi = 0; // After returning from author feature, go back to main menu
            continue;
        }

        int total_halaman = (total_item_di_list_aktif > 0) ? (total_item_di_list_aktif + ITEM_PER_HALAMAN - 1) / ITEM_PER_HALAMAN : 1;

        printf("        Urutan Saat Ini: %s \n", urutan_aktif_str);
        printf("        Halaman %d / %d dari total %d jurnal\n", halaman_sekarang, total_halaman, total_item_di_list_aktif);
        printf("      --------------------------------------------------\n\n");

        printf("Pilihan Aksi:\n");
        printf("1. Tahun (Terbaru)               2. Tahun (Terlama)\n");
        printf("3. Popularitas (Terbanyak)       4. Popularitas (Tersedikit)\n");
        printf("5. Judul (A-Z)                   6. Judul (Z-A)\n");
        printf("7. Lihat Abstrak Jurnal\n");
        printf("8. Tampilkan Author dan Paper\n");
        if (total_item_di_list_aktif > 0) { // Hanya tampilkan navigasi jika ada item
            if (halaman_sekarang < total_halaman) {
                printf("9. Halaman Berikutnya (Next)\n");
            }
            if (halaman_sekarang > 1) {
                printf("10. Halaman Sebelumnya (Prev)\n");
            }
        }
        printf("0. Kembali ke Menu Utama\n");
        printf("\nPilihan Urutan/Aksi: ");
        
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
            case 8: // New feature for author-based display
                kelolaOpsiUrutanAuthor(node_bst_field);
                break;
            case 9: 
                if (halaman_sekarang < total_halaman) {
                    halaman_sekarang++;
                } else {
                    printf("Anda sudah di halaman terakhir.\n");
                    tungguEnter();
                }
                break;
            case 10: 
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

void jalankanFiturPencarianJurnal(BSTNodeField* root_bst, SearchHistoryStack *history) {
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

    // Push query ke riwayat pencarian
    pushSearchHistory(history, input_fos);

    BSTNodeField* node_ditemukan = cariBSTNodeField(root_bst, input_fos);

    if (node_ditemukan == NULL) {
        printf("Field of Study '%s' tidak ditemukan.\n", input_fos);
        tungguEnter();
    } else {
        kelolaOpsiUrutan(node_ditemukan);
    }
}