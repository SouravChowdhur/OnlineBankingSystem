#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
struct customer
{
    char phone[15];
    char ac[25];
    char password[20];
    float balance;
};
int main()
{
    struct customer xyz, xyz1;
    int choice, choice2;
    float rate, time, emi;
    float amount;
    FILE *fp;
    char filename[50], accountnum[34], pword[25];
    char cont = 'y';
    printf("\nWhat service you want to use now ??");
    printf("\n\n1.New User?? Register an account first");
    printf("\n2.Already have an account ?? Login now\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        system("cls");
        printf("Please enter your account number: \n");
        scanf("%s", &xyz.ac);
        printf("Enter your phone number: \n");
        scanf("%s", &xyz.phone);
        printf("Enter your password: \n");
        scanf("%s", &xyz.password);
        xyz.balance = 0;
        strcpy(filename, xyz.ac);
        fp = fopen(strcat(filename, ".bnk"), "w");
        fwrite(&xyz, sizeof(struct customer), 1, fp);
        if (fwrite != 0)
        {
            printf("Congratulations! Account has created successfully");
        }
        else
        {
            printf("Error! Please try again");
        }
        fclose(fp);
    }
    if (choice == 2)
    {
        system("cls");
        printf("\nAccount Number: ");
        scanf("%s", &accountnum);
        printf("\nPassword: ");
        scanf("%s", &pword);
        strcpy(filename, accountnum);
        fp = fopen(strcat(filename, ".bnk"), "r");
        if (fp == NULL)
        {
            printf("Account is not registered");
        }
        else
        {
            fread(&xyz, sizeof(struct customer), 1, fp);
            fclose(fp);
            if (!strcmp(pword, xyz.password))
            {
                printf("Password matched");
                while (cont == 'y')
                {
                    system("cls");
                    printf("Press 1 to deposit money\n");
                    printf("Press 2 to withdraw money\n");
                    printf("Press 3 to check current balance\n");
                    printf("Press 4 to transfer money\n");
                    printf("Press 5 for generate emi on your current balance\n");
                    printf("Your Choice: ");
                    scanf("%d", &choice2);

                    switch (choice2)
                    {
                    case 1:
                        printf("Enter the amount you want to be deposited: ");
                        scanf("%f", &amount);
                        xyz.balance += amount;
                        fp = fopen(filename, "w");
                        fwrite(&xyz, sizeof(struct customer), 1, fp);
                        if (fwrite != NULL)
                        {
                            printf("Your amount has been deposited successfully\n");
                        }
                        fclose(fp);
                        break;
                    case 2:
                        printf("Enter the amount you want to be withdrawed: ");
                        scanf("%f", &amount);
                        xyz.balance -= amount;
                        fp = fopen(filename, "w");
                        fwrite(&xyz, sizeof(struct customer), 1, fp);
                        if (fwrite != NULL)
                        {
                            printf("Your amount has been withdrawed successfully\n");
                        }
                        fclose(fp);
                        break;
                    case 3:
                        printf("Your current balance is %0.2f", xyz.balance);
                        break;
                    case 4:
                        printf("Enter the account number to transfer: \n");
                        scanf("%s", &accountnum);
                        printf("Enter t5he money to be transfered: \n");
                        scanf("%f", &amount);
                        if(amount > xyz.balance){
                            printf("Sorry! Insufficient Money");
                        }
                        else{
                            strcpy(filename, accountnum);
                            fp = fopen(strcat(filename, ".bnk"), "r");

                            fread(&xyz1, sizeof(struct customer), 1, fp);
                            fclose(fp);
                            fp = fopen(filename, "w");
                            xyz1.balance += amount;
                            fwrite(&xyz1, sizeof(struct customer), 1, fp);
                            fclose(fp);
                            if(fp != NULL){
                                printf("You have debited %0.2f to account number %s", amount, accountnum);
                                strcpy(filename, xyz.ac);
                                fp = fopen(strcat(filename,".bnk"), "w");
                                xyz.balance -= amount;
                                fwrite(&xyz, sizeof(struct customer), 1, fp);
                                fclose(fp);
                                break;
                            }
                        }
                    case 5:
                        printf("Enter rate: \n");
                        scanf("%f", &rate);
                        printf("Enter time in years: ");
                        scanf("%f", &time);
                        rate = rate/(12*100);
                        time = time*12;
                        emi = (xyz.balance*rate*pow(1+rate, time))/(pow(1+rate, time)-1);
                        printf("Monthly emi = %0.2f\n", emi);
                        break;
                    }
                    printf("\nDo you want to continue the transaction ?? [y/n]\n");
                    scanf("%s", &cont);
                }
            }
            else
            {
                printf("Wrong password!");
            }
        }
    }
    return 0;
}