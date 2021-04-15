#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
FILE *fp;
struct pc {
    char* type;char* name;char* cpu;char* ram;char* storage;char* gpu;char* motherboard;
    float price;
 };
struct node {
    struct pc* val;
    struct node *next;
    struct node *prev;
};
struct pc *make_pc(){
    struct pc* temp = malloc(sizeof(struct pc));
    temp->type = malloc(128*sizeof(char));
    temp->name = malloc(128*sizeof(char));
    temp->cpu = malloc(128*sizeof(char));
    temp->ram = malloc(128*sizeof(char));
    temp->storage = malloc(128*sizeof(char));
    temp->gpu = malloc(128*sizeof(char));
    temp->motherboard = malloc(128*sizeof(char));
    temp->price = -1.0f;
    return temp;
}
struct pc *init_pc(char* n,char* t,char* c,char* r,char* s,char* g,char* m,float p){
    struct pc *temp = make_pc();
    temp->type = strdup(t);
    temp->name = strdup(n);
    temp->cpu = strdup(c);
    temp->ram = strdup(r);
    temp->storage = strdup(s);
    temp->gpu = strdup(g);
    temp->motherboard = strdup(m);
    temp->price = p;
    return temp;
}
struct list{
    struct node *first;
    struct node *last;
    int size;
};
struct node *empty_node ( ) {
    struct node *temp = malloc(sizeof(struct node));
    temp->next = NULL;
    temp->prev = NULL;
    temp->val = make_pc();
    return temp;
}
struct node *make_node(char* n,char* t,char* c,char* r,char* s,char* g,char* m,float p){
    struct node *temp = malloc(sizeof(struct node));
    temp->next = NULL;
    temp->prev = NULL;
    temp->val = init_pc(n,t,c,r,s,g,m,p);
    return temp;
}
void free_pc (struct pc* temp) {
     free(temp->type);
     free(temp->name);
     free(temp->cpu);
     free(temp->ram);
     free(temp->storage);
     free(temp->gpu);
     free(temp->motherboard);
}
struct list make_list(){
    struct list l;
    l.first = NULL;
    l.last = NULL;
    l.size = 0;
    return l;
}
void append(struct list *l, struct node* temp){
    if (l->size == 0) {
        struct node *first;
        first = temp;
        l->first = first;
        l->size = l->size + 1;
    }
    else {
        struct node *last;
        last = temp;
        if (l->last==NULL)
        {
            l->last = last;
            l->first->next = last;
            l->last->prev = l->first;
            l->size = l->size + 1;
        }
        else {
            struct node *new_last;
            new_last = temp;
            new_last->prev = l->last;
            l->last->next = new_last;
            l->last = new_last;
            l->size = l->size + 1;
        }
    }
}
void display(struct list l, int chk  ){
    if (l.size!=0) {
        int i = 1;
        struct node *p;
        p = empty_node();
        p->val = l.first->val;
        p->next = l.first->next;
        while ( p != NULL ) {
            printf("%d. %s %s %s %s %s %s %s %.2f\n",i,p->val->name,p->val->type,p->val->cpu,p->val->ram, // do not like this
                   p->val->storage,p->val->gpu,p->val->motherboard,p->val->price); // but too lazy to write 2 printfs
            p = p->next;
            i++;
        }
    }
    else printf("Database empty\n");
    if ( chk == 1 ) {printf("Press a key to continue\n");
    //getch();
  //fflush(stdin);
}
}
void write(struct list l) {
    fp  = fopen("db.txt","a");
    if (l.size!=0) {
        int i = 1;
        struct node *p;
        p = l.first;
        while ( p != NULL ) {
            fprintf(fp,"%s,%s,%s,%s,%s,%s,%s,%.2f,\n",p->val->name,p->val->type,p->val->cpu,p->val->ram, // do not like this
            p->val->storage,p->val->gpu,p->val->motherboard,p->val->price); // but too lazy to write 2 printfs
            fclose(fp);
            p = p->next;
            i++;
        }
    }
    else printf("Database is empty, nothing to write into a file.\n");
}
void read(struct list *l) {
  char* buffer = malloc(9 * 128 * sizeof(char));
  fp =  fopen("db.txt","r");
  int chk = -1;
  int line = 1;
  while(fgets(buffer,10*sizeof(buffer),fp)) {
      size_t count = 0;
      char* prot = malloc(sizeof(buffer));
      strcpy(prot,buffer);
      while(*prot != '\0'){
          count += *prot++ == ',';
      }
      if(count == 8){
      struct node* temp = empty_node();
      chk = sscanf(buffer,"%127[a-zA-Z0-9- ],%127[a-zA-Z0-9- ],%127[a-zA-Z0-9- ],%127[a-zA-Z0-9- ],%127[a-zA-Z0-9- ],%127[a-zA-Z0-9- ],%127[a-zA-Z0-9- ],%f,\n",temp->val->name,temp->val->type,temp->val->cpu,temp->val->ram,
      temp->val->storage,temp->val->gpu,temp->val->motherboard,&temp->val->price);
      append(l,temp);
      } else {
          printf("On line %d data is invalid\n",line);
      }
  }
  if(chk == -1) printf("\nDatabase file empty");
}
void remove_by_position( struct list* l,int index ,int checker) {
    if( l->size != 0 && l->size != 1) {
        if ( index == 0 ) {
              l->first->next->prev = NULL;
              struct node *temp;
              temp = l->first->next;
              free_pc(l->first->val);
              free(l->first);
              l->first = temp;
              l->size = l->size - 1;
              if (checker == 1) printf("Pc at index %d deleted.\n",index);
          } else if( index == l->size-1 ){
              l->last->prev->next = NULL;
              free_pc(l->last->val);
              free(l->last);
              l->last = l->last->prev;
              l->size = l->size - 1;
              if (checker == 1) printf("Pc at index %d deleted.\n",index);
          }
            else  {
            struct node* temp = l->first;
            int i = 0 ;
            while ( i < index) {
                i++;
                temp = temp->next;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            l->size = l->size - 1;
            free_pc(temp->val);
            free(temp);
            if (checker == 1) printf("Pc at index %d deleted.\n",index);
          }
    } else if ( l->size == 1 ) {
        if ( index != 0 && index != 1) printf("Invalid index!\n"); else {
            free_pc(l->first->val);
            free(l->first);
            l->size = l->size - 1;
            l->first->next = NULL;
            l->first->prev = NULL;
            l->first->val = NULL;
            if (checker == 1) printf("Pc at index %d deleted.\n",index);
        }
    } else printf("Database empty\n");
}
void modify_pc (struct list *l) {
    printf("Choose the pc you want to modify by it's index:\n");
    display(*l,0);
    fflush(stdin);
    int index;
    scanf("%d",&index);
    while ( index > l->size ) {
      printf("Wrong index, choose again.\n");
      display(*l,0);
      fflush(stdin);
      scanf("%d",&index);
    }
    int i = 1;
    struct node* temp;
    temp = l->first;
    while (i < index) {
        temp = temp -> next;
        i++;
    }
    int check = 10;
    char* data_to_update = malloc(128*sizeof(char));
    float pr;
    while ( check != 0) {
        printf("Choose what field to update:\n0.To exit.\n1.Name\n2.Type\n3.Cpu\n4.Ram size\n5.Storage size\n6.Gpu\n7.Motheboard\n8.Price\n");
        scanf("%d",&check);
        fflush(stdin);
        switch (check) {
            case 1:
            printf("Enter the updated name:\n");
            gets(data_to_update);
            strcpy(temp->val->name,data_to_update);
            break;
            case 2:
            printf("Enter the updated type\n");
            gets(data_to_update);
            strcpy(temp->val->type,data_to_update);
            break;
            case 3:
            printf("Enter the updated cpu\n");
            gets(data_to_update);
            strcpy(temp->val->cpu,data_to_update);
            break;
            case 4:
            printf("Enter the updated ram\n");
            gets(data_to_update);
            strcpy(temp->val->ram,data_to_update);
            break;
            case 5:
            printf("Enter the updated storage\n");
            gets(data_to_update);
            strcpy(temp->val->storage,data_to_update);
            break;
            case 6:
            printf("Enter the updated gpu\n");
            gets(data_to_update);
            strcpy(temp->val->gpu,data_to_update);
            break;
            case 7:
            printf("Enter the updated motherboard\n");
            gets(data_to_update);
            strcpy(temp->val->motherboard,data_to_update);
            break;
            case 8:
            printf("Enter the updated price\n");
            scanf("%f",&pr);
            temp->val->price = pr;
            break;
            case 0:
            break;
            default:
            printf("You have entered a wrong index.\n");
            break;
        }
    }
}
void remove_pc ( struct list *l ) {
    char *a = malloc(sizeof(char)*128);
    float ll;
    fflush(stdin);
    int cts;
    display(*l,0);
    printf("Choose what field to remove a pc by:\n1.Name\n2.Type\n3.Cpu\n4.Ram size\n5.Storage size\n6.Gpu\n7.Motheboard\n8.Price\n");
    scanf("%d",&cts);
    int check;
    struct node* p;
    struct node* k;
    p = l->first;
    int i = 0;
    switch (cts) {
        case 1:
        fflush(stdin);
        printf("Choose the name of the pc to be deleted:\n");
        gets(a);
        while ( p !=  NULL) {
        check = 0;
        if ( strcmp ( p->val->name, a) == 0){
            k = p->next;
            printf("the pc named %s was deleted\n",p->val->name);
            remove_by_position(l,i,0);
            check++;
            }
            i++;
            if ( check == 1) p = k;
            else p = p->next;
        }
        if (check == 0 ) printf("No pc with that field was found.\n");
        break;
        case 2:
        fflush(stdin);
        printf("Choose the type of the pc to be deleted:\n");
        gets(a);
        while ( p !=  NULL) {
        check = 0;
        if ( strcmp ( p->val->type, a) == 0){
            k = p->next;
            printf("the pc with the type %s was deleted\n",p->val->type);
            remove_by_position(l,i,0);
            check++;
            }
            i++;
            if ( check == 1) p = k;
            else p = p->next;
        }
        if (check == 0 ) printf("No pc with that field was found.\n");
        break;
        case 3:
        fflush(stdin);
        printf("Choose the cpu of the pc to be deleted:\n");
        gets(a);
        while ( p !=  NULL) {
        check = 0;
        if ( strcmp ( p->val->cpu, a) == 0){
            k = p->next;
            printf("the pc with the cpu %s was deleted\n",p->val->cpu);
            remove_by_position(l,i,0);
            check++;
            }
            i++;
            if ( check == 1) p = k;
            else p = p->next;
        }
        if (check == 0 ) printf("No pc with that field was found.\n");
		break;
        case 4:
        fflush(stdin);
        printf("Choose the ram of the pc to be deleted:\n");
        gets(a);
        while ( p !=  NULL) {
        check = 0;
        if ( strcmp ( p->val->ram, a) == 0){
            k = p->next;
            printf("the pc with the ram %s was deleted\n",p->val->ram);
            remove_by_position(l,i,0);
            check++;
            }
            i++;
            if ( check == 1) p = k;
            else p = p->next;
        }
        if (check == 0 ) printf("No pc with that field was found.\n");
		break;
        case 5:
        fflush(stdin);
        printf("Choose the storage of the pc to be deleted:\n");
        gets(a);
        while ( p !=  NULL) {
        check = 0;
        if ( strcmp ( p->val->storage, a) == 0){
            k = p->next;
            printf("the pc with the storage %s was deleted\n",p->val->storage);
            remove_by_position(l,i,0);
            check++;
            }
            i++;
            if ( check == 1) p = k;
            else p = p->next;
        }
        if (check == 0 ) printf("No pc with that field was found.\n");
		break;
        case 6:
        fflush(stdin);
        printf("Choose the gpu of the pc to be deleted:\n");
        gets(a);
        while ( p !=  NULL) {
        check = 0;
        if ( strcmp ( p->val->gpu, a) == 0){
            k = p->next;
            printf("the pc with the gpu %s was deleted\n",p->val->gpu);
            remove_by_position(l,i,0);
            check++;
            }
            i++;
            if ( check == 1) p = k;
            else p = p->next;
        }
        if (check == 0 ) printf("No pc with that field was found.\n");
		break;
        case 7:
        fflush(stdin);
        printf("Choose the motherboard of the pc to be deleted:\n");
        gets(a);
        while ( p !=  NULL) {
        check = 0;
        if ( strcmp ( p->val->motherboard, a) == 0){
            k = p->next;
            printf("the pc with the motherboard %s was deleted\n",p->val->motherboard);
            remove_by_position(l,i,0);
            check++;
            }
            i++;
            if ( check == 1) p = k;
            else p = p->next;
        }
        if (check == 0 ) printf("No pc with that field was found.\n");
		break;
        case 8:
        fflush(stdin);
        printf("Choose the price of the pc to be deleted:\n");
        scanf("%d",&ll);
        while ( p !=  NULL) {
        check = 0;
        if ( p->val->price == ll){
            k = p->next;
            printf("the pc with the price %.2f was deleted\n",p->val->price);
            remove_by_position(l,i,0);
            check++;
            }
            i++;
            if ( check == 1) p = k;
            else p = p->next;
        }
        if (check == 0 ) printf("No pc with that field was found.\n");
		break;
        }
}
void add_pc(struct list* db) {
    char *name = malloc(128*sizeof(char));
    char *type = malloc(128*sizeof(char));
    char *cpu = malloc(128*sizeof(char));
    char *ram = malloc(128*sizeof(char));
    char *storage = malloc(128*sizeof(char));
    char *gpu = malloc(128*sizeof(char));
    char *mobo = malloc(128*sizeof(char));
    float p;
    while ( 1 ) {
        fflush(stdin);
        printf("Name:\n");
        gets(name);
        printf("Type:\n");
        gets(type);
        printf("Cpu:\n");
        gets(cpu);
        printf("Ram size:\n");
        gets(ram);
        printf("Storage size:\n");
        gets(storage);
        printf("Gpu:\n");
        gets(gpu);
        printf("Motherboard:\n");
        gets(mobo);
        printf("Price:\n");
        scanf("%f",&p);
        append(db,make_node(name,type,cpu,ram,storage,gpu,mobo,p));
        printf("0 to stop, 1 to add another pc\n");
        int a = 0;
        scanf("%d",&a);
        if (a == 0 ) break;
    }
    free(name);free(type);free(cpu);free(ram);free(storage);free(gpu);free(mobo);
}
void menu() {
    printf("Choices: \n");
    printf("1. Add a pc to the database.\n");
    printf("2. Remove pc.\n");
    printf("3. Remove pc by index.\n");
    printf("4. Update a pc.\n");
    printf("5. Display.\n");
    printf("6. Load database from file.\n");
    printf("7. Write database to file.\n");
    printf("0. Exit.\n");
}
int main() {
    struct list db = make_list();
    int choice = 1;
    int to_del;
    while ( choice != 0 ) {
      menu();
      fflush(stdin);
      scanf("%d",&choice);
      switch ( choice ) {
        case 1:
        add_pc(&db);
        
        break;
        case 2:
        remove_pc(&db);
        
        break;
        case 3:
        fflush(stdin);
        printf("Index to be deleted:\n");
        scanf("%d",&to_del);
        remove_by_position(&db,to_del,1);
        
        break;
        case 4:
        modify_pc(&db);
        
        break;
        case 5:
        display(db,1);
        
        break;
        case 6:
        read(&db);
        
        break;
        case 7:
        write(db);
        
        break;
      }
   }
}
