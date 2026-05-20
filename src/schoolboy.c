#include <stdio.h>
#include <stdlib.h>
#include "schoolboy.h"

void generate_test_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка создания файла %s\n", filename);
        return;
    }
    
    fprintf(file, "Иванов Иван Иванович М Белорус 1.45 40.5 2012 5 12 123-45-67 220000 РБ Минская Центральный Минск Ленина 10 15 42 5\n");
    fprintf(file, "Петров Петр Петрович М Белорус 1.60 55.0 2010 8 20 987-65-43 210000 РБ Витебская Октябрьский Витебск Кирова 5 1 12 7\n");
    fprintf(file, "Сидорова Анна Сергеевна Ж Белоруска 1.42 38.0 2012 1 10 111-22-33 220111 РБ Минская Московский Минск Правды 2 33 42 5\n");
    
    fclose(file);
    printf("Файл '%s' успешно создан и заполнен произвольной информацией.\n", filename);
}

// 2. Организовать просмотр содержимого файла
void view_file_content(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Файл '%s' не найден. Сначала создайте его.\n", filename);
        return;
    }

    Schoolboy s;
    printf("\n=== Содержимое файла %s ===\n", filename);
    int count = 0;
    
    while (fscanf(file, "%s %s %s %s %s %f %f %d %d %d %s %s %s %s %s %s %s %s %s %d %d",
           s.last_name, s.first_name, s.patronymic, s.gender, s.nationality, 
           &s.height, &s.weight, &s.dob_y, &s.dob_m, &s.dob_d, s.phone,
           s.index, s.country, s.region, s.district, s.city, s.street, 
           s.house, s.apartment, &s.school, &s.class_num) == 21) {
        
        printf("%d. %s %s (Класс: %d, Школа: %d) | Адрес: г.%s, ул.%s, %s-%s\n", 
               ++count, s.last_name, s.first_name, s.class_num, s.school, 
               s.city, s.street, s.house, s.apartment);
    }
    
    if (count == 0) printf("Файл пуст.\n");
    fclose(file);
}

void process_and_save(const char *in_file, const char *out_file, int target_class) {
    FILE *fin = fopen(in_file, "r");
    if (!fin) {
        printf("Исходный файл '%s' не найден.\n", in_file);
        return;
    }

    FILE *fout = fopen(out_file, "w");
    if (!fout) {
        printf("Ошибка создания файла результатов '%s'.\n", out_file);
        fclose(fin);
        return;
    }

    Schoolboy s;
    int found = 0;
    
    while (fscanf(fin, "%s %s %s %s %s %f %f %d %d %d %s %s %s %s %s %s %s %s %s %d %d",
           s.last_name, s.first_name, s.patronymic, s.gender, s.nationality, 
           &s.height, &s.weight, &s.dob_y, &s.dob_m, &s.dob_d, s.phone,
           s.index, s.country, s.region, s.district, s.city, s.street, 
           s.house, s.apartment, &s.school, &s.class_num) == 21) {
        
        if (s.class_num == target_class) {
            fprintf(fout, "%s %s %s %s %s %.2f %.2f %d %d %d %s %s %s %s %s %s %s %s %s %d %d\n",
                s.last_name, s.first_name, s.patronymic, s.gender, s.nationality, 
                s.height, s.weight, s.dob_y, s.dob_m, s.dob_d, s.phone,
                s.index, s.country, s.region, s.district, s.city, s.street, 
                s.house, s.apartment, s.school, s.class_num);
            found++;
        }
    }
    
    fclose(fin);
    fclose(fout);
    
    printf("Обработка завершена. Найдено учеников %d-го класса: %d.\n", target_class, found);
    printf("Результаты сохранены в файл '%s'.\n", out_file);
}

void edit_file_record(const char *filename) {
    Schoolboy arr[100]; 
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Файл '%s' не найден. Сначала создайте его.\n", filename);
        return;
    }

    int count = 0;
    while (fscanf(file, "%s %s %s %s %s %f %f %d %d %d %s %s %s %s %s %s %s %s %s %d %d",
           arr[count].last_name, arr[count].first_name, arr[count].patronymic, 
           arr[count].gender, arr[count].nationality, &arr[count].height, 
           &arr[count].weight, &arr[count].dob_y, &arr[count].dob_m, &arr[count].dob_d, 
           arr[count].phone, arr[count].index, arr[count].country, arr[count].region, 
           arr[count].district, arr[count].city, arr[count].street, arr[count].house, 
           arr[count].apartment, &arr[count].school, &arr[count].class_num) == 21) {
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("Файл пуст, нечего редактировать.\n");
        return;
    }

    // Выводим список для выбора
    printf("\n=== Выберите ученика для редактирования ===\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s %s (Текущий класс: %d, Школа: %d)\n", 
               i + 1, arr[i].last_name, arr[i].first_name, arr[i].class_num, arr[i].school);
    }

    int choice;
    printf("Введите номер записи (от 1 до %d) или 0 для отмены: ", count);
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
        if (choice != 0) printf("Неверный ввод. Отмена редактирования.\n");
        while(getchar() != '\n'); 
        return;
    }

    int idx = choice - 1;
    printf("Введите новый класс для %s: ", arr[idx].last_name);
    scanf("%d", &arr[idx].class_num);
    printf("Введите новую школу для %s: ", arr[idx].last_name);
    scanf("%d", &arr[idx].school);

    file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка открытия файла для записи.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
         fprintf(file, "%s %s %s %s %s %.2f %.2f %d %d %d %s %s %s %s %s %s %s %s %s %d %d\n",
                arr[i].last_name, arr[i].first_name, arr[i].patronymic, arr[i].gender, arr[i].nationality, 
                arr[i].height, arr[i].weight, arr[i].dob_y, arr[i].dob_m, arr[i].dob_d, arr[i].phone,
                arr[i].index, arr[i].country, arr[i].region, arr[i].district, arr[i].city, arr[i].street, 
                arr[i].house, arr[i].apartment, arr[i].school, arr[i].class_num);
    }
    fclose(file);
    
    printf("Запись успешно обновлена!\n");
}