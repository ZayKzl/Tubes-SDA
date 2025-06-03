#ifndef LINKED_LIST_PAPER_H
#define LINKED_LIST_PAPER_H

#include "structs.h"

PaperNode* buatPaperNode(JurnalData data_jurnal);

// Menyisipkan paper ke DLL yang diurutkan berdasarkan TAHUN (MENAIK: terlama dulu)
void sisipkanDLLUrutTahunAsc(PaperNode** head_ptr, PaperNode** tail_ptr, JurnalData data_jurnal);

// Menyisipkan paper ke DLL yang diurutkan berdasarkan JUMLAH INCITATIONS (MENURUN: terbanyak dulu)
void sisipkanDLLUrutIncitationsDesc(PaperNode** head_ptr, PaperNode** tail_ptr, JurnalData data_jurnal);

// Menyisipkan paper ke DLL yang diurutkan berdasarkan JUDUL (abjad A-Z, case-insensitive)
void sisipkanDLLUrutJudulAsc(PaperNode** head_ptr, PaperNode** tail_ptr, JurnalData data_jurnal);

void tampilkanListPaper(PaperNode* head, const char* list_name); // Traversal maju
void tampilkanListPaperReverse(PaperNode* tail, const char* list_name); // Traversal mundur
void hapusListPaper(PaperNode** head_ptr, PaperNode** tail_ptr);

#endif // LINKED_LIST_PAPER_H