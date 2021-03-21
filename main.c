#include <stdio.h>
#include <string.h>
struct pc {
    char type[15],name[30],cpu[40],ram[20],storage[20],gpu[50],mobo[40],cooler[30];
    float price;
    int bool;
 };
struct pc db[50];
void add_pc() {
    int i;
    int c;
    for ( i = 0 ; i < 50 ; i ++ ) if ( ! db[i].bool ) break;
    if ( i == 50 ) printf("No more space in the storage, remove a pc if you want to add another one!\n");
    printf("PC type: \n");
    scanf(" %[^\n]s",&db[i].type);
    printf("PC name: \n");
    scanf(" %[^\n]s",&db[i].name);
    printf("PC CPU: \n");
    scanf(" %[^\n]s",&db[i].cpu);
    printf("PC RAM size: \n");
    scanf(" %[^\n]s",&db[i].ram);
    printf("PC storage size: \n");
    scanf(" %[^\n]s",&db[i].storage);
    printf("PC GPU: \n");
    scanf(" %[^\n]s",&db[i].gpu);
    printf("PC motherboard: \n");
    scanf(" %[^\n]s",&db[i].mobo);
    printf("CPU cooler: \n");
    scanf(" %[^\n]s",&db[i].cooler);
    printf("PC price: \n");
    scanf("%f",&db[i].price);
    printf("Enter 1 to add one more, or 0 to stop.\n");
    scanf("%d",&c);
    db[i].bool = 1;
    if ( c == 1) add_pc();
};
void show_pcs(){
    for ( int i = 0 ; i < 50 ; i++)
        if ( db[i].bool == 1 )
            printf("%s,%s,%s,%s,%s,%s,%s,%s,%.2f\n",
                   db[i].type,db[i].name,db[i].cpu,db[i].ram,
                   db[i].storage,db[i].gpu,db[i].mobo,db[i].cooler,db[i].price);

};
void remove_pc_by_name() {
    char to_remove[30];
    printf("Enter the name of the pc you want to remove:\n");
    scanf("%s",&to_remove);
    for (int i = 0 ; i < 50 ; i++) {
        if( strcmp(db[i].name,to_remove) == 0) db[i].bool = 0;
    }
};
void remove_pc_by_position() {
    int last;
    for ( int i  =  0 ; i < 50 ; i ++ )
        if ( db[i].bool == 1 ) last = i;
    int which;
    printf("Enter 1 to remove the last pc added to the storage, and 2 to remove the first pc added to the storage.\n");
    scanf("%d",&which);
    switch ( which ) {
        case 1:
            db[last].bool = 0;
            break;
        case 2:
            db[0].bool = 0;
            break;
        default:
            printf("Invalid value.\n");
            remove_pc_by_position();
    }
}
void remove_pc() {
    int c;
    printf("Enter 1 to remove a pc from the storage by position, or 2 to remove a pc by name.\n");
    scanf("%d",&c);
    switch( c ) {
        case 1:
            remove_pc_by_position();
            break;
        case 2:
            remove_pc_by_name();
        default:
            printf("Invalid value!\n");
            break;
    }

}
void menu() {
    printf("Actions:\n"
           "1. Add a computer.\n"
           "2. Remove a computer.\n"
           "3. Show the computers.\n"
           "0. Exit.\n");
}
int main() {
    for (int i = 0 ; i < 50 ; i++) db[i].bool = 0;
    while (1) {
        for (int i = 0 ; i < 50 ; i++) printf("%d",db[i].bool);
        fflush(stdin);
        int choice;
        menu();
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                add_pc();
                break;
            case 2:
                remove_pc();
                break;
            case 3:
                show_pcs();
                break;
            case 0:
                return 0;
            default:
                printf("The choice entered isn't valid.\n");
                break;
        }
    }

}
