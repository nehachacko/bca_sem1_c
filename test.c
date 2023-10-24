#include <stdio.h>
#include <conio.h>
#include "myfileutil.h"
/**
 *  struct TransactionRecord sample1;
    sample1.amount=4444.94;
    sample1.date = "10-10-2023";
    sample1.description= "test description";
    sample1.income_expense="I";
    sample1.category_id=2;
    sample1.member_id=1;
    saveAndAppendTransactions(sample1);

    struct member_record sample2;
    sample2.member_name="Nethan";
    append_to_member_record(sample2);

    struct category_record sample3;
    sample3.category_name="Groceries";
    append_to_category_record(sample3);


    //printf("hello word %d",getKeyValueAndIncrementNSave("MEMBER.KEY"));
    //printf("hello word %d",getKeyValueAndIncrementNSave("TRANSACTION.KEY"));

*/

int print_menu(int flag)
{
    if (flag == 1)
    {
        printf("Please any key to continue....");
        getch();
    }

    system("cls");
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
           201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);

    printf("%c Transactions                  %c\n", 186, 186);
    printf("%c                               %c\n", 186, 186);
    printf("%c 1.Enter a new transaction     %c\n", 186, 186);
    printf("%c 2.Delete a transaction        %c\n", 186, 186);
    printf("%c                               %c\n", 186, 186);
    printf("%c Reports                       %c\n", 186, 186);
    printf("%c                               %c\n", 186, 186);
    printf("%c 3.All records                 %c\n", 186, 186);
    printf("%c 4.Transactions of a member    %c\n", 186, 186);
    printf("%c 5.Transactions of a catergory %c\n", 186, 186);
    printf("%c                               %c\n", 186, 186);
    printf("%c Setup                         %c\n", 186, 186);
    printf("%c                               %c\n", 186, 186);
    printf("%c 6.Add a new member            %c\n", 186, 186);
    printf("%c 7.Delete a member name        %c\n", 186, 186);
    printf("%c 8.Add a new category          %c\n", 186, 186);
    printf("%c 9.Delete a category name      %c\n", 186, 186);
    printf("%c                               %c\n", 186, 186);
    printf("%c X. Exit                       %c\n", 186, 186);

    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
           200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);
    printf("Choose an option....\n");

    return 0;
}

int main_menu_with_loop()
{
    print_menu(0);
    int a = 0;
    do
    {
        a = getch();
        switch (a)
        {
        case '1':
            acceptDataForNewTransaction();
            print_menu(1);
            break;
        case '2':
            // TODO change the method name to a generic one
            deleteRowFromTable("transactions_dat", "Transaction List\nNo|Transaction Details\n", "Enter Transaction No : ", "Enter a valid transaction No\n");
            print_menu(1);
            break;
        case '3':
            _printAllRowsFromFileWithLabel("transactions_dat", "Transaction List\nNo|Transaction Details\n", 255);
            print_menu(1);
            break;
        case '4':
            reportTransactionsOfAMemberOrCategory("member_dat", "\nNo|Member Name\n", "Enter Member No : ", "Enter a valid member No\n");
            print_menu(1);
            break;
        case '5':
            reportTransactionsOfAMemberOrCategory("category_dat", "\nNo|Category Name\n", "Enter Category No : ", " Enter a valid category No\n");
            print_menu(1);
            break;
        case '6':
            acceptNewMemberOrCategoryData("Member name :", "member_dat", "MEMBER_KEY");
            print_menu(1);
            break;
        case '7':
            deleteRowFromTable("member_dat", "\nNo|Member Name\n", "Enter Member No : ", "Enter a valid member No\n");
            print_menu(1);
            break;
        case '8':
            acceptNewMemberOrCategoryData("Category name :", "category_dat", "CATEGORY_KEY");
            print_menu(1);
            break;
        case '9':
            deleteRowFromTable("category_dat", "\nNo|Category Name\n", "Enter Category No : ", "Enter a valid Category No\n");
            print_menu(1);
            break;
        default:
            break;
        }

    } while (a != 'X' && a != 'x');
    printf("Bye!!!");
    return 0;
}

int main()
{
    main_menu_with_loop();
    return 0;
}