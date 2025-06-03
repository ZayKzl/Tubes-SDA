#ifndef LINKED_LIST_PAPER_H
#define LINKED_LIST_PAPER_H

#include "structs.h"

PaperNode* buatPaperNode(JurnalData data_jurnal);

// Fungsi sisip DLL
void sisipkanDLLUrutTahunAsc(PaperNode** head_ptr, PaperNode** tail_ptr, JurnalData data_jurnal);
void sisipkanDLLUrutIncitationsDesc(PaperNode** head_ptr, PaperNode** tail_ptr, JurnalData data_jurnal);
void sisipkanDLLUrutJudulAsc(PaperNode** head_ptr, PaperNode** tail_ptr, JurnalData data_jurnal);

int tampilkanListPaper(PaperNode* head, const char* list_name, int halaman_sekarang, int item_per_halaman);
int tampilkanListPaperReverse(PaperNode* tail, const char* list_name, int halaman_sekarang, int item_per_halaman);

// Fungsi helper untuk menghitung total item dalam list
int hitungTotalItemDiList(PaperNode* head);

PaperNode* pilihJurnalDariList(PaperNode* head, int nomor_pilihan_global);
PaperNode* pilihJurnalDariListReverse(PaperNode* tail, int nomor_pilihan_global_dari_depan); 

void hapusListPaper(PaperNode** head_ptr, PaperNode** tail_ptr);

#endif // LINKED_LIST_PAPER_H