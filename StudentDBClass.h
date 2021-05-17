#pragma once
#include "StudentClass.h"
#include <iostream>
#include "FileManagerClass.h"
using namespace std;
class StudentDBClass : public FileManagerClass
{
private:
	StudentNode* head;
	StudentNode* getNextNode;
	int count;
public:
	StudentDBClass() {
		head = NULL;
		getNextNode = NULL;
		count = 0;
	}
	~StudentDBClass() {
		Erase();
	}
	bool Erase() {
		head = NULL;
		return true;
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	void loadDataFromFile() {
		string line;
		int count = 0;
		std::ifstream inFile(FileName); // окрываем файл для чтения
		if (inFile.is_open())
		{
			bool isRecord = false;
			StudentNode* sn = new StudentNode();
			for (int i = 0; i < 9; i++)
				for (int j = 0; j < 10; j++)
					sn->examsRecordsData[i][j].isEmpty = true;
			int studentId = 0;
			while (getline(inFile, line))
			{
				if (strcmp(startRecordString.c_str(), line.c_str()) == 0) {
					isRecord = true;
					continue;
				}
				if (strcmp(endRecordString.c_str(), line.c_str()) == 0) {
					isRecord = false;
					studentId++;
					Add(sn);           //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					/// add
					for (int i = 0; i < 9; i++)
						for (int j = 0; j < 10; j++)
							sn->examsRecordsData[i][j].isEmpty = true;
					continue;
				}
				if (isRecord) {

					string valueName = getName(line);
					if (strcmp(getType(line).c_str(), "str") == 0)
					{
						string value = getValueStr(line);
						//cout << value << endl;
						if (strcmp("surName", valueName.c_str()) == 0)
							sn->surName = value;
						if (strcmp("name", valueName.c_str()) == 0)
							sn->name = value;
						if (strcmp("middleName", valueName.c_str()) == 0)
							sn->middleName = value;
						if (strcmp("faculty", valueName.c_str()) == 0)
							sn->faculty = value;
						if (strcmp("department", valueName.c_str()) == 0)
							sn->department = value;
						if (strcmp("group", valueName.c_str()) == 0)
							sn->group = value;
						if (strcmp("recordСardNumber", valueName.c_str()) == 0)
							sn->recordСardNumber = value;
						if (strcmp("birthDateString", valueName.c_str()) == 0)
							sn->birthDateString = value;
						// ExamsRecords
						for (int i = 0; i < 9; i++)
							for (int j = 0; j < 10; j++) {
								//examsResults_0_2_n
											// i j
								string testNameString = "";
								testNameString = testNameString + "examsResults_" + std::to_string(i) + "_" + std::to_string(j) + "_n";
								string testMarkString = "";
								testMarkString = testMarkString + "examsResults_" + std::to_string(i) + "_" + std::to_string(j) + "_m";
								if (strcmp(testNameString.c_str(), valueName.c_str()) == 0) {
									sn->examsRecordsData[i][j].name = value;
									sn->examsRecordsData[i][j].isEmpty = false;
								}
								if (strcmp(testMarkString.c_str(), valueName.c_str()) == 0) {
									sn->examsRecordsData[i][j].mark = atoi(value.c_str());
									sn->examsRecordsData[i][j].isEmpty = false;
								}
							}
					}
					else // Тогда явно int но надо проверить
					{
						int value = getValueInt(line);
						if (strcmp("id", valueName.c_str()) == 0)
							sn->id = studentId;  // сейчас здесь порядковый номер записи в файле
						//должно быть value хорошо бы, но ладно;) !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						if (strcmp("startYear", valueName.c_str()) == 0)
							sn->startYear = value;
						if (strcmp("sex", valueName.c_str()) == 0)
							if (value == 0)
								sn->sex = false;
							else
								sn->sex = true;
					}
				}
			}
			inFile.close();     // закрываем файл
		}
		else {
			cout << " \n Файл БД не найден \n";
			_getch();
		}
		inFile.close();
	}
	void saveDataToFile(string inFileName) {
		std::ofstream outFile;          // поток для записи
		ifstream iff(inFileName); //если файл есть удаляем
		if (iff.bad() == false)
		{
			iff.close();
			if (remove(inFileName.c_str())) {
				printf("Error removing file");
				_getch();
			}

		}
		outFile.open(inFileName, std::ios::app); // окрываем файл для записи
		// outFile.open(FileName, std::ios::app); // окрываем файл для записи
		if (outFile.is_open())
		{
			StudentClass st = StudentClass();
			int recordsCount = GetRecordCountOfList();
			StudentNode* sn;
			for (int i = 0; i < recordsCount; i++) {
				//st.addRusakov();
				outFile << startRecordString << std::endl;
				sn = getStudentNode(i);
				st.UpdateMasString(sn);
				st.getInitStringRecord();
				string resultString = st.getStringRecord();
				while (resultString.length() > 0) {
					outFile << resultString << std::endl;
					resultString = st.getStringRecord();
				}
				outFile << endRecordString << std::endl;
			}

		}
		outFile.close();
	}
	void setData(StudentNode* tNode, StudentNode* st) {
		tNode->surName = st->surName;
		tNode->name = st->name;
		tNode->middleName = st->middleName;
		tNode->faculty = st->faculty;
		tNode->department = st->department;
		tNode->group = st->group;
		tNode->recordСardNumber = st->recordСardNumber;
		tNode->sex = st->sex;
		tNode->startYear = st->startYear;
		tNode->birthDateString = st->birthDateString;
		tNode->avrMarks = st->avrMarks; ///!!!!
		// //по аналогии
		//ExamsRecords data[9][10];
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 10; j++) {
				tNode->examsRecordsData[i][j].isEmpty = st->examsRecordsData[i][j].isEmpty;
				tNode->examsRecordsData[i][j].name = st->examsRecordsData[i][j].name;
				tNode->examsRecordsData[i][j].mark = st->examsRecordsData[i][j].mark;
			}
		//tNode->isNULL = false;
	}
	bool Add(StudentNode* st) {
		if (!head)
		{
			head = new StudentNode();
			//head->surName = st->surName;
			setData(head, st);
			//head->data = st;
			head->next = NULL;
			count++;
			return true;
		}
		else
		{
			StudentNode* tmp = new StudentNode();
			setData(tmp, st); //!!!!
			//tmp->data = st;
			tmp->next = head;
			head = tmp;
			count++;
			return true;
		}
		return false;
	}
	StudentNode* getInit() {
		return getNextNode = head;
	}
	int getCount() {
		return count;
	}
	void printAllSurName() {
		StudentNode* curr = NULL;
		curr = head;
		while (curr) {
			cout << curr->surName << endl;
			curr = curr->next;
		}
	}
	StudentNode* getStudentNode(int num) {
		StudentNode* curr = NULL;
		curr = head;
		int ind = 0;
		while (curr) {
			//cout << curr->surName << endl;
			if (ind == num) {
				return curr;
				break;
			}
			else {
				curr = curr->next;
				ind++;
			}
		}
		return NULL;
	}
	int GetRecordCountOfList() {
		return count;
	};
	void delRecord(int num) {
		StudentNode* curr = NULL;
		curr = head;
		if (num == 0) {
			if (head->next == NULL) {
				delete(head);
			}
			else {
				head = head->next;
				delete(curr);
			}
		}
		else {
			int cCount = 0;
			while (curr) {
				if (cCount == num - 1) {  ///!!!!!!!!!!!!!!!111111
					StudentNode* tmp;
					tmp = curr->next;
					if (curr->next->next == NULL) {
						curr->next = NULL;
					}
					else
						curr->next = curr->next->next;
					delete(tmp);
				}
				else
					curr = curr->next;
				cCount++;
			}
		}
		count--;
	};
	int getSameRecordСardNumber(string inString) {
		StudentNode* curr = NULL;
		curr = head;
		int count = 0;
		while (curr) {
			//cout << curr->surName << endl;
			if (strcmp(inString.c_str(), curr->recordСardNumber.c_str()) == 0) {
				count++;
			}
			curr = curr->next;
		}
		return count;
	}



