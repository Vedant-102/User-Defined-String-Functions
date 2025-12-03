#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int my_strlen(char *str) {
    int count = 0;
    while (str[count] != '\0') {
        count++;
    }
    return count;
}

void my_strcpy(char *dest, char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0'; 
}

int my_strcmp(char *s1, char *s2) {
    int i = 0;
    while (s1[i] != '\0' || s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return (s1[i] - s2[i]); 
        }
        i++;
    }
    return 0; 
}

void my_strcat(char *dest, char *src) {
    int dest_len = my_strlen(dest);
    int i = 0;
    
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
}


void generate_password(char *buffer) {

    buffer[0] = '\0'; 
    
    char temp[2]; 
    temp[1] = '\0';

    temp[0] = (rand() % 26) + 'A';
    my_strcat(buffer, temp);

    temp[0] = (rand() % 10) + '0';
    my_strcat(buffer, temp);

    char specials[] = "!@#$%^&*";
    temp[0] = specials[rand() % 8];
    my_strcat(buffer, temp);

    int remaining_len = (rand() % 4) + 7; 

    for(int i = 0; i < remaining_len; i++) {
        temp[0] = (char)((rand() % (126 - 33 + 1)) + 33);
        my_strcat(buffer, temp);
    }
}

int main() {
    char stored_password[100];
    char input_buffer[100];
    int choice;
    int password_set = 0; 
    srand(time(NULL));
    printf("===PASSWORD MANAGER===\n");

    while (1) {
        printf("\n--- MAIN MENU ---\n");
        printf("1. Set Password\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        while(getchar() != '\n'); 

        switch (choice) {
            case 1: 
                printf("\n--- SET PASSWORD ---\n");
                printf("A. Generate Secure Password\n");
                printf("B. Enter Manual Password\n");
                printf("Choose (A/B): ");
                char sub_choice;
                scanf("%c", &sub_choice);
                while(getchar() != '\n');
                if (sub_choice == 'A' || sub_choice == 'a') {
                    generate_password(input_buffer);
                    my_strcpy(stored_password, input_buffer); 
                    password_set = 1;
                    printf("Password Generated and Set: %s\n", stored_password);
                    printf("Length: %d\n", my_strlen(stored_password));
                } 
                
                else if (sub_choice == 'B' || sub_choice == 'b') {
                    printf("Enter password (10 characters minimum): ");
                    int k = 0;
                    char c;
                    while((c = getchar()) != '\n' && k < 99) {
                        input_buffer[k++] = c;
                    }
                    input_buffer[k] = '\0';

                    int len = my_strlen(input_buffer);
                    if (len >= 10) {
                        my_strcpy(stored_password, input_buffer);
                        password_set = 1;
                        printf("Password Set Successfully.\n");
                    } else {
                        printf("Error: Password must be of 10 characters minimum. Your length: %d\n", len);
                    }
                }
                break;

            case 2:
                if (password_set == 0) {
                    printf("Error: No password set yet! Please go to option 1.\n");
                } else {
                    printf("\n--- LOGIN ---\n");
                    printf("Enter Password: ");
                    
                    int k = 0;
                    char c;
                    while((c = getchar()) != '\n' && k < 99) {
                        input_buffer[k++] = c;
                    }
                    input_buffer[k] = '\0';

                    if (my_strcmp(stored_password, input_buffer) == 0) {
                        printf("LOGIN SUCCESSFUL! \n");
                    } else {
                        printf("LOGIN FAILED! Wrong Password.\n");
                    }
                }
                break;

            case 3:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
