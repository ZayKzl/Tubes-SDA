#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/manajemen_file.h"   // Deklarasi fungsi dan include "structs.h"
#include "../include/bst_field_study.h"  // Untuk memanggil tambahkanJurnalKeBST
#include "../cJSON/cJSON.h"            // Library untuk parsing JSON

// --- Fungsi untuk Memuat Data Jurnal dari File JSON ---
int muatDataDariMasterFile(const char* nama_file_json, BSTNodeField** root_bst_ptr) {
    char* json_string_buffer = NULL;
    FILE* file_json = NULL;
    long file_length = 0;
    size_t read_length = 0;
    cJSON* json_root = NULL;
    int berhasil = 0; // 0 untuk gagal, 1 untuk berhasil
    int jumlah_dimuat = 0;

    file_json = fopen(nama_file_json, "rb");
    if (file_json == NULL) {
        perror("Gagal membuka master file JSON");
        *root_bst_ptr = NULL;
        return 0;
    }

    fseek(file_json, 0, SEEK_END);
    file_length = ftell(file_json);
    if (file_length <= 0) {
        fprintf(stderr, "File JSON kosong atau error saat membaca ukuran file.\n");
        fclose(file_json);
        *root_bst_ptr = NULL;
        return 0;
    }
    fseek(file_json, 0, SEEK_SET);

    json_string_buffer = (char*)malloc(file_length + 1);
    if (json_string_buffer == NULL) {
        perror("Gagal alokasi memori untuk buffer JSON");
        fclose(file_json);
        *root_bst_ptr = NULL;
        return 0;
    }

    read_length = fread(json_string_buffer, 1, file_length, file_json);
    fclose(file_json);

    if (read_length != (size_t)file_length) {
        perror("Gagal membaca seluruh isi file JSON");
        free(json_string_buffer);
        *root_bst_ptr = NULL;
        return 0;
    }
    json_string_buffer[file_length] = '\0';

    json_root = cJSON_Parse(json_string_buffer);
    if (json_root == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error parsing JSON sebelum: %s\n", error_ptr);
        } else {
            fprintf(stderr, "Error parsing JSON: Struktur JSON tidak valid atau memori habis.\n");
        }
        free(json_string_buffer);
        *root_bst_ptr = NULL;
        return 0;
    }

    if (!cJSON_IsArray(json_root)) {
        fprintf(stderr, "Error: Root JSON bukan sebuah array.\n");
        cJSON_Delete(json_root);
        free(json_string_buffer);
        *root_bst_ptr = NULL;
        return 0;
    }

    cJSON* jurnal_json_obj = NULL;
    cJSON_ArrayForEach(jurnal_json_obj, json_root) {
        if (!cJSON_IsObject(jurnal_json_obj)) {
            fprintf(stderr, "Peringatan: Item dalam array JSON bukan objek, dilewati.\n");
            continue;
        }
        
        JurnalData temp_jurnal = {0}; 
        cJSON* item_json_current;

        // Mengambil 'id_paper' (JSON key: "id_paper")
        item_json_current = cJSON_GetObjectItemCaseSensitive(jurnal_json_obj, "id_paper");
        if (cJSON_IsString(item_json_current) && (item_json_current->valuestring != NULL)) {
            strncpy(temp_jurnal.id_paper, item_json_current->valuestring, MAX_ID_PAPER - 1);
            temp_jurnal.id_paper[MAX_ID_PAPER - 1] = '\0'; 
        }

        // Mengambil 'judul' (JSON key: "judul")
        item_json_current = cJSON_GetObjectItemCaseSensitive(jurnal_json_obj, "judul");
        if (cJSON_IsString(item_json_current) && (item_json_current->valuestring != NULL)) {
            strncpy(temp_jurnal.judul, item_json_current->valuestring, MAX_JUDUL - 1);
            temp_jurnal.judul[MAX_JUDUL - 1] = '\0';
        }
        
        // Mengambil 'tahun_terbit' (JSON key: "tahun_terbit")
        item_json_current = cJSON_GetObjectItemCaseSensitive(jurnal_json_obj, "tahun_terbit");
        if (cJSON_IsNumber(item_json_current)) {
            temp_jurnal.tahun_terbit = item_json_current->valueint;
        }

        // Mengambil 'abstrak' (JSON key: "abstrak")
        item_json_current = cJSON_GetObjectItemCaseSensitive(jurnal_json_obj, "abstrak");
        if (cJSON_IsString(item_json_current) && (item_json_current->valuestring != NULL)) {
            strncpy(temp_jurnal.abstrak, item_json_current->valuestring, MAX_ABSTRAK - 1);
            temp_jurnal.abstrak[MAX_ABSTRAK - 1] = '\0';
        }

        // Mengambil 'penulis' (JSON key: "penulis") dan menyimpannya ke temp_jurnal.nama_penulis
        item_json_current = cJSON_GetObjectItemCaseSensitive(jurnal_json_obj, "penulis");
        if (cJSON_IsString(item_json_current) && (item_json_current->valuestring != NULL)) {
            strncpy(temp_jurnal.nama_penulis, item_json_current->valuestring, MAX_PENULIS - 1);
            temp_jurnal.nama_penulis[MAX_PENULIS - 1] = '\0';
        }
        
        // Mengambil 'jumlah_incitations' (JSON key: "jumlah_incitations")
        item_json_current = cJSON_GetObjectItemCaseSensitive(jurnal_json_obj, "jumlah_incitations");
        if (cJSON_IsNumber(item_json_current)) {
            temp_jurnal.jumlah_incitations = item_json_current->valueint;
        }
        
        // Mengambil 'field_of_study' (JSON key: "field_of_study")
        item_json_current = cJSON_GetObjectItemCaseSensitive(jurnal_json_obj, "field_of_study");
        if (cJSON_IsString(item_json_current) && (item_json_current->valuestring != NULL)) {
            strncpy(temp_jurnal.field_of_study, item_json_current->valuestring, MAX_FIELD_STUDY - 1);
            temp_jurnal.field_of_study[MAX_FIELD_STUDY - 1] = '\0';
        }
        
        // Anda bisa menambahkan printf debug di sini jika perlu, contoh:
        /*
        printf("Dibaca -> ID: [%s], Judul: [%.30s...], FoS: [%s], Penulis: [%s], Tahun: [%d], InCit: [%d]\n", 
               temp_jurnal.id_paper,
               temp_jurnal.judul, 
               temp_jurnal.field_of_study,
               temp_jurnal.nama_penulis,
               temp_jurnal.tahun_terbit,
               temp_jurnal.jumlah_incitations);
        */

        tambahkanJurnalKeBST(root_bst_ptr, temp_jurnal);
        jumlah_dimuat++;
    }

    printf("Berhasil memuat %d data jurnal dari file JSON '%s'.\n", jumlah_dimuat, nama_file_json);
    berhasil = 1;

    cJSON_Delete(json_root);
    free(json_string_buffer);

    return berhasil;
}