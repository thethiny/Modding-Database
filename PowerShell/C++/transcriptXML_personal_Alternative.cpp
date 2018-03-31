#include<iostream>
#include<fstream>
#include<cmath>
#include<windows.h>
using namespace std;

struct parsedObj
{
    int size;
    string item[100];
    parsedObj() {size = 0;}
    bool operator<(parsedObj);
};

int to_int(string a)
{
    int sum = 0;
    for (int i = 0; i < a.length(); i++)
    {
        sum += (a[a.length()-1-i] - '0') * pow(10, i);
    }
    return sum;
}

parsedObj parse(string, string);

int main()
{
    system("title UoS Scraper v1.2");
    //system("color 80");
    system("color 3F");
    //system("color -h");
    system("MKDIR cache 2>nul");
    string command = "powershell -Command \"Invoke-WebRequest '\"https://uos.sharjah.ac.ae:9050/reports/rwservlet?server=RptSvr_uosas5_INB_asinst\"&\"userid=uos_mis/u_pick_it@PROD\"&\"desformat=xml\"&\"destype=cache\"&\"REPORT=SYFTRTE_REP.rep";
    string command2 = "powershell -Command \"Invoke-WebRequest '\"https://uos.sharjah.ac.ae:9050/reports/rwservlet?server=RptSvr_uosas5_INB_asinst\"&\"userid=uos_mis/u_pick_it@PROD\"&\"desformat=xml\"&\"destype=cache\"&\"REPORT=syrexdt_rep.rep\"&\"p_obj_inst_name=UNIVERSITY OF SHARJAH\"&\"p_obj_dept=ADMISSION DEPARTMENT\"&\"p_obj_title=Personal Information Summary\"&\"p_obj_form_name=SYFEXDT/SYREXDT_REP\"&\"p_obj_footer=\"&\"paramform=no\"&\"ENVID=UOSE";
    string ID, XML, XML2;
    ifstream fin, fin2;
    unsigned char c;
    cout<<"Enter your UOS ID: ";
    cin>>ID;
    if (ID[0] == 'u')
        ID[0] = 'U';
    fin.open(("Cache\\" + ID+"_transcript.xml").c_str());
    if (fin.good())
    {
        fin.close();
        char c;
        cout<<"File already exists, would you like to update your transcript from the server (Y/N): ";
        cin>>c;
        if (c == 'Y' || c == 'y')
        {
            system(("Del /A Cache\\" + ID+"_transcript.xml 2>nul").c_str());
            system((command + "\"&\"P_ID=" + ID + "'\" -OutFile Cache\\" + ID + "_transcript.xml\"").c_str());
            system(("Del /A Cache\\" + ID+"_personal.xml 2>nul").c_str());
            system((command2 + "\"&\"P_SPRIDEN_ID=" + ID + "'\" -OutFile Cache\\" + ID + "_personal.xml\"").c_str());
        }

    }
    else
    {
        system((command + "\"&\"P_ID=" + ID + "'\" -OutFile Cache\\" + ID + "_transcript.xml\"").c_str());
        system((command2 + "\"&\"P_SPRIDEN_ID=" + ID + "'\" -OutFile Cache\\" + ID + "_personal.xml\"").c_str());
    }
    system("cls");
    fin.open(("Cache\\" + ID+"_transcript.xml").c_str());
    fin>>noskipws;
    fin2.open(("Cache\\" + ID+"_personal.xml").c_str());
    fin2>>noskipws;
    if (fin.good())
    {
        while(fin>>c)
            XML += c;
        while(fin2>>c)
            XML2 += c;
        parsedObj name, enrolled, BD, GPA, major, hours, standing, activeSem;
        parsedObj phone, UAE_ID, nation, sgrade, cert, school, birthP;
        phone = parse("PHONE", XML2);
        UAE_ID = parse("ID_NUMBER", XML2);
        nation = parse("ENATN", XML2);
        sgrade = parse("CERT_PERCNTG", XML2);
        cert = parse("SCHOOL_CERT", XML2);
        school = parse("SCHOOL", XML2);
        birthP = parse("CITY_OF_BIRTH", XML2);
        name = parse("STUDENT_NAME", XML);
        enrolled = parse("FIRST_TERM_ADMIT_DESC", XML);
        BD = parse("SPBPERS_BIRTH_DATE", XML);
        GPA = parse("SYRTGPA_LGPA", XML);
        major = parse("PROG_TITLE", XML);
        hours = parse("SYRTGPA_LGPA_HOURS", XML);
        standing = parse("TERM_ASTD_DESC1", XML);
        activeSem = parse("SFRSTCR_TERM_CODE_DESC", XML);
        parsedObj testN = parse("CF_TESC_DESC", XML);
        parsedObj testS = parse("SORTEST_TEST_SCORE", XML);
        parsedObj testD = parse("SORTEST_TEST_DATE", XML);
        parsedObj livCity = parse("SPRADDR_CITY", XML);
        parsedObj livCountry = parse("NATN_DESC", XML);
        if (!name.size)
        {
            cerr<<"Invalid ID!";
            return 2;
        }
        cout<<"========Personal Info========\n";
        cout<<"Name: "<<name.item[0].substr(1)<<endl;
        cout<<"ID: U"<<ID.substr(1)<<endl;
        cout<<"UAE ID: "<<UAE_ID.item[0]<<endl;
        cout<<"Nationality: "<<nation.item[0]<<endl;
        cout<<"Birth Date: "<<BD.item[0]<<endl;
        cout<<"Born in: "<<birthP.item[0]<<endl;
        cout<<"Home Address: "<<livCity.item[0]<<", "<<livCountry.item[0]<<endl;
        cout<<"Phone Number(s): "<<phone.item[0]<<endl;
        cout<<"School Name: "<<school.item[0]<<endl;
        cout<<"Grade: "<<sgrade.item[0]<<"%"<<endl;
        cout<<"Certificate Type: "<<cert.item[0]<<endl;
        cout<<"Enroll Date: "<<enrolled.item[0]<<endl;
        cout<<"Major: "<<major.item[0]<<endl;
        cout<<"Credit Hours: "<<hours.item[hours.size-1]<<endl;
        cout<<"CGPA: "<<GPA.item[GPA.size-1]<<endl;
        cout<<"Rating: "<<standing.item[standing.size-1]<<endl;
        cout<<"Last Active Semester: "<<activeSem.item[0]<<endl;
        cout<<endl;
        cout<<"Would you like to obtain a detailed view (Y/N): ";
        char x;
        cin>>x;
        if (x == 'y' || x == 'Y')
        {
            cout<<"========Detailed View========\n";
            if (testN.size > 0)
            {
                cout<<"Entry Tests:\n";
                for (int i = 0; i < testN.size; i++)
                {
                    cout<<"\tTest: "<<testN.item[i]<<endl;
                    cout<<"\tScore: "<<testS.item[i]<<endl;
                    cout<<"\tDate: "<<testD.item[i]<<endl;
                    cout<<endl;
                }
            }
            parsedObj terms = parse("TERM_TERM_DESC", XML);
            parsedObj hoursPS = parse("INST_TGPA_HOURS", XML);
            parsedObj GPAPS = parse("INST_TGPA", XML);
            parsedObj coursePS = parse("COURSE_TITLE", XML);
            parsedObj gradePC = parse("GRDE_CODE_FINAL", XML);
            parsedObj hoursPC = parse("CREDIT_HOURS", XML);
            parsedObj CRN = parse("CRN_KEY", XML);
            parsedObj CRNN = parse("CRSE_NUMBER", XML);
            parsedObj CRNS = parse("SUBJ_CODE", XML);
            parsedObj CGPAPS = parse("INST_GPA", XML);
            parsedObj section = parse("SEQ_NUMB", XML);
            parsedObj seq = parse("CS_TERM_CRSE_SEQ", XML);

            int courses = 0;
            for (int i = 0; i < terms.size; i++)
            {
                cout<<"Semester "<<terms.item[i]<<endl;
                int sum = 0;
                int last = 0, cur = 1;
                while(cur > last && courses < coursePS.size)
                {
                    cout<<"\tCourse: "<<coursePS.item[courses]<<endl;
                    cout<<"\t\tCourse ID: "<<CRNS.item[courses].substr(0, CRNS.item[courses].length()-CRNN.item[courses].length())<<" "<<CRNN.item[courses]<<endl;
                    cout<<"\t\tCRN: "<<CRN.item[courses]<<endl;
                    //cout<<"\t\tSection: "<<section.item[courses]<<endl;
                    cout<<"\t\tCH: "<<hoursPC.item[courses]<<endl;
                    cout<<"\tGrade: "<<gradePC.item[courses]<<endl;
                    //cout<<"SUQENCE: "<<seq.item[courses]<<endl;
                    //cout<<"CUR: "<<cur<<"\tLAST: "<<last<<endl;
                    cout<<endl;
                    //sum += to_int(hoursPC.item[courses]);
                    courses++;
                    last = cur;
                    cur = to_int(seq.item[courses]);

                }
                cout<<"Total CH: "<<hoursPS.item[i]<<endl;
                cout<<"GPA: "<<GPAPS.item[i]<<endl;
                cout<<"CGPA: "<<CGPAPS.item[i]<<endl;
                cout<<endl;

            }

            if (activeSem.item[0] != terms.item[terms.size-1] && activeSem.item[0] != "")
            {
                parsedObj course = parse("SFRSTCR_COURSE_TITLE", XML);
                parsedObj courseCH = parse("SFRSTCR_CREDIT_HR", XML);
                parsedObj CRN = parse("SFRSTCR_CRN", XML);
                parsedObj CRNS = parse("SSBSECT_SUBJ_CODE", XML);
                parsedObj CRNN = parse("SSBSECT_CRSE_NUMB", XML);
                parsedObj section = parse("SSBSECT_SEQ_NUMB", XML);

                cout<<"Current Semester "<<activeSem.item[0]<<endl;
                for (int i = 0; i < course.size; i++)
                {
                    cout<<"\tCourse: "<<course.item[i].substr(2)<<endl;
                    cout<<"\t\tCourse ID: "<<CRNS.item[i]<<" "<<CRNN.item[i]<<endl;
                    cout<<"\t\tCRN: "<<CRN.item[i]<<endl;
                    cout<<"\t\tSection: "<<section.item[i]<<endl;
                    cout<<"\t\tCH: "<<courseCH.item[i]<<endl;
                    cout<<endl;
                }
                cout<<"CGPA: "<<CGPAPS.item[terms.size-1]<<endl;
                cout<<endl;

            }
        }



    }
    else
    {
        cerr<<"Couldn't obtain storage permission!";
        return 1;
    }

    system("pause");

}

parsedObj parse(string s, string XML)
{
    parsedObj obj;
    s = '<' + s + '>';

    for (int i = 0; i < XML.length() - s.length(); i++)
    {
        bool b = 1;
        for (int j = 0; j < s.length(); j++, i++)
        {
            if (s[j] != XML[i])
            {
                b = 0;
                break;
            }
        }

        if (b)
        {
            string parsed("");
            while(XML[i] != '<')
            {
                parsed += XML[i++];
            }
                if (parsed.find("&amp;") != string::npos)
                    parsed.replace(parsed.find("&amp;"), 5, "&");

            obj.item[obj.size++] = parsed;
        }


    }
    return obj;
}
