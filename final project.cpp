#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;
int sss=0;

void removeDupWord(string str)
{
    string s=" ";
    // Used to split string around spaces.
    istringstream ss(str);
 
    // To store individual visited words
    unordered_set<string> hsh;
 int k=1;
    // Traverse through all words
    do
    {
        string word;
        ss >> word;
       
        if (word!= "+"){
           
        // If current word is not seen before.
        while (hsh.find(word) == hsh.end()) {
            cout << word << " ";
            hsh.insert(word);
            k=1;
        }
        }
        else {
            if (k==1) {cout<< "+ ";}
            k=0;
                    }
    } while (ss);
}


class M{
public:
char A, B, C;
int decimal;
int neighbours=0;
M(int x)
{
decimal = x;
if(x==1 || x==3 || x==5 || x ==7)
C = '1'; else C = '0';

if(x==2 || x==3 || x==6 || x ==7)
B = '1'; else B = '0';

if(x== 4|| x==6 || x==5 || x ==7)
A = '1'; else A = '0';
}


string content()
{
string res;
res += A;
res += B;
res += C;
return res;
}

};

M* Xnor(M A)
{
M* minterm = new M(0);

minterm->A = (A.A =='0') ? 'a' : 'A';
minterm->B = (A.B =='0') ? 'b' : 'B';
minterm->C = (A.C =='0') ?'c'  : 'C';

return minterm;
}

M* xnor(M A, M B)
{
M* minterm = new M(0);

if(A.A == B.A)
{
//lowercase means bar
if(A.A != 'x' && A.A != 'a' && A.A != 'A')
minterm->A = (A.A =='0') ? 'a' : 'A';
else if (A.A == 'a')
minterm->A = 'a';
else if (A.A == 'A')
minterm->A = 'A';
else if (A.A == 'x')
minterm->A = 'x';
}

else if(A.A != B.A)
{
minterm->A = 'x';
}


if(A.B == B.B)
{
//lowercase means bar
if(A.B != 'x'&& A.B != 'b' && A.B != 'B')
minterm->B = (A.B =='0')? 'b' : 'B';

else if (A.B == 'b')
minterm->B = 'b';
else if (A.B == 'B')
minterm->B = 'B';
else if (A.B == 'x')
minterm->B = 'x';
 
}
else if(A.B != B.B)
{
minterm->B = 'x';
}

if(A.C == B.C)
{
//lowercase means bar
if(A.C != 'x'&& A.C != 'c' && A.C != 'C')
minterm->C = (A.C =='0') ?'c' : 'C';

else if (A.C == 'c')
minterm->C = 'c';
else if (A.C == 'C')
minterm->C = 'C';
else if (A.C == 'x')
minterm->C = 'x';
}
else if(A.C != B.C)
{
minterm->C = 'x';
}
return minterm;
}

void visualize(int* minT)
{
    cout<<" BC        00     01      11      10"<<endl;
   
    cout<<"       ";
    for(int i=0; i<33; i++)
    cout<<"-";
    cout<<endl;
   
   
   cout<<"  A  0 ";cout<<"|   "<<minT[0]<<"   |   "<<minT[1]<<"   |   "<<minT[3]<<"   |   "<<minT[2]<<"   |"<<endl;
   
    cout<<"       ";for(int i=0; i<33; i++)
    cout<<"-";
    cout<<endl;
     
   cout<<"     1 ";cout<<"|   "<<minT[4]<<"   |   "<<minT[5]<<"   |   "<<minT[7]<<"   |   "<<minT[6]<<"   |"<<endl;
   
   
    cout<<"       ";
    for(int i=0; i<33; i++)
    cout<<"-";
    cout<<endl;

}


