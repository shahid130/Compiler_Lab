#include <bits/stdc++.h>
using namespace std;

vector<string> token, allarr;
vector<int> idIndx, numIndx, lineIndx;

int flag, sno=0;

struct smbl
{
    int sl_no;
    string id_name;
    string id_type;
    string data_type;
    string scope;
    string value;
};

int dataType(string s)
{
    if(s=="int" || s=="float" || s=="double" || s=="bool"  )
        return 1;
    else
        return 0;
}

void inserrt(string a, string b,string c,string d,struct smbl *symbls)
{
    symbls[sno].sl_no = sno+1;
    symbls[sno].id_name = a;
    symbls[sno].id_type = b;
    symbls[sno].data_type = c;
    symbls[sno].scope = d;
    sno++;
}

string lookupp( string a, string b, struct smbl *symbls)
{
    for(int i=0; i<sno; i++)
    {
        if(a==symbls[i].id_name && b==symbls[i].scope)
            return to_string(symbls[i].sl_no);
    }
}

void display(struct smbl *symbls)
{
    cout << "    SL No     " << "Name     " << "ID Type     " << "Data Type     "<< "Scope       " << "Value" << endl;
    for(int i=0; i<sno; i++)
    {

        cout << "    " << symbls[i].sl_no << "         "   <<symbls[i].id_name<< "         " <<symbls[i].id_type<< "        " <<symbls[i].data_type << "         "<<symbls[i].scope << "        "<<symbls[i].value << endl;
    }
}


int chkdigit(int a)
{
    for(int i=0; i<numIndx.size(); i++)
    {
        int ck = numIndx[i];
        if(ck==a)
        {
            return 1;
        }
    }

    return 0;
}

//===============================================================

void Parenthesis(string s)
{
    if(s=="["||s=="]"||s=="{"||s=="}"||s=="("||s==")")
    {
        s="[par " + s +"] ";
        token.push_back(s);
        flag=1;
    }
}

void Separetor(string s)
{
    if(s==","||s==";"||s=="'"||s=="\"")
    {
        s="[sep " + s +"] ";
        token.push_back(s);
        flag=1;
    }
}

void Keyword(string s)
{
    string kw[32] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
    for(int i =0; i<32; i++)
    {
        if(s==kw[i])
        {
            s="[kw " + s +"] ";
            token.push_back(s);
            flag=1;
            break;
        }
    }
}

void Operator(string s)
{
    char c = s[0];
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%'||c=='<'||c=='>'||c=='='||c=='!'||c=='&'||c=='|'||c=='^')
    {
        s="[op " + s +"] ";
        token.push_back(s);
        flag=1;
    }
}

void Number(string s)
{
    int f =0;
    for(int i =0; i<s.length(); i++)
    {
        if(isdigit(s[i])||s[i]=='.')
            f=1;
        else
        {
            f=0;
            break;
        }
    }
    if(f==1)
    {
        s="[num " + s +"] ";
        token.push_back(s);
        numIndx.push_back((token.size()-1));
        flag=1;
    }
}

void Identifier(string s)
{
    if(isalpha(s[0])||s[0]=='_')
    {
        int f =1;
        for(int i =1; i<s.length(); i++)
        {
            if(isalpha(s[i])||isdigit(s[i])||s[i]=='_')
                f=1;
            else
            {
                f=0;
                break;
            }
        }
        if(f==1)
        {
            s="[id " + s +"] ";
            token.push_back(s);
            idIndx.push_back(token.size()-1);
            flag=1;
        }
    }
}

void unKnown(string s)
{
    s="[unkn " + s +"] ";
}

int lineNumber(int a)
{
    int cnt=0;
    for(int i=0; i<lineIndx.size(); i++)
    {
        int lNo = lineIndx[i];
        if(a<lNo)
        {
            return cnt;
        }
        cnt ++;
    }
}


//======================================================
void CFG();

int indxx=0;
bool expn(int i, int j)
{

    return true;
}

