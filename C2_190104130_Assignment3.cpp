#include <bits/stdc++.h>
using namespace std;

int nmres, allid=0, sno=0;

struct smbl
{
    int sl_no;
    string id_name;
    string id_type;
    string data_type;
    string scope;
    string value;
};

string clrID(string name)
{
    int l,y1,y2;
    char c;
    l=name.length();
    for(int i=0; i<l; i++)
    {
        c= name[i];
        if(c==' ')
        {
            y1=i+1;
        }
        else if(c==']')
        {
            y2=i;
        }
    }

    y2=y2-y1;
    name = name.substr(y1,y2);
    return name;
}

string clrOthers(string name)
{
    int l,y1=1;
    l=name.length();
    l=l-y1-1;
    name = name.substr(y1,l);
    return name;
}

int chkdigit(int number,vector <int> &vnum)
{
    int l = vnum.size();
    for(int i=0; i<l; i++)
    {
        int ck = vnum[i];
        if(ck==number)
        {
            return 1;
        }
    }

    return 0;
}

int duplicate(string dtype)
{
    if(dtype=="int" || dtype=="float" || dtype=="double" || dtype=="bool"  )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void inserrt( string a, string b,string c,string d,struct smbl *symbls )
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


int main()
{
    string s,s1,tkn,bfridnm, bfr_id, aftr_id, idname,s2,  chkname,scp,idtype, datatype, valu,  snonm, findnumb,d,y,z;
    s1.clear();
    int l, slen, pos=0, vlen,len,idp,b1=0,p, idpo=0, chk,  ck_dgt, chk_d_n, dn_size, gb_size,dgt, sp, snop;
    char c1,c2,c3,c4,c5,c6,c7;

    vector <string> vect, posi;
    vector <int> idpos, globalsno, localsno, vnum;

    ifstream inpfile("input.txt");
    ofstream outfile("output.txt");

    if(inpfile.is_open())
    {
        while(getline (inpfile, s))
        {
            s1=s1+s;
        }
        s1=s1+" ";
        cout << s1 <<"\n\n";

        //=================================take token in vector=============

        l = s1.length();
        for(int i=0; i<l; i++)
        {
            c1=s1[i];
            c2=s1[i+1];

            if(c1==']' && c2==' ')
            {
                slen=i+1-pos;
                tkn = s1.substr(pos,slen);
                vect.push_back(tkn);
                pos=i+2;
            }
        }

        //===========step 1: only identifiers pairs & numbers=============================================

        vlen=vect.size();
        for(int i=0; i<vlen; i++)
        {
            tkn = vect[i];
            len = tkn.length();

            //=========finding value===========
            findnumb = tkn.substr(1,3);
            if(findnumb=="num")
            {
                vnum.push_back(i);
            }

            //=========step 1, separate id token===========
            for(int j=0; j<len; j++)
            {
                c3= tkn[j];

                if(c3==' ')
                {
                    c4= tkn[j-2];
                    c5= tkn[j-1];
                    if(c4=='i' && c5=='d')
                    {
                        idpos.push_back(i);
                        allid++;
                        break;
                    }
                    else
                    {
                        tkn.erase(tkn.begin() + 1, tkn.begin() +(j+1));
                        vect[i]=tkn;
                        break;
                    }
                }
            }
        }

        cout << "Step 1: \n";
        for(int i=0; i<vlen; i++)
        {
            cout <<vect[i] << " ";
        }
        cout << "\n\na";


        //============================table generate=============================================

        smbl symbls[allid];   //allid=13

        for(int i=0; i<allid; i++)
        {
            idp=idpos[i];
            bfridnm = vect[idp];
            idname=clrID(bfridnm);

            aftr_id = vect[idp+1];
            aftr_id = clrOthers(aftr_id);

            bfr_id = vect[idp-1];
            bfr_id= clrOthers(bfr_id);
            chk=duplicate(bfr_id);

            if(aftr_id=="(")
            {
                localsno.clear();
                if(chk==1)
                {
                    scp=idname;
                    inserrt(idname,"func",bfr_id,"Global", symbls);

                    y = to_string(sno);
                    z = "[id " + y + "]";
                    vect[idp]=z;
                }

                idp+=2;
                for(int j=idp; j<vlen; j++)
                {
                    s2 = vect[j];
                    c7 = s2[1];
                    if(c7 == '{')
                    {
                        b1++;
                    }
                    if(c7 == '}' )
                    {
                        b1--;
                        if(b1==0)
                        {
                            break;
                        }
                    }
                    idpo = idpos[i+1];
                    if(idpo==j)
                    {
                        aftr_id = vect[idpo+1];
                        aftr_id = clrOthers(aftr_id);

                        bfr_id = vect[idpo-1];
                        bfr_id= clrOthers(bfr_id);
                        chk=duplicate(bfr_id);

                        if(aftr_id=="(")
                        {
                            if(chk==0)
                            {
                                bfridnm = vect[idpo];
                                idname=clrID(bfridnm);
                                y = lookupp(idname, "Global", symbls);
                                z = "[id " + y + "]";
                                vect[idpo]=z;
                            }
                        }
                        else
                        {
                            i++;
                            idp=idpos[i];
                            bfridnm = vect[idp];
                            idname=clrID(bfridnm);

                            if(chk==1)
                            {
                                localsno.push_back(sno);
                                inserrt(idname,"var",bfr_id,scp, symbls);

                                y = to_string(sno);
                                z = "[id " + y + "]";
                                vect[idp]=z;
                            }
                            if(chk==0)
                            {
                                y = lookupp(idname, scp, symbls);
                                z = "[id " + y + "]";
                                vect[idp]=z;
                            }

                            dgt = idpo+2;
                            ck_dgt = chkdigit(dgt, vnum);
                            if(ck_dgt==1)
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
                                d= vect[dgt];
                                d=clrOthers(d);
                                symbls[sp].value = d ;
                            }
                        }
                    }
                }
            }
            else
            {
                idname=clrID(bfridnm);
                if(chk==1)
                {
                    globalsno.push_back(sno);
                    inserrt(idname,"var",bfr_id,"Global", symbls);
                    y = to_string(sno);
                    z = "[id " + y + "]";
                    vect[idp]= z ;
                }
                if(chk==0)
                {
                    y = lookupp(idname, scp, symbls);
                    z = "[id " + y + "]";
                    vect[idp]=z;
                }
                dgt = idp+2;
                ck_dgt = chkdigit(dgt, vnum);
                if(ck_dgt==1)
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
                    d= vect[dgt];
                    d=clrOthers(d);
                    symbls[sp].value = d ;
                }
            }
        }

        cout << endl;
        cout << "Step 2: \n";
        display(symbls);

        cout << endl;
        cout << "Step 4: \n";

        s.clear();
        for(int i=0; i<vlen; i++)
        {
            string s0=vect[i];
            s=s+s0;
        }

        outfile << s;
        outfile.close();
        cout<< s << "\n";
    }
    else
        cout << "File2 can't be open";
    return 0;
}