	void updateAvrMarks() {
		StudentNode* curr = NULL;
		StudentClass* stud = new StudentClass();
		curr = head;
		while (curr) {
			curr->avrMarks = stud->getAvrMarks(curr);
			curr = curr->next;
		}
		delete stud;
	}
	void updateAvrMarks1() {
		StudentNode* curr = NULL;
		StudentClass* stud = new StudentClass();
		curr = head;
		while (curr) {
			curr->avrMarks = stud->getAvrMarks1(curr);
			curr = curr->next;
		}
		delete stud;
	}
	void updateAvrMarks2() {
		StudentNode* curr = NULL;
		StudentClass* stud = new StudentClass();
		curr = head;
		while (curr) {
			curr->avrMarks = stud->getAvrMarks2(curr);
			curr = curr->next;
		}
		delete stud;
	}
	void updateAvrMarks3() {
		StudentNode* curr = NULL;
		StudentClass* stud = new StudentClass();
		curr = head;
		while (curr) {
			curr->avrMarks = stud->getAvrMarks3(curr);
			curr = curr->next;
		}
		delete stud;
	}
	void updateAvrMarks4() {
		StudentNode* curr = NULL;
		StudentClass* stud = new StudentClass();
		curr = head;
		while (curr) {
			curr->avrMarks = stud->getAvrMarks4(curr);
			curr = curr->next;
		}
		delete stud;
	}
	void updateAvrMarks5() {
		StudentNode* curr = NULL;
		StudentClass* stud = new StudentClass();
		curr = head;
		while (curr) {
			curr->avrMarks = stud->getAvrMarks5(curr);
			curr = curr->next;
		}
		delete stud;
	}
	void updateAvrMarks6() {
		StudentNode* curr = NULL;
		StudentClass* stud = new StudentClass();
		curr = head;
		while (curr) {
			curr->avrMarks = stud->getAvrMarks6(curr);
			curr = curr->next;
		}
		delete stud;
	}
	void updateAvrMarks7() {
		StudentNode* curr = NULL;
		StudentClass* stud = new StudentClass();
		curr = head;
		while (curr) {
			curr->avrMarks = stud->getAvrMarks7(curr);
			curr = curr->next;
		}
		delete stud;
	}
	void updateAvrMarks8() {
		StudentNode* curr = NULL;
		StudentClass* stud = new StudentClass();
		curr = head;
		while (curr) {
			curr->avrMarks = stud->getAvrMarks8(curr);
			curr = curr->next;
		}
		delete stud;
	}
	void updateAvrMarks9() {
		StudentNode* curr = NULL;
		StudentClass* stud = new StudentClass();
		curr = head;
		while (curr) {
			curr->avrMarks = stud->getAvrMarks9(curr);
			curr = curr->next;
		}
		delete stud;
	}

