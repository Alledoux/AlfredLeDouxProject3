import sqlite3
conn = sqlite3.connect("drugs.db")
c = conn.cursor()
c.execute(''' CREATE TABLE IF NOT EXISTS DRUGS(
    id TEXT NOT NULL,
    drugName TEXT PRIMARY KEY,
    condition TEXT NOT NULL,
    review TEXT NOT NULL,
    rating TEXT NOT NULL,
    date TEXT NOT NULL,
    usefulcount TEXT NOT NULL)
''')
conn.commit()
def insertDrugData(filepath):
    conn = sqlite3.connect("drugs.db")
    c = conn.cursor()

    with open(filepath,'r',encoding='utf-8') as file:
        for line in file:
            columns = line.strip().split('\t')
            if len(columns) == 7:
                id, drugName, condition, review, rating, date, usefulCount = columns
                c.execute(''' INSERT OR REPLACE INTO Drugs (id,drugName,condition,review,rating,date,usefulcount)
                VALUES (?,?,?,?,?,?,?)''',
                          (id,drugName,condition,review,rating,date,usefulCount))
    conn.commit()
    conn.close()
insertDrugData('drugsComTest_raw.tsv')
def searchDrug(drugName):
    conn = sqlite3.connect("drugs.db")
    c = conn.cursor()
    c.execute('SELECT * FROM Drugs WHERE drugName = ?', (drugName,))
    result = c.fetchone()
    if result:
        print(f"Drug Name: {result[1]}")
        print(f"Condition: {result[2]}")
        print(f"Review: {result[3]}")
        print(f"Rating: {result[4]}")
        print(f"Date: {result[5]}")
        print(f"Useful Count: {result[6]}")
    else:
        print("Drug not found.")
    conn.close()
if __name__ == '__main__':
    while True:
        drug_name = input("Enter a drug name to search, or type exit to stop): ")
        if drug_name.lower() == 'exit':
            break
        searchDrug(drug_name)


#https://realpython.com/read-write-files-python/
#https://www.sqlitetutorial.net/sqlite-python/insert/
#https://www.geeksforgeeks.org/python-sqlite/
#https://docs.python.org/3/library/sqlite3.html
