#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct pc {
    char type[128],name[128],cpu[128],ram[128],storage[128],gpu[128],motherboard[128];
    float price;
 };
struct node {
    struct pc* val;
    struct node *next;
    struct node *prev;
};
struct pc *make_pc(char* n,char* t,char* c,char* r,char* s,char* g,char* m,float p){
    struct pc *temp = malloc(sizeof(struct pc));
    strcpy(temp->type,t);
    strcpy(temp->name,n);
    strcpy(temp->cpu,c);
    strcpy(temp->ram,r);
    strcpy(temp->storage,s);
    strcpy(temp->gpu,g);
    strcpy(temp->motherboard,m);
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
    temp->next = malloc(sizeof(struct node));
    temp->next = NULL;
    temp->prev = NULL;
    temp->val = make_pc(n,t,c,r,s,g,m,p);
    return temp;
}
struct list make_list(){
    struct list l;
    l.first = malloc(sizeof(struct node));
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
        }  // first -next > last  && last - prev > first
        else {
            //
            //
            struct node *new_last;
            new_last = temp;
            new_last->prev = l->last;
            l->last->next = new_last;
            l->last = new_last;
            l->size = l->size + 1;
        }
    }
}
void remove_by_position(struct list l,int index  ) {
    if( l.size != 0) {
        if ( index == 0 ) {
              l.first->next->prev = NULL;
              struct node *temp = l.first->next;
              free(l.first);
              l.first = temp;
          } else if( index == l.size-1 ){
              l.last->prev->next = NULL;
              free(l.last);
              l.last = l.last->prev;
          }
            else  {
            struct node* temp = l.first;
            int i = 0 ;
            while ( i < index) {
                i++;
                temp = temp->next;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            free(temp);
          }
    } else printf("Database empty");
}
void display(struct list l){
    if (l.size!=0) {struct node *p;
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
        printf("??\n");
        gets(type);
        printf("??\n");
        gets(cpu);
        printf("??\n");
        gets(ram);
        printf("??\n");
        gets(storage);
        printf("??\n");
        gets(gpu);
        printf("??\n");
        gets(mobo);
        printf("float\n");
        scanf("%f",&p);
        append(db,make_node(name,type,cpu,ram,storage,gpu,mobo,p));
        printf("y/n\n");
        int a = 0;
        scanf("%d",&a);
        if (a == 0 ) break;
    }
    free(name);free(type);free(cpu);free(ram);free(storage);free(gpu);free(mobo);
}
int main() {
    struct list db = make_list();
    int choice = 1;
    while ( choice != 0 ) {
      fflush(stdin);
      printf("choice\n");
      scanf("%d",&choice);
      switch ( choice ) {
        case 1:
        add_pc(&db);
      }
   }

    display(db);
    remove_by_position(db,db.size-1);
    display(db);
}
