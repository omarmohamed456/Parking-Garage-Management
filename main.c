#include <stdio.h>
#include <stdlib.h> //to use exit() in switch case 9
#include <string.h> // to deal with strings using strcpy() and strcmp()

#define totalspots 100

typedef struct {
    char license_plate[20];
    char type[20];
    int is_parked;
    int is_parked_in;
    int cost;
    int timeinstruct;

} vehicle;

int total_pay = 0;
vehicle parking_lot[totalspots]; // an array  of elements of type "vehicle". == int parking_lot[totalspots]

void initialize_parking_lot() {
    for (int i = 1; i <= totalspots; i++) {
        parking_lot[i].is_parked = 0; //set all spots in the parking lot to 0(empety)
    }
}


//if parked --> vehicle with liscence plate in spot $$  $$ parked for $$ must pay $$  //removed  vehicle with liscence plate $$ leaved after $$ $$ is paid
void history_of_park(int i) { //func to create a record in a file
        FILE *fptr = fopen("C:/Users/omara/CLionProjects/untitled1/record.txt", "a"); //pointer of type file intiallized to -->

    if (fptr == NULL) { //to avoid error
        printf("Error opening file.\n");
        return;
    }

    fprintf(fptr, "%s with license plate %s in spot %d parked for %d hours must pay %d pounds\n",
            parking_lot[i].type, parking_lot[i].license_plate, i + 1, parking_lot[i].timeinstruct,
            parking_lot[i].cost);

    fclose(fptr);
}
void history_of_remove(int i,int total_pay) {
    FILE *fptr = fopen("C:/Users/omara/CLionProjects/untitled1/record.txt", "a");

    if (fptr == NULL) { //to avoid error
        printf("Error opening file.\n");
        return;
    }
    fprintf(fptr, "%s with license plate %s left after %d hours. The parking fee of %d pounds is paid.\n",
            parking_lot[i].type, parking_lot[i].license_plate, parking_lot[i].timeinstruct, parking_lot[i].cost);
    fprintf(fptr,"Total revenue is: %d Pounds",total_pay);

    fclose(fptr);
}


int park(const char* license_plate,const char*type,int time) {
    int cost2;
        if (strcmp(type, "car") == 0)
            cost2 = time * 5;
    else if (strcmp(type, "bus") == 0)
        cost2 = time * 6;
    else if (strcmp(type, "motorcycle") == 0)
        cost2 = time * 4;
    else
        printf("not a valid option");

    for (int i = 1; i <= totalspots; i++) {
        if (parking_lot[i].is_parked == 0) { //coping stuff because inner scoop of the function
            strncpy(parking_lot[i].license_plate, license_plate, 20); //copy the license_plate to the license_plate in the spot
            strncpy(parking_lot[i].type, type, 20);
            parking_lot[i].cost = cost2;
            parking_lot[i].timeinstruct = time;
            parking_lot[i].is_parked = 1; //the vehicle is parked
            printf("vehicle with license plate %s parked at spot %d.\nTotal cost for parking is: %d pounds", license_plate, i,cost2);
            history_of_park(i); //record
            return i;
        }
    }
    printf("Parking lot is full.\n");
    return -1;
}

int search(const char* license_plate) { //must be before remove
    for (int i = 1; i <= totalspots; i++) {
        if (parking_lot[i].is_parked && strcmp(parking_lot[i].license_plate, license_plate) == 0) { //is parked & is the same
            return i; //why not i+1
        }
    }
    return -1; //in the remove this will mean it doesn't exist
}

void remove_vehicle(const char* license_plate) {
    int spot = search(license_plate);
    if (spot != -1) {
        parking_lot[spot].is_parked = 0;
        printf("vehicle with license plate %s removed from spot %d.\n", license_plate, spot); //if search returns i this will be spot + 1 vice vera
        printf("Thanks for parking in Btats garage");
        total_pay = total_pay + parking_lot[spot].cost;
        history_of_remove(spot,total_pay); //spot = i in the remove func because it depends on search func //record
    } else {
        printf("vehicle with license plate %s not found.\n", license_plate);
    }
}

void display_parking_lot() {
    printf("Parking lot map:\n");
    for (int i = 1; i <= totalspots; i++) {
        printf("Spot %d: ", i);
        if (parking_lot[i].is_parked) {
            printf("%s", parking_lot[i].license_plate);
        } else {
            printf("Empty");
        }
        printf("\t"); //add three spaces between each spot
        if (i % 7 == 0) {
            printf("\n \n"); // Add a space after every 7 spots
        }
    }
}

