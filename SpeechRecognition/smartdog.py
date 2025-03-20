import serial  
import speech_recognition as sr

#for index, name in enumerate(sr.Microphone.list_microphone_names()):
#    print("Microphone with name \"{1}\" found for 'Microhone(device_index={0})'".format(index, name))

#sudo python3 -m speech_recognition
#Set minimum energy threshold to 1000.0237125219328

ser = serial.Serial ("/dev/ttyACM0", 9600)

recognizer = sr.Recognizer()

#recognizer.energy_threshold = 1001
#recognizer.dynamic_energy_threshold = True

mic = sr.Microphone()
speechData = ""

def speech_recognition():
    global speechData #for modifying global varaibles in the function
    
    while True:
        with mic as source:
            
            #recognizer.adjust_for_ambient_noise(source, duration=0.5)
            audio = recognizer.listen(source)
        
        try:
            speechData = recognizer.recognize_google(audio)
            
        except sr.UnknownValueError:
            speechData = "Did not understand... Repeat please!"
            
        finally:
            print(speechData)
            ser.write(bytes(speechData, 'utf-8'))

    
print("I am listening...")
speech_recognition()
