#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>

void color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void GoToXY(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

struct Meeting
{
    char name[50];
    int day;
    int month;
    int year;
    int start_hour;
    int start_minute;
    int end_hour;
    int end_minute;
};

void readMeetingsFromFile(struct Meeting meetings[], int* num_meetings)
{
    FILE* file = fopen("C:\\Users\\Alesia\\Desktop\\Proiect C - PP\\Proiect citire fisier\\meeting.txt", "r");
    if (file == NULL)
    {
        printf("Fisierul nu a putut fi deschis!");
        return;
    }
    while (fscanf(file, "%49s %d %d %d %d %d %d %d",
                  meetings[*num_meetings].name, &meetings[*num_meetings].day,
                  &meetings[*num_meetings].month, &meetings[*num_meetings].year,
                  &meetings[*num_meetings].start_hour, &meetings[*num_meetings].start_minute,
                  &meetings[*num_meetings].end_hour, &meetings[*num_meetings].end_minute) == 8)
    {
        (*num_meetings)++;
    }
    fclose(file);
}

void writeMeetingsToFile(struct Meeting meetings[], int num_meetings)
{
    int i;
    FILE* file = fopen("C:\\Users\\Alesia\\Desktop\\Proiect C - PP\\Proiect citire fisier\\meeting.txt", "w");
    if (file == NULL)
    {
        printf("Fisierul nu a putut fi deschis!");
        return;
    }
    for (i = 0; i < num_meetings; i++)
    {
        fprintf(file, "%s %d %d %d %d %d %d %d\n", meetings[i].name, meetings[i].day,
                meetings[i].month, meetings[i].year, meetings[i].start_hour,
                meetings[i].start_minute, meetings[i].end_hour, meetings[i].end_minute);
    }
    fclose(file);
}

void deleteMeetingFromFile()
{
    FILE* file = fopen("C:\\Users\\Alesia\\Desktop\\Proiect C - PP\\Proiect citire fisier\\meeting.txt", "r");
    if (file == NULL)
    {
        printf("Fisierul nu a putut fi deschis!");
        return;
    }
    struct Meeting meetings[50];
    int num_meetings = 0;
    while (fscanf(file, "%49s %d %d %d %d %d %d %d",
                  meetings[num_meetings].name, &meetings[num_meetings].day,
                  &meetings[num_meetings].month, &meetings[num_meetings].year,
                  &meetings[num_meetings].start_hour, &meetings[num_meetings].start_minute,
                  &meetings[num_meetings].end_hour, &meetings[num_meetings].end_minute) == 8)
    {
        num_meetings++;
    }
    fclose(file);

    int day, month, year, i, j;
    char name[50];
    printf("Introduceti numele si data intalnirii pe care doriti sa o stergeti (format: nume dd/mm/yyyy): ");
    scanf("%49s %d/%d/%d", name, &day, &month, &year);
    for (i = 0; i < num_meetings; i++)
    {
        if (strcmp(meetings[i].name, name) == 0 && meetings[i].day == day && meetings[i].month == month && meetings[i].year == year)
        {
            for (j = i; j < num_meetings - 1; j++)
            {
                meetings[j] = meetings[j+1];
            }
            num_meetings--;
            printf("Intalnirea a fost stearsa cu succes!");

            FILE* file = fopen("C:\\Users\\Alesia\\Desktop\\Proiect C - PP\\Proiect citire fisier\\meeting.txt", "w");
            if (file == NULL)
            {
                printf("Fisierul nu a putut fi deschis!");
                return;
            }
            for (i = 0; i < num_meetings; i++)
            {
                fprintf(file, "%s %d %d %d %d %d %d %d\n", meetings[i].name, meetings[i].day,
                        meetings[i].month, meetings[i].year, meetings[i].start_hour,
                        meetings[i].start_minute, meetings[i].end_hour, meetings[i].end_minute);
            }
            fclose(file);

            return;
        }
    }
    printf("Nu s-a gasit nicio intalnire pentru numele si data specificate.");
}


void viewMeeting(struct Meeting meetings[], int* num_meetings)
{
    int day, month, year, i, ok = 0, count = 9;
    GoToXY(10,7);
    printf("Introduceti data dorita (format dd/mm/yyyy): ");
    scanf("%d/%d/%d", &day, &month, &year);

    // Citirea intalnirilor din fisier

    GoToXY(10,count);
    for (i = 0; i < *num_meetings; i++)
    {
        if (meetings[i].day == day && meetings[i].month == month && meetings[i].year == year)
        {
            ok = 1;
            printf("%s - %d/%d/%d %d:%d - %d:%d ", meetings[i].name, meetings[i].day, meetings[i].month, meetings[i].year, meetings[i].start_hour, meetings[i].start_minute,meetings[i].end_hour, meetings[i].end_minute);
            printf("\n");
            count++;
            GoToXY(10,count);
        }
    }

    if(ok == 0)
    {
        system("cls");
        GoToXY(10,5);
        printf("Nu s-a gasit nicio intalnire pentru data specificata.\n");
        GoToXY(10,7);
        printf("Apasati sageata stanga pentru a reveni la meniul principal.");
    }

    // Scrierea intalnirilor in fisier

}



int differenceBetweenDates(int d1, int m1, int y1, int d2, int m2, int y2)
{
    int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    long firstDateTotalDays = 0;
    long secondDateTotalDays = 0;
    int i;

    firstDateTotalDays = y1 * 365 + d1;
    secondDateTotalDays = y2 * 365 + d2;

    for(i = 0; i<m1; ++i)
        firstDateTotalDays += monthDays[i];

    for(i = 0; i<m2; ++i)
        secondDateTotalDays += monthDays[i];

    return (secondDateTotalDays - firstDateTotalDays);
}


void view30DaysMeetings(struct Meeting meetings[], int* num_meetings)
{


    SYSTEMTIME time;
    GetLocalTime(&time);
    GoToXY(10, 7);
    int count = 7,i;
    for( i = 0; i < *num_meetings; ++i)
    {
        int difference = differenceBetweenDates(time.wDay, time.wMonth, time.wYear, meetings[i].day, meetings[i].month, meetings[i].year);
        if(difference >= 0 && difference <= 30)
        {
            printf("%s - %d/%d/%d %d:%d - %d:%d ", meetings[i].name, meetings[i].day, meetings[i].month, meetings[i].year, meetings[i].start_hour, meetings[i].start_minute,meetings[i].end_hour, meetings[i].end_minute);
            printf("\n");
            ++count;
            GoToXY(10, count);
        }
    }

}

void printMeetingsFromFile()
{

    FILE* file = fopen("meeting.txt", "r");
    if (file == NULL)
    {
        printf("Fisierul nu a putut fi deschis!");
        return;
    }
    struct Meeting meeting;

    while (fscanf(file, "%s %d %d %d %d %d %d %d",
                  &meeting.name, &meeting.day, &meeting.month, &meeting.year,
                  &meeting.start_hour, &meeting.start_minute, &meeting.end_hour,
                  &meeting.end_minute) == 8)
    {

        printf("          %s %02d/%02d/%d %02d:%02d-%02d:%02d\n", meeting.name, meeting.day,
               meeting.month, meeting.year, meeting.start_hour, meeting.start_minute,
               meeting.end_hour, meeting.end_minute);

    }
    fclose(file);
}

void addMeeting(struct Meeting meetings[], int* num_meetings)
{
    if (*num_meetings >= 50)
    {
        system("cls");
        GoToXY(10,7);
        printf("Nu mai poti adauga intalniri, ai atins numarul maxim!\n");
    }
    else
    {
        system("cls");
        GoToXY(10,5);
        printf("Ati ales optiunea 1 -> Adauga o intalnire noua");

        GoToXY(10,7);
        printf("Introduceti numele intalnirii: ");
        scanf("%s", &meetings[*num_meetings].name);

        GoToXY(10,8);
        printf("Introduceti data intalnirii (format dd/mm/yyyy): ");
        scanf("%d/", &meetings[*num_meetings].day);
        scanf("%d/", &meetings[*num_meetings].month);
        scanf("%d", &meetings[*num_meetings].year);

        GoToXY(10,9);
        printf("Introduceti ora de start a intalnirii (format hh:mm): ");
        scanf("%d:", &meetings[*num_meetings].start_hour);
        scanf("%d", &meetings[*num_meetings].start_minute);

        GoToXY(10,10);
        printf("Introduceti ora de sfarsit a intalnirii (format hh:mm): ");
        scanf("%d:", &meetings[*num_meetings].end_hour);
        scanf("%d", &meetings[*num_meetings].end_minute);

        (*num_meetings)++;
        system("cls");
        GoToXY(10,5);
        printf("Intalnire adaugata cu succes!");
    }
    GoToXY(10,7);
    printf("Apasati sageata stanga pentru a reveni la meniul principal.");
}

void printMeetingsForNext30Days()
{
    FILE *fp;
    fp = fopen("meeting.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    SYSTEMTIME time;
    GetLocalTime(&time);
    int count = 7;

    char name[50];
    int day, month, year, start_hour, start_minute, end_hour, end_minute;
    GoToXY(10, 7);
    while (fscanf(fp, "%s %d %d %d %d %d %d %d", name, &day, &month, &year, &start_hour, &start_minute, &end_hour, &end_minute) == 8)
    {
        int difference = differenceBetweenDates(time.wDay, time.wMonth, time.wYear, day, month, year);
        if (difference >= 0 && difference <= 30)
        {
            printf("%s - %d/%d/%d %d:%d - %d:%d\n", name, day, month, year, start_hour, start_minute, end_hour, end_minute);
            ++count;
            GoToXY(10, count);
        }
    }

    fclose(fp);
}





int main()
{


    struct Meeting meetings[50];
    int num_meetings = 0;
    int Set[] = {7,7,7,7,7,7};
    Set[1] = 12;
    int counter = 2;
    char key;
    bool Exit = false; // variabila pentru a verifica daca programul trebuie sa se incheie
    while(!Exit)
    {

        system("cls");
        GoToXY(10,5);
        color(Set[0]);
        printf("Meniul principal ");

        GoToXY(10,7);
        color(Set[1]);
        printf("Optiunea 1 : Adauga o intalnire noua");

        GoToXY(10,8);
        color(Set[2]);
        printf("Optiunea 2 : Sterge o intalnire");

        GoToXY(10,9);
        color(Set[3]);
        printf("Optiunea 3 : Vizualizeaza intalnirile din urmatoarele 30 de zile");

        GoToXY(10,10);
        color(Set[4]);
        printf("Optiunea 4 : Vizualizeaza intalnirile introducand o data exacta");

        GoToXY(10,13);
        color(Set[5]);
        printf("Apasa ENTER pentru a selecta optiunea dorita.");
        GoToXY(10,14);
        color(Set[5]);
        printf("Apasa ESC pentru a inchide meniul.\n");

        key = _getch();

        if(key == 72 && (counter >=3 && counter <=5)) //sageata sus
            counter --;

        if(key == 80 && (counter >=1 && counter <=4)) //sageata jos
            counter ++;
        if(key == 27) // tasta esc
        {
            Exit = true;
            break;
        }

        if(key == '\r')
        {
            system("cls");
            if(counter == 2)
            {
                system("cls");
                GoToXY(10,5);
                printf("Ati ales optiunea 1 -> Adauga o intalnire noua");
                readMeetingsFromFile(meetings, &num_meetings);
                addMeeting(meetings, &num_meetings);
                writeMeetingsToFile(meetings, num_meetings);
                if(key == 75) // sageata stanga
                    break;
            }

            if(counter == 3)
            {

                GoToXY(10,5);
                printf("Ati ales optiunea 2 -> Sterge o intalnire\n");
                deleteMeetingFromFile();
                GoToXY(10,8);
                printf("Apasati sageata stanga pentru a reveni la meniul principal.");

            }

            if(counter == 4)
            {

                GoToXY(10,5);
                printf("Ati ales optiunea 3 -> Intalnirile din urmatoarele 30 de zile \n");
                //view30DaysMeetings(meetings, &num_meetings);
                //printMeetingsFromFile();
                printMeetingsForNext30Days();


            }

            if(counter == 5)
            {

                GoToXY(10,5);
                readMeetingsFromFile(meetings, &num_meetings);
                printf("Ati ales optiunea 4 -> Vizualizeaza intalnirile introducand o data exacta");
                viewMeeting(meetings, &num_meetings);
            }

            _getch();
            counter = 2;
        }
        Set[1] = 7;
        Set[2] = 7;
        Set[3] = 7;
        Set[4] = 7;
        if(counter == 2)
            Set[1] = 12;
        if(counter == 3)
            Set[2] = 12;
        if(counter == 4)
            Set[3] = 12;
        if(counter == 5)
            Set[4] = 12;

    }
    return 0;
}
