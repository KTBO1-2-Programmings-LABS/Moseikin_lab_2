#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>


struct Data
{
    char city[64];
    char street[64];
    char index[16];
    char fio[256];
    Data* prev;
    Data* next;
};

struct DoubleList
{
    Data* head;
    Data* end;
};

DoubleList create_list()
{
    DoubleList list;
    list.head = 0;
    list.end = 0;
    return list;
}

Data* create(const char* city, const char* street, const char* index, const char* fio)
{
    Data* new_data = (Data*)malloc(sizeof(Data));

    if (new_data != 0)
    {
        strcpy(new_data->city, city);
        strcpy(new_data->street, street);
        strcpy(new_data->index, index);
        strcpy(new_data->fio, fio);
        new_data->prev = 0;
        new_data->next = 0;
    }

    return new_data;
}

void print(const Data* data)
{
    printf("Улица: %s; Индекс: %s; Адрес ячейки: %p; Предыдущая: %p; Следующая: %p\n", data->street, data->index, data, data->prev, data->next);
}

void print_list(DoubleList* list)
{
    if (list->head)
    {
        printf("Начало списка %p\n", list->head);

        Data* temp = list->head;
        while (temp != 0)
        {
            print(temp);
            temp = temp->next;
        }

        printf("\nКонец списка %p\n", list->end);
        printf("/////////////////////\n");
    }
    else
        printf("Список пуст\n");
}

void append(DoubleList* list, Data* new_data)
{
    if (list->head != 0)
    {
        list->end->next = new_data;
        new_data->prev = list->end;
        list->end = new_data;
    }
    else
    {
        list->head = new_data;
        list->end = new_data;
    }
}

void add_by_pos(DoubleList* list, const unsigned pos, Data* new_data)
{
    if (list->head != 0)
    {
        if (pos == 0)
        {
            new_data->next = list->head;
            list->head->prev = new_data;
            list->head = new_data;
        }
        else
        {
            Data* temp = list->head;
            unsigned cur_pos = 0;

            while (temp->next != 0 && cur_pos < pos - 1)
            {
                temp = temp->next;
                cur_pos++;
            }

            if (cur_pos == pos - 1)
            {
                new_data->next = temp->next;
                new_data->prev = temp;
                temp->next = new_data;

                if (new_data->next != 0)
                    new_data->next->prev = new_data;
                else
                    list->end = new_data;
            }
            else
                printf("Указанного индекса не существует\n");
        }
    }
    else if (pos == 0)
    {
        list->head = new_data;
        list->end = new_data;
    }
    else
        printf("Список пуст, добавление по индексу %d невозможно\n", pos);
}

void add_by_number_after(DoubleList* list, const char* index, Data* new_data)
{
    if (list->head != 0)
    {
        Data* temp = list->head;

        while (temp != 0)
        {
            if (strcmp(temp->index, index) == 0)
            {
                new_data->next = temp->next;
                new_data->prev = temp;
                temp->next = new_data;

                if (new_data->next != 0)
                    new_data->next->prev = new_data;
                else
                    list->end = new_data;

                break;
            }
            else
                temp = temp->next;
        }
    }
    else
        printf("Ошибка, список пуст\n");
}


void add_by_number_before(DoubleList* list, const char* index, Data* new_data)
{
    if (list->head != 0)
    {
        Data* temp = list->head;

        while (temp != 0)
        {
            if (strcmp(temp->index, index) == 0)
            {
                new_data->next = temp;
                new_data->prev = temp->prev;
                temp->prev = new_data;

                if (new_data->prev != 0)
                    new_data->prev->next = new_data;
                else
                    list->head = new_data;
                break;
            }
            else
                temp = temp->next;
        }
    }
    else
        printf("Ошибка, список пуст\n");
}

void add_in_center(DoubleList* list, Data* new_data)
{
    if (list->head != 0)
    {
        Data* mid = list->head;
        Data* end = mid->next;

        while (end != 0 && end->next != 0)
        {
            mid = mid->next;
            end = end->next->next;
        }

        new_data->next = mid->next;
        new_data->prev = mid;
        mid->next = new_data;

        if (new_data->next != 0)
            new_data->next->prev = new_data;
        else
            list->end = new_data;
    }
    else
    {
        list->head = new_data;
        list->end = new_data;
    }
}

