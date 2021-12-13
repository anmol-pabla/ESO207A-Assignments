#include <iostream>
using namespace std;

class Poly{
public:
    long int coeff;
    long int expo;
    Poly* prev;
    Poly* next;
};

Poly* sentinel1 = new Poly(); //sentinel node for Polynomial 1
Poly* sentinel2 = new Poly(); //sentinel node for Polynomial 2
Poly* fpoly = new Poly();  //sentinel node for Final Polynomial obtained after addition

//Doubly linked list creating Nodes
void createNode(Poly *head, long int coeff, long int expo)
{
    Poly* temp = new Poly();
    temp->coeff = coeff;
    temp->expo = expo;    
    Poly *last = head->prev;
    temp->next=head;
    head->prev=temp;
    temp->prev=last;
    last->next=temp;    
}

//Printing the coefficients and the exponents
void print(Poly* head)
{    
    Poly* temp = head->next;
    while(temp!=head)
    {      
        cout<<temp->coeff<<" "<<temp->expo<<" ";            
        temp = temp->next;
    }    
}

void addpoly(Poly* polya, Poly* polyb)
{
    fpoly->prev = fpoly;
    fpoly->next = fpoly;
    while(polya!=sentinel1&&polyb!=sentinel2)
    { 
        if((polya->expo)<(polyb->expo))
        {
           createNode(fpoly,polya->coeff,polya->expo);
           polya = polya->next;
        }
        else  if((polyb->expo)<(polya->expo))
        {
           createNode(fpoly,polyb->coeff,polyb->expo);
           polyb = polyb->next;
        }
        else
        {
             if(polya->coeff + polyb->coeff != 0)
                 createNode(fpoly,polya->coeff + polyb->coeff,polya->expo);
             polya = polya->next;
             polyb = polyb->next;
        }
    }
    while(polya!=sentinel1)
    {
        createNode(fpoly,polya->coeff,polya->expo);
        polya = polya->next;
    }
    
     while(polyb!=sentinel2)
    {
        createNode(fpoly,polyb->coeff,polyb->expo);
        polyb = polyb->next;
    }
   
}
int main() {
    
    // input format: - 
    // First Line
    // n - degree of Polynomial1 +1
    // m - degree of Polynomial2 +1
    // Next n lines: - 
    // coefficient and exponent of Polynomial1 (ascending order of exponents)
    // Next m lines: - 
    // coefficient and exponent of Polynomial2 (ascending order of exponents)
    
    // e.g 3 2
    //     8 0
    //     9 1
    //     10 2
    //     3 0
    //     5 1
    //The two polynomials are 10x^2 + 9x + 8 and 5x +3
   
    
    long int n,m;
    cin>>n>>m;
    sentinel1->prev = sentinel1;
    sentinel1->next = sentinel1;
    sentinel2->prev = sentinel2;
    sentinel2->next = sentinel2;
    while(n--)
    {
        long int coeff,expo;
        cin>>coeff>>expo;
        createNode(sentinel1,coeff,expo);
    }
    while(m--)
    {
        long int coeff,expo;
        cin>>coeff>>expo;
        createNode(sentinel2,coeff,expo);
    }
    addpoly(sentinel1->next,sentinel2->next);
    print(fpoly);
    return 0;
}
