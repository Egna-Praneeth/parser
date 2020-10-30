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
void printTypeExpressionTable(TypeExprNode* T)
{
    // FILE* f = fopen("output.txt","w");
    TypeExprNode* ptr = T;
    printf("\n<Field1>  <Field2>  <Field3>  <Field3>\n\n");
    while (ptr)
    {
        Array a;
        RangeRect* r;
        RangeJagged* rj;
        printf("<%s>  <%s>  <%s>  ", ptr->name, prim_or_arr_str[ptr->tag1],stat_or_dyn_str[ptr->tag2]);
        switch (ptr->tag1)
        {
        case 0:
            printf(" <type = %s>", type_to_char[ptr->TE.primitive]);
            break;
        case 1:
            a = ptr->TE.arr;
            printf(" <type = %s, dimensions = %d, ", prim_or_arr_str[ptr->tag1], a.dimensions);
            r = a.rng.rect;
            for (int i = 0; i < a.dimensions; i++)
            {
                printf("range_R%d = (%d, %d), ", i+1, r->lower.limit, r->upper.limit);
                r = r->next;
            }
            printf("basicElemntType = %s>", type_to_char[a.t]);
            break;
        case 2:
            a = ptr->TE.arr;
            printf(" <type = %s, dimensions = %d, range_R1 = (%d, %d), ", 
            prim_or_arr_str[ptr->tag1], a.dimensions, a.rng.jagged[0]->data, a.rng.jagged[0]->next->data);
            
            rj = a.rng.jagged[1];
            printf("range_R2 = (");
            while (rj->next)
            {
                printf("%d", rj->data);
                if (a.dimensions==3)
                {
                    printf("[");
                    RangeJagged3D* r1 = rj->head;
                    while (r1->next)
                    {
                        printf("%d, ", r1->data);
                        r1 = r1->next;
                    }
                    printf("%d]",r1->data);  
                }
                printf(", ");
                rj = rj->next;
            }
            printf("%d), ", rj->data);
            printf("basicElemntType = %s>", type_to_char[a.t]);
            break;
        }
        printf("\n");
        ptr = ptr->next;
    }
    printf("The End\n");
    // fclose(f);
}