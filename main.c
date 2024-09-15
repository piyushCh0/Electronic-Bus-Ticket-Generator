#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Bus
{
    // attributes of a bus
    int bus_id;
    int bus_seats[33];
    int no_of_seat_in_bus;
    float bus_fare;
    char bus_route[100];
    char bus_name[50];
    char bus_time[30];

    // pointer to generate bus obj function
    struct Bus (*generate_bus)(int id, char bus_name[], char bus_time[], float bus_fare, char bus_route[], struct Bus *bus);
} BUS;

// Generate Bus Function
BUS GenerateBusObj(int id, char bus_name[], char bus_time[], float bus_fare, char bus_route[], BUS *bus)
{
    //                                         MODULE 2

    // assigning values
    bus->bus_id = id;
    strcpy(bus->bus_name, bus_name);
    strcpy(bus->bus_time, bus_time);
    strcpy(bus->bus_route, bus_route);
    bus->bus_fare = bus_fare;

    // assigning bus seats their number
    int max_seat_bus = 33;

    bus->no_of_seat_in_bus = max_seat_bus;

    for (int i = 0; i < max_seat_bus; i++)
    {
        bus->bus_seats[i] = 0;
    }

    return *bus;
}

//                                               MODULE 2
//                                  global variable declarations
// Bus object
BUS bus;

// Bus object pointer
BUS *bus_ptr = &bus;

// maximum seats in a bus
int max_seat_in_bus = 33;

int num_of_buses;

void Add_New_Bus()
{
    //                                          MODULE 2
    // Initialising the function pointer
    bus.generate_bus = GenerateBusObj;

    // taking input for number of buses
    printf("-----> Enter number of buses you want to add:- \n");
    scanf("%d", &num_of_buses);

    // Allocating memory for buses
    BUS *buses = (BUS *)malloc(num_of_buses * sizeof(BUS));

    for (int i = 0; i < num_of_buses; i++)
    {
        // variables
        int bus_id;
        char bus_name[50];
        char bus_time[30];
        float bus_fare;
        char bus_route[100];

        // taking inputs
        printf("Enter Bus Id:- \n");
        scanf("%d", &bus_id);
        getchar();
        printf("Enter Bus Name:- \n");
        fgets(bus_name, 50, stdin);
        printf("Enter Bus Time (in the format HH:MM AM/PM):- \n");
        fgets(bus_time, 30, stdin);
        printf("Enter Bus Fare:- \n");
        scanf("%f", &bus_fare);
        getchar();
        printf("Enter Bus Route Name  (Remember the route name you typed as it will help you get available buses for a route):- \n");
        fgets(bus_route, 100, stdin);

        // Storing the bus in the allocated array
        buses[i] = (bus.generate_bus)(bus_id, bus_name, bus_time, bus_fare, bus_route, bus_ptr);
    }
}

// Available Buses for a route
void Get_Bus_For_A_Route(BUS *buses)
{
    //                                     MODULE 1
    // variables
    char route[100];
    getchar();
    printf("Enter route name:- \n");
    fgets(route, 100, stdin);
    printf("\n");
    int bus_available = 0;

    // Searching buses for the given route
    for (int i = 0; i < num_of_buses; i++)
    {

        if (strcmp(buses[i].bus_route, route) == 0)
        {
            printf("Bus ID:- %d\n", buses[i].bus_id);
            buses[i].bus_name[strcspn(buses[i].bus_name, "\n")] = '\0';
            printf("Bus name:- %s\n", buses[i].bus_name);
            printf("Bus fare:- %f\n", buses[i].bus_fare);
            buses[i].bus_route[strcspn(buses[i].bus_route, "\n")] = '\0';
            printf("Bus route:- %s\n", buses[i].bus_route);
            printf("No. of seat in bus:- %d\n", buses[i].no_of_seat_in_bus);
            buses[i].bus_time[strcspn(buses[i].bus_time, "\n")] = '\0';
            printf("Bus time:- %s\n", buses[i].bus_time);
            bus_available = 1;
        }
    }

    // If no bus found
    if (!bus_available)
    {
        printf("\n");
        printf("-----> -----> -----> -----> -----> ----->                                       'No buses available'\n");
        printf("\n");
    }
}

