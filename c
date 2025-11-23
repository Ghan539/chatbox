import speech_recognition as sr
import pyttsx3
import pywhatkit
import webbrowser
import os
import matplotlib.pyplot as plt
import datetime

engine = pyttsx3.init()
voices = engine.getProperty('voices')
engine.setProperty('rate', 170) # Speed of speech
# Initialize the speech recognizer
listener = sr.Recognizer()

def speak(text):
    """Converts text to audible speech."""
    print(f"Assistant: {text}")
    engine.say(text)
    engine.runAndWait()

def take_command():
    """Listens to the microphone and returns the text command."""
    command = ""
    try:
        with sr.Microphone() as source:
            print("Listening...")
            # Adjust for ambient noise to improve accuracy
            listener.adjust_for_ambient_noise(source) 
            voice = listener.listen(source)
            command = listener.recognize_google(voice)
            command = command.lower()
            print(f"User said: {command}")
    except sr.UnknownValueError:
        pass # Don't speak errors, just return empty to loop again
    except sr.RequestError:
        speak("Sorry, my speech service is down.")
    except Exception as e:
        print(f"Error: {e}")
    
    return command

def generate_chart():
    """Uses matplotlib to create a dummy chart."""
    speak("Generating a sales performance chart for you.")
    
    # Data
    months = ['Jan', 'Feb', 'Mar', 'Apr', 'May']
    sales = [1500, 2300, 1800, 3200, 2900]

    # Plotting
    plt.figure(figsize=(8, 5))
    plt.bar(months, sales, color='teal')
    plt.title('Monthly Sales Data (Voice Generated)')
    plt.xlabel('Month')
    plt.ylabel('Sales ($)')
    plt.grid(axis='y', linestyle='--', alpha=0.7)
    
    # Show the plot
    plt.show()
    speak("Here is the chart.")

def wish_me():
    """Greets the user based on the time of day."""
    hour = int(datetime.datetime.now().hour)
    if hour >= 0 and hour < 12:
        speak("Good Morning!")
    elif hour >= 12 and hour < 18:
        speak("Good Afternoon!")
    else:
        speak("Good Evening!")
    speak("I am your Python Assistant. How can I help you today?")

def run_assistant():
    """Main execution logic."""
    wish_me()
    
    while True:
        command = take_command()

        if 'play' in command:
            song = command.replace('play', '').strip()
            speak(f"Playing {song} on YouTube")
            pywhatkit.playonyt(song)

        elif 'time' in command:
            time = datetime.datetime.now().strftime('%I:%M %p')
            speak(f"The current time is {time}")

        elif 'search' in command:
            # Example: "Search Python tutorials"
            query = command.replace('search', '').strip()
            speak(f"Searching Google for {query}")
            webbrowser.open(f"https://www.google.com/search?q={query}")

        elif 'chart' in command or 'graph' in command or 'plot' in command:
            # Uses matplotlib
            generate_chart()

        elif 'notepad' in command or 'editor' in command:
            # Uses OS module to open a system app
            speak("Opening Notepad...")
            # Note: 'notepad' works on Windows. On Mac/Linux change to 'open -a TextEdit' or 'gedit'
            os.system('notepad') 

        elif 'exit' in command or 'stop' in command or 'quit' in command:
            speak("Goodbye! Have a nice day.")
            break
            
        elif command: # If command is not empty but not recognized
            speak("I'm not sure how to help with that yet.")

if __name__ == "__main__":
    run_assistant()