string represent(M** sim2, int size)
{

string result = "Simplified = ";
for(int i=0; i<size; i++)
{
//function would replace lowercase with teldas, add + signs between minterms + remove X chars

if(isupper(sim2[i]->A))
{
string t;
t = sim2[i]->A;
result += t;


}

if (islower(sim2[i]->A) && sim2[i]->A != 'x')
{
string t;
t += "~";
t += ((sim2[i]->A)-32);
result += t;

}


if(isupper(sim2[i]->B))
{

string t;
t = sim2[i]->B;
result += t;
}
if (islower(sim2[i]->B) && sim2[i]->B != 'x')
{
string t;
t += "~";
t += ((sim2[i]->B)-32);
result += t;

}


if(isupper(sim2[i]->C))
{
string t;
t = sim2[i]->C;
result += t;
}
if (islower(sim2[i]->C) && sim2[i]->C != 'x')
{
string t;
t += "~";
t += ((sim2[i]->C)-32);
result +=t;
}

if (i!= size-1){
result += " + ";
}


}
 
return result;
}


bool is_grey_neighbour(M* A, M* B)
{
int counter =0;

if (A->A != B->A) counter++;
if (A->B != B->B) counter++;
if (A->C != B->C) counter++;


if (counter == 1) {A->neighbours += 1; B->neighbours += 1;  return true;}
else return false;
}





void simplify(int* minT, int size)
{
M** m;
m = new M* [8];
int c = 0;
for(int i=0; i<8; i++)
{
if(minT[i]==1)
{ m[c] = new M (i);
c++;
}
}

M** simplified1;
simplified1 = new M* [size];
M** simplified2;
simplified2 = new M* [size];

int counter = 0;


if(size==1)
{
simplified1[0] = Xnor(*m[0]);
cout << represent(simplified1, size) <<endl;
return;
}

if(size==8) { cout<<"Simplified = "<<1<<endl; return;}
if(size==0) { cout<<"Simplified = "<<0<<endl; return;}

//keep counts of elements' neigbors, if one doesn't have any neighbors call the small xnor on them
for(int i=0; i<size-1; i++)
{
//compare all other elements, see if they were grey neighbors, run xnor more than once until we are done.
for(int j=i+1; j<size; j++)
{
if(is_grey_neighbour(m[i], m[j]))
{
simplified1[counter] = xnor(*m[i], *m[j]);
counter++;
}
}

}
for (int k=0; k<size; k++){
    if (m[k]->neighbours ==0)
    {
        simplified1[counter]= Xnor(*m[k]);
        counter++;
    }
}
string res1 = represent(simplified1, counter);
cout << res1<<endl;


int counter2 = counter;
counter = 0;


for(int i=0; i<counter2-1; i++)
{

for(int j=i+1; j<counter2; j++)
{
if(is_grey_neighbour(simplified1[i], simplified1[j]))
{
simplified2[counter] = xnor(*simplified1[i], *simplified1[j]);
counter++;
}
}

}
for (int k=0; k<counter2; k++){
    if (simplified1[k]->neighbours ==0)
    {
        simplified2[counter]= simplified1[k];
        counter++;
    }
}
if (counter2>=4){
string res2 = represent(simplified2, counter);

    removeDupWord(res2); }
}
int main()
{
     bool check;
     int minterm[8];
     int counterO = 0;

     cout<<"\t\tHello, This is Mina and Seif's Kmap simpilifier\n\n";
   
   do{
        check = false;
        cout<<"\tplease enter your minterms: ";
   
    string input;
    getline(cin, input);
    stringstream ss(input);
   
       
          string a;
          int counter=0;
         
     for(int i=0; i<8; i++)
            minterm[i]=0;
 
    while(getline(ss,a,','))
    {
       
        int temp = stoi(a);
        if(temp<0 || temp > 7 ){ cout<<"\nERROR:\tyou entred an invalid minterm, you cannot have "<<temp<<" as a minterm in a 3 variable K-map\nrestarting the program.....\n\n"; check = true; break;}
       if (minterm[temp] == 1){ cout<<"\nERROR:\tyou entered "<<temp<<" more than one time as a minterm. you can't enter a minterm more than one time\nrestarting the program.....\n\n"; check = true; break;
       } minterm[temp] = 1;
        counter++;
            if(counter>8) {cout<<"you entered more than 8 minterms\n restarting the program.....\n"; check = true; break;}

       
    }
     counterO = counter;
}while(check==true);
 
   visualize(minterm);
   
   simplify(minterm, counterO);
   
  return 0;
}
