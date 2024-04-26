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

    Data* next;
};

Data* create(const char* city, const char* street, const char* index, const char* fio)
{
    Data* new_data = (Data*)malloc(sizeof(Data));

    if (new_data)
    {
        strcpy(new_data->city, city);
        strcpy(new_data->street, street);
        strcpy(new_data->index, index);
        strcpy(new_data->fio, fio);
        new_data->next = 0;
    }

    return new_data;
}

void print(const Data* data)
{
    printf("Улица: %s; Индекс: %s; Адрес ячейки: %p; Следующая: %p\n", data->street, data->index, data, data->next);
}

void print_list(Data* head)
{
    if (head != 0)
    {
        printf("Начало списка \n");
        Data* temp = head;

        while (temp != 0)
        {
            print(temp);
            temp = temp->next;
        }
        printf("\nКонец списка \n");
        printf("/////////////////////\n");
    }
    else
        printf("Список пуст\n");
}

void append(Data** head, Data* new_data)
{
    if (*head != 0)
    {
        Data* last = *head;

        while (last->next != 0)
            last = last->next;

        last->next = new_data;
    }
    else
        *head = new_data;
}

void add_by_pos(Data** head, const unsigned pos, Data* new_data)
{
    if (*head)
    {
        if (pos == 0)
        {
            new_data->next = *head;
            *head = new_data;
        }
        else
        {
            Data* last = *head;
            unsigned cur_pos = 0;

            while (last->next != 0 && cur_pos < pos - 1)
            {
                last = last->next;
                cur_pos = cur_pos + 1;
            };

            if (cur_pos == pos - 1)
            {
                new_data->next = last->next;
                last->next = new_data;
            }
            else
                printf("Указанного индекса не существует\n");
        }
    }
    else if (pos == 0)
        *head = new_data;
    else
        printf("Указанного индекса не существует\n");
}


void add_by_number_after(Data** head, const char* index, Data* new_data)
{
    if (*head != 0)
    {
        Data* temp = *head;

        while (temp != 0)
        {
            if (strcmp(temp->index, index) == 0)
            {
                new_data->next = temp->next;
                temp->next = new_data;
                break;
            }
            else
                temp = temp->next;
        }
    }
    else
        printf("Список пуст, добавление по указанному индексу невозможно\n");
}

void add_by_number_before(Data** head, const char* index, Data* new_data)
{
    if (*head != 0)
    {
        if (strcmp((*head)->index, index) == 0)
        {
            new_data->next = *head;
            *head = new_data;
        }
        else
        {
            Data* temp = *head;

            while (temp->next != 0)
            {
                if (strcmp(temp->next->index, index) == 0)
                {
                    new_data->next = temp->next;
                    temp->next = new_data;
                    break;
                }
                else
                    temp = temp->next;
            }
        }
    }
    else
        printf("Ошибка, список пуст\n");
}

void add_in_center(Data** head, Data* new_data)
{
    if (*head != 0)
    {
        Data* mid = *head;
        Data* end = mid->next;

        while (end != 0 && end->next != 0)
        {
            mid = mid->next;
            end = end->next->next;
        }

        new_data->next = mid->next;
        mid->next = new_data;
    }
    else
        *head = new_data;
}

void delete_from_center(Data** head)
{
    if (*head != 0)
    {
        Data* mid = *head;
        Data* end = *head;
        Data* prev = 0;

        while (end != 0 && end->next != 0)
        {
            prev = mid;
            mid = mid->next;
            end = end->next->next;
        }

        if (prev != 0)
            prev->next = mid->next;
        else
            *head = 0;

        free(mid);
    }
    else
        printf("Ошибка, список пуст\n");
}

void delete_by_number(Data** head, const char* index)
{
    if (*head != 0)
    {
        Data* temp = *head;

        if (strcmp(temp->index, index) == 0)
        {
            *head = temp->next;
            free(temp);
        }
        else
        {
            while (temp->next != 0)
            {
                if (strcmp(temp->next->index, index) == 0)
                {
                    Data* del = temp->next;
                    temp->next = temp->next->next;
                    free(del);
                    break;
                }
                else
                    temp = temp->next;
            }
        }
    }
    else
        printf("Ошибка, список пуст\n");
}

void delete_last(Data** head)
{
    if (*head != 0)
    {
        Data* temp = *head;

        if (temp->next == 0)
        {
            free(temp);
            *head = 0;
        }
        else
        {
            while (temp->next->next != 0)
                temp = temp->next;

            free(temp->next);
            temp->next = 0;
        }
    }
    else
        printf("Error: List is empty!\n");
}

void delete_by_pos(Data** head, const unsigned pos)
{
    if (*head != 0)
    {
        Data* temp = *head;

        if (pos == 0)
        {
            *head = temp->next;
            free(temp);
        }
        else
        {
            unsigned cur_pos = 0;

            while (temp != 0 && cur_pos < pos - 1)
            {
                temp = temp->next;
                cur_pos = cur_pos + 1;
            }

            if (cur_pos == pos - 1 && temp != 0 && temp->next != 0)
            {
                Data* del = temp->next;
                temp->next = temp->next->next;
                free(del);
            }
            else
                printf("Указанного индекса не существует\n");
        }
    }
    else
        printf("Ошибка: список пуст\n");
}

void delete_first(Data** head)
{
    if (*head != 0)
    {
        Data* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    else
        printf("Ошибка: список пуст\n");
}

int main()
{
    setlocale(LC_ALL, "ru");
    Data* new_data_0 = create("Taganrog", "Svobody", "324567", "Petrov Petr Petrovich");
    Data* new_data_1 = create("Rostov", "Pervomayskaya", "783367", "Vasilyev Vasiliy Vasilyevich");
    Data* new_data_2 = create("Moscow", "Sadovaya", "729812", "Ivanov Ivan Ivanovich");
    Data* new_data_3 = create("Zernograd", "Oktyabrskaya", "347740", "Alexeev Alexey Alexeyevich");
    Data* new_data_4 = create("Volgodonsk", "Mira", "340912", "Antonov Anton Antonovich");


    Data* head = 0;

    printf("\n");
    print_list(head);

    printf("После добавления в конец списка:\n");
    append(&head, new_data_0);
    print_list(head);

    printf("После добавления элемента по индексу 1:\n");
    add_by_pos(&head, 1, new_data_1);
    print_list(head);

    printf("Добавление элемента после элемента с заданной информационной частью(\"324567\"):\n");
    add_by_number_after(&head, "324567", new_data_2);
    print_list(head);

    printf("Добавление элемента перед элементом с заданной информационной частью(\"783367\"):\n");
    add_by_number_before(&head, "783367", new_data_3);
    print_list(head);

    printf("Добавление элемента в середину списка:\n");
    add_in_center(&head, new_data_4);
    print_list(head);

    printf("Исключение элемента из середины списка:\n");
    delete_from_center(&head);
    print_list(head);

    printf("Исключение элемента с заданной информационной частью(\"729812\"):\n");
    delete_by_number(&head, "729812");
    print_list(head);

    printf("Исключение элемента из конца списка:\n");
    delete_last(&head);
    print_list(head);

    printf("Исключение элемента по заданному пользователем индексу (1):\n");
    delete_by_pos(&head, 1);
    print_list(head);

    printf("Исключение элемента из начала списка:\n");
    delete_first(&head);
    print_list(head);

    return 0;
}
