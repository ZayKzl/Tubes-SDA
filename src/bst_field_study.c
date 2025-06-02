#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "bst_field_study.h"   // Berisi deklarasi fungsi dan include "structs.h"
#include "linked_list_paper.h" // Diperlukan untuk memanggil fungsi list paper

// --- Fungsi untuk Membuat Node BST Field of Study Baru ---
BSTNodeField* buatBSTNodeField(const char* field_of_study) {
    BSTNodeField* node_baru = (BSTNodeField*)malloc(sizeof(BSTNodeField));
    if (node_baru == NULL) {
        perror("Gagal alokasi memori untuk BSTNodeField baru");
        return NULL;
    }
    strncpy(node_baru->field_of_study, field_of_study, MAX_FIELD_STUDY - 1);
    node_baru->field_of_study[MAX_FIELD_STUDY - 1] = '\0'; // Pastikan null-terminated

    node_baru->list_by_year_head = NULL;
    node_baru->list_by_incitations_head = NULL;
    node_baru->list_by_title_head = NULL;
    node_baru->list_by_year_asc_head = NULL; // Inisialisasi head list baru
    
    node_baru->left_child = NULL;
    node_baru->right_child = NULL;
    return node_baru;
}

// --- Fungsi untuk Menyisipkan Node ke BST Field of Study ---
// (Implementasi BST insert standar, berdasarkan field_of_study)
BSTNodeField* sisipkanBSTNodeField(BSTNodeField* root, const char* field_of_study) {
    if (root == NULL) {
        return buatBSTNodeField(field_of_study);
    }

    int cmp = strcasecmp(field_of_study, root->field_of_study);

    if (cmp < 0) {
        root->left_child = sisipkanBSTNodeField(root->left_child, field_of_study);
    } else if (cmp > 0) {
        root->right_child = sisipkanBSTNodeField(root->right_child, field_of_study);
    }
    // Jika cmp == 0, field_of_study sudah ada, tidak perlu disisipkan lagi (node-nya sudah ada)
    return root;
}

// --- Fungsi untuk Mencari Node di BST Field of Study ---
BSTNodeField* cariBSTNodeField(BSTNodeField* root, const char* field_of_study) {
    if (root == NULL || strcmp(field_of_study, root->field_of_study) == 0) {
        return root;
    }
    if (strcmp(field_of_study, root->field_of_study) < 0) {
        return cariBSTNodeField(root->left_child, field_of_study);
    } else {
        return cariBSTNodeField(root->right_child, field_of_study);
    }
}

// --- Fungsi untuk Menambahkan JurnalData ke BSTNodeField yang Tepat ---
void tambahkanJurnalKeBST(BSTNodeField** root_bst_ptr, JurnalData data_jurnal) {
    if (root_bst_ptr == NULL) return; // Guard clause

    BSTNodeField* target_node_bst = cariBSTNodeField(*root_bst_ptr, data_jurnal.field_of_study);

    if (target_node_bst == NULL) {
        // Field of study belum ada di BST, buat node BST baru dan sisipkan
        // Karena sisipkanBSTNodeField mengembalikan root baru, kita perlu update root_bst_ptr
        *root_bst_ptr = sisipkanBSTNodeField(*root_bst_ptr, data_jurnal.field_of_study);
        // Setelah disisipkan, cari lagi node yang baru dibuat itu
        target_node_bst = cariBSTNodeField(*root_bst_ptr, data_jurnal.field_of_study);
        if (target_node_bst == NULL) {
            // Seharusnya tidak terjadi jika sisipkanBSTNodeField dan buatBSTNodeField berhasil
            fprintf(stderr, "Error: Gagal membuat atau menemukan node BST untuk %s\n", data_jurnal.field_of_study);
            return;
        }
    }

    // Sekarang target_node_bst menunjuk ke node BST yang benar (lama atau baru)
    // Sisipkan data jurnal ke 3 linked list di node BST ini
    target_node_bst->list_by_year_head = sisipkanPaperUrutTahun(target_node_bst->list_by_year_head, data_jurnal);
    target_node_bst->list_by_incitations_head = sisipkanPaperUrutIncitations(target_node_bst->list_by_incitations_head, data_jurnal);
    target_node_bst->list_by_title_head = sisipkanPaperUrutJudul(target_node_bst->list_by_title_head, data_jurnal);

    target_node_bst->list_by_year_head = sisipkanPaperUrutTahun(target_node_bst->list_by_year_head, data_jurnal);
    target_node_bst->list_by_incitations_head = sisipkanPaperUrutIncitations(target_node_bst->list_by_incitations_head, data_jurnal);
    target_node_bst->list_by_title_head = sisipkanPaperUrutJudul(target_node_bst->list_by_title_head, data_jurnal);
    // Panggil fungsi sisip untuk list tahun ascending BARU:
    target_node_bst->list_by_year_asc_head = sisipkanPaperUrutTahunAsc(target_node_bst->list_by_year_asc_head, data_jurnal);
}

// --- Fungsi untuk Menampilkan BST (InOrder traversal untuk debugging) ---
void tampilkanBSTInOrder(BSTNodeField* root) {
    if (root != NULL) {
        tampilkanBSTInOrder(root->left_child);
        printf("Field of Study: %s\n", root->field_of_study);
        // Opsi: tampilkan jumlah paper di setiap list untuk verifikasi
        // printf("  Papers (by Year):\n"); tampilkanListPaper(root->list_by_year_head);
        // printf("  Papers (by Incitations):\n"); tampilkanListPaper(root->list_by_incitations_head);
        // printf("  Papers (by Title):\n"); tampilkanListPaper(root->list_by_title_head);
        tampilkanBSTInOrder(root->right_child);
    }
}

// --- Fungsi untuk Menghapus (Dealokasi Memori) Keseluruhan BST ---
void hapusBST(BSTNodeField* root) {
    if (root == NULL) {
        return;
    }
    // Hapus anak kiri dan kanan dulu (post-order traversal)
    hapusBST(root->left_child);
    hapusBST(root->right_child);

    // Hapus semua linked list paper di node ini
    hapusListPaper(root->list_by_year_head);
    hapusListPaper(root->list_by_incitations_head);
    hapusListPaper(root->list_by_title_head);

    hapusListPaper(root->list_by_year_asc_head); // Hapus list baru

    // Akhirnya, hapus node BST itu sendiri
    free(root);
}

