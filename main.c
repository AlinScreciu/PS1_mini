#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
    char* type = malloc(128*sizeof(char));
    char* name = malloc(128*sizeof(char));
    char* cpu = malloc(128*sizeof(char));
    char* ram = malloc(128*sizeof(char));
    char* storage = malloc(128*sizeof(char));
    char* gpu = malloc(128*sizeof(char));
    char* motherboard = malloc(128*sizeof(char));
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
void remove_by_position( struct list* l,int index ) {
    if( l->size != 0 && l->size != 1) {
        if ( index == 0 ) {
              l->first->next->prev = NULL;
              struct node *temp;
              temp = l->first->next;
              free_pc(l->first->val);
              free(l->first);
              l->first = temp;
              l->size = l->size - 1;
          } else if( index == l->size-1 ){
              l->last->prev->next = NULL;
              free_pc(l->last->val);
              free(l->last);
              l->last = l->last->prev;
              l->size = l->size - 1;
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
          }
    } else if ( l->size == 1 ) {
        if ( index != 0 && index != 1) printf("Invalid index!\n"); else {
            free_pc(l->first->val);
            free(l->first);
            l->size = l->size - 1;
            l->first->next = NULL;
            l->first->prev = NULL;
            l->first->val = NULL;
        }
    } else printf("Database empty\n");
}
void modify_pc (struct list *l) {
struct node* p;
    p = l->first;
    p->val->name = " CHANGED KEKW";

} 
void remove_pc ( struct list *l ) {
    char *a = malloc(sizeof(char)*128);
    float ll;
    fflush(stdin);
    int cts;
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
            remove_by_position(l,i);
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
            remove_by_position(l,i);
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
            remove_by_position(l,i);
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
            remove_by_position(l,i);
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
            remove_by_position(l,i);
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
            remove_by_position(l,i);
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
            remove_by_position(l,i);
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
            remove_by_position(l,i);
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
void display(struct list l){
    if (l.size!=0) {
        struct node *p;
        p = l.first;
        while ( p != NULL ) {
            printf("%s %s %s %s %s %s %s %.2f\n",p->val->name,p->val->type,p->val->cpu,p->val->ram, // do not like this
                   p->val->storage,p->val->gpu,p->val->motherboard,p->val->price); // but too lazy to write 2 printfs
            p = p->next;
        }

    }else printf("empty\n");

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
    printf("Choices:\n1. Add a pc to the database.\n");
    printf("Choices:\n2. Remove pc.\n");
    printf("Choices:\n3. Display.\n");
    printf("Choices:\n0. Exit.\n");
}
int main() {
    struct list db = make_list();
    int choice = 1;
    while ( choice != 0 ) {
      fflush(stdin);
      menu();
      scanf("%d",&choice);
      switch ( choice ) {
        case 1:
        add_pc(&db);
        break;
        case 2:
        remove_pc(&db);
        break;
        case 3:
        display(db);
      }
   }
}
