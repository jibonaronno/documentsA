from flask import Flask

app = Flask(__name__)

@app.route('/')

def main():
	return 'Welcome To Flask App'

if __name__ == '__main__':
	app.run(host='192.168.0.102')
