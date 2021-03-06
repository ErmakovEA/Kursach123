#include <iostream>
#include "StringBuilderClass.h"
#include "FileManagerClass.h"
#include "ClassMenu.h"
#include "StudentDBClass.h"
#include "StudentClass.h"
#include "ClassEdit.h"
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
    SetConsoleOutputCP(1251);
    std::cout << "Курсовая работа запущена...\n";
    StudentDBClass* sdb = new StudentDBClass();    
    StudentDBClass* sdb1 = new StudentDBClass();
    StudentDBClass* sdb2 = new StudentDBClass();
    int l = 0;
    sdb->FileName = "DB.txt";
    sdb->loadDataFromFile();
    //cout << sdb->GetRecordCount() << endl;
    ClassMenu* mainMenu = new ClassMenu();
    mainMenu->addTitleItem("Главное меню");
    mainMenu->addItem("Просмотреть список студетов (удалить или изменить данные)"); //0
    mainMenu->addItem("Добавить данные о студенте в БД"); //1
    mainMenu->addItem("Сохранить БД студентов в файл"); //2
    mainMenu->addItem("Выполнить вариант 20"); //3
    mainMenu->addItem("Выход"); //4
    int resultSelectedItem = 0;
    int exitInt = 3;
    ClassMenu* studentsMenu = new ClassMenu();
    studentsMenu->addTitleItem("Список студентов");
    int resultStudentSelectedItem = 1;
    const int exitIntStudentMenu = 0;
    StudentNode* sn;
    StudentClass* st = new StudentClass();
    ClassMenu* delStudentsMenu = new ClassMenu();
    int curCount;
    ClassEdit* ce = new  ClassEdit();
    int startYear = 0;
    int endYear = 0;
    int year = 0;
    StringBuilderClass* sb = new StringBuilderClass();
    while (resultSelectedItem != exitInt) {
        mainMenu->run();
        resultSelectedItem = mainMenu->getSelectedItem();
        switch (resultSelectedItem) {
        case 0:
            resultStudentSelectedItem = 1;
            while (resultStudentSelectedItem != exitIntStudentMenu) {
                studentsMenu->eraseItem();
                studentsMenu->addItem("Выход");
                studentsMenu->addItem("Удалить данные о студенте");
                sn = sdb->getInit();
                while (sn) { // добавить пункты меню ФИО студентов
                    string tmpString = sn->surName + " " + sn->name + " " + sn->middleName + " " + sn->group;
                    studentsMenu->addItem(tmpString); //добавить в меню студентов
                    sn = sn->next;
                }
                studentsMenu->run();
                resultStudentSelectedItem = studentsMenu->getSelectedItem();
                if (resultStudentSelectedItem == exitIntStudentMenu) {
                    break;
                }
                if (resultStudentSelectedItem == 1) //удаление данных о студенте
                {
                    delStudentsMenu->eraseAll();
                    delStudentsMenu->addTitleItem("Выберите студента для удаления данных");
                    delStudentsMenu->addItem("Выход");
                    int resultDel = 1;
                    const int exitDel = 0;
                    sn = sdb->getInit();
                    while (sn) { // добавить пункты меню ФИО студентов
                        string tmpString = sn->surName + " " + sn->name + " " + sn->middleName + " " + sn->group;
                        delStudentsMenu->addItem(tmpString); //добавить в меню студентов
                        sn = sn->next;
                    }
                    while (resultDel != exitDel){
                        delStudentsMenu->run();
                        resultDel = delStudentsMenu->getSelectedItem();
                        //if (resultDel == exitDel) {
                        //    break;
                        //}
                        int num = resultDel - 1;
                        //sdb->delRecord();
                    }
                }
                if (resultStudentSelectedItem>1)
                {
                    int num = resultStudentSelectedItem - 2; //!
                    sn = sdb->getStudentNode(num);   
                    string oldRecordСardNumber = "";
                    oldRecordСardNumber = sn->recordСardNumber;
                    st->editStudent(sn);

                    if (sdb->getSameRecordСardNumber(sn->recordСardNumber)>1)
                    {
                        sn->recordСardNumber = oldRecordСardNumber;
                        cout << "Ошибка введен номер зачетной книжки который уже есть в БД";
                        _getch();
                    }
                }
            }
            //resultSelectedItem = exitInt;
            break;
        case 1:
            sn = new StudentNode();
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 10; j++)
                    sn->examsRecordsData[i][j].isEmpty = true;
            st->editStudent(sn);
            if (sdb->getSameRecordСardNumber(sn->recordСardNumber)==1)
            {
                cout << "Ошибка введен номер зачетной книжки который уже есть в БД";
                _getch();
            }
            else
            {
                sdb->Add(sn);
            }
            break;        
        case 2: //Сохранить в файл
            sdb->saveDataToFile(sdb->FileName);
            //sdb->saveDataToFile("d:\\db1.txt");
            break;
        case 3://Вариант 20
            //sdb->updateAvrMarks();
            system("cls");
            /*cout << "Полный список студентов" << endl;
            //sdb->delRecord(2);
            sdb->printAllSurName_Name_MName_bYaear_avrMarks();
            sdb->sortByAvrMarks();*/
            cout << "Введите за какой семестр выводить студентов: " << endl;
            cin >> l;
            l = l + 10;
            switch(l){
            case 11:
                sdb->updateAvrMarks1();
                cout << "Полный список студентов" << endl;
                sdb->printAllSurName_Name_MName_bYaear_avrMarks();
                sdb->sortByAvrMarks();
                cout << endl << "Отсортированный список студентов" << endl;
                sdb->printAllSurName_Name_MName_bYaear_avrMarks();
                sn = sdb->getInit();
                sdb1->Erase();
                sdb2->Erase();
                break;
            case 12:
                sdb->updateAvrMarks2();
                cout << endl << "Полный список студентов: " << endl;
                sdb->printAllSurName_Name_MName_bYaear_avrMarks();
                sdb->sortByAvrMarks();
                cout << endl << "Отсортированный список студентов" << endl;
                sdb->printAllSurName_Name_MName_bYaear_avrMarks();
                sn = sdb->getInit();
                sdb1->Erase();
                sdb2->Erase();
                break;
            case 13:
                sdb->updateAvrMarks3();
                cout << "Полный список студентов" << endl;
                sdb->printAllSurName_Name_MName_bYaear_avrMarks();
                sdb->sortByAvrMarks();
                cout << endl << "Отсортированный список студентов" << endl;
                sdb->printAllSurName_Name_MName_bYaear_avrMarks();
                sn = sdb->getInit();
                sdb1->Erase();
                sdb2->Erase();
                break;
            case 14:
                sdb->updateAvrMarks4();
                cout << "Полный список студентов" << endl;
                sdb->printAllSurName_Name_MName_bYaear_avrMarks();
                sdb->sortByAvrMarks();
                cout << endl << "Отсортированный список студентов" << endl;
                sdb->printAllSurName_Name_MName_bYaear_avrMarks();
                sn = sdb->getInit();
                sdb1->Erase();
                sdb2->Erase();
                break;
            case 15:
                sdb->updateAvrMarks5();
                cout << "Полный список студентов" << endl;
                sdb->printAllSurName_Name_MName_bYaear_avrMarks();
                sdb->sortByAvrMarks();
                cout << endl << "Отсортированный список студентов" << endl;
                sdb->printAllSurName_Name_MName_bYaear_avrMarks();
                sn = sdb->getInit();
                sdb1->Erase();
                sdb2->Erase();
                break;
            case 16:
                sdb->updateAvrMarks6();
                cout << "Полный список студентов" << endl;
                sdb->printAllSurName_Name_MName_bYaear_avrMarks();
                sdb->sortByAvrMarks();
                cout << endl << "Отсортированный список студентов" << endl;
                sdb->printAllSurName_Name_MName_bYaear_avrMarks();
                sn = sdb->getInit();
                sdb1->Erase();
                sdb2->Erase();
                break;
            case 17:
                sdb->updateAvrMarks7();
                cout << "Полный список студентов" << endl;
                sdb->printAllSurName_Name_MName_bYaear_avrMarks();
                sdb->sortByAvrMarks();
                cout << endl << "Отсортированный список студентов" << endl;
                sdb->printAllSurName_Name_MName_bYaear_avrMarks();
                sn = sdb->getInit();
                sdb1->Erase();
                sdb2->Erase();
                break;
            case 18:
                sdb->updateAvrMarks8();
                cout << "Полный список студентов" << endl;
                sdb->printAllSurName_Name_MName_bYaear_avrMarks();
                sdb->sortByAvrMarks();
                cout << endl << "Отсортированный список студентов" << endl;
                sdb->printAllSurName_Name_MName_bYaear_avrMarks();
                sn = sdb->getInit();
                sdb1->Erase();
                sdb2->Erase();
                break;
            case 19:
                sdb->updateAvrMarks9();
                cout << "Полный список студентов" << endl;
                sdb->printAllSurName_Name_MName_bYaear_avrMarks();
                sdb->sortByAvrMarks();
                cout << endl << "Отсортированный список студентов" << endl;
                sdb->printAllSurName_Name_MName_bYaear_avrMarks();
                sn = sdb->getInit();
                sdb1->Erase();
                sdb2->Erase();
                break;


            }
            break;
        case 4://Выход
            resultSelectedItem = exitInt;
            break;
        default:
            break;
        }
    }
    //_getch();
    
}

