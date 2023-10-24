#include <stdio.h>
#include <conio.h>
#include "myfileutil.h"

int print_menu(int flag)
{
    // prints menu
    if (flag == 1) // if flag is 1,at the end of the screen a message is printed to press any key to continue
    {
        printf("Please any key to continue....");
        getch();
    }

    system("cls"); // clears screen before printing the menu
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

    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n",
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
        a = getch(); // inputs which operation is to be performed
        switch (a)
        {
        case '1':          // to enter a new transaction
            system("cls"); // clears screen and starts by printing the message given below
            printf("==========NEW TRANSACTION ENTRY==========\n\n");
            acceptDataForNewTransaction();
            print_menu(1);
            break;
        case '2':          // to delete a transaction
            system("cls"); // clears screen and starts by printing the message given below
            printf("==========DELETE A TRANSACTION ENTRY==========\n\n");
            deleteRowFromTable("transactions_dat", "Transaction List\nNo|Transaction Details\n", "Enter Transaction No : ", "Enter a valid transaction No\n");
            print_menu(1);
            break;
        case '3':          // to report all transactions
            system("cls"); // clears screen and starts by printing the message given below
            printf("==========REPORTING ALL TRANSACTIONS==========\n");
            reportTransactions("transactions_dat", "", "", "", 0);
            print_menu(1);
            break;
        case '4':          // to report all transactions of a particular member
            system("cls"); // clears screen and starts by printing the message given below
            printf("==========REPORTING TRANSACTIONS OF A MEMBER==========\n\n");
            reportTransactions("member_dat", "\nNo|Member Name\n", "Enter Member No : ", "Enter a valid member No\n", 1);
            print_menu(1);
            break;
        case '5':          // to report all transactions of a particular category
            system("cls"); // clears screen and starts by printing the message given below
            printf("==========REPORTING TRANSACTIONS OF A CATEGORY==========\n\n");
            reportTransactions("category_dat", "\nNo|Category Name\n", "Enter Category No : ", " Enter a valid category No\n", 1);
            print_menu(1);
            break;
        case '6':          // to add a new member
            system("cls"); // clears screen and starts by printing the message given below
            printf("==========NEW MEMBER ENTRY==========\n\n");
            acceptNewMemberOrCategoryData("Member name :", "member_dat", "MEMBER_KEY");
            print_menu(1);
            break;
        case '7':          // to delete a member
            system("cls"); // clears screen and starts by printing the message given below
            printf("==========DELETE A MEMBER==========\n\n");
            deleteRowFromTable("member_dat", "\nNo|Member Name\n", "Enter Member No : ", "Enter a valid member No\n");
            print_menu(1);
            break;
        case '8':          // to add a new category
            system("cls"); // clears screen and starts by printing the message given below
            printf("==========NEW CATEGORY ENTRY==========\n\n");
            acceptNewMemberOrCategoryData("Category name :", "category_dat", "CATEGORY_KEY");
            print_menu(1);
            break;
        case '9':          // to delete a category
            system("cls"); // clears screen and starts by printing the message given below
            printf("==========DELETE A CATEGORY==========\n\n");
            deleteRowFromTable("category_dat", "\nNo|Category Name\n", "Enter Category No : ", "Enter a valid Category No\n");
            print_menu(1);
            break;
        default:
            break;
        }

    } while (a != 'X' && a != 'x'); // exits from the program execution
    printf("Bye!!!");
    return 0;
}

int main()
{
    main_menu_with_loop();
    return 0;
}