from flask import Flask, render_template, send_file
import datetime
import time
import serial

##import atexit

#from apscheduler.scheduler import Scheduler
#defining the serial port
ser = serial.Serial( port='/dev/ttyS0',
       baudrate = 9600,
       parity=serial.PARITY_NONE,
       stopbits=serial.STOPBITS_ONE,
       bytesize=serial.EIGHTBITS,
       timeout=1
       )
#create a flask object
app = Flask(__name__)

@app.route('/jquery.js')
def getjq():
    return send_file('jquery.js')

@app.route("/")
def hello():
    templateData={
            'title': 'A B C',
            'time': 0
    }
    return render_template('index.html', **templateData)

x='0, 0, 0'
y='0, 0, 0'
y_t='0, 0, 0'
x_t='0, 0, 0'
a=0
b=0
@app.route('/data')
def data():
    global a,b,x,y,x_t,y_t
    ser.flushInput()
    ser.flush()
    ser.flushOutput()
    if x:
     x_t=x
    ser.write('a.r.?\n'.encode())
    x=ser.readline().strip()
    if x:
         a=x
    else:
         a=x_t
    if y:
     y_t=y
    ser.write('b.r.?\n'.encode())
    y=ser.readline().strip()
    if y:
         b=y
    else:
        b=y_t
    a=a.decode('ascii')
    b=b.decode('ascii')
    return str(a)+','+str(b)
@app.route('/device1_ON')
def device1_ON():
    ser.flushInput()
    ser.flush()
    ser.flushOutput()
    ser.write('a.w.1\n'.encode())
    time.sleep(0)
   
@app.route('/device1_OFF')
def device1_OFF():
    ser.flushInput()
    ser.flush()
    ser.flushOutput()
    ser.write('a.w.0\n'.encode())
    time.sleep()
    

@app.route('/device2_ON')
def device2_ON():
    ser.write('b.w.1\n'.encode())
    time.sleep(1)
    

@app.route('/device2_OFF')
def device2_OFF():
    ser.write('b.w.0\n'.encode())
    time.sleep(1)



if __name__ == "__main__":
    app.run(debug=True, host='0.0.0.0')

