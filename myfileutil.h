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
    fprintf(fp, "%d|%s|%s|%c|%.2lf|%s|%s|\n",
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
void _printAllRowsFromFileWithLabel(char *fileName, char *label, int linesize)
{
    printf(label);
    FILE *fp;
    fp = fopen(fileName, "r");
    char line[linesize];
    // Read and print each line

    while (fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }
    fclose(fp);
}

char *_getValueCorrespondingToEnteredId(char *input, char *fileName, char *errorMessage)
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
        char name[255];
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
char *_safelyReturnValidTableRowValue(char *file, char *prompt1, char *prompt2, char *error)
{
    _printAllRowsFromFileWithLabel(file, prompt1, 255);
    printf("\n");
    char enteredId[50];
    char *tempSelectedVal;
    do
    {
        printf(prompt2);
        gets(enteredId);
        // Remove the trailing newline character from the user input
        enteredId[strcspn(enteredId, "\n")] = '\0';

        tempSelectedVal = _getValueCorrespondingToEnteredId(enteredId, file, error);

    } while (tempSelectedVal == "NOT_FOUND");
    return tempSelectedVal;
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
    system("cls");
    printf("\t\t===============New Transaction Entry===============\n");
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

    tempSelectedVal = _safelyReturnValidTableRowValue("category_dat", "\nNo|Category Name\n", "Enter category No : ", "Enter a valid category No\n");

    sscanf(tempSelectedVal, "%255[^\n]", record.category_name);
    printf("Category selected:%s\n", record.category_name);

    tempSelectedVal = _safelyReturnValidTableRowValue("member_dat", "\nNo|Member Name\n", "Enter Member No : ", "Enter a valid member No\n");
    sscanf(tempSelectedVal, "%255[^\n]", record.member_name);

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

int deleteRowFromTable(char *file, char *prompt1, char *prompt2, char *error)
{
    int deletedCount = 0, count = 0;

    char *tempSelectedVal = _safelyReturnValidTableRowValue(file, prompt1, prompt2, error);

    // temp selected value could be  either the membername or category name.
    char selectedName[255];
    sscanf(tempSelectedVal, "%255[^\n]", selectedName);

    printf("\nAre you sure the remove %s (Y/N) ?", selectedName);
    char yn = 'y';
    yn = getche();
    if (yn == 'y' || yn == 'Y')
    {

        FILE *fp_input, *fp_output;
        fp_input = fopen(file, "r");
        fp_output = fopen("temp", "w");
        char line[1000];
        while (fgets(line, sizeof(line), fp_input))
        {
            int no = 0;
            char name[255];
            sscanf(line, "%d|%255[^\n]", &no, name);
            printf("Name:%s\n", name);
            printf("SelectedName:%s\n", selectedName);
            if (strcmp(name, selectedName) != 0) // this has to be string compare
            {
                fprintf(fp_output, "%d|%s\n",
                        ++count,
                        name);
            }
            else
            {
                deletedCount++;
            }
        }
        fclose(fp_input);
        fclose(fp_output);
        // Delete the original file
        remove(file);
        rename("temp", file);
    }
    else
    {
        deletedCount = -1;
    }
    printf(" Deleted %d record(s)\n", deletedCount);
    return 0;
}
long dateStringToLongValue(char *str)
{
    int day, month, year;
    sscanf(str, "%d/%d/%d", &day, &month, &year);
    long result = year * 10000L + month * 100L + day;
    return result;
}
bool _checkIfTransactionDateBetween(char *line, long stDateLong, long endDateLong)
{
    char transactionDate[20], tempVar;
    int tempNo;
    sscanf(line, "%d|%s|%255[^\n]", &tempNo, transactionDate, tempVar);
    long transDateLong = dateStringToLongValue(transactionDate);

    return transDateLong > stDateLong && transDateLong < endDateLong;
}

// TODO Make this function name as report Transactions and pass a flag, check flag for all transactions.
int reportTransactionsOfAMemberOrCategory(char *file, char *prompt1, char *prompt2, char *error)
{
    char tempValue[255];

    // if flag
    char *tempSelectedVal = _safelyReturnValidTableRowValue(file, prompt1, prompt2, error);
    sscanf(tempSelectedVal, "%255[^\n]", tempValue);
    // else
    // sscanf("", "%s", tempValue);

    char stDate[20] = "";
    do
    {
        printf("Start Date [DD/MM/YYYY] (01/01/1900): ");
        gets(stDate);
        if (strlen(stDate) == 0)
            strcpy(stDate, "01/01/1900");
    } while (!_validateDate(stDate, "Please enter a valid start date"));

    char endDate[20] = "";
    do
    {
        printf("End Date [DD/MM/YYYY] (31/12/9999): ");
        gets(endDate);
        if (strlen(endDate) == 0)
            strcpy(endDate, "31/12/9999");
    } while (!_validateDate(stDate, "Please enter a valid end date"));

    // TODO Concat pipes infornt and behind of tempValue
    FILE *fp;
    fp = fopen("transactions_dat", "r");
    char line[1000];
    while (fgets(line, sizeof(line), fp))
    {
        if (strstr(line, tempValue) != NULL && _checkIfTransactionDateBetween(line, dateStringToLongValue(stDate), dateStringToLongValue(endDate)))
            printf("%s", line);
    }
    fclose(fp);
    return 0;
}