//                                               MODULE 3
// print available seats function declaration
void Dipslay_Bus_Layout(BUS *buses, int bus_id, char bus_name[]);

//                                               MODULE 3
// Book Seat in the bus
void Book_Seat(BUS *buses)
{
    // variables
    int option;
    int bus_id;
    char bus_name[50];
    int seat_no;

    printf("\n");
    printf("-----> -----> -----> -----> -----> ----->                   (You can search for the bus by either entering the 'Bus ID' OR 'Bus Name')\n");
    printf("1. Search bus by Bus ID\n");
    printf("2. Search bus by Bus Name\n");
    printf("Enter the option number:- \n");
    scanf("%d", &option);
    printf("\n");

    switch (option)
    {
    case 1:
        printf("Enter Bus ID:-\n");
        scanf("%d", &bus_id);
        Dipslay_Bus_Layout(bus_ptr, bus_id, bus_name);
        printf("\n");
        printf("\n");
        printf("Enter seat number to book:- \n");
        scanf("%d", &seat_no);
        for (int i = 0; i < num_of_buses; i++)
        {
            if (buses[i].bus_id == bus_id)
            {
                buses[i].bus_seats[seat_no - 1] = 1;
            }
        }
        break;

    case 2:
        printf("Enter Bus Name:-\n");
        getchar();
        fgets(bus_name, 50, stdin);
        Dipslay_Bus_Layout(bus_ptr, bus_id, bus_name);
        printf("\n");
        printf("\n");
        printf("Enter seat number to book:- \n");
        scanf("%d", &seat_no);
        for (int i = 0; i < num_of_buses; i++)
        {
            if (strcmp(buses[i].bus_name, bus_name) == 0)
            {
                buses[i].bus_seats[seat_no - 1] = 1;
            }
        }
        break;

    default:
        printf("Please enter a valid option number\n");
        break;
    }
}

//                                      MODULE 3 and 4
// Print bus top view
void Dipslay_Bus_Layout(BUS *buses, int bus_id, char bus_name[])
{
    //                                MODULE 3
    // print available seats
    int i;
    int j;
    int bus_pos_in_array;
    printf("         Window\n");
    printf("------------------------\n");

    for (int k = 0; k < max_seat_in_bus; k++)
    {
        if (buses[k].bus_id == bus_id)
        {
            bus_pos_in_array = k;
            break;
        }
        else if (strcmp(buses[k].bus_name, bus_name) == 0)
        {
            bus_pos_in_array = k;
            break;
        }
    }

    for (i = 0, j = 0; i < max_seat_in_bus; i++)
    {
        // booked_seats[i] == 0
        if (buses[bus_pos_in_array].bus_seats[i] == 0)
        {
            if (i + 1 <= 9)
            {
                printf("%d  ", i + 1);
            }
            else if (i == 16)
            {
                printf("    (Bus Top View)   %d |", i + 1);
                printf("\n");
            }
            else
            {

                printf("%d ", i + 1);
            }
            if (i != 16)
            {
                j++;
            }
            if (j == 8)
            {
                printf("|");
                printf("\n");
            }
            else if (j == 16)
            {
                printf("|");
                printf("\n");
                j = 0;
            }
        }
        else
        {
            if (i + 1 <= 9)
            {
                printf("B  ");
            }
            else if (i == 16)
            {
                printf("    (Bus Top View)    ~ |");
                printf("\n");
            }
            else
            {
                printf("B  ");
            }
            if (i != 16)
            {
                j++;
            }
            if (j == 8)
            {
                printf("|");
                printf("\n");
            }
            else if (j == 16)
            {
                printf("|");
                printf("\n");
                j = 0;
            }
        }
    }
    printf("------------------------\n");
    printf("         Window\n");
}

