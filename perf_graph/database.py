import sqlite3

conn = sqlite3.connect('metrics.db')
print("Opened database successfully")
c = conn.cursor()
c.execute('''CREATE TABLE IF NOT EXISTS performance 
(id INTEGER PRIMARY KEY AUTOINCREMENT ,
 DATA TEXT NOT NULL,
 DATATYPE TEXT NOT NULL,
 KEY TEXT,
 TIMESTAMP INT NOT NULL);''')
# c.execute('''Drop table performance''')
print("Table created successfully")
conn.commit()
conn.close()
