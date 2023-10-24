#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int getKeyValueAndIncrementNSave(char *key_name)
{
    // used to add ids to each of the records in all three files,that is,transactions_dat,member_dat and category_name
    //'key_name' is the name of the file
    FILE *fp;
    int val = 0; // the first time the function is called, 0 is appended and 1 is written into the file
    fp = fopen(key_name, "r");
    fscanf(fp, "%d,", &val); // reads the value from the file
    fclose(fp);
    fp = fopen(key_name, "w");
    fprintf(fp, "%d", ++val); // overwrites the appended value to the file
    fclose(fp);
    return val;
}

struct TransactionRecord
{
    // describes the structure of an individual record in the transaction file
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
    fp = fopen("transactions_dat", "a+");                    // opens the file 'transactions_dat' in append mode
    fprintf(fp, "%d|%s|%s|%c|%.2lf|%s|%s|\n",                // writes 'a_record' to the file 'transactions_dat'
            getKeyValueAndIncrementNSave("TRANSACTION_KEY"), // increments 1 to the TRANSACTION_KEY whose value signifies the id of that particular record
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
    // used for printing the contents of the variable 'a_record' which is of the type struct TransactionRecord
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
    // describes the structure of an individual record in the member or category file
    int id;
    char name[50];
};

int appendNewMemberOrCategory(char *file, char *keyFileName, struct memberOrCategoryRecord a_record)
{
    //'file' indicate if the record need to be written into 'member_dat' or 'category_dat'
    //'keyFileName' is used to indicate whether to key value to be incremented is in 'MEMBER_KEY' or 'CATEGORY_KEY'
    //'a_record' is the record to be written into 'file'
    FILE *fp;
    fp = fopen(file, "a+");                            // opens 'file' in append mode
    fprintf(fp, "%d|%s\n",                             // writes 'a_record' to 'file'
            getKeyValueAndIncrementNSave(keyFileName), // increments 1 to 'keyFileName' whose value signifies the id of that particular record
            a_record.name);
    fclose(fp);
    return 0;
}

bool _isLeapYear(int year)
{
    // Checks if a particular year is a leap year. If it is a leap year then 29th of February will be considered a valid date
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool _validateDate(const char *dateStr, char *error) // Checks if a date is valid,that is, in the form DD/MM/YYYY where the date, month and year have valid values
{
    int month, day, year;
    if (sscanf(dateStr, "%d/%d/%d", &day, &month, &year) == 3) // Checks if all three, that is, day,month and year are present and if false prints error message
    {
        if (month >= 1 && month <= 12) // Checks if the month value is between 1 and 12 and if false prints error message
        {
            int daysInMonth[] = {0, 31, 28 + _isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // daysInMonth stores the number of valid days in a month depending on the month
            if (day >= 1 && day <= daysInMonth[month])                                                   // Checks if the date value is valid for the given month and if false prints error message
            {
                return true; // returns true if the date is valid
            }
        }
    }
    printf(error); // prints an error message stating that the date is not valid
    printf("\n");
    return false; // returns false if the date is not valid
}

bool _isIE(char ch)
{
    // Checks is the variable 'ch' is valid, that is either i,I,e or E. If valid, the fuction returns true and if invalid,prints error message and the function returns false
    if (ch == 'I' || ch == 'E' || ch == 'i' || ch == 'e')
        return true;
    else
    {
        printf("Valid entries are only I or E\n");
        return false;
    }
}

bool _checkAmountGtZero(double dbl, char *error)
{
    // Checks if the amount entered by user is >0.If true, the function returns true and if false, prints appropriate error message and the function returns false
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
    // used for printing each record of a file
    //'fileName' is the file from which the contents are to be printed
    //'label' is the message to be printed before displaying the contents of the file
    //'linesize' is the maximum size of the character array 'line' which stores each record of a file
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
    int inputVal = -1;
    sscanf(input, "%d", &inputVal);

    FILE *file;
    file = fopen(fileName, "r"); // opens file
    char line[1000];
    while (fgets(line, sizeof(line), file)) //'line' is each record of the file with each iteration
    {
        int no = 0;
        char name[255];
        sscanf(line, "%d|%255[^\n]", &no, name); // obtains the id and text after the id from each record and reads to 'no' and 'name' respectively

        if (inputVal == no) // Checks is the entered id is equal to no(which is the id of each record with each iteration)
        {
            fclose(file);
            a = name; // name(all contents of a record except for id) is read to a variable 'a'
            break;
        }
    }
    fclose(file);
    if (a == "NOT_FOUND")
    {
        printf(errorMessage); // if entered is is not present in the file,appropriate error message is printed
    }
    return a;
}
char *_safelyReturnValidTableRowValue(char *file, char *prompt1, char *prompt2, char *error)
{
    // Checks if the entered id of a file is present in the table
    //'file' is the file to be displayed
    //'prompt1' is the message to be displayed before printing the contents of 'file'
    //'prompt2' is the message to be printed to the user for recieving input
    //'error' is the message to be printed if the entered id is not present in 'file'
    _printAllRowsFromFileWithLabel(file, prompt1, 255);
    printf("\n");
    char enteredId[50];
    char *tempSelectedVal;
    do
    {
        // loop will continue execution till a valid id is entered
        printf(prompt2);
        gets(enteredId);
        enteredId[strcspn(enteredId, "\n")] = '\0'; // Remove the trailing newline character from the user input

        tempSelectedVal = _getValueCorrespondingToEnteredId(enteredId, file, error); // if entered id is not present in the file, 'tempSelectedVal' will be 'NOT_FOUND'

    } while (tempSelectedVal == "NOT_FOUND");
    return tempSelectedVal; // reurns the value of each record excluding the id
}

int acceptDataForNewTransaction()
{
    // Used to accept a new transaction record

    struct TransactionRecord record;
    record.transaction_id = 0;
    record.amount = 0;
    sscanf("", "%s", record.description);
    sscanf("", "%s", record.date);
    record.income_expense = ' ';
    sscanf("", "%s", record.category_name);
    sscanf("", "%s", record.member_name);
    // Creates a new variable 'record' of type 'struct TransactionRecord' in which all members that are numbers are equated to 0 and all members that are strings are read as empty strings

    char *tempSelectedVal;

    char amountString[20];
    char enteredCategory[50];
    do
    {
        printf("Date [DD/MM/YYYY] : ");
        gets(record.date);
    } while (!_validateDate(record.date, "Please enter a valid transaction date")); // inputs dates from the user till a valid date in entered

    printf("Description :");
    gets(record.description);

    do
    {
        printf("Income/Expense[I/E] : ");
        record.income_expense = toupper(getche());
        // getch(); // This is a hack
    } while (!_isIE(record.income_expense)); // accepts input from the user till the valid input is entered, that is , i,I,e or E is entered

    do
    {
        printf("\nAmount :");
        gets(amountString);
        record.amount = strtod(amountString, NULL);
    } while (!_checkAmountGtZero(record.amount, "Transaction should be more than zero")); // accepts input from the user till an amount >0 is entered

    tempSelectedVal = _safelyReturnValidTableRowValue("category_dat", "\nNo|Category Name\n", "Enter category No : ", "Enter a valid category No\n"); // tempSelectedVal will be the category name

    sscanf(tempSelectedVal, "%255[^\n]", record.category_name); // reads category_name to the structure 'record'
    printf("Category selected:%s\n", record.category_name);

    tempSelectedVal = _safelyReturnValidTableRowValue("member_dat", "\nNo|Member Name\n", "Enter Member No : ", "Enter a valid member No\n"); // tempSelectedVal will be the member name

    sscanf(tempSelectedVal, "%255[^\n]", record.member_name); // reads member_name to the structure
    printf("Member selected:%s\n", record.member_name);

    printf("\n\n");
    printTransactionRecord(record);                        // displays the data in 'record'
    printf("\nAre you sure the above transacton (Y/N) ?"); // confirms is the displayed data can be read to the file
    char yn = 'y';
    yn = getche();
    if (yn == 'y' || yn == 'Y' || yn == 13) // if confirmation is recieved as 'y' or 'Y' the record is written into the file 'transactions_dat'
    {
        saveAndAppendTransactions(record);
        printf("\nTransaction Saved\n");
    }
    else // if confirmation is not recieved, the record is discarded
    {
        printf("\nDiscarded..\n");
    }

    return 0;
}

int acceptNewMemberOrCategoryData(char *label, char *file, char *keyFileName)
{
    // Used to accept a new member or category record
    //'label' is the message to be printed for getting the member or category name from the user
    //'file' is used to indicate whether the record to be added is to 'member_dat' or 'category_dat'
    //'keyFileName' is used to indicate whether to key value to be incremented is in 'MEMBER_KEY' or 'CATEGORY_KEY'
    struct memberOrCategoryRecord record;
    printf(label);
    gets(record.name);
    appendNewMemberOrCategory(file, keyFileName, record);
    return 0;
}

int deleteRowFromTable(char *file, char *prompt1, char *prompt2, char *error)
{
    // used to delete a particular row from a file based on the record id
    int deletedCount = 0, count = 0;

    char *tempSelectedVal = _safelyReturnValidTableRowValue(file, prompt1, prompt2, error); // tempSelectedVal is the content of the record except for the id
    //'_safelyReturnValidTableRowValue' is used to check if the id (of the record to be deleted) inputed from the user is a valid id
    //'file' is the file to be displayed
    //'prompt1' is the message to be displayed before printing the contents of 'file'
    //'prompt2' is the message to be printed to the user for recieving input about the id to be removed
    //'error' is the message to be printed if the entered id is not present in 'file'
    char selectedName[255];                             //'selectedName' is the content of the record whose id is selected except for the id itself
    sscanf(tempSelectedVal, "%255[^\n]", selectedName); // since tempSelectedVal is a string pointer, its contents are written into a fized array 'selectedName'

    printf("\nAre you sure the remove %s (Y/N) ?", selectedName); // the user is asked for confirmation to remove the particular record
    char yn = 'y';
    yn = getche();
    if (yn == 'y' || yn == 'Y')
    {

        FILE *fp_input, *fp_output;
        fp_input = fopen(file, "r");    //'file' is opened in read mode
        fp_output = fopen("temp", "w"); // a new file 'temp' is opened in write mode
        char line[1000];
        while (fgets(line, sizeof(line), fp_input)) //'line' is each record with each iteration
        {
            int no = 0;
            char name[255];
            sscanf(line, "%d|%255[^\n]", &no, name); //'name' is the contents of each record except its id
            if (strcmp(name, selectedName) != 0)     // if 'name' is not the contents of the record whose id is selected, 'name' is written into the temporary file
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
        remove(file);         // Deletes the original file
        rename("temp", file); // Renames the temporary file "temp" to the original file name
    }
    else
    {
        deletedCount = -1;
    }
    if (deletedCount > 0)
    {
        printf(" Deleted %d record(s)\n", deletedCount); // prints the number of records that were deleted
    }
    return 0;
}
long ddMmYyToLongValue(int year, int month, int day)
{
    // used to find the long value of a date when the value of the year,month and day are given
    long result = year * 10000L + month * 100L + day;
    return result;
}

long dateStringToLongValue(char *str)
{
    // used to obtain 3 numbers each representing the day,month and year from a date string of the form DD/MM/YYYY
    int day, month, year;
    sscanf(str, "%d/%d/%d", &day, &month, &year);
    return ddMmYyToLongValue(year, month, day);
}

bool _checkIfTransactionDateBetween(char *line, long stDateLong, long endDateLong)
{
    // used to check if the date obtained from a record falls between a given start and end date
    //'line' is the record from which the date is to be obtained
    //'stDateLong' is the long value of the start date
    //'endDateLong' is the long value of the end date
    char transactionDate[20], tempVar[255];
    int tempNo, d, m, y;
    sscanf(line, "%d|%d/%d/%d|%s|", &tempNo, &d, &m, &y, tempVar); // the day,month and year is read into d,m and y respectively
    long transDateLong = ddMmYyToLongValue(y, m, d);

    return transDateLong > stDateLong && transDateLong < endDateLong; // returns true if the obtained date falls between the start and end date
}

void reportTransactions(char *file, char *prompt1, char *prompt2, char *error, int flag)
{
    // Used for printing transactions between a start and end date
    char memberOrCategoryName[255];
    char tempValue[255] = "|";

    if (flag == 1)
    {
        // The flag is passed as 1 for printing the transactions of a particular member or cataegory between a start and end date
        char *tempSelectedVal = _safelyReturnValidTableRowValue(file, prompt1, prompt2, error);
        //'file' is the file to be displayed
        //'prompt1' is the message to be displayed before printing the contents of 'file'
        //'prompt2' is the message to be printed to the user for recieving input about the id of the member or caategory whose transactions are to be printed
        //'error' is the message to be printed if the entered id is not present in 'file'

        sscanf(tempSelectedVal, "%255[^\n]", memberOrCategoryName);
        strcat(tempValue, memberOrCategoryName);
        strcat(tempValue, "|"); //'tempValue is the name of the member or category with '|' (pipes) on both sides
        // pipes are provided on both sides of the member or category name so that if the name occurs elsewhere (such as the description), it is not taken into consideration
    }
    else
    {
        sscanf("|", "%s", tempValue); // if all transactions are to be printed,tempValue is '|'
    }

    char stDate[20] = "";
    do
    {
        printf("Start Date [DD/MM/YYYY] (01/01/1900): ");
        gets(stDate); // inputs the start date
        if (strlen(stDate) == 0)
            strcpy(stDate, "01/01/1900");                                // if no start date is provided by the user, 01/01/1900 is set as the start date
    } while (!_validateDate(stDate, "Please enter a valid start date")); // inputs dates from the user till a valid date is entered or no date is entered

    char endDate[20] = "";
    do
    {
        printf("End Date [DD/MM/YYYY] (31/12/9999): ");
        gets(endDate); // inputs the start date
        if (strlen(endDate) == 0)
            strcpy(endDate, "31/12/9999");                             // if no end date is provided by the user, 31/12/9999 is set as the end date
    } while (!_validateDate(stDate, "Please enter a valid end date")); // inputs dates from the user till a valid date is entered or no date is entered

    FILE *fp;
    fp = fopen("transactions_dat", "r");
    char line[1000];
    while (fgets(line, sizeof(line), fp))
    {
        if (strstr(line, tempValue) != NULL && _checkIfTransactionDateBetween(line, dateStringToLongValue(stDate), dateStringToLongValue(endDate)))
            // if the date of the record falls between the start and end date and tempValue is a substring of the string line(teh whole record),the record is printed
            printf("%s", line);
    }
    fclose(fp);
}