//                                           MODULE 4
void Cancel_Seat(BUS *buses)
{
    // variables
    int option;
    int bus_id;
    char bus_name[50];
    int seat_no;

    printf("\n");
    printf("-----> -----> -----> -----> -----> ----->                   (You can search for the bus by either entering the 'Bus ID' OR 'Bus Name')\n");
    printf("1. Search bus by Bus ID\n");
    printf("2. Search bus by Bus Name\n");
    printf("Enter the option number:- \n");
    scanf("%d", &option);
    printf("\n");

    switch (option)
    {
    case 1:
        printf("Enter Bus ID:-\n");
        scanf("%d", &bus_id);
        Dipslay_Bus_Layout(bus_ptr, bus_id, bus_name);
        printf("\n");
        printf("\n");
        printf("Enter your booked seat number to cancel:- \n");
        scanf("%d", &seat_no);
        for (int i = 0; i < num_of_buses; i++)
        {
            if (buses[i].bus_id == bus_id)
            {
                buses[i].bus_seats[seat_no - 1] = 0;
            }
        }
        break;

    case 2:
        printf("Enter Bus Name:-\n");
        getchar();
        fgets(bus_name, 50, stdin);
        Dipslay_Bus_Layout(bus_ptr, bus_id, bus_name);
        printf("\n");
        printf("\n");
        printf("Enter your booked seat number to cancel:- \n");
        scanf("%d", &seat_no);
        for (int i = 0; i < num_of_buses; i++)
        {
            if (strcmp(buses[i].bus_name, bus_name) == 0)
            {
                buses[i].bus_seats[seat_no - 1] = 0;
            }
        }
        break;

    default:
        printf("Please enter a valid option number\n");
        break;
    }
}

//                                             MODULE 5
void Delete_Update_Bus_Detail(BUS *buses, int bus_pos_in_array)
{
    // variables
    int option;
    char bus_name[50];
    int bus_id;
    float bus_fare;
    char bus_route[100];
    char bus_time[30];

    // menu
    printf("choose the option to change that particular detail:- \n");
    printf("1. Bus Name\n");
    printf("2. Bus ID\n");
    printf("3. Bus Fare\n");
    printf("4. Bus Route\n");
    printf("5. Bus Time\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        printf("Enter new name for the bus:- \n");
        getchar();
        fgets(bus_name, 50, stdin);
        strcpy(buses[bus_pos_in_array].bus_name, bus_name);
        printf("Bus name successfully updated\n");
        break;

    case 2:
        printf("Enter new bus ID for the bus:- \n");
        getchar();
        scanf("%d", &bus_id);
        buses[bus_pos_in_array].bus_id = bus_id;
        printf("Bus ID successfully updated\n");
        break;

    case 3:
        printf("Enter new bus fare for the bus:- \n");
        getchar();
        scanf("%f", &bus_fare);
        buses[bus_pos_in_array].bus_fare = bus_fare;
        printf("Bus fare successfully updated\n");
        break;

    case 4:
        printf("Enter new bus route for the bus:- \n");
        getchar();
        fgets(bus_route, 100, stdin);
        strcpy(buses[bus_pos_in_array].bus_route, bus_route);
        printf("Bus route successfully updated\n");
        break;

    case 5:
        printf("Enter new bus time for the bus:- \n");
        getchar();
        fgets(bus_time, 30, stdin);
        strcpy(buses[bus_pos_in_array].bus_time, bus_time);
        printf("Bus timing successfully updated\n");
        break;

    default:
        printf("Please enter the listed option number only.\n");
        break;
    }
}

