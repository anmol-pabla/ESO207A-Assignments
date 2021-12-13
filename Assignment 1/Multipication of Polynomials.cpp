#include <iostream>
using namespace std;

class Poly{
public:
    long long int coeff;
    long long int expo;
    Poly* prev;
    Poly* next;
};

Poly* sentinel1 = new Poly(); //sentinel node for Polynomial 1
Poly* sentinel2 = new Poly(); //sentinel node for Polynomial 2
Poly* finalpoly = new Poly();  //sentinel node for Final Polynomial obtained after multiplication

//Doubly linked list creating Nodes
void createNode(Poly *head, long long int coeff, long long int expo)
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

Poly* addpoly(Poly* polya, Poly* polyb)
{
    Poly* sumpoly = new Poly();  
    sumpoly->prev = sumpoly;
    sumpoly->next = sumpoly;
    
    Poly* poly1 = polya;
    Poly* poly2 = polyb;
    
    polya = polya->next;
    polyb = polyb->next;
    
    while(polya!=poly1&&polyb!=poly2)
    { 
        if((polya->expo)<(polyb->expo))
        {
           createNode(sumpoly,polya->coeff,polya->expo);
           polya = polya->next;
        }
        else  if((polyb->expo)<(polya->expo))
        {
           createNode(sumpoly,polyb->coeff,polyb->expo);
           polyb = polyb->next;
        }
        else
        {
             if(polya->coeff + polyb->coeff != 0)
                 createNode(sumpoly,polya->coeff + polyb->coeff,polya->expo);
             polya = polya->next;
             polyb = polyb->next;
        }
        
      
    }
    while(polya!=poly1)
    {
        createNode(sumpoly,polya->coeff,polya->expo);
        polya = polya->next;
    }
    
     while(polyb!=poly2)
    {
        createNode(sumpoly,polyb->coeff,polyb->expo);
        polyb = polyb->next;
    }
    return sumpoly;
}

void multipoly(Poly* polya, Poly* polyb)
{
    finalpoly->prev = finalpoly;
    finalpoly->next = finalpoly;
    
    
    while(polya!=sentinel1)
    {
        Poly* fpoly = new Poly();  
        fpoly->prev = fpoly;
        fpoly->next = fpoly;
        
        Poly* polyit = polyb;
        
        while(polyit!=sentinel2)
        {
            createNode(fpoly,polya->coeff * polyit->coeff,polya->expo + polyit->expo);
            polyit = polyit->next;
        }
        
        finalpoly = addpoly(finalpoly,fpoly);
        polya = polya->next; 
        delete fpoly;
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
   
    
    long long int n,m;
    cin>>n>>m;
    sentinel1->prev = sentinel1;
    sentinel1->next = sentinel1;
    sentinel2->prev = sentinel2;
    sentinel2->next = sentinel2;
    while(n--)
    {
        long long int coeff,expo;
        cin>>coeff>>expo;
        createNode(sentinel1,coeff,expo);
    }
    while(m--)
    {
        long long int coeff,expo;
        cin>>coeff>>expo;
        createNode(sentinel2,coeff,expo);
    }
    
    multipoly(sentinel1->next,sentinel2->next);
    print(finalpoly);
    
    delete finalpoly;
    delete sentinel1;
    delete sentinel2;
    
    return 0;
}
