#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

float bill = 0, discount = 0, deleted_items_bill = 0, today_sell = 0;
char items[10][30] = {"Burger", "Pizza", "Sandwich", "Veggie Wrap", "Momos"};
int price[10] = {60, 200, 50, 50, 40};
int bill_no = 0, order_item_number[30], no_of_items = 0, quantity_of_items[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

void displayitems()
{
    FILE *menu;
    char ch[100];
    menu = fopen("Menu.txt", "r");
    while (fgets(ch, 99, menu) != NULL)
    {
        printf("%s", ch);
    }
    printf("\nPlease type the item number of your order from the menu with quantity. Type 0 in both order no. and quantity if you completed the order.");
    fclose(menu);
}

void additems()
{

    FILE *order;
    order = fopen("Order.txt", "w");
    for (int j = 0; j >= 0; ++j)
    {
        int quant;
        int x;
        char result[10];
        printf("\nEnter order no.%d: ", j + 1);
        while (scanf("%d", &x) != 1)
        {
            printf("You did not enter a valid number\n");
            printf("\nEnter order no.%d: ", j + 1);
            scanf("%*s");
        }
        order_item_number[j] = x - 1;
        no_of_items++;
        printf("Enter the quantity of your %d order: ", j + 1);
        while (scanf("%d", &quant) != 1)
        {
            printf("You did not enter a valid quantity\n");
            printf("Enter the quantity of your %d order: ", j + 1);
            scanf("%*s");
        }
        quantity_of_items[x - 1] = quant;
        sprintf(result, "%d", quant);
        if (x == 0)
        {
            break;
        }
        else if (x > 5)
        {
            printf("Sorry! We don't have this item right now. Please choose another one.\n");
        }
        else
        {
            bill += price[x - 1] * quant;
            int value = price[x - 1] * quant;
            char value_str[10], price_str[10];
            sprintf(value_str, "%d", value);
            sprintf(price_str, "%d", price[x - 1]);
            fputs(items[x - 1], order);
            for (int i = 0; i < 16 - strlen(items[x - 1]); ++i)
            {
                fputs(" ", order);
            }
            fputs(result, order);
            for (int i = 0; i < 9; ++i)
            {
                fputs(" ", order);
            }
            fputs(price_str, order);
            for (int i = 0; i < 11 - strlen(price_str); ++i)
            {
                fputs(" ", order);
            }
            fputs(value_str, order);
            fputs("\n", order);
        }
    }
    fclose(order);
}

void deleteitems()
{
    FILE *order, *delete_item;
    printf("\nDo you want to cancel any item in your order list? If yes then type the item no.\nType 0 in both order no. and quantity if you completed.\n\nYour orders are:\n");
    printf("Item Name       Qty.      Price      Value\n");
    order = fopen("Order.txt", "r");
    delete_item = fopen("Delete.txt", "w");
    char ch[50], sh[50];
    int x, quant;
    char value_str[30], price_str[10], result[10];
    while (fgets(ch, 49, order) != NULL)
    {
        printf("%s", ch);
    }
    for (int j = 0;; ++j)
    {
        int count = 0;
        printf("\nEnter cancel order no.%d: ", j + 1);
        while (scanf("%d", &x) != 1)
        {
            printf("You did not enter a valid order number.\n\n");
            printf("\nEnter cancel order no.%d: ", j + 1);
            scanf("%*s");
        }
        printf("Enter the quantity of order to cancel: ");
        while (scanf("%d", &quant) != 1)
        {
            printf("You did not enter a valid quantity.\n\n");
            printf("Enter the quantity of order to cancel: ");
            scanf("%*s");
        }
        if (quant > quantity_of_items[x - 1])
        {
            printf("You cancelled more items than ordered.\n");
            quant = quantity_of_items[x - 1];
        }
        if (x == 0)
        {
            break;
        }
        else
        {
            sprintf(result, "%d", quant);
            int value = price[x - 1] * quant;
            sprintf(value_str, "%d", value);
            sprintf(price_str, "%d", price[x - 1]);
            for (int j = 0; j < no_of_items - 1; ++j)
            {
                if (x - 1 == order_item_number[j])
                {
                    count++;
                }
            }

            if (count > 0)
            {
                deleted_items_bill += value;
                fputs(items[x - 1], delete_item);
                for (int i = 0; i < 16 - strlen(items[x - 1]); ++i)
                {
                    fputs(" ", delete_item);
                }
                fputs(result, delete_item);
                for (int i = 0; i < 9; ++i)
                {
                    fputs(" ", delete_item);
                }
                fputs(price_str, delete_item);
                for (int i = 0; i < 10 - strlen(price_str); ++i)
                {
                    fputs(" ", delete_item);
                }
                fputs("-", delete_item);
                fputs(value_str, delete_item);
                fputs("\n", delete_item);
            }
            else
            {
                printf("This item is not in your order list. Please type correct item number.\n");
            }
        }
    }
    fclose(order);
    fclose(delete_item);
}

void dis_count()
{
    if (bill - deleted_items_bill >= 500)
    {
        discount += 50;
    }
    else if (bill - deleted_items_bill >= 300)
    {
        discount += 20;
    }
}

void payment_mode()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    FILE *customer_info, *order, *delete;
    order = fopen("Order.txt", "r");
    delete = fopen("Delete.txt", "r");
    char ch[50], sh[50];

    printf("\n                Puff Cafe\n");
    printf("        G.T Road, Phagwara, Punjab\n");
    printf(" Phone no: +91 XXXXXXXXXX, +91 XXXXXXXXXX\n");
    printf("          GSTIN: XXXXXXXXXXXXXXX\n");
    printf("------------------------------------------\n");
    printf("Bill no.: %d      Date: %d/%02d/%02d %02d:%02d:%02d\n", ++bill_no, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("------------------------------------------\n");
    printf("Item Name       Qty.      Price      Value\n");
    printf("------------------------------------------\n");
    while (fgets(ch, 49, order) != NULL)
    {
        printf("%s", ch);
    }
    printf("------------------------------------------\n");
    printf("Cancelled Order\n");
    printf("------------------------------------------\n");
    while (fgets(sh, 49, delete) != NULL)
    {
        printf("%s", sh);
    }
    printf("------------------------------------------\n");
    printf("Sub Total                          %.2f \n", bill - deleted_items_bill);
    printf("Discount                           -%.2f\n\n", discount);
    printf("Add S GST(9.000) on %.2f         %.2f \n", bill, bill * 0.09);
    printf("Add C GST(9.000) on %.2f         %.2f \n", bill, bill * 0.09);
    bill -= 2 * bill * 0.09;
    printf("                                  --------\n");
    printf("Amount Incl. of All Taxes          %.2f \n", ceil(bill - discount - deleted_items_bill));
    today_sell += ceil(bill - discount - deleted_items_bill);
    printf("                                  --------\n");
    printf("Cashier: XXXX                      E & OE\n");
    printf("         Thank You for your visit\n");
    printf("             Have a nice day\n\n\n");
    fclose(customer_info);
    fclose(order);
    fclose(delete);
}

int main()
{
    while (1)
    {
        int choice;
        printf("\nWELCOME TO CAFE PUFF!\n\n");
        FILE *customer_info;
        customer_info = fopen("CustomerInfo.txt", "a");
        char name[50], address[100];
        char mob_no[10];
        printf("Please enter your name: ");
        gets(name);
        fputs(name, customer_info);
        fputs("\n", customer_info);
        printf("Please enter your address: ");
        gets(address);
        fputs(address, customer_info);
        fputs("\n", customer_info);
        printf("Please enter your mobile number: ");
        gets(mob_no);
        fputs(mob_no, customer_info);
        fputs("\n\n", customer_info);
        printf("\nHello %s! What would you like to have from our cafe? We have items as listed:\n", name);
        displayitems();
        printf("\n");
        additems();
        deleteitems();
        dis_count();
        printf("\n\nHere is your bill. Please pay it and enjoy your meal.\n\n");
        payment_mode();
        fclose(customer_info);
        fflush(stdin);
        printf("Do you want to order again? Type 0 to exit or any key to continue.\n");
        scanf("%d", &choice);
        if (choice == 0)
        {
            break;
        }
        fflush(stdin);
    }
    return 0;
}
