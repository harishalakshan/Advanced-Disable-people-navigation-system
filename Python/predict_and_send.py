
import serial
import joblib
import time

model = joblib.load('navigation_model.pkl')
arduino = serial.Serial('COM3', 9600, timeout=1)
time.sleep(2)

def predict_and_act(data):
    prediction = model.predict([data])[0]
    if prediction == 0:
        print("STOP 🚫")
        arduino.write(b'STOP\n')
    elif prediction == 1:
        print("TURN LEFT ⬅️")
        arduino.write(b'LEFT\n')
    elif prediction == 2:
        print("TURN RIGHT ➡️")
        arduino.write(b'RIGHT\n')
    elif prediction == 3:
        print("MOVE FORWARD ⬆️")
        arduino.write(b'FORWARD\n')

while True:
    try:
        line = arduino.readline().decode().strip()
        if line:
            values = list(map(int, line.split(',')))
            if len(values) == 3:
                predict_and_act(values)
    except Exception as e:
        print("Error:", e)
