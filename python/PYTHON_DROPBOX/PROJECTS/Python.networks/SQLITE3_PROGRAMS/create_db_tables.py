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


def create_table():
    try:
        db = sqlite3.connect("/home/database/txrx.db")
        cursor = db.cursor()
        cursor.execute(
            ''' CREATE TABLE IF NOT EXISTS incoming_data(serno INTEGER, devid TEXT, tdate TEXT, ttime TEXT, tdata TEXT) ''')
        db.commit()
    except Exception as e:
        print e


# create_db()

create_table()