void check_spot(int spot_num) {
    if (spot_num < 1 || spot_num > totalspots) { //to make sure the user enters a valied number
        printf("Invalid spot number. Please enter a number between 1 and %d.\n", totalspots);
        return; //to end
    }

    if (parking_lot[spot_num].is_parked) {
        printf("Spot %d is occupied by vehicle with license plate %s.\n", spot_num,parking_lot[spot_num].type,parking_lot[spot_num].license_plate);
    } else {
        printf("Spot %d is empty.\n", spot_num);
    }
}
void number_of_vehicles_parked(){
    int number_of_parked_vehicles;
    for (int i = 1; i <= totalspots; i++) {
        if(parking_lot[i].is_parked) {
            number_of_parked_vehicles++;
        }
    }
    printf("Number of parked vehicles is: %d",number_of_parked_vehicles);
}
void number_of_type_parked(char *wanted_type)
{
    int number_of_type_parked;
    for (int i = 1; i <= totalspots; i++) {
        if(strcmp(parking_lot[i].type, wanted_type) == 0) {
            number_of_type_parked++;
        }
    }
    printf("Number of parked %s is: %d",wanted_type,number_of_type_parked);

}
void history() {
    FILE *fptr = fopen("C:/Users/omara/CLionProjects/untitled1/record.txt", "r");

    if (fptr == NULL) { //to avoid error
        printf("Error opening file.\n");
        return;
    }
    char line[500]; // line legth

    while (fgets(line, sizeof(line), fptr) != NULL) { //fgets(string where characters read will be stored, number of characters to be read, file to read from) mot == zero
        printf("%s", line);
    }

    fclose(fptr);
}
void delete_record() {
    FILE *fptr = fopen("C:/Users/omara/CLionProjects/untitled1/record.txt", "w");

    if (fptr == NULL) { //to avoid error
        printf("Error opening file.\n");
        return;
    }

    fclose(fptr);
}

void menu() {
    printf("\n\n\n\t\t\tWelcome to BTATS Garage!\n");
    printf("What do you want to do?:\n");
    printf("1. Park a vehicle\n");
    printf("2. Remove a vehicle\n");
    printf("3. search a vehicle\n");
    printf("4. check a spot\n");
    printf("5. Number of Vehicles in the garage\n");
    printf("6. Number of Vehicles of a specific type in the garage\n");
    printf("7. Display parking lot status\n");
    printf("8. History\n"); //reads recorrd
    printf("9. delete history\n");
    printf("10. Exit\n");
}

int main() { //the main function and where most variaples are deined
    int choice,cost,time,timeinstruct,spot,spot_num,total_pay,is_parked_in;
    char license_plate[20];
    char type[20];
    char wanted_type[20];
    initialize_parking_lot();

    while (1) { //main loop to make sure the programme keeps running
        menu();
        printf("What do you want to do?");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the vehicle's license plate: ");
                scanf("%s", license_plate);

                printf("Enter the vehicle's type (car, bus or motorcycle):");
                scanf("%s", type);

                if (strcmp(type, "car") == 0 || strcmp(type, "bus") == 0 || strcmp(type, "motorcycle") == 0) {

                    printf("How long will you park your %s? (minimum is 1 hour)? \n Enter in time hours: \n",type);
                    scanf("%d",&time);

                    if (time > 0) {
                        park(license_plate,type,time);
                    } else {
                        printf("Enter a valid time. (must be > 0) ");
                    }


                } else {
                    printf("%s is not a valid option. Check for spelling mistakes. \n",type);
                }
                break;

            case 2:
                printf("Enter the vehicle's license plate to remove: ");
                scanf("%s", license_plate);
                remove_vehicle(license_plate);
                break;

            case 3:
                printf("Enter the vehicle's license plate: ");
                scanf("%s", license_plate);
                spot = search(license_plate);
            if (spot == -1)
                printf("vehicle isn't parked here.");
            else
                printf("Your vehicle is parked in Spot %d",spot);
                break;

            case 4:
                printf("Enter the spot's number: (from 1 to 100) ");
                scanf("%d", spot_num);
                if (spot_num > 0 && spot_num < 101) {
                    check_spot(spot_num);
                } else
                    printf("Invalid spot number.");
            break;

            case 5:
                number_of_vehicles_parked();
            break;

            case 6:
                printf("Enter the type you want: ");
                scanf("%s",wanted_type);
            if (strcmp(type, "car") == 0 || strcmp(type, "bus") == 0 || strcmp(type, "motorcycle") == 0) {
                number_of_type_parked(wanted_type);
            } else {
                printf("%s is not a valid option. Check for spelling mistakes. \n",type);
            }
            break;

            case 7:
                display_parking_lot();
                break;

            case 8:
                history();
                break;

            case 9:
                delete_record();
            break;

            case 10:
                printf("Total revenue is: %d Pounds",total_pay);
                printf("Exiting...\n");
                exit(0);
                break;

            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
