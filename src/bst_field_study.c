#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // Untuk strcasecmp
#include "../include/bst_field_study.h"
#include "../include/linked_list_paper.h" // Perlu disesuaikan jika nama struct berubah

// --- FUNGSI BANTU AVL ---

// Mengembalikan tinggi sebuah node. Tinggi node NULL adalah -1.
int getHeight(BSTNodeField* node) {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}

// Fungsi bantu untuk mendapatkan nilai maksimum.
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Memperbarui tinggi node berdasarkan tinggi anak-anaknya.
// Harus dipanggil setelah setiap perubahan pada anak-anak node.
void updateHeight(BSTNodeField* node) {
    if (node != NULL) {
        node->height = 1 + max(getHeight(node->left_child), getHeight(node->right_child));
    }
}

// Mendapatkan faktor keseimbangan sebuah node (tinggi subtree kiri - tinggi subtree kanan).
int getBalanceFactor(BSTNodeField* node) {
    if (node == NULL) {
        return 0; // Node kosong memiliki faktor keseimbangan 0
    }
    return getHeight(node->left_child) - getHeight(node->right_child);
}

// --- FUNGSI ROTASI AVL ---

// Melakukan rotasi kanan pada subtree yang berakar pada node 'y'.
// Mengembalikan root baru dari subtree yang dirotasi.
BSTNodeField* rightRotate(BSTNodeField* y) {
    BSTNodeField* x = y->left_child;
    BSTNodeField* T2 = x->right_child;

    // Lakukan rotasi
    x->right_child = y;
    y->left_child = T2;

    // Perbarui tinggi node-node yang terlibat
    updateHeight(y);
    updateHeight(x);

    // Kembalikan root baru
    return x;
}

// Melakukan rotasi kiri pada subtree yang berakar pada node 'x'.
// Mengembalikan root baru dari subtree yang dirotasi.
BSTNodeField* leftRotate(BSTNodeField* x) {
    BSTNodeField* y = x->right_child;
    BSTNodeField* T2 = y->left_child;

    // Lakukan rotasi
    y->left_child = x; 
    x->right_child = T2;

    // Perbarui tinggi node-node yang terlibat
    updateHeight(x);
    updateHeight(y);

    // Kembalikan root baru
    return y;
}

// --- IMPLEMENTASI BST/AVL UTAMA ---

BSTNodeField* buatBSTNodeField(const char* field_of_study) {
    BSTNodeField* node_baru = (BSTNodeField*)malloc(sizeof(BSTNodeField));
    if (node_baru == NULL) {
        perror("Gagal alokasi memori untuk BSTNodeField baru");
        return NULL;
    }
    strncpy(node_baru->field_of_study, field_of_study, MAX_FIELD_STUDY - 1);
    node_baru->field_of_study[MAX_FIELD_STUDY - 1] = '\0';

    node_baru->year_list_head = NULL;
    node_baru->year_list_tail = NULL;
    node_baru->incitations_list_head = NULL;
    node_baru->incitations_list_tail = NULL;
    node_baru->title_list_head = NULL;
    node_baru->title_list_tail = NULL;
    
    node_baru->left_child = NULL;
    node_baru->right_child = NULL;
    node_baru->height = 0; // Inisialisasi tinggi untuk node baru (daun)
    return node_baru;
}

// !!! FUNGSI PENYISIPAN AVL DINAMIS !!!
BSTNodeField* sisipkanBSTNodeField(BSTNodeField* node, const char* field_of_study) {
    // 1. Lakukan penyisipan BST standar (rekursif)
    if (node == NULL) {
        return buatBSTNodeField(field_of_study);
    }

    int cmp = strcasecmp(field_of_study, node->field_of_study);

    if (cmp < 0) {
        node->left_child = sisipkanBSTNodeField(node->left_child, field_of_study);
    } else if (cmp > 0) {
        node->right_child = sisipkanBSTNodeField(node->right_child, field_of_study);
    } else {
        // field_of_study sudah ada, tidak perlu disisipkan lagi.
        return node;
    }

    // 2. Perbarui tinggi node leluhur saat ini (node yang sedang dikunjungi saat rekursi kembali)
    updateHeight(node);

    // 3. Dapatkan faktor keseimbangan node ini
    int balance = getBalanceFactor(node);

    // 4. Lakukan rotasi jika node tidak seimbang (kasus-kasus AVL)
    // Left Left Case: Penyisipan di subtree kiri dari anak kiri
    if (balance > 1 && getBalanceFactor(node->left_child) >= 0) {
        return rightRotate(node);
    }

    // Right Right Case: Penyisipan di subtree kanan dari anak kanan
    if (balance < -1 && getBalanceFactor(node->right_child) <= 0) {
        return leftRotate(node);
    }

    // Left Right Case: Penyisipan di subtree kanan dari anak kiri
    if (balance > 1 && getBalanceFactor(node->left_child) < 0) {
        node->left_child = leftRotate(node->left_child);
        return rightRotate(node);
    }

    // Right Left Case: Penyisipan di subtree kiri dari anak kanan
    if (balance < -1 && getBalanceFactor(node->right_child) > 0) {
        node->right_child = rightRotate(node->right_child);
        return leftRotate(node);
    }

    // Kembalikan node (mungkin setelah rotasi atau tidak)
    return node;
}


