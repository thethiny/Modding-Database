from selenium.webdriver import Chrome
import os

#Function
def makeValid(s):
    string = ""
    for c in s:
        if not(c == '/' or c == '?' or c == '*' or c == '\\' or c == ':' or c == '<' or c == '>' or c == '|' or c == '\"'):
            string += c
    return string


domain = "https://www.alarabiya.net"
#$file = Get-Content "OrgLinks.txt"
links = open("OrgLinks.txt", "r", encoding="utf-8")
ctr = 0
#lines = len(links)
#with open("OrgLinks.txt", "r", encoding="utf-8") as links:
for link in links:
    print("===============")
    ctr += 1
    #print("$ctr/$lines")
    name = "output/"
    if not os.path.exists(name):
        os.makedirs(name)
    print("Scraping",domain,link,"...")
    site = Chrome()
    site.get(domain + link)
    print("Parsing...")

    category = ""
    category = site.find_elements_by_class_name("breadcrumbs")
    try:
        category = ((category[0].get_attribute("innerText")).replace("»",'/')).replace("\n","")
    except IndexError:
        category = "السعودية-اليوم"
    print(category)

    name += category + '/'
    if not os.path.exists(name):
        os.makedirs(name)

    print("Category Scraped", category)

    title = ""
    title = site.find_elements_by_class_name("highline")
    try:
        title = title[0].get_attribute("textContent")
    except IndexError:
        continue
    title = makeValid(title) #Declare this later
    name += title + ".txt"
    file = open(name, "w+", encoding="utf-8")
    print("Title", title)
    file.write("Title\n")
    file.write(title)

    source = ""
    source = site.find_elements_by_class_name("source")
    try:
        source = source[0].get_attribute("textContent")
    except IndexError:
        continue
    print("Source",source)
    file.write("\nSource\n" + source)

    file.write("\nBody\n")
    for element in site.find_elements_by_class_name("article-body"):
        file.write(element.get_attribute("innerText"))
        print("Body Scraped into ",name)
    file.close()
    site.close()
print("Finished")