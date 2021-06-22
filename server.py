from flask import Flask
from flask import render_template
from flask import request

app = Flask(__name__)

drive = 0
steer = 0

@app.route('/')
def control():
    return render_template('control.html')

@app.route('/control.js')
def code():
    return render_template('control.js')

@app.route('/input', methods=['POST'])
def get_names():
   if request.method == 'POST':
        names = request.get_json()
        steer = names['steer']
        drive = names['drive']
        # print('Steer mode: ' + str(names['steer']))
        # print('Drive mode: ' + str(names['drive']))
        return '', 200

''' while True:
        print("Input:")
        print(f"\tdrive = {drive}")
        print(f"\tsteer = {steer}") '''