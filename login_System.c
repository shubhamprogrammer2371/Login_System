#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

typedef struct account
{
    char firstName[20];
    char lastName[20];
    char userName[20];
    char phoneNumber[20];
    char dateOfBirth[12];
    char password[20];
    char gender;
} ac;
ac ac1;

void divider()
{
    for (int i = 0; i < 50; i++)
        printf("-");
}

void takePassword(char password[])
{
    int i = 0;
    char ch;
    while (1)
    {
        ch = getch();
        if (ch == 13) // after the user presses enter the above written content will be saved as apssword
        {
            password[i] = '\0';
            break;
        }
        else if (ch == 8) // for backspace
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else if ((ch == 9) || (ch == 32)) // for horizontal tab and space
        {
            continue;
        }
        else
        {
            password[i++] = ch;
            printf("*");
        }
    }
}

int menu()
{
    int choice;
    system("cls");
    printf("************** MAIN MENU **************\n");
    divider();
    printf("\n1) Sign Up\n2) Login\n3) Forgot Password\n4) Change Password\n5) Delete Account\n6) Exit\n");
    divider();
    printf("\nEnter your Choice from the MENU given above : ");
    scanf("%d", &choice);
    return choice;
}

void signUp()
{
    char pass2[20];
    FILE *fp;
    printf("************** CREATING NEW ACCOUNT **************\n");
    divider();
    printf("\nEnter your First Name : ");
    scanf("%s", ac1.firstName);
    printf("\nEnter Last Name : ");
    scanf("%s", ac1.lastName);
    printf("\nEnter your Phone Number : ");
    scanf("%s", ac1.phoneNumber);
    printf("\nEnter your Date of Birth(dd/mm/yyyy) : ");
    scanf("%s", ac1.dateOfBirth);
    printf("\nEnter your Gender (M/F/T) M - Male , F - Female , T - Transgender: ");
    scanf("%s", &ac1.gender);
    printf("\nEnter your User Name : ");
    scanf("%s", ac1.userName);
pass:
    printf("\nEnter your Password : ");
    takePassword(ac1.password);
    printf("\nConfirm your Password : ");
    takePassword(pass2);
    if (strcmp(pass2, ac1.password))
    {
        printf("\nIncorrect Password :(\n");
        goto pass;
    }
    else
    {
        printf("\nAccount Created Successfully :)\n");
        fp = fopen("Login_Details.txt", "a");
        fwrite(&ac1, sizeof(ac), 1, fp);
        fclose(fp);
    }
}

void login()
{
    char user[20], pass[20];
    FILE *fp = fopen("Login_Details.txt", "r");
    fread(&ac1, sizeof(ac), 1, fp);
    printf("************** LOGIN **************\n");
    divider();
uname:
    printf("\nEnter your User Name : ");
    scanf("%s", user);
    if (strcmp(user, ac1.userName))
    {
        printf("\nIncorrect Username :(\n");
        goto uname;
    }
    else
    {
    password:
        printf("\nEnter your Password : ");
        takePassword(pass);
        if (strcmp(pass, ac1.password))
        {
            printf("\nIncorrect Password :(\n");
            goto password;
        }
        else
        {
            system("cls");
            printf("\n************** LOGIN SUCCESSFULL **************\n");
            divider();
            printf("\n\t\t** YOUR DETAILS **\n");
            printf("Uset Name : %s\n", ac1.userName);
            printf("First Name : %s\n", ac1.firstName);
            printf("Last Name : %s\n", ac1.lastName);
            printf("Phone Number : %s\n", ac1.phoneNumber);
            printf("Date Of Birth : %s\n", ac1.dateOfBirth);
            printf("Gender : %c\n", ac1.gender);
            printf("Password : %s\n", ac1.password);
        }
    }
    fclose(fp);
}
void accountFound()
{
    printf("\nAccount Found :) \n");
    printf("Username         : %s\n", ac1.userName);
    printf("First Name       : %s\n", ac1.firstName);
    printf("Last Name        : %s\n", ac1.lastName);
    printf("Phone Number     : %s\n", ac1.phoneNumber);
    printf("Password         : \"%s\"\n", ac1.password);
}