void loop_stat(int i)
{
    cout << "loop";
    if(allarr[i] == "while"){
            i++;
        if(allarr[i] == "("){
            i++;
            int j=i;
            while(j<allarr.size())
            {
                if(allarr[j]==")")
                    break;
                    else
                        j++;
            }

            if(expn(i,j-1)){
                i=j;
                if(allarr[j] == ")"){
                    i++;
                    indxx=i;
                    cout << " ok ";
                    CFG();
                }
            }
        }
        cout << "Wrong syntax for while loop at line no " << i << lineNumber(i) << endl;
        indxx=i;
        CFG();
    }
}

void dscn_stat(int i)
{
    i++;
    indxx =i;
    CFG();
}

void asgn_stat(int i)
{
    i++;
    indxx =i;
    CFG();
}


void CFG()
{
    int i=indxx;
    if(i>=allarr.size())
        return;
        else if(allarr[i]=="for" || allarr[i]=="while" || allarr[i]== "do")
            loop_stat(i);
        /*else if(allarr[i]=="if" || allarr[i]=="else" || allarr[i]== "switch")
            dscn_stat(i);
        else
            asgn_stat(i);*/
        else
        {
            cout << allarr[i];
            i++;
            indxx=i;
            CFG();
        }
}

int main()
{
    string s, str, tkn;
    char c,c1,c2;
    int line=0, l, indx1,p=1, p1=0, y1=0,y2=0,y3=0;
    ifstream inpfile("input.c");
    ofstream outfile("output.txt");

    while(getline (inpfile, s))
    {
        //cout << s << endl;
        for(int i=1; i<s.length(); i++)   //remove single line comment
        {
            if(s[i-1]== '/'&& s[(i)] == '/')
            {
                s.erase(i-1);
                break;
            }
        }
        line++;
        s = to_string(line) + " " + s;
        str=str+s +" ";
    }

    for(int i=0; i<str.length(); i++)  //remove multiple line comment
    {
        if(str[i]== '/'&& str[i+1] == '*')
        {
            indx1 = i;
            continue;
        }
        else if(str[i] == '*'&& str[i+1] == '/')
        {
            str.erase( str.begin() + indx1,str.end()-(str.length()-i-2));
        }
    }

    //cout << str <<endl <<endl;

    for(int i=0; i<str.length(); i++)
    {
        c1 = str[i];
        c2 = str[(i+1)];

        if(c1 == ' '|| c1 == '\n'|| c1 == '\t'|| c1 == '\v'|| c1 == '\r'|| c1 == '\f')
        {
            if(c2 == ' '|| c2 == '\n'|| c2 == '\t'|| c2 == '\v'|| c2 == '\r'|| c2 == '\f')
            {
                str.erase((i+1), 1);
                i--;
            }
            else
                str[i] = ' ';
        }

        if(c1 == '('||c1 == ')'||c1 == '<'|| c1 == '>'|| c1 == '{'||c1 == '}'|| c1 == ';' || c1 == '=')
        {
            if(c2 == ' '|| c2 == '\n'|| c2 == '\t'|| c2 == '\v'|| c2 == '\r'|| c2 == '\f')
            {
                str.erase((i+1), 1);
                i--;
            }
        }
    }
    //===========================ass 1 done ==================
    for(int i=0; i<str.length(); i++)
    {
        c=str[i];
        c1=str[(i+1)];
        if(c == ';' || c == ',' || c == 39 || c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')'|| c == '{'|| c == '}'|| c == '['|| c == ']')
        {
            str.insert(i," ");
            i+=2;
            str.insert(i," ");
            l+=2;
        }
        else if(c == '>' || c == '<' || c == '!' || c == '|' || c == '&' || c == '=')
        {
            if(c1 == '>' || c1 == '<' || c1 == '!' || c1 == '|' || c1 == '&' || c1 == '=')
            {
                str.insert(i," ");
                i+=3;
                str.insert(i," ");
            }
            else
            {
                str.insert(i," ");
                i+=2;
                str.insert(i," ");
            }
            l+=2;
        }
    }
    for(int i=0; i<str.length(); i++)
    {
        c=str[i];
        c1=str[(i+1)];
        if(c==' ' &&c1==' ')
        {
            str.erase((i+1), 1);
            i--;
        }
    }


    for(int m=0; m<str.length(); m++)
    {
        y2++;
        if(str[m]==' ')
        {
            y2--;
            allarr.push_back(str.substr(y1,y2));
            y3++;
            y1=m+1;
            y2=0;
        }
    }

    for(int i=0; i<allarr.size(); i++)
    {
        flag=0;
        tkn = allarr[i];

        if(flag==0)
        {
            Parenthesis(tkn);
        }
        if(flag==0)
        {
            Separetor(tkn);
        }
        if(flag==0)
        {
            Keyword(tkn);
        }
        if(flag==0)
        {
            Operator(tkn);
        }
        if(flag==0)
        {
            Number(tkn);
        }
        if(flag==0)
        {
            Identifier(tkn);
        }
        if(flag==0)
        {
            unKnown(tkn);
        }
    }

   /* for(int i=0; i<token.size(); i++)
    {
        cout << token[i];
    }*/

    //===============================ass2 done=====================

    map<int, int> linemap;
    int l1=1;

    //intermediate line print

    cout << endl;
    cout << allarr[0]<< " ";
    lineIndx.push_back(0);
    for(int i=1; i<allarr.size(); i++)
    {
        int nIndx = numIndx[p];
        if(i==nIndx)
        {
            if(((allarr[i-1])=="=")||((allarr[i-1])=="return" )||((allarr[i-1])==">") ||((allarr[i-1])=="<"))
            {
                //do nothing
            }
            else
            {
                lineIndx.push_back(i);
                cout << endl;
                linemap[i]=l1;
                l1++;

            }

            p++;
        }

        if(idIndx[p1]==i)
        {
            cout << "id ";
            p1++;
        }
        cout << allarr[i] << " ";
    }

    cout << endl;

//======================line printing done============================

    smbl symbls[(idIndx.size())];

    string s1,bfridnm, bfr_id, aftr_id, idname,s2,scp,idtype, datatype, valu,  snonm;
    s1.clear();
    int slen, pos=0, vlen,len,idp,b1=0, idpo=0, chk,  ck_dgt, chk_d_n, dn_size, gb_size,dgt, sp, snop;
    char c3,c4,c5,c6,c7;

    vector <string> vect, posi;
    vector <int>  globalsno, localsno, vnum;

    for(int i=0; i<idIndx.size(); i++)
    {
        idp=idIndx[i];

        idname = allarr[idp];
        aftr_id = allarr[idp+1];
        bfr_id = allarr[idp-1];
        chk=dataType(bfr_id);

        if(aftr_id=="(")
        {
            localsno.clear();
            if(chk==1)
            {
                scp=idname;
                inserrt(idname,"func",bfr_id,"Global", symbls);
            }

            idp+=2;
            for(int j=idp; j<allarr.size(); j++)
            {
                if(allarr[j] == "{")
                {
                    b1++;
                }
                if(allarr[j] == "}")
                {
                    b1--;
                    if(b1==0)
                    {
                        break;
                    }
                }
                idpo = idIndx[i+1];
                if(idpo==j)
                {
                    aftr_id = allarr[idpo+1];
                    bfr_id = allarr[idpo-1];
                    chk=dataType(bfr_id);

                    if(aftr_id=="(")
                    {
                        if(chk==0)
                        {
                            idname = allarr[idpo];

                        }
                    }
                    else
                    {
                        i++;
                        idp=idIndx[i];
                        idname = allarr[idp];

                        if(chk==1)
                        {
                            localsno.push_back(sno);
                            inserrt(idname,"var",bfr_id,scp, symbls);
                        }

                        dgt = idpo+2;
                        ck_dgt = chkdigit(dgt);
                        if(ck_dgt==1 && allarr[idpo+1]=="=")
                        {
                            dn_size = localsno.size();
                            for(int k=0; k<dn_size; k++)
                            {
                                snop = localsno[k];
                                snonm = symbls[snop].id_name;
                                if(idname==snonm)
                                {
                                    sp=snop;
                                    break;
                                }
                            }
                            symbls[sp].value =allarr[dgt] ;
                        }
                    }
                }
            }
        }
        else
        {
            if(chk==1)
            {
                globalsno.push_back(sno);
                inserrt(idname,"var",bfr_id,"Global", symbls);
            }
            if(chk==0)
            {
            }
            dgt = idp+2;
            ck_dgt = chkdigit(dgt);
            if(ck_dgt==1 && allarr[idp+1]=="=")
            {
                gb_size = globalsno.size();
                for(int k=0; k<gb_size; k++)
                {
                    snop = globalsno[k];
                    snonm = symbls[snop].id_name;
                    if(idname==snonm)
                    {
                        sp=snop;
                        break;
                    }
                }
                symbls[sp].value = allarr[dgt] ;
            }
        }
    }

   // cout << endl;
    //display(symbls);

    //cout << endl;


/*
    //======================ass3 done=======================================
    vector<string>dupli;

    for(int i=0; i<sno; i++)
    {
        for(int j=i+1; j<sno; j++)
        {
            if((symbls[i].id_name==symbls[j].id_name) && (symbls[i].scope==symbls[j].scope))
            {
                dupli.push_back(symbls[i].id_name);
            }
        }
    }
    int pp=0,in,loca;
    string abc,bc;

    for(int i=0; i<dupli.size(); i++)
    {
        string a= dupli[i];

        for(int j=0; j<idIndx.size(); j++)
        {
            in=idIndx[j];
            abc=allarr[in];
            bc=allarr[in-1];
            if(abc==a)
            {
                if(dataType(bc)==1)
                {
                    pp++;
                    if(pp==2)
                    {
                        cout << "Duplicate Identifier " << a << " at line " << lineNumber(in) << endl;
                        break;
                    }

                }
            }

        }
    }
    int flg, bb;

    for(int i=0; i<idIndx.size() ; i++)
    {
        flg=0;
        for(int j=0; j<sno; j++)
        {
            string a = symbls[j].id_name;
            bb = idIndx[i];

            if(allarr[bb]== a)
            {
                flg=1;
                break;
            }
        }
        if(flg==0)
        {
            cout << "Undiclered Identifier " << allarr[bb] << " at line " << lineNumber(bb) << endl;
        }
    }


    int li=1, lNo, lineNo=2;
    if(allarr[1]==";" && allarr[2]==";" )
        cout << "Duplicate token at line 1" << endl;

    for(int i=2; i<allarr.size(); i++)
    {
        if(allarr[i]==";" && allarr[i+1]==";")
        {
            if(allarr[i-2]!="for")
            {
                cout << "Duplicate token at line " << lineNumber(i)  << endl;
            }
            if(i!=numIndx[li+1])
            {
                i++;
            }
        }
    }


    stack<string> brac;
    string br;
    li=1;
    lineNo=1;

    for(int i=0; i<allarr.size(); i++)
    {
        br= allarr[i];
        if(br=="("||br=="{"||br=="[")
        {
            brac.push(br);
        }

        if(br==")"||br=="}"||br=="}")
        {
            if(brac.empty())
            {
                cout << "Misplaced " << br << " at line " << lineNumber(i)  << endl;
                break;
            }
        }

        if(br==")")
        {
            if("("!=brac.top())
            {
                cout << "Misplaced ) at line" << lineNumber(i) << endl;
            }
            brac.pop();
        }

        else if(br=="}")
        {
            if("{"!=brac.top())
            {
                cout << "Misplaced } at line" << lineNumber(i) << endl;
            }
            brac.pop();
        }
        else if(br=="]")
        {
            if("]"!=brac.top())
            {
                cout << "Misplaced ] at line" << lineNumber(i)  <<endl;
            }
            brac.pop();
        }
    }

    stack<string> ifElse;
    li=1;
    lineNo=1;

    for(int i=1; i<allarr.size(); i++)
    {
        if(allarr[i]=="if")
        {
            ifElse.push(allarr[i]);
        }
        if(allarr[i]=="else")
        {
            if(ifElse.empty())
            {
                cout << "Unmatched else at line " << lineNumber(i) << " ";
            }
            ifElse.pop();
        }
    }

*/
        cout << "Mimmah" << endl;


    //=============ass 5 ========================

    CFG();

    cout << "endd";

    return 0;
}

