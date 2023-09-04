#include <bits/stdc++.h>
using namespace std;
int main()
{
    string s, cks, s1,spc=" ",s3,sF;
    s1.clear();
    char c,c1,c2,c3,c4,c5,c6;
    int n,l,k1;
    ifstream inpfile("output.txt");
    ofstream outfile("output1.txt");

    if(inpfile.is_open())
    {
        while(getline (inpfile, s))
        {
            s1=s1+s;
        }
        l=s1.length();

        for(int i=0; i<l; i++)
        {
            c=s1[i];
            c1=s1[(i+1)];
            if(c == ';' || c == ',' || c == 39 || c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')'|| c == '{'|| c == '}'|| c == '['|| c == ']')
            {
                s1.insert(i,spc);
                i+=2;
                s1.insert(i,spc);
                l+=2;
            }
            else if(c == '>' || c == '<' || c == '!' || c == '|' || c == '&' || c == '=')
            {
                if(c1 == '>' || c1 == '<' || c1 == '!' || c1 == '|' || c1 == '&' || c1 == '=')
                {
                    s1.insert(i,spc);
                    i+=3;
                    s1.insert(i,spc);
                }
                else
                {
                    s1.insert(i,spc);
                    i+=2;
                    s1.insert(i,spc);
                }
                l+=2;
            }
        }
        for(int i=0; i<l; i++)
        {
            c=s1[i];
            c1=s1[(i+1)];
            if(c==' ' &&c1==' ')
            {
                s1.erase(s1.begin() + (i+1));
            }
        }
        outfile << s1;
        outfile.close();
    }
    else
        cout << "File can't be open";


    ifstream inpfile1("output1.txt");
    ofstream outfile1("finalOutput.txt");


            s1.clear();

    if(inpfile1.is_open())
    {
        while(getline (inpfile1, s))
        {
            s1=s1+s;
        }
        cout << s1 <<"\n";

        int y1=0,y2=0,ydif,spcsum=0,ky=0,y3=0, newl, fval=0;
        char chk, chk1, chk2,chk3;
        string cStr, cStr1, cStr2,shou,rav;
        l=s1.length();
        string kw[32] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for	goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};



        for(int m=0; m<l; m++)
        {
            chk3 =s1[m];
            if(chk3==' ')
            {
                spcsum++;
            }
        }

        string allarr[spcsum];
        string finalArr[spcsum];

        for(int m=0; m<l; m++)
        {
            chk3 =s1[m];
            y2++;
            if(chk3==' ')
            {
                y2--;
                cStr = s1.substr(y1,y2);
                allarr[y3]=cStr;
                y3++;
                y1=m+1;
                y2=0;
            }
        }


        for(int i=0; i<spcsum; i++)
        {
            ky=0;
            cStr1 = allarr[i];
            //cout << "cstr= " << cStr1 << "\n";
            newl=cStr1.length();

            cks= "fhvbri";

            if(cStr1=="["||cStr1=="]"||cStr1=="{"||cStr1=="}"||cStr1=="("||cStr1==")")
            {
                cks="Parenthesis";
                ky=1;
            }

            else if(cStr1==","||cStr1==";"||cStr1=="'"||cStr1=="\"")
            {
                cks="Separator";
                ky=1;
            }



            for(int k=0; k<32; k++)
            {
                cStr2= kw[k];

                if(cStr1==cStr2)
                {

                    cks="Keyword";
                    ky=1;
                    break;
                }

            }




            for(int q=0; q<newl; q++)
            {
                if(ky==1)
                {
                    break;
                }

                chk1 = cStr1[0];
                chk2 = cStr1[q];


                if(chk1=='+'||chk1=='-'||chk1=='*'||chk1=='/'||chk1=='%'||chk1=='<'||chk1=='>'||chk1=='='||chk1=='!'||chk1=='&'||chk1=='|'||chk1=='^')
                {
                    if(newl==1)
                    {
                        cks="Operator";
                    }
                    else if(chk2=='=' ||chk2=='&' ||chk2=='|')
                    {
                        cks="Operator";
                    }
                }
                else if((chk1>='0' && chk1<='9')||chk1=='.')
                {
                    if(newl==1)
                    {
                        cks="Numerical";
                    }
                    else if((chk2>='0' && chk2<='9')||chk2=='.')
                    {
                        cks="Numerical";
                    }
                    else
                    {
                        cks="unknown";
                        break;
                    }
                }

                else if((chk1>='a' && chk1<='z')||(chk1>='A' && chk1<='Z')||chk1=='_')
                {
                    if(newl==1 && chk1!='_')
                    {
                        cks="Identifier";
                    }
                    else if((chk2>='a' && chk2<='z')||(chk2>='A' && chk2<='Z'))
                    {
                        cks="Identifier";
                    }
                    else if((chk2>='0' && chk2<='9')||chk2=='_')
                    {
                        cks="Identifier";
                    }
                }

            }

            if(cks=="Separator")
            {
                shou = "[sep ";
                shou = shou + cStr1;
                rav = "] ";
                shou = shou +rav;

                finalArr[fval]=shou;
                fval++;
            }
            else if(cks=="Parenthesis")
            {
                shou = "[par ";
                shou = shou + cStr1;
                rav = "] ";
                shou = shou +rav;

                finalArr[fval]=shou;
                fval++;
            }
            else if(cks=="Operator")
            {
                shou = "[op ";
                shou = shou + cStr1;
                rav = "] ";
                shou = shou +rav;

                finalArr[fval]=shou;
                fval++;
            }
            else if(cks=="Numerical")
            {
                shou = "[num ";
                shou = shou + cStr1;
                rav = "] ";
                shou = shou +rav;

                finalArr[fval]=shou;
                fval++;
            }
            else if(cks=="Keyword")
            {
                shou = "[kw ";
                shou = shou + cStr1;
                rav = "] ";
                shou = shou +rav;

                finalArr[fval]=shou;
                fval++;
            }
            else if(cks=="Identifier")
            {
                shou = "[id ";
                shou = shou + cStr1;
                rav = "] ";
                shou = shou +rav;

                finalArr[fval]=shou;
                fval++;
            }
            else
            {
                shou = "[unkn ";
                shou = shou + cStr1;
                rav = "] ";
                shou = shou +rav;

                finalArr[fval]=shou;
                fval++;
            }
            cks="abcd";
        }
        string FinalOutput = " ", fo;
        FinalOutput.clear();
        for(int p=0; p<spcsum; p++)
        {
            fo = finalArr[p];
            FinalOutput = FinalOutput +fo;
        }

        outfile1 << FinalOutput;
        outfile1.close();
        cout << FinalOutput << "\n";

    }
    else
        cout << "File2 can't be open";


    return 0;
}
