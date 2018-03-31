import requests
from bs4 import BeautifulSoup
import os

#Function
def makeValid(s):
    string = ""
    for c in s:
        if not(c == '/' or c == '?' or c == '*' or c == '\\' or c == ':' or c == '<' or c == '>' or c == '|' or c == '\"' or c == '.' or c == ' '):
            string += c
        elif c == ' ':
            string += '-'
    return string


domain = "https://www.alarabiya.net"
#$file = Get-Content "OrgLinks.txt"
links = open("OrgLinks.txt", "r", encoding="utf-8")
ctr = 1
#lines = len(links)
#with open("OrgLinks.txt", "r", encoding="utf-8") as links:
for link in links:
    done = 0
    while done < 3:
        done += 1 #Maximum 3 Retries
        #print("===============")
        print("Link #" + str(ctr))
        #print("$ctr/$lines")
        name = "output/"
        if not os.path.exists(name):
            os.makedirs(name)
        if (link[len(link)-1] is '\n'):
            link = link[:-1]
        print("Scraping",domain+link)
        site = requests.get(domain+link).text
        site = BeautifulSoup(site, "html.parser")
        #print("Parsing...")

        category = ""
        category = site.find("ul", class_="breadcrumbs")
        if category is None:
            category = "الرئيسية/السعودية-اليوم"
            print("==WARNING: NO CATEGORY==\n==ASSUMING SAUDI TODAY==\n")
        else:
            category = category.text.replace("»", '/').replace("\n", "").replace(" ", "-")
        #print(category)

        name += category + '/'
        if not os.path.exists(name):
            os.makedirs(name)

        #print("Category\n", category)

        title = ""
        #title = site.find_elements_by_class_name("highline")
        try:
            title = (site.findAll("div", class_= "highline"))[1].text
        except IndexError:
            print("Couldn't find title!\n")
            continue
        #print("\nTitle\n",title)

        name += makeValid(title) + ".txt"
        file = open(name, "w+", encoding="utf-8")
        file.write("Title\n")
        file.write(title)

        source = ""
        #source = site.find_elements_by_class_name("source")
        try:
            source = site.find("div", class_="source").text
        except:
            print("Couldn't find source!\n")
            os.rmdir(name)
            continue

        #print("\nSource\n",source)
        file.write("\nSource\n" + source)

        file.write("\nBody")
        #print("\nBody")
        body = site.find("div", class_="article-body").text
        if body is None:
            print("Couldn't find body!\n")
            os.rmdir(name)
            continue
        #print(body)
        file.write(body)
        #print("Body Scraped into",name)
        file.close()
        done = 10
        ctr += 1
    if (done < 10):
        print("==Multipled Failed Attempts!==")
        temp = open("output/log.txt", "a+", encoding="utf-8")
        temp.write(domain+link)
        temp.close()
print("Finished")
links.close()