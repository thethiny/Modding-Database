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


domain = "https://www.alarabiya.net/ar/"
#Skipping Saudi-Today for now
middle = {"sport", "last-page", "politics", "variety", "medicine-and-health", "technology", #sport is enough instead of all variants
          "social-media", "knowmore/smart-devices", "knowmore/phobia", "knowmore/alternative-energy",
          "knowmore/alnojoom", "knowmore/movember", "culture-and-art", "fashion-beauty", "science", "qafilah"}
last = "/archive.news.html?currentPage="
file = open("All_Links_Dir.txt", "w+", encoding="utf-8")
file.close()

for category in middle:
    #category = "qafilah"
    print(category)
    page = 1
    done = 0
    writtenPage = page-1
    while done < 3: #3 Time-Outs
        #print(category)
        print("Page:",page,"Retry:",done)
        #print(domain + category + last + str(page))
        site = requests.get(domain+category+last+str(page)).text
        site = BeautifulSoup(site, "html.parser")


        links = site.findAll("div", class_="item")
        if links is not None:
            file = open("All_Links_Dir.txt", "a+", encoding="utf-8")
            for link in links:
                hLink = link.findAll("a")
                if hLink is not None:
                    url = link.find("a")['href']
                    if url is not None and writtenPage is not page:
                        file.write(url)
                        file.write("\n")
                        #print("In\n")
                    #print(url)
            file.close()
            #done = 0
            #page += 1
        #else:
            #No more pages or timeout
            #done += 1
            #continue

        writtenPage = page

        #testing region
        footer = site.findAll("ul", class_="paging")
        found = 0
        try:
            footer = footer[0].text
            if footer.find("التالي") >= 0:
                found = 1
        except IndexError:
            print("Couldn't Find the navigation bar\n")
            #done = 3
            #continue
        #end of testing region

        if found:
            #writtenPage = page
            page += 1
            done = 0
        else:
            #No more pages or timeout
            done += 1
#file.close()