	void printAllSurName_Name_MName_bYaear_avrMarks1() {//выводит всех студентов
		StudentNode* curr = NULL;
		StringBuilderClass* sb = new StringBuilderClass();
		curr = head;
		while (curr) {
			cout << curr->surName + " " + curr->name + " " + curr->middleName + " " + " " << endl;
			curr = curr->next;
		}
		delete sb;
	}

	void printAllSurName_Name_MName_bYaear_avrMarks() {//выводит уже сортировкy по оценке
		StudentNode* curr = NULL;
		StringBuilderClass* sb = new StringBuilderClass();
		curr = head;
		while (curr) {
			cout << curr->surName + " " + curr->name + " " + curr->middleName + " " + " " + to_string(curr->avrMarks) << endl;
			curr = curr->next;
		}
		delete sb;
	}

	double getMaxAvrMarks() {//сама сортировка

		StudentNode* curr = NULL;
		curr = head;
		int max = 0, i = 0;

		while (curr) {
			if (max < curr->avrMarks)
				max = curr->avrMarks;
			curr = curr->next;
		}
		return max;
	}
	double getMaxAvrMarks1() {//сама сортировка

		StudentNode* curr = NULL;
		curr = head;
		int max = 0, i = 0;

		while (curr) {
			if (max < curr->avrMarks)
				max = curr->avrMarks;
			curr = curr->next;
		}
		return max;
	}
	double getMaxAvrMarks2() {//сама сортировка
		StudentNode* curr = NULL;
		curr = head;
		int max = 0, i = 1;

		while (curr) {
			if (max < curr->avrMarks)
				max = curr->avrMarks;
			curr = curr->next;
		}
		return max;

	}
	double getMaxAvrMarks3() {//сама сортировка
		StudentNode* curr = NULL;
		curr = head;
		int max = 0, i = 2;
		while (curr) {
			if (max < curr->avrMarks)
				max = curr->avrMarks;
			curr = curr->next;
		}
		return max;

	}
	double getMaxAvrMarks4() {//сама сортировка
		StudentNode* curr = NULL;
		curr = head;
		int max = 0, i = 3;
		while (curr) {
			if (max < curr->avrMarks)
				max = curr->avrMarks;
			curr = curr->next;
		}
		return max;

	}
	double getMaxAvrMarks5() {//сама сортировка
		StudentNode* curr = NULL;
		curr = head;
		int max = 0, i = 4;
		while (curr) {
			if (max < curr->avrMarks)
				max = curr->avrMarks;
			curr = curr->next;
		}
		return max;

	}
	double getMaxAvrMarks6() {//сама сортировка
		StudentNode* curr = NULL;
		curr = head;
		int max = 0, i = 5;
		while (curr) {
			if (max < curr->avrMarks)
				max = curr->avrMarks;
			curr = curr->next;
		}
		return max;

	}
	double getMaxAvrMarks7() {//сама сортировка
		StudentNode* curr = NULL;
		curr = head;
		int max = 0, i = 6;
		while (curr) {
			if (max < curr->avrMarks)
				max = curr->avrMarks;
			curr = curr->next;
		}
		return max;

	}
	double getMaxAvrMarks8() {//сама сортировка
		StudentNode* curr = NULL;
		curr = head;
		int max = 0, i = 7;
		while (curr) {
			if (max < curr->avrMarks)
				max = curr->avrMarks;
			curr = curr->next;
		}
		return max;

	}
	double getMaxAvrMarks9() {//сама сортировка
		StudentNode* curr = NULL;
		curr = head;
		int max = 0, i = 8;
		while (curr) {
			if (max < curr->avrMarks)
				max = curr->avrMarks;
			curr = curr->next;
		}
		return max;

	}


