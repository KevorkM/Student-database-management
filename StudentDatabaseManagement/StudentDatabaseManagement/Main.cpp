#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <iomanip>

using namespace std;


int main() {

	FILE *fp, *ft;
	char another, choice;

	struct student {
		char FirstName[50], LastName[50];
		char Course[100];
		int section;
	};

	struct student e;
	char xFirstName[50], xLastName[50];
	long int RecSize;

	fp = fopen("users.txt", "rb+");

	if (fp == NULL) {
		fp = fopen("users.txt", "wb+");
		if (fp == NULL) {
			puts("Cannot open file");
			return 0;
		}
	}

	RecSize = sizeof(e);

	while (1) {
		system("cls");

		cout << "\t\t ===== STUDENT DATABASE MANAGEMENT SYSTEM ======";
		cout << "\n\n";
		cout << "\n\n";
		cout << "\n \t\t\t 1. Add		Records";
		cout << "\n \t\t\t 2. List		Records";
		cout << "\n \t\t\t 3. Modify	Records";
		cout << "\n \t\t\t 4. Delete	Records";
		cout << "\n \t\t\t 5. Exit		Records";
		cout << "\n\n";
		cout << "\t\t\t Select your choice :=>";
		fflush(stdin);
		choice = getche();
		
		switch (choice) {
		case 1:
			fseek(fp, 0, SEEK_END);
			another = 'Y';
			while (another == 'Y' || another == 'y') {
				system("cls");
				cout << "Enter the first name: ";
				cin >> e.FirstName;
				cout << "Enter the last name: ";
				cin >> e.LastName;
				cout << "Enter the name of the course: ";
				cin >> e.Course;
				cout << "Enter the Section: ";
				cin >> e.section;

				fwrite(&e, RecSize, 1, fp);
				cout << "\n Add an other record? (Y/N) ";
				fflush(stdin);
				another = getchar();
			}
			break;

			case 2:
				system("cls");
				rewind(fp);
				cout << "=== View the records in the database ===";
				cout << "\n";

				while (fread(&e, RecSize, 1, fp) == 1) {
					cout << "\n";
					cout << "\n" << e.FirstName << setw(10) << e.LastName;
					cout << "\n";
					cout << "\n" << e.Course << setw(8) << e.section;
				}
				cout << "\n\n";
				system("pause");
				break;

			case 3:
				system("cls");
				another = 'Y';
				while (another == 'Y' || another == 'y') {
					cout << "\n Enter the last name of the student: ";
					cin >> xLastName;

					rewind(fp);
					while (fread(&e, RecSize, 1, fp) == 1) {
						if (strcmp(e.LastName, xLastName) == 0) {
							cout << "Enter the new First Name: ";
							cin >> e.FirstName;
							cout << "Enter the new Last name: ";
							cin >> e.LastName;
							cout << "Enter the new Course: ";
							cin >> e.Course;
							cout << "Enter the new section";
							cin >> e.section;
							
							fseek(fp, -RecSize, SEEK_CUR);
							fwrite(&e, RecSize, 1, fp);
							break;
						}
						else 
							cout << "record not found";
						}
						cout << "\n Modify another record? (Y/N) ";
						fflush(stdin);

						another = getchar();
					}
				break;
				
			case 4:
				system("cls");
				another = 'Y';

				while (another == 'Y' || another == 'y'){
					cout << "\n Enter the last name of the student to delete: ";
					cin >> xLastName;

					ft = fopen("temp.dat", "wb");

					rewind(fp);

					while (fread(&e, RecSize, 1, fp) == 1)
						if (strcmp(e.LastName, xLastName) != 0) {
							fwrite(&e, RecSize, 1, ft);
						}
					fclose(fp);
					fclose(ft);
					remove("user.txt");
					rename("temp.dat", "users.txt");

					fp = fopen("user.txt", "rb+");

					cout << "\n Delete Another Record (Y/N)";
					fflush(stdin);
					another = getchar();
				}
				break;

			case 5:
				fclose(fp);
				cout << "\n\n";
				cout << "\t\t		THANK YOU FOR USING THIS SOFTWARE";
				cout << "\n\n";
				exit(0);
			}
		}
		system("pause");
		return 0;
	}
