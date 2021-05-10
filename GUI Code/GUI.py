from tkinter import *
import time
import matplotlib.pyplot as plt
#from PIL import ImageTk, Image
import serial
from time import sleep
import csv
import datetime


# Variable declarations

global ser #Used for opening and closing serial port connections

global serial_data
serial_data = ''

global temp,light
temp = 0
light = 0.0

global dateList
dateList = []

global temp_array
temp_array = []

global light_array
light_array = []

global Counter
Counter = 0


fig,ax = plt.subplots(2,1,figsize=(15,20)) #create subplots for the data

# Function definitions

def open_connect():
    """
    Opens the serial port on the COM3 port
    """
    global ser
    ser = serial.Serial("COM3", 9600, timeout=20)

def close_connect():
    """
    Closes the serial port connection
    """
    ser.close()
    quit(window)

def quit(window):
	window.destroy()

def get_data():
    """
    Read the data that's sent over the COM3 port and format it properly
    Store the split data in the required variables
    """
    #while(1):
    try:
        global temp
        global light
        x = float(str(ser.readline(),'utf-8').strip('\r').strip('\n'))
        y = float(str(ser.readline(),'utf-8').strip('\r').strip('\n'))
        temp = max([x,y])
        light = min([x,y])
    except TypeError:
        pass

def get_date():
    today = datetime.date.today()
    return today.strftime("%d/%m/%Y")

def store_data():
    """
    Store the present date, recorded temperature, light intensity values
    """
    file = open('data.csv','a')
    writer = csv.writer(file)
    writer.writerow([get_date(),temp,light])
    file.close()

def fileget():
    """
    Read the data.csv file to get the past data
    Store the read data into separate arrays based on the type of data
    """
    file2 = open('data.csv','r')
    reader = csv.reader(file2,delimiter = ',')
    linecount = 0
    for i in reader:
        if linecount == 0:
            linecount = 1 + linecount
        elif len(i) == 0:
            linecount = 1 + linecount
        else:
            dateList.append(i[0])
            temp_array.append(i[1])
            light_array.append(i[2])
            linecount = 1 + linecount
    file2.close()


def plot_temp():
    """
    Plot a temperature vs date graph
    """
    ax[0].plot_date(dateList,temp_array,xdate=True,ydate=False,linestyle='solid',color='orange')

def plot_light():
    """
    Plot a relative lightity vs date graph
    """
    ax[1].plot_date(dateList,light_array,xdate=True,ydate=False,linestyle='solid',color='blue')

def plot():
    fileget()
    plot_temp()
    plot_light()
    plt.show()

def Weather():
    get_data()
    store_data()
    WeatherArea.config(height="3",state=NORMAL)
    WeatherArea.delete(1.0,END)
    WeatherArea.insert(1.0,"\t\tDate: "+get_date()+"\n\t\tTemperature: "+str(temp)+"oF\n\t\tLight Intensity: "+str(light)+"%")
    WeatherArea.config(state=DISABLED)

# Window initialization and configuration
global window

window = Tk()
window.title('Weather Monitoring System - Group 8')

window.resizable(False,False)

# Set the icon of the window
img = PhotoImage(file = 'Icon.png')
window.iconphoto(False,img)


# Set background image
image = PhotoImage(file = 'Back2.png')
window_label = Label(window,image=image)
window_label.place(x=0, y=0, relwidth=1, relheight=1)


# Set the button symbols

img3 = PhotoImage(file = 'Im2.png')

sym1 = Label(window, image = img3)
sym1.config(borderwidth=3,relief="solid")
sym1.place(x=500,y=50,anchor = CENTER)

sym2 = Label(window, image = img3)
sym2.config(borderwidth=3,relief="solid")
sym2.place(x=500,y=450,anchor = CENTER)

img5 = PhotoImage(file = 'Graph.png')

sym3 = Label(window, image = img5)
sym3.config(borderwidth=3,relief="solid")
sym3.place(x=520,y=350,anchor = CENTER)


# Configure the buttons

openButton = Button(window, text = 'Open Connection', command = open_connect)
openButton.config(borderwidth=5,relief="raised")
openButton.place(x=600,y=50,anchor=CENTER)

WeatherButton = Button(window, text = 'Weather', command = Weather)
WeatherButton.config(borderwidth=5,relief="raised")
WeatherButton.place(x=600,y=150,anchor=CENTER)

PlotButton = Button(window, text = 'Plot', command = plot)
PlotButton.config(borderwidth=5,relief="raised")
PlotButton.place(x=600,y=350,anchor=CENTER)

closeButton = Button(window, text = 'Close Connection', command = close_connect)
closeButton.config(borderwidth=5,relief="raised")
closeButton.place(x=600,y=450,anchor=CENTER)


# Configure the text area for displaying the data
global WeatherArea
WeatherArea = Text(window,bg="black",font="Arial",fg="white",bd="2",height="1",width="50",selectbackground="steel blue",wrap=WORD)
WeatherArea.place(x=600,y=250,anchor=CENTER)
WeatherArea.insert(1.0,"\tWelcome to the Weather Monitoring System")
WeatherArea.config(state=DISABLED)

# Set geometry of the window and initialize the application
window.geometry("1200x500")
window.mainloop()