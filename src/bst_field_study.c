#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // Untuk strcasecmp
#include "../include/bst_field_study.h"
#include "../include/linked_list_paper.h"

BSTNodeField* buatBSTNodeField(const char* field_of_study) {
    BSTNodeField* node_baru = (BSTNodeField*)malloc(sizeof(BSTNodeField));
    if (node_baru == NULL) {
        perror("Gagal alokasi memori untuk BSTNodeField baru");
        return NULL;
    }
    strncpy(node_baru->field_of_study, field_of_study, MAX_FIELD_STUDY - 1);
    node_baru->field_of_study[MAX_FIELD_STUDY - 1] = '\0';

    // Inisialisasi semua head dan tail dari DLL ke NULL
    node_baru->year_list_head = NULL;
    node_baru->year_list_tail = NULL;
    node_baru->incitations_list_head = NULL;
    node_baru->incitations_list_tail = NULL;
    node_baru->title_list_head = NULL;
    node_baru->title_list_tail = NULL;
    
    node_baru->left_child = NULL;
    node_baru->right_child = NULL;
    return node_baru;
}

BSTNodeField* sisipkanBSTNodeField(BSTNodeField* root, const char* field_of_study) {
    if (root == NULL) {
        return buatBSTNodeField(field_of_study);
    }
    // Gunakan strcasecmp untuk BST key agar case-insensitive
    int cmp = strcasecmp(field_of_study, root->field_of_study); 

    if (cmp < 0) {
        root->left_child = sisipkanBSTNodeField(root->left_child, field_of_study);
    } else if (cmp > 0) {
        root->right_child = sisipkanBSTNodeField(root->right_child, field_of_study);
    }
    return root;
}

BSTNodeField* cariBSTNodeField(BSTNodeField* root, const char* field_of_study) {
    if (root == NULL) return NULL;
    // Gunakan strcasecmp untuk pencarian case-insensitive
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

void tambahkanJurnalKeBST(BSTNodeField** root_bst_ptr, JurnalData data_jurnal) {
    if (root_bst_ptr == NULL) return;

    BSTNodeField* target_node_bst = cariBSTNodeField(*root_bst_ptr, data_jurnal.field_of_study);

    if (target_node_bst == NULL) {
        *root_bst_ptr = sisipkanBSTNodeField(*root_bst_ptr, data_jurnal.field_of_study);
        target_node_bst = cariBSTNodeField(*root_bst_ptr, data_jurnal.field_of_study);
        if (target_node_bst == NULL) {
            fprintf(stderr, "Error: Gagal membuat atau menemukan node BST untuk %s setelah disisipkan\n", data_jurnal.field_of_study);
            return;
        }
    }

    // Sisipkan ke tiga DLL yang berbeda
    sisipkanDLLUrutTahunAsc(&(target_node_bst->year_list_head), &(target_node_bst->year_list_tail), data_jurnal);
    sisipkanDLLUrutIncitationsDesc(&(target_node_bst->incitations_list_head), &(target_node_bst->incitations_list_tail), data_jurnal);
    sisipkanDLLUrutJudulAsc(&(target_node_bst->title_list_head), &(target_node_bst->title_list_tail), data_jurnal);
}

void tampilkanBSTInOrder(BSTNodeField* root) {
    if (root != NULL) {
        tampilkanBSTInOrder(root->left_child);
        printf("Field of Study: %s\n", root->field_of_study);
        // Tambahkan detail lain jika perlu untuk debugging
        tampilkanBSTInOrder(root->right_child);
    }
}

void hapusBST(BSTNodeField* root) {
    if (root == NULL) return;
    hapusBST(root->left_child);
    hapusBST(root->right_child);

    hapusListPaper(&(root->year_list_head), &(root->year_list_tail));
    hapusListPaper(&(root->incitations_list_head), &(root->incitations_list_tail));
    hapusListPaper(&(root->title_list_head), &(root->title_list_tail));
    
    free(root);
}