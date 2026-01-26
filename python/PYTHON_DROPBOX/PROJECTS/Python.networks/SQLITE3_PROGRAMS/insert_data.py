import sqlite3

db = None
db_connected = False


def create_db():
    try:
        db = sqlite3.connect("/home/database/txrx.db")
    except Exception as e:
        print e
    finally:
        db_created = True
        print "database created"
    if (db_created):
        db.close()


def connect_db():
    try:
        db = sqlite3.connect("/home/database/txrx.db")
    except Exception as e:
        print e
    finally:
        db_connected = True


def insert_data():
    data_arr = [('5', '3234', '11/07/2014', '03:25', r'"temp":"31","volt":"53","curr":"1","genrun":"566"'),
                ('6', '3234', '12/07/2014', '06:55', r'"temp":"29", "volt":"49", "curr":"5", "genrun":"570"')]
    try:
        db = sqlite3.connect("/home/database/txrx.db")
        cursor = db.cursor()
        cursor.executemany(''' INSERT INTO incoming_data(serno, devid, tdate, ttime, tdata) VALUES(?,?,?,?,?) ''',
                           data_arr)
        db.commit()
    except Exception as e:
        print e


insert_data()
