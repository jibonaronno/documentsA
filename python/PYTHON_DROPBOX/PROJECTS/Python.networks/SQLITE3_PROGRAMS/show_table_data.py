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


def show_table():
    try:
        db = sqlite3.connect("/home/database/txrx.db")
        cursor = db.cursor()
        cursor.execute(''' SELECT serno, devid, tdate, ttime, tdata from incoming_data ''')

        one_row = []
        for i in range(7):
            if (one_row <> None):
                one_row = cursor.fetchone()
                print one_row

    except Exception as e:
        print e


show_table()
