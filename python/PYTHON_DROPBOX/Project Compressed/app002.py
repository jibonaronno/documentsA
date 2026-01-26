from flask import Flask, render_template, json, request
from flaskext.mysql import MySQL
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)

mysql = MySQL()
mysql.init_app(app)
app.config['MYSQL_DATABASE_USER'] = 'root'
app.config['MYSQL_DATABASE_PASSWORD'] = 'redhat07'
app.config['MYSQL_DATABASE_DB'] = 'bucketlist'
app.config['MYSQL_DATABASE_HOST'] = 'localhost'

@app.route('/main')
def main2():
	return render_template('index002.html')

@app.route('/')
def main():
	return render_template('index002.html')

@app.route('/showSignUp')
def showSignUp():
	return render_template('signup.html')

@app.route('/signUp', methods=['POST'])
def signUp():
	# Read the post values
	_name = request.form['inputName']
	_email = request.form['inputEmail']
	_password = request.form['inputPassword']
	
	# Validate the recieved values
	if _name and _email and _password:
		conn = mysql.get_db() #mysql.connect()
		cursor = conn.cursor()
		_hashed_password = generate_password_hash(_password)
		cursor.callproc('sp_createUser',(_name,_email,_hashed_password))
		data = cursor.fetchall()

		if len(data) is 0:
			conn.commit()
			return json.dumps({'message':'User Created Succesfully'})
		else:
			return json.dumps({'error':'Could Not Create User'})

		#return json.dumps({'html':'<span>All fields good</span>'})
	else:
		return json.dumps({'html':'<span>Enter Required Fields</span>'})

if __name__ == '__main__':
	app.run(host='192.168.88.10')