	void sortByAvrMarks() {
		StudentNode* curr = NULL;
		curr = head;
		int max = 0;
		StudentDBClass* sdbT = new StudentDBClass();
		while (count > 1) {
			curr = head;
			max = getMaxAvrMarks();
			int cCount = 0;
			while (curr) {
				if (curr->avrMarks == max)
				{
					sdbT->Add(curr);
					delRecord(cCount);
					break;
				}
				curr = curr->next;
				cCount++;
			}

		}
		while (sdbT->getCount() > 0) {
			Add(sdbT->getStudentNode(0));
			sdbT->delRecord(0);
		}
		delete sdbT;
	}
	void sortByAvrMarks1() {
		StudentNode* curr = NULL;
		curr = head;
		int max = 0;
		StudentDBClass* sdbT = new StudentDBClass();
		while (count > 1) {
			curr = head;
			max = getMaxAvrMarks1();
			int cCount = 0;
			while (curr) {
				if (curr->avrMarks == max)
				{
					sdbT->Add(curr);
					delRecord(cCount);
					break;
				}
				curr = curr->next;
				cCount++;
			}

		}
		while (sdbT->getCount() > 0) {
			Add(sdbT->getStudentNode(0));
			sdbT->delRecord(0);
		}
		delete sdbT;
	}
	void sortByAvrMarks2() {
		StudentNode* curr = NULL;
		curr = head;
		int max = 0;
		StudentDBClass* sdbT = new StudentDBClass();
		while (count > 1) {
			curr = head;
			max = getMaxAvrMarks2();
			int cCount = 0;
			while (curr) {
				if (curr->avrMarks == max)
				{
					sdbT->Add(curr);
					delRecord(cCount);
					break;
				}
				curr = curr->next;
				cCount++;
			}
		}
		while (sdbT->getCount() > 0) {
			Add(sdbT->getStudentNode(0));
			sdbT->delRecord(0);
		}
		delete sdbT;
	}
	void sortByAvrMarks3() {
		StudentNode* curr = NULL;
		curr = head;
		int max = 0;
		StudentDBClass* sdbT = new StudentDBClass();
		while (count > 1) {
			curr = head;
			max = getMaxAvrMarks3();
			int cCount = 0;
			while (curr) {
				if (curr->avrMarks == max)
				{
					sdbT->Add(curr);
					delRecord(cCount);
					break;
				}
				curr = curr->next;
				cCount++;
			}
		}
		while (sdbT->getCount() > 0) {
			Add(sdbT->getStudentNode(0));
			sdbT->delRecord(0);
		}
		delete sdbT;
	}
	void sortByAvrMarks4() {
		StudentNode* curr = NULL;
		curr = head;
		int max = 0;
		StudentDBClass* sdbT = new StudentDBClass();
		while (count > 1) {
			curr = head;
			max = getMaxAvrMarks4();
			int cCount = 0;
			while (curr) {
				if (curr->avrMarks == max)
				{
					sdbT->Add(curr);
					delRecord(cCount);
					break;
				}
				curr = curr->next;
				cCount++;
			}
		}
		while (sdbT->getCount() > 0) {
			Add(sdbT->getStudentNode(0));
			sdbT->delRecord(0);
		}
		delete sdbT;
	}
	void sortByAvrMarks5() {
		StudentNode* curr = NULL;
		curr = head;
		int max = 0;
		StudentDBClass* sdbT = new StudentDBClass();
		while (count > 1) {
			curr = head;
			max = getMaxAvrMarks5();
			int cCount = 0;
			while (curr) {
				if (curr->avrMarks == max)
				{
					sdbT->Add(curr);
					delRecord(cCount);
					break;
				}
				curr = curr->next;
				cCount++;
			}
		}
		while (sdbT->getCount() > 0) {
			Add(sdbT->getStudentNode(0));
			sdbT->delRecord(0);
		}
		delete sdbT;
	}
	void sortByAvrMarks6() {
		StudentNode* curr = NULL;
		curr = head;
		int max = 0;
		StudentDBClass* sdbT = new StudentDBClass();
		while (count > 1) {
			curr = head;
			max = getMaxAvrMarks6();
			int cCount = 0;
			while (curr) {
				if (curr->avrMarks == max)
				{
					sdbT->Add(curr);
					delRecord(cCount);
					break;
				}
				curr = curr->next;
				cCount++;
			}
		}
		while (sdbT->getCount() > 0) {
			Add(sdbT->getStudentNode(0));
			sdbT->delRecord(0);
		}
		delete sdbT;
	}
	void sortByAvrMarks7() {
		StudentNode* curr = NULL;
		curr = head;
		int max = 0;
		StudentDBClass* sdbT = new StudentDBClass();
		while (count > 1) {
			curr = head;
			max = getMaxAvrMarks7();
			int cCount = 0;
			while (curr) {
				if (curr->avrMarks == max)
				{
					sdbT->Add(curr);
					delRecord(cCount);
					break;
				}
				curr = curr->next;
				cCount++;
			}
		}
		while (sdbT->getCount() > 0) {
			Add(sdbT->getStudentNode(0));
			sdbT->delRecord(0);
		}
		delete sdbT;
	}
	void sortByAvrMarks8() {
		StudentNode* curr = NULL;
		curr = head;
		int max = 0;
		StudentDBClass* sdbT = new StudentDBClass();
		while (count > 1) {
			curr = head;
			max = getMaxAvrMarks8();
			int cCount = 0;
			while (curr) {
				if (curr->avrMarks == max)
				{
					sdbT->Add(curr);
					delRecord(cCount);
					break;
				}
				curr = curr->next;
				cCount++;
			}
		}
		while (sdbT->getCount() > 0) {
			Add(sdbT->getStudentNode(0));
			sdbT->delRecord(0);
		}
		delete sdbT;
	}
	void sortByAvrMarks9() {
		StudentNode* curr = NULL;
		curr = head;
		int max = 0;
		StudentDBClass* sdbT = new StudentDBClass();
		while (count > 1) {
			curr = head;
			max = getMaxAvrMarks9();
			int cCount = 0;
			while (curr) {
				if (curr->avrMarks == max)
				{
					sdbT->Add(curr);
					delRecord(cCount);
					break;
				}
				curr = curr->next;
				cCount++;
			}
		}
		while (sdbT->getCount() > 0) {
			Add(sdbT->getStudentNode(0));
			sdbT->delRecord(0);
		}
		delete sdbT;
	}
};