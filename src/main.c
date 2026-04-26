#include <stdio.h>
#include "schoolboy.h"

int main() {
    int choice;
    const char *in_file = "input.txt";
    const char *out_file = "output.txt";

    do {
        printf("\n=== МЕНЮ (Обработка текстовых файлов) ===\n");
        printf("1. Создать текстовый файл с произвольной информацией\n");
        printf("2. Просмотреть содержимое исходного файла\n");
        printf("3. Обработать данные (найти 5-классников) и сохранить в новый файл\n");
        printf("4. Просмотреть содержимое файла с результатами\n");
        printf("5. Редактировать запись в исходном файле\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); 
            continue;
        }

        switch (choice) {
            case 1:
                generate_test_file(in_file);
                break;
            case 2:
                view_file_content(in_file);
                break;
            case 3:
                process_and_save(in_file, out_file, 5); // Ищем 5-й класс
                break;
            case 4:
                view_file_content(out_file);
                break;
            case 5:
                edit_file_record(in_file);
                break;
            case 0:
                printf("Завершение программы.\n");
                break;
            default:
                printf("Неверный пункт меню.\n");
        }
    } while (choice != 0);

    return 0;
}