#include<iostream>
#include<fstream>
using namespace std;

struct parsedObj
{
    int size;
    string item[10000];
    parsedObj() {size = 0;}
};

parsedObj parse(string, const string&);

int main()
{
    string fname;
    cout<<"Input XML file: ";
    cin>>fname;
    ifstream fin(fname.c_str());
    fin>>noskipws;
    unsigned char c;
    string XML("");
    while (fin>>c)
        XML += c;


    //parsedObj test = parse("/SYFTRTE_REP/LIST_G_SGBSTDN/G_SGBSTDN/LIST_G_SFRSTCR_PIDM/G_SFRSTCR_PIDM/LIST_G_SFRSTCR_DETAIL/G_SFRSTCR_DETAIL/SFRSTCR_COURSE_TITLE/", XML);
    //parsedObj test = parse("/SYFTRTE_REP/LIST_G_SGBSTDN/G_SGBSTDN/LIST_G_SFRSTCR_PIDM/G_SFRSTCR_PIDM/LIST_G_SFRSTCR_DETAIL/G_SFRSTCR_DETAIL/", XML);
    string query;
    cout<<"Enter your xPath Query: ";
        cin>>query;
    while (query != "-1")
    {
        parsedObj test = parse(query, XML);
        for (int i = 0; i < test.size; i++)
            cout<<test.item[i]<<endl;
        cout<<"Enter your xPath Query: ";
        cin>>query;
    }

}


parsedObj parse(string s, const string &XML)
{
    parsedObj obj;
    string S;
    bool any = 0;
    if (s[0] == '/' && s[1] == '/')
    {
        any = 1;
        s = s.substr(2);
    }
    else if (s[0] == '/')
    {
        s = s.substr(1);
    }
    while (s[s.length()-1] == '/')
    {
        s = s.substr(0, s.length()-1);
    }
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != '/')
            S += s[i];
        else
        {
            //s = s.substr(S.length()+1, s.length() - S.length() -1);
            s = s.substr(S.length(), s.length() - S.length());
            break;
        }
    }

    cout<<"s is: "<<s<<endl<<"S is: "<<S<<endl;
    string S2 = "</" + S + '>';
    S = '<' + S + '>';

    string parsed("");
    for (int i = 0; i < XML.length(); i++)
    {
        if (XML.substr(i, 2) == "<?")
        {
            i += 1;
            continue;
        }
        if (XML.substr(i, 4) == "<!--")
        {
            i+=3;
            continue;
        }
        string now("");
        if (XML[i] == '<')
        {
            while(XML[i] != '>')
            {
                now += XML[i++];
            }
            now += '>';
            //cout<<"Now: "<<now<<endl<<"S: "<<S<<endl;
            if (now == S) ///Found my parse
            {
                //cout<<"Found"<<endl;
                i++;
                while(XML.substr(i, S2.length()) != S2)
                {
                    while(parsed[0] == ' ' || parsed[0] == '\t' || parsed[0] == '\n' || parsed[0] == '\r')
                        parsed = parsed.substr(1);
                    parsed += XML[i++];
                }
                if ('<' + s + '>' != S)
                {
                    obj = parse(s, parsed);
                }
                else
                {
                    while(parsed[0] == ' ' || parsed[0] == '\t' || parsed[0] == '\n' || parsed[0] == '\r')
                        parsed = parsed.substr(1);
                    obj.item[obj.size++] = parsed;
                    parsed = "";
                }
            }
            else if (!any)
            {
                while(XML.substr(i, now.length()+1) != "</" + now.substr(1))
                    i++;
                //cout<<"XML: "<<XML.substr(i, now.length()+1)<<endl;
                //cout<<"Now: "<<"</" + now.substr(1)<<endl;
            }
        }


    }

    return obj;
}
