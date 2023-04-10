import json
import requests
from dotenv import dotenv_values
import csv
import requests
import pandas as pd
from pathlib import Path
from dotenv import dotenv_values
env_path = Path(__file__).parent / ".\\.env"
config = dotenv_values(str(env_path))
GITHUB_TOKEN = config["GITHUB_TOKEN"]
headers = {"Authorization": ("Bearer " + GITHUB_TOKEN)}

def writeToFile(repo,path):
    df = pd.json_normalize(repo)
    df.to_csv(path,encoding='utf-8', index=False)

def writeIntoCsv(repo,path):
    jsonArray = []
    with open(path, encoding='utf-8') as csvf: 
        csvReader = csv.DictReader(csvf)
        for row in csvReader: 
            jsonArray.append(row)
        jsonArray.append(repo)
        writeToFile(jsonArray,path)
    
def getPrsFromRepo(repo):
    print("Analisando: "+repo["url"])
    split = repo['url'].split("/")
    owner = split[3]
    name = split[4]
    page = 1
    prs = []
    havePages = True
    while havePages:
        url = "https://api.github.com/repos/%s/%s/pulls?state=all&page=%s"%(owner, name, page)
        try:
            request = requests.get(url,headers = headers)
            if request.status_code == 200:
                    responses = (request.json())
                    if(len(responses)>0):
                        data = checkRules(responses)
                        if(len(data)>0):
                            prs.append(data)
                        page+=1
                    else:
                        havePages=False
            else:
                return
        except:
            print("Erro ao Procurar")
            return
    if(len(prs)>=100):
        writeIntoCsv(repo,'dados.csv')
    else:
        writeIntoCsv(repo,'jaFoiENaoDeu.csv')
    return prs
    
def getData():
    jsonArray = []
    with open('dados.csv', encoding='utf-8') as csvf: 
        csvReader = csv.DictReader(csvf)
        for row in csvReader: 
            jsonArray.append(row)
    return jsonArray

def getAll():
    repos = getData()
    for repo in repos:
        getPrsFromRepo(repo)

def checkRules(prs):
    dados = []
    for pr in prs:
        if(pr["merged_at"]!=None or pr["closed_at"]!=None):
            dados.append(pr)
    if(len(dados)<=0):
        return []
    dados2 = []
    for dado in dados:
        if(compareHours(dado["created_at"][11:19],dado["closed_at"][11:19])):
            dados2.append(dado)
    if(len(dados2)<=0):
        return []
    dados3 = []
    for dado in dados2:
        if(len(dado["requested_reviewers"])>0):
            dados3.append(dado)
    if(len(dados3)<=0):
        return []
    return dados3

def compareHours(data1,data2):
    isBigger = False
    if((int(data2.split(":")[0])-int(data1.split(":")[0]))>1):
        isBigger = True
    elif((int(data2.split(":")[0])-int(data1.split(":")[0]))==1):
        if((int(data2.split(":")[1])-int(data1.split(":")[1]))>0):
            isBigger = True
    return isBigger

getAll()