void delete_from_center(DoubleList* list)
{
    if (list->head != 0)
    {
        Data* mid = list->head;
        Data* end = mid->next;

        while (end != 0 && end->next != 0)
        {
            mid = mid->next;
            end = end->next->next;
        }

        if (mid->prev != 0)
            mid->prev->next = mid->next;
        else
            list->head = mid->next;

        if (mid->next != 0)
            mid->next->prev = mid->prev;
        else
            list->end = mid->prev;

        free(mid);
    }
    else
        printf("Ошибка, список пуст\n");
}

void delete_by_number(DoubleList* list, const char* index)
{
    if (list->head)
    {
        Data* temp = list->head;

        while (temp != 0)
        {
            if (strcmp(temp->index, index) == 0)
            {
                if (temp->prev != 0)
                    temp->prev->next = temp->next;
                else
                    list->head = temp->next;
                if (temp->next != 0)
                    temp->next->prev = temp->prev;
                else
                    list->end = temp->prev;

                free(temp);

                break;
            }
            else
                temp = temp->next;
        }
    }
    else
        printf("Ошибка, список пуст\n");
}

void delete_last(DoubleList* list)
{
    if (list->end != 0)
    {
        Data* temp = list->end;

        if (temp->prev != 0)
        {
            list->end = temp->prev;
            list->end->next = 0;
        }
        else
            list->head = list->end = 0;

        free(temp);
    }
    else
        printf("Ошибка, список пуст\n");
}

void delete_by_pos(DoubleList* list, const unsigned pos)
{
    if (list->head != 0)
    {
        Data* current = list->head;
        unsigned cur_pos = 0;

        while (current != 0 && cur_pos < pos)
        {
            current = current->next;
            cur_pos++;
        }

        if (current && cur_pos == pos)
        {
            if (current->prev != 0)
                current->prev->next = current->next;
            else
                list->head = current->next;

            if (current->next != 0)
                current->next->prev = current->prev;
            else
                list->end = current->prev;

            free(current);
        }
        else
            printf("Удаление по индексу %d невозможно, элементов недостаточно\n", pos);
    }
    else
        printf("Удаление по индексу %d невозможно, элементов недостаточно\n", pos);
}

void delete_first(DoubleList* list)
{
    Data* temp = list->head;
    list->head = temp->next;
    if (temp->next != 0)
        temp->next->prev = 0;
    else
        list->end = 0;

    free(temp);
}

int main()
{
    setlocale(LC_ALL, "RU");
    Data* new_data_0 = create("Taganrog", "Svobody", "324567", "Petrov Petr Petrovich");
    Data* new_data_1 = create("Rostov", "Pervomayskaya", "783367", "Vasilyev Vasiliy Vasilyevich");
    Data* new_data_2 = create("Moscow", "Sadovaya", "729812", "Ivanov Ivan Ivanovich");
    Data* new_data_3 = create("Zernograd", "Oktyabrskaya", "347740", "Alexeev Alexey Alexeyevich");
    Data* new_data_4 = create("Volgodonsk", "Mira", "340912", "Antonov Anton Antonovich");

    DoubleList list = create_list();

    printf("\n");
    print_list(&list);

    printf("После добавления в конец списка:\n");
    append(&list, new_data_0);
    print_list(&list);

    printf("После добавления элемента по индексу 1:\n");
    add_by_pos(&list, 1, new_data_1);
    print_list(&list);

    printf("Добавление элемента после элемента с заданной информационной частью(\"324567\"):\n");
    add_by_number_after(&list, "324567", new_data_2);
    print_list(&list);

    printf("Добавление элемента перед элементом с заданной информационной частью(\"783367\"):\n");
    add_by_number_before(&list, "783367", new_data_3);
    print_list(&list);

    printf("Добавление элемента в середину списка:\n");
    add_in_center(&list, new_data_4);
    print_list(&list);

    printf("Исключение элемента из середины списка:\n");
    delete_from_center(&list);
    print_list(&list);

    printf("Исключение элемента с заданной информационной частью(\"729812\"):\n");
    delete_by_number(&list, "729812");
    print_list(&list);

    printf("Исключение элемента из конца списка:\n");
    delete_last(&list);
    print_list(&list);

    printf("Исключение элемента по заданному пользователем индексу (1):\n");
    delete_by_pos(&list, 1);
    print_list(&list);

    printf("Исключение элемента из начала списка:\n");
    delete_first(&list);
    print_list(&list);

    return 0;
}