BSTNodeField* cariBSTNodeField(BSTNodeField* root, const char* field_of_study) {
    if (root == NULL) return NULL;
    int cmp = strcasecmp(field_of_study, root->field_of_study);

    if (cmp == 0) {
        return root;
    }
    if (cmp < 0) {
        return cariBSTNodeField(root->left_child, field_of_study);
    } else {
        return cariBSTNodeField(root->right_child, field_of_study);
    }
}

// Fungsi bangunBSTSeimbang TIDAK DIGUNAKAN LAGI untuk FULL AVL dinamis.
// Hapus atau abaikan implementasinya.

void tambahkanJurnalKeBST(BSTNodeField** root_bst_ptr, JurnalData data_jurnal) {
    if (root_bst_ptr == NULL) return;

    // Penyisipan field_of_study ke BST (akan otomatis menjaga keseimbangan AVL)
    // Jika field_of_study sudah ada, sisipkanBSTNodeField akan mengembalikan node yang sudah ada.
    // Jika field_of_study baru, sisipkanBSTNodeField akan membuat node baru dan menyeimbangkan pohon.
    *root_bst_ptr = sisipkanBSTNodeField(*root_bst_ptr, data_jurnal.field_of_study);

    // Cari node target di BST yang sudah ada/baru dibuat
    BSTNodeField* target_node_bst = cariBSTNodeField(*root_bst_ptr, data_jurnal.field_of_study);

    if (target_node_bst == NULL) {
        // Ini seharusnya tidak terjadi jika sisipkanBSTNodeField berfungsi dengan benar
        fprintf(stderr, "Error internal: Gagal menemukan node BST untuk '%s' setelah upaya penyisipan. Jurnal '%s' dilewati.\n", 
                data_jurnal.field_of_study, data_jurnal.judul);
        return;
    }

    // Sisipkan ke tiga DLL yang berbeda
    // Pastikan fungsi sisipkanDLLUrut... di linked_list_paper.h/c juga disesuaikan dengan PaperNode*
    sisipkanDLLUrutTahunAsc(&(target_node_bst->year_list_head), &(target_node_bst->year_list_tail), data_jurnal);
    sisipkanDLLUrutIncitationsDesc(&(target_node_bst->incitations_list_head), &(target_node_bst->incitations_list_tail), data_jurnal);
    sisipkanDLLUrutJudulAsc(&(target_node_bst->title_list_head), &(target_node_bst->title_list_tail), data_jurnal);
}

void tampilkanBSTInOrder(BSTNodeField* root) {
    if (root != NULL) {
        tampilkanBSTInOrder(root->left_child);
        // Tampilkan field_of_study beserta tinggi dan faktor keseimbangan untuk debugging AVL
        printf(" %s\n", root->field_of_study);
        //printf(" %s (H: %d, BF: %d)\n", root->field_of_study, getHeight(root), getBalanceFactor(root));
        tampilkanBSTInOrder(root->right_child);
    }
}

// (Opsional) Fungsi untuk memeriksa apakah seluruh BST seimbang (untuk debugging/verifikasi)
// Ini adalah fungsi yang Anda minta sebelumnya.
int isBalanced(BSTNodeField* root) {
    if (root == NULL) {
        return 1; // Pohon kosong dianggap seimbang
    }

    int balance_factor = getBalanceFactor(root);
    if (balance_factor > 1 || balance_factor < -1) {
        return 0; // Tidak seimbang jika |faktor_keseimbangan| > 1
    }

    return isBalanced(root->left_child) && isBalanced(root->right_child);
}


void hapusBST(BSTNodeField* root) {
    if (root == NULL) return;
    hapusBST(root->left_child);
    hapusBST(root->right_child);

    // Pastikan fungsi hapusListPaper juga disesuaikan dengan PaperNode*
    hapusListPaper(&(root->year_list_head), &(root->year_list_tail));
    hapusListPaper(&(root->incitations_list_head), &(root->incitations_list_tail));
    hapusListPaper(&(root->title_list_head), &(root->title_list_tail));
    
    free(root);
}