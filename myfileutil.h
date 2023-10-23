#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
/*
10-10-2025#abcdegdfdfd#333.3343#

Transaction Table
Sl_NO, Date, Description, Income_Expense (I/E),Amout, Category, Member_ID


Member Table
Member_ID, Name

Category_Table
Category_ID,Category

Keys
Key_name,Key_Value

Read all Expenses
    From_DATE to To_DATE
    Category Wise
    Member Wise

Append Expense / Income
Delete a Record

CRUD for other tables.

===================================
Read Max Key value & increment a value

*/

int getKeyValueAndIncrementNSave(char *key_name)
{
    FILE *fp;
    int val = 0;
    /* Opens a file and read the value*/
    fp = fopen(key_name, "r");
    fscanf(fp, "%d,", &val);
    fclose(fp);
    fp = fopen(key_name, "w");
    fprintf(fp, "%d", ++val);
    fclose(fp);
    return val;
}

struct TransactionRecord
{
    int transaction_id;
    char date[15];
    char description[100];
    char income_expense;
    double amount;
    char category_name[50];
    char member_name[50];
};

int saveAndAppendTransactions(struct TransactionRecord a_record)
{
    FILE *fp;
    fp = fopen("transactions_dat", "a+");
    fprintf(fp, "%d|%s|%s|%c|%.2lf|%s|%s\n",
            getKeyValueAndIncrementNSave("TRANSACTION_KEY"),
            a_record.date,
            a_record.description,
            a_record.income_expense,
            a_record.amount,
            a_record.category_name,
            a_record.member_name);
    fclose(fp);
    return 0;
}

int printTransactionRecord(struct TransactionRecord a_record)
{

    printf("Date:%s\nDescription:%s\nIncome/Expense:%c\nAmount:%.2lf\nCategory Name:%s\nMember Name:%s\n",
           a_record.date,
           a_record.description,
           a_record.income_expense,
           a_record.amount,
           a_record.category_name,
           a_record.member_name);
    return 0;
}

struct memberOrCategoryRecord
{
    int id;
    char name[50];
};

int appendNewMemberOrCategory(char *file, char *keyFileName, struct memberOrCategoryRecord a_record)
{
    FILE *fp;
    fp = fopen(file, "a+");
    fprintf(fp, "%d|%s\n",
            getKeyValueAndIncrementNSave(keyFileName),
            a_record.name);
    fclose(fp);
    return 0;
}

bool _isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool _validateDate(const char *dateStr, char *error)
{
    int month, day, year;
    if (sscanf(dateStr, "%d/%d/%d", &day, &month, &year) == 3)
    {
        if (month >= 1 && month <= 12)
        {
            int daysInMonth[] = {0, 31, 28 + _isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if (day >= 1 && day <= daysInMonth[month])
            {
                return true;
            }
        }
    }
    printf(error);
    printf("\n");
    return false;
}

// bool isNotIE(char *)

bool _isIE(char ch)
{
    if (ch == 'I' || ch == 'E')
        return true;
    else
    {
        printf("Valid entries are only I or E\n");
        return false;
    }
}

bool _checkAmountGtZero(double dbl, char *error)
{
    if (dbl <= 0)
    {
        printf(error);
        printf("\n");
        return false;
    }
    else
    {
        return true;
    }
}
void _printAllCategoriesOrMembers(char *fileName, char *label)
{
    printf(label);
    FILE *fp;
    fp = fopen(fileName, "r");
    char line[80];
    // Read and print each line
    while (fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }
    fclose(fp);
}

char *_checkCatgoryOrMember(char *input, char *fileName, char *errorMessage)
{

    char *a = "NOT_FOUND";
    int inputVal = 0;
    // read the category id from user input
    sscanf(input, "%d", &inputVal);

    FILE *file;
    file = fopen(fileName, "r");
    char line[1000];
    while (fgets(line, sizeof(line), file))
    {
        int no = 0;
        char name[50];
        sscanf(line, "%d|%255[^\n]", &no, name);
        if (inputVal == no)
        {
            fclose(file);
            a = name;
            break;
        }
    }
    fclose(file);
    if (a == "NOT_FOUND")
    {
        printf(errorMessage);
    }
    return a;
}

int acceptDataForNewTransaction()
{
    struct TransactionRecord record;
    record.transaction_id = 0;
    record.amount = 0;

    sscanf("", "%s", record.description);
    sscanf("", "%s", record.date);
    record.income_expense = ' ';
    sscanf("", "%s", record.category_name);
    sscanf("", "%s", record.member_name);

    char *tempSelectedVal;

    char amountString[20];
    char enteredCategory[50];
    char enteredMember[50];

    do
    {
        printf("Date [DD/MM/YYYY] : ");
        gets(record.date);

    } while (!_validateDate(record.date, "Please enter a valid transaction date"));

    printf("Description :");
    gets(record.description);

    do
    {
        printf("Income/Expense[I/E] : ");
        record.income_expense = toupper(getche());
        // getch(); // This is a hack
    } while (!_isIE(record.income_expense));

    do
    {
        printf("\nAmount :");
        gets(amountString);
        record.amount = strtod(amountString, NULL);
    } while (!_checkAmountGtZero(record.amount, "Transaction should be more than zero"));

    _printAllCategoriesOrMembers("category_dat", "\nNo|Category Name\n");
    printf("\n");

    do
    {
        printf("Enter category No : ");
        gets(enteredCategory);
        // Remove the trailing newline character from the user input
        enteredCategory[strcspn(enteredCategory, "\n")] = '\0';
        tempSelectedVal = _checkCatgoryOrMember(enteredCategory, "category_dat", "Enter a valid category No\n");

    } while (tempSelectedVal == "NOT_FOUND");
    sscanf(tempSelectedVal, "%s", record.category_name);
    printf("Category selected:%s\n", record.category_name);

    _printAllCategoriesOrMembers("member_dat", "\nNo|Member Name\n");

    do
    {
        printf("Enter Member No : ");
        gets(enteredMember);
        // Remove the trailing newline character from the user input
        enteredMember[strcspn(enteredMember, "\n")] = '\0';

        tempSelectedVal = _checkCatgoryOrMember(enteredMember, "member_dat", "Enter a valid member No\n");

    } while (tempSelectedVal == "NOT_FOUND");
    sscanf(tempSelectedVal, "%s", record.member_name);

    printf("Member selected:%s\n", record.member_name);

    printf("\n\n");
    printTransactionRecord(record);
    printf("\nAre you sure the above transacton (Y/N) ?");
    char yn = 'y';
    yn = getche();
    if (yn == 'y' || yn == 'Y' || yn == 13)
    {
        saveAndAppendTransactions(record);
        printf("\nTransaction Saved\n");
    }
    else
    {
        printf("\nDiscarded..\n");
    }
    return 0;
}

int acceptNewMemberOrCategoryData(char *label, char *file, char *keyFileName)
{
    struct memberOrCategoryRecord record;
    printf(label);
    gets(record.name);
    appendNewMemberOrCategory(file, keyFileName, record);
    return 0;
}