void forgotPassword()
{
    int choice;
    char uname[20], phone[10], dob[12];
    FILE *fp = fopen("Login_Details.txt", "r");
    fread(&ac1, sizeof(ac), 1, fp);
menu:
    system("cls");
    printf("************** FORGOT PASSWORD **************\n");
    divider();
    printf("\n1) Search by UserName\n2) Search by Phone Number\n3) Search by Date Of Birth\n");
    printf("Enter your choice : ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        system("cls");
        printf("\nEnter your User Name : ");
        scanf("%s", uname);
        if (strcmp(uname, ac1.userName))
        {
            printf("\nAccount Not Found :/\n");
            printf("Press any key to navigate to the \"Forgot Password\" Window \n");
            getch();
            goto menu;
        }
        else
        {
            accountFound();
        }
        break;
    case 2:
        system("cls");
        printf("\nEnter your Phone Number : ");
        scanf("%s", phone);
        if (strcmp(phone, ac1.phoneNumber))
        {
            printf("\nAccount Not Found :/\n");
            printf("Press any key to navigate to the \"Forgot Password\" Window \n");
            getch();
            goto menu;
        }
        else
        {
            accountFound();
        }
        break;
    case 3:
        system("cls");
        printf("\nEnter your Date Of Birth(dd/mm/yyyy) : ");
        scanf("%s", dob);
        if (strcmp(dob, ac1.dateOfBirth))
        {
            printf("\nAccount Not Found :/\n");
            printf("Press any key to navigate to the \"Forgot Password\" Window \n");
            getch();
            goto menu;
        }
        else
        {
            accountFound();
        }
        break;
    default:
        printf("Invalid Input\n");
        break;
    }
    fclose(fp);
}

void changePassword()
{
    int num, num1;
    char oldpass[20], newpass[20], confirmpass[20];
    printf("************** CHANGE YOUR PASSWORD **************\n");
    divider();
generatenum:
    srand(time(0));
    num = rand();
    printf("\nSecurity Number : %d\n", num);
    printf("Enter the above security number : ");
    scanf("%d", &num1);
    if (num == num1)
    {
        FILE *fp = fopen("Login_Details.txt", "r");
        fread(&ac1, sizeof(ac), 1, fp);
    oldpass:
        printf("\nEnter your old Password : ");
        takePassword(oldpass);
        if (strcmp(oldpass, ac1.password))
        {
            printf("\nInvalid Old Password , please enter correct Old Password\n");
            goto oldpass;
        }
        else
        {
        newpass:
            system("cls");
            printf("Enter your New Password : ");
            takePassword(newpass);
            printf("\nConfirm your New Password : ");
            takePassword(confirmpass);
            if (strcmp(confirmpass, newpass))
            {
                printf("\nPassword dosen't match with the new password.\nEnter the new password again\nPress any key to continue.....");
                getch();
                goto newpass;
            }
            else
            {
                printf("\nPassword changed Successfully :) \n");
                strcpy(ac1.password, newpass);
                fp = fopen("Login_Details.txt", "w");
                fwrite(&ac1, sizeof(ac), 1, fp);
            }
        }
        fclose(fp);
    }
    else
    {
        printf("The security number dosen't match the computer generated security number.\n");
        goto generatenum;
    }
}

void deleteAccount()
{
    FILE *fp = fopen("Login_Details.txt", "r");
    char c, ch = fgetc(fp);
    if (ch != EOF)
    {
    surity:
        system("cls");
        printf("\n************** ACCOUNT DELETION **************\n");
        divider();
        printf("\nAre you sure you want to delete your account (Y/N) : ");
        scanf("%s", &c);

        if ((c == 'Y') || (c == 'y'))
        {
            fp = fopen("Login_Details.txt", "w");
            fprintf(fp, "  ");
            printf("\nAccount deleted Successfully :(\n");
        }
        else if ((c == 'N') || (c == 'n'))
        {
            printf("\nAccount deletion is Stopped.\nEnjoy using our Services :)");
        }
        else
        {
            printf("Please enter (Y , y) or (N , n)\nPress any key to continue.....");
            getch();
            goto surity;
        }
    }
    else
    {
        printf("No Account to delete :(\n");
    }
    fclose(fp);
}

int main()
{
    while (1)
    {
        switch (menu())
        {
        case 1:
            system("cls");
            signUp();
            printf("\nPress any Key to Continue..............");
            getch();
            break;
        case 2:
            system("cls");
            login();
            printf("\nPress any Key to Continue..............");
            getch();
            break;
        case 3:
            forgotPassword();
            printf("\nPress any Key to Continue..............");
            getch();
            break;
        case 4:
            system("cls");
            changePassword();
            printf("\nPress any Key to Continue..............");
            getch();
            break;
        case 5:
            deleteAccount();
            printf("\nPress any Key to Continue..............");
            getch();
            break;
        case 6:
            system("cls");
            exit(0);
            break;
        default:
            printf("Invalid Input\n");
            printf("\nPress any Key to Continue..............");
            getch();
            break;
        }
    }
    return 0;
}