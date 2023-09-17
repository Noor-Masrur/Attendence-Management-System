#include<bits/stdc++.h>

using namespace std;

string identity;
bool entry(string s)
{
    s=s+"txt";
    fstream fin;
    fin.open(s.c_str(), ios:: in);
    string pass,pass2;
    string id,id2;
a:
    {
        cout<<"\nEnter ID: ";
        cin>>id;
        cout<<"\nEnter password: ";
        cin>>pass;
        while(!fin.eof())
        {
            fin>>id2>>pass2;
            if(id==id2)
            {
                if(pass==pass2)
                {
                    identity=id;
                    fin.close();
                    return true;
                }
                else
                {
                    cout<<"Invalid username or password";
                    goto a;
                }
            }
        }
    }


}



class student
{
protected:
    string roll;
    float percent;
public:
    student()
    {
        roll="";
    }
    student(string r)
    {
        roll=r;
    }
    virtual void show_percentage(string subject)
    {
        fstream f1,f2;
        int cls,pre;
        string ex=".txt",r;
        f1.open((subject+ex).c_str(),ios::in | ios::out | ios:: app);
        while(!f1.eof())
        {
            f1>>r>>pre>>cls;
            if(r==roll)
            {
                cout<<"Attendence: "<<(double)pre/cls*100.0<<'%'<<endl;
            }
        }
    }
    void show_needed_percentage(string subject)
    {
        fstream f1,f2;
        int cls,pre;
        string ex=".txt",r;
        f1.open((subject+ex).c_str(),ios::in | ios::out | ios:: app);
        while(!f1.eof())
        {
            f1>>r>>pre>>cls;
            if(r==roll)
            {
                if(pre>12)
                    cout<<"Completed attendence"<<endl;
                else
                    cout<<"Needed "<<12-pre<<" classes to complete attendence"<<endl;
            }
        }

    }
};


class teacher : public student
{
protected:
    string subject;
    int att;
    int cls_no;

public:
    teacher()
    {
        subject="";
    }
    teacher(string sub)
    {
        subject=sub;
    }

    void attendence()
    {
        fstream f1,f2;
        string ex=".txt",r;
        f1.open((subject+ex).c_str(),ios::in | ios::out | ios:: app);
        f2.open("new.txt", ios::out | ios:: app);
        int x=0,arr[6]= {0};
        cout<<"If present,press 1\nIf absent,press 0\n";
        for(int i=1; i<=5; i++)
        {
            f1>>roll>>att>>cls_no;
            cout<<r<<" : ";
            cin>>x;

            if(x)
                arr[i]++;
            f2<<r<<" "<<att+arr[i]<<" "<<cls_no+1<<endl;

        }
        remove((subject+ex).c_str());
        rename("new.txt",(subject+ex).c_str());
        f2.close();
        f1.close();



    }
    void show_percentage(string s)
    {
        fstream f1,f2;
        int cls,pre;
        string ex=".txt",r;
        f1.open((subject+ex).c_str(),ios::in | ios::out | ios:: app);
        while(!f1.eof())
        {
            f1>>r>>pre>>cls;
            cout<<"Attendence of roll "<<r<<": "<<(double)pre/cls*100.0<<'%'<<endl;

        }
    }
    bool operator>(student s1,student s2)
    {
        fstream f1,f2;
        int cls,pre;
        double a1,a2;
        string ex=".txt",r;
        f1.open((subject+ex).c_str(),ios::in | ios::out | ios:: app);
        while(!f1.eof())
        {
            f1>>r>>pre>>cls;
            if(r==s1.roll)
            {
                //cout<<"Attendence: "<<(double)pre/cls*100.0<<'%'<<endl;
                a1=(double)pre/cls*100.0;
            }
            if(r==s2.roll)
            {
                a2=(double)pre/cls*100.0;
            }
        }
        f1.close();
        if(a1>a2)
            return true;
        else return false;

    };


    class controller : public teacher
    {
    public:
        void special_case()
        {
            int plus;
            string r3,pre3,cls3;
            cout<<"Enter roll and  subject "<<endl;
            cin>>roll>>subject;
            subject=subject+".txt";
            fstream fin,fin2;
            fin.open(subject.c_str(), ios:: in | ios:: out | ios:: app);
            fin2.open("new2.txt", ios:: in | ios:: out | ios:: app);
            cout<<"Enter applied attendence: ";
            cin>>plus;
            while(!fin.eof())
            {
                fin>>r3>>pre3>>cls3;
                if(r3==roll)
                    fin2<<r3<<" "<<pre3+plus<<" "<<cls3<<endl;
                else
                    fin2<<r3<<" "<<pre3<<" "<<cls3<<endl;

            }

        }
        void incomplete()
        {
            fstream f1,f2;
            int cls,pre;
            string ex=".txt",r;
            cout<<"\nEnter subject:";
            cin>>subject;
            f1.open((subject+ex).c_str(),ios::in | ios::out | ios:: app);
            while(!f1.eof())
            {
                f1>>r>>pre>>cls;
                //cout<<"Attendence of roll "<<roll<<": "<<(double)pre/cls*100.0<<'%'<<endl;
                if(((double)pre/cls*100.0)>=60.0)
                    cout<<"Verdict of roll "<<r<<"is completed"<<endl;
                else
                    cout<<"Verdict of roll "<<r<<"is incompleted"<<endl;


            }

        }


    };






    int main()
    {
        cout<<"\t\t\t\t\tWelcome to attendence management sysytem\n\n\n\n"<<endl;
        cout<<"1.Student\n2.Teacher\n3.Controller\n";
        int x;
        cin>>x;
        student *bptr;
        string subj,blank;
        if(x==1 && entry("student"))
        {
            student stud(identity);
            string subb;
            cout<<"1.Show attendence\n2.Show required attendence\n";
            cin>>x;
            if(x==1)
            {

                cout<<"\nEnter course name : ";
                cin>>subb;
                bptr=&stud;
                bptr->show_percentage(subb);

            }
            else
            {
                cout<<"\nEnter course name : ";
                cin>>subb;
                bptr=&stud;
                // bptr->show_percentage(subb);
                bptr->show_needed_percentage(subb);
            }
        }
        else if(x==2 && entry("teacher"))
        {
            teacher tech(identity);
            bptr=&tech;
            cout<<"1.Show attendence\n2.Take Attendence\n3.Compare attendence\n";
            cin>>x;
            if(x==1)
            {
                bptr->show_percentage("");
            }
            else
            {
                tech.attendence();
            }



        }
        else if(x==3 && entry("controller"))
        {
            controller cntr;
            teacher t;
            cout<<"1.Applied Attendence Update\n2.Show results\n3.Compare attendence\n";
            cin>>x;
            if(x==1)
            {
                cntr.special_case();
            }
            else if(x==2)
            {
                cntr.incomplete();
            }


        }
    }
