#ifndef STRUCTS_H
#define STRUCTS_H

// Konstanta untuk ukuran array char, bisa disesuaikan
#define MAX_ID_PAPER 50
#define MAX_FIELD_STUDY 100
#define MAX_JUDUL 255
#define MAX_SITASI_INFO 50
#define MAX_PENULIS 255 // Cukupkan untuk gabungan nama
#define MAX_ABSTRAK 2000

typedef struct {
    char id_paper[MAX_ID_PAPER];
    char field_of_study[MAX_FIELD_STUDY];
    char judul[MAX_JUDUL];
    int tahun_terbit;
    char sitasi_info[MAX_SITASI_INFO];
    char nama_penulis[MAX_PENULIS];
    char abstrak[MAX_ABSTRAK];
    int jumlah_incitations;
} JurnalData;

typedef struct PaperNode {
    JurnalData data;
    struct PaperNode* next;
    struct PaperNode* prev;
} PaperNode;

typedef struct BSTNodeField {
    char field_of_study[MAX_FIELD_STUDY];

    PaperNode* year_list_head;          // Urut Tahun MENAIK (Terlama -> Terbaru)
    PaperNode* year_list_tail;

    PaperNode* incitations_list_head;   // Urut Incitations MENURUN (Terbanyak -> Tersedikit)
    PaperNode* incitations_list_tail;

    PaperNode* title_list_head;         // Urut Judul MENAIK (A -> Z)
    PaperNode* title_list_tail;

    struct BSTNodeField* left_child;
    struct BSTNodeField* right_child;
} BSTNodeField;

#endif // STRUCTS_H