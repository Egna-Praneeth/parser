/*
Group no.: 11
Group member names and IDs:
Aditya V. Bodade
2018A7PS0256P

Egna Praneeth Gummana
2018A7PS0284P

Yogya Modi
2018A7PS0235P

Kartikaya Sharma
2018A7PS0386P

*/

#include <stdio.h>
#include "metadata.h"
#include "typeExpr.h"
int main()
{
    TypeExprNode* ptr;
    
    while (ptr)
    {
        Array a;
        printf("<%s> <%s> <%s> ", ptr->name, prim_or_arr_str[ptr->tag1],stat_or_dyn_str[ptr->tag2]);
        switch (ptr->tag1)
        {
        case 0:
            printf(" <type = %s>", enumtochar[ptr->TE.primitive]);
            break;
        case 1:
            a = ptr->TE.arr;
            printf(" <type = %s, dimensions = %d", prim_or_arr_str[ptr->tag1], a.dimensions);
            for (int i = 0; i < a.dimensions; i++)
            {
                RangeRect* r = a.rng.rect;
                printf("range_R%d = (%d, %d), ", i+1, r->lower.limit, r->upper.limit);
                r = r->next;
            }
            printf("basicElemntType = %s>", enumtochar[a.t]);
            break;
        case 2:
            a = ptr->TE.arr;
            printf(" <type = %s, dimensions = %d, range_R1 = (%d, %d), ", 
            prim_or_arr_str[ptr->tag1], a.dimensions, a.rng.jagged[0]->data, a.rng.jagged[0]->next->data);
            
            RangeJagged* r = a.rng.jagged[1];
            printf("range_R2 = ( ");
            while (r->next)
            {
                printf("%d", r->data);
                if (a.dimensions==3)
                {
                    printf("[");
                    RangeJagged3D* r1 = r->head;
                    while (r1->next)
                    {
                        printf("%d, ", r1->data);
                        r1 = r1->next;
                    }
                    printf("%d]",r1->data);  
                }
                printf(", ");
                r = r->next;
            }
            printf("%d), ", r->data);
            printf("basicElemntType = %s>", enumtochar[a.t]);
            break;
        }
    
        ptr = ptr->next;
    }
}