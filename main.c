#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct uzel{
    struct uzel *levy, *pravy;
    int prvek;
    int pocet;
    int level;
} node;

//typedef struct uzel node;


node* cre(int x);
void tisk(node *pt);
void bintree1(int x);
void bintree2(node **pt, int x);
bool najdi(node *pt, int x);
void vymaz(node **pt, int x);


void pruchod(node *pt1, node *pt2);

void intersect(node **pt1, node **pt2);

node *root;
bool tak=true;


int main(int argc, char **argv)
{
	
    node *root1 = NULL;
    node *root2 = NULL;
    
    
   
    
    int pole[]={8,2,6,9,4,7};
    for(int i=0;i<6;i++){
        bintree1(pole[i]);
    }
    
    int pole2[]={80,20,60,91,44,77};
    for(int i=0;i<6;i++){
        bintree2(&root1, pole2[i]);
    }
        
     
    int pole3[]={80,20,60,90,44,77};
    for(int i=0;i<6;i++){
        bintree2(&root2, pole3[i]);
    }
    vymaz(&root2,77);
    
    
    tisk(root1);
    
    
	return 0;
}

void pruchod(node *pt1,node *pt2){
    if(pt1!=NULL){
        pruchod(pt1->pravy, pt2);
        najdi(pt2, pt1->prvek);
        pruchod(pt1->levy, pt2);
    }
}

bool najdi(node *pt, int x){
    if(pt->prvek==x){
        printf("nalezeno na urovni: %d\n",pt->level);
        return true;
    }else if(pt->prvek < x){
            if(pt->pravy != NULL)
                najdi(pt->pravy, x);
            else {
                  printf("nenalezeno\n");
                  return false;
            }
    }else if(pt->levy != NULL)
                najdi(pt->levy, x);
          else {
                printf("nenalezeno\n");
                return false;
          }
}

node* cre(int x){
    node *uk=(node*)malloc(sizeof(node));
    uk->pravy=uk->levy=NULL;
    uk->prvek=x;
    uk->level=0;
    return uk;
}

void bintree1(int x){
    node* uzel=cre(x);
    node* pom=root; 
    bool je=true;
    while(je){
        if(root==NULL){
            root=uzel;
            je=false;
        }
        else if(pom->prvek < x){
                if(pom->pravy != NULL)
                    pom=pom->pravy;
                else {
                    uzel->level=pom->level+1;
                    pom->pravy=uzel;
                    je=false;
                }
        }
        else if(pom->prvek > x){
                if(pom->levy != NULL)
                    pom=pom->levy;
                else{
                    uzel->level=pom->level+1;
                    pom->levy=uzel;
                    je=false;
                }
            }
        }
}
    
    

void tisk(node *pt){
    if(pt==NULL) return;
    else if(tak){
            printf("root: %d\n",pt->prvek);
            tak=false;
    }
    if(pt->pravy != NULL)
        printf("pravy: %d\n", pt->pravy->prvek);
    if(pt->levy != NULL)
        printf("levy: %d\n", pt->levy->prvek);
    tisk(pt->pravy);
    tisk(pt->levy);
}


void bintree2(node **pt, int x){
    node *uzel=cre(x);
    bool jeste=true;
    node *uk = *pt;
    
    while(jeste){
        if(uk == NULL){    //*pt
            uk = uzel;     //*pt
            *pt = uk;
            jeste=false;
        }
        else if(uk->prvek < x){
                if(uk->pravy != NULL)
                    uk=uk->pravy;
                else {
                    uzel->level=uk->level+1;
                    uk->pravy=uzel;
                    jeste=false;
                }
        }
        else if(uk->prvek > x){
                if(uk->levy != NULL)
                    uk=uk->levy;
                else{
                    uzel->level=uk->level+1;
                    uk->levy=uzel;
                    jeste=false;
                }
            }
        }
}


void intersect(node **pt1, node **pt2){
    
}

void vymaz(node **pt, int x){
    node *u, *pred, *pom;
    u=pred=pom=*pt;
    bool jeste=true;
    if(*pt==NULL){
        puts("strom je prazdny");
        return;
    }
    while(jeste){
        if(u->prvek==x){
            jeste=false;
            pom=u;
            if(u->pravy==NULL && u->levy==NULL){
                if(pred!=u){
                    if(pred->pravy==u)
                        pred->pravy=NULL;
                    else pred->levy=NULL;
                }
                free(u);
                return;
            }else if(u->pravy!=NULL && u->levy!=NULL){
                pred=u;
                u=u->levy;
                while(u->pravy!=NULL){
                    pred=u;
                    u=u->pravy;
                }
                pom->prvek=u->prvek;
                if(u->levy!=NULL){
                    if(pred->pravy==u)
                        pred->pravy=u->levy;
                    else pred->levy=u->levy;
                    free(u);
                    return;
                }else{
                    if(pred->pravy==u)
                        pred->pravy=NULL;
                    else pred->levy=NULL;
                    free(u);
                    return;
                }
                }else{
                    if(u->pravy==NULL){
                        if(pred->pravy==u)
                            pred->pravy=u->levy;
                        else pred->levy=u->levy;
                        free(u);
                        return;
                    }else{
                        if(pred->pravy==u)
                            pred->pravy=u->pravy;
                        else pred->levy=u->pravy;
                        free(u);
                        return;
                    }
                }
        
        }else if(u->prvek < x){
                if(u->pravy != NULL){
                    pred=u;
                    u=u->pravy;
                }else{
                    puts("nenalezen");
                    return;
                }
              }else if(u->levy != NULL) {
                        pred=u;
                        u=u->levy;
                    }else{
                        puts("nenalezeno");
                        return;
                    }   
    }
        
}

