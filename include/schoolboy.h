#ifndef SCHOOLBOY_H
#define SCHOOLBOY_H

#define MAX_STR 50

typedef struct {
    char last_name[MAX_STR];
    char first_name[MAX_STR];
    char patronymic[MAX_STR];
    char gender[5];
    char nationality[MAX_STR];
    float height;
    float weight;
    int dob_y, dob_m, dob_d;
    char phone[20];
    char index[15];
    char country[MAX_STR];
    char region[MAX_STR];
    char district[MAX_STR];
    char city[MAX_STR];
    char street[MAX_STR];
    char house[10];
    char apartment[10];
    int school;
    int class_num;
} Schoolboy;

// Прототипы функций (Сервер)
void generate_test_file(const char *filename);
void view_file_content(const char *filename);
void process_and_save(const char *in_file, const char *out_file, int target_class);
void edit_file_record(const char *filename);

#endif