//                                           MODULE 5
void Search_Bus_For_Update_Operation(BUS *buses)
{
    // variables
    int option;
    int bus_id;
    char bus_name[50];
    int bus_pos_in_array;

    printf("\n");
    printf("-----> -----> -----> -----> -----> ----->                   (You can search for the bus by either entering the 'Bus ID' OR 'Bus Name')\n");
    printf("1. Search bus by Bus ID\n");
    printf("2. Search bus by Bus Name\n");
    printf("Enter the option number:- \n");
    scanf("%d", &option);
    printf("\n");

    switch (option)
    {
    case 1:
        printf("Enter Bus ID:-\n");
        scanf("%d", &bus_id);
        printf("\n");
        printf("\n");
        for (int i = 0; i < num_of_buses; i++)
        {
            if (buses[i].bus_id == bus_id)
            {
                bus_pos_in_array = i;
                buses[i].bus_name[strcspn(buses[i].bus_name, "\n")] = '\0';
                printf("Bus name:- %s\n", buses[i].bus_name);
                printf("Bus ID:- %d\n", buses[i].bus_id);
                printf("Bus fare:- %f\n", buses[i].bus_fare);
                buses[i].bus_route[strcspn(buses[i].bus_route, "\n")] = '\0';
                printf("Bus route:- %s\n", buses[i].bus_route);
                buses[i].bus_time[strcspn(buses[i].bus_time, "\n")] = '\0';
                printf("Bus time:- %s\n", buses[i].bus_time);
                printf("\n");
                break;
            }
        }
        Delete_Update_Bus_Detail(bus_ptr, bus_pos_in_array);
        break;

    case 2:
        getchar();
        printf("Enter Bus Name:-\n");
        fgets(bus_name, 50, stdin);
        printf("\n");
        for (int i = 0; i < num_of_buses; i++)
        {
            if (strcmp(buses[i].bus_name, bus_name) == 0)
            {
                bus_pos_in_array = i;
                printf("Bus name:- %s", buses[i].bus_name);
                printf("Bus ID:- %d\n", buses[i].bus_id);
                printf("Bus fare:- %f\n", buses[i].bus_fare);
                printf("Bus route:- %s", buses[i].bus_route);
                printf("Bus time:- %s\n", buses[i].bus_time);
                break;
            }
        }
        Delete_Update_Bus_Detail(bus_ptr, bus_pos_in_array);
        break;

    default:
        printf("Please enter a valid option number\n");
        break;
    }
}

// deallocating dynamically allocated buses
void cleanup(BUS *buses, int num_of_buses)
{
    for (int i = 0; i < num_of_buses; i++)
    {
        if (*buses[i].generate_bus != NULL)
        {
            free(buses[i].generate_bus);
            buses[i].generate_bus = NULL;
        }
    }
    free(buses);
    printf("                                                  Dynamically allocated memory was deallocated\n");
    buses = NULL;
}

int main()
{
    //                                         MAIN MENU
    // variable
    int option;

    while (option)
    {
    Main_Menu:
        printf("                                                                           Electronic Bus Ticket Generator\n");
        printf("1. Available buses for a route\n");
        printf("2. Add new bus\n");
        printf("3. Book seat\n");
        printf("4. Cancel seat\n");
        printf("5. Delete/Update a bus deatil\n");
        printf("6. Go to Menu\n");
        printf("7. Exit\n");
        printf("                                                        Made by Piyush Chaudhary, Nikhil Kumar, Shubhanshu Kumar Srivastava");
        printf("                                                                                                                               (K22FU)\n");
        printf("Enter the option number:- \n");
        scanf("%d", &option);

        switch (option)
        {

        case 1:
            Get_Bus_For_A_Route(bus_ptr);
            break;

        case 2:
            Add_New_Bus();
            printf("-----> -----> -----> -----> -----> ----->                                      'Bus seccessfully added'\n");
            printf("\n");
            break;

        case 3:
            Book_Seat(bus_ptr);
            printf("\n");
            printf("-----> -----> -----> -----> -----> ----->                                      'Seat seccessfully booked'\n");
            break;

        case 4:
            Cancel_Seat(bus_ptr);
            printf("\n");
            printf("-----> -----> -----> -----> -----> ----->                                     'Seat seccessfully canceled'\n");
            break;

        case 5:
            Search_Bus_For_Update_Operation(bus_ptr);
            printf("\n");
            printf("-----> -----> -----> -----> -----> ----->                                  'Bus details successfully updated'\n");
            break;

        case 6:
            goto Main_Menu;
            break;

        case 7:
            option = 0;
            break;

        default:
            printf("Please enter a valid option number.\n");
            goto Main_Menu;
            break;
        }
    }

    cleanup(bus_ptr, num_of_buses);
}