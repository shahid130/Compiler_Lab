#include <bits/stdc++.h>
using namespace std;
int main()
{
    string s, ns= "a", ns2 =" " ;
    char c,c2,c3,c4,c5,c6;
    int f =0, l, l2,slen, i= 0,j=0,indx1, indx2, inlenth;
    ifstream inpfile("input.c");
    ofstream outfile("output.txt");

    while(getline (inpfile, s))
    {
        slen=s.length();

        for(int p=0; p<slen; p++)
        {
            c= s[p];
            c2 = s[(p+1)];

            if(c == '/'&& c2 == '/')
            {
                s.erase(p);

                break;
            }
        }

        ns2=ns2+s;

    }


        l2=ns2.length();
    while(j<l2-1)
    {
        c4=ns2[j];
        c5=ns2[(j+1)];

        if(c4 == '/'&& c5 == '*')
        {
           indx1 =j;

        }

        if(c4 == '*'&& c5 == '/')
        {
           indx2 =j;
           f=1;
        }

        if(f==1)
        {
            inlenth = l2-indx2-2;
            ns2.erase( ns2.begin() + indx1 ,ns2.end()-inlenth);
            l2=ns2.length();
            j=0;
            f=0;
        }
        j++;
    }

    l=ns2.length();

    while(i<l)
    {
        c3=ns2[i];
        c6=ns2[(i+1)];

if(c3 == ' '|| c3 == '\n'|| c3 == '\t'|| c3 == '\v'|| c3 == '\r'|| c3 == '\f')
{
    if(c6 == ' '|| c6 == '\n'|| c6 == '\t'|| c6 == '\v'|| c6 == '\r'|| c6 == '\f')
        {
            ns2.erase(ns2.begin() + (i+1));
            i--;
            l=ns2.length();
        }
        else
            ns2[i] = ' ';
}


if(c3 == '('||c3 == ')'||c3 == '<'|| c3 == '>'|| c3 == '{'||c3 == '}'|| c3 == ';')
{
    if(c6 == ' '|| c6 == '\n'|| c6 == '\t'|| c6 == '\v'|| c6 == '\r'|| c6 == '\f')
    {
        ns2.erase(ns2.begin() + (i+1));
        i--;
        l=ns2.length();
    }
}

        i++;
    }

outfile << ns2;


outfile.close();


cout << ns2 << endl;



    return 0;
}

