import requests
import tkinter as tk
import time

Planets = ["Sun", "Moon", "Mercury", "Venus", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"]

def fetch_data():
    # API endpoint URL
    url = "https://api.visibleplanets.dev/v3?latitude=7.4818&longitude=80.3609&showCoords=true&aboveHorizon=false"

    # Sending a GET request to the API
    response = requests.get(url)

    # Checking if the request was successful (status code 200)
    if response.status_code == 200:
        # Parsing JSON response
        json_data = response.json()

        planet_data = []
        for i in range(0, 10):
            RA = str(json_data['data'][i]['rightAscension']['hours']) + " h" + " " + str(
                json_data['data'][i]['rightAscension']['minutes']) + " m" + " " + str(
                json_data['data'][i]['rightAscension']['seconds']) + " s"
            D = str(json_data['data'][i]['declination']['degrees']) + " deg" + " " + str(
                json_data['data'][i]['declination']['arcminutes']) + " am" + " " + str(
                json_data['data'][i]['declination']['arcseconds']) + " as"
            planet_data.append(f"{Planets[i]:<15} : RA = {RA:<20} : {D}")
        
        return planet_data
    else:
        return ["Failed to fetch data from the API"]


def update_data():
    data = fetch_data()
    text_area.delete(1.0, tk.END)  # Clear previous text
    for item in data:
        text_area.insert(tk.END, item + "\n")
    text_area.insert(tk.END, "---------------------------------------------------------update in 3 seconds\n")
    root.after(3000, update_data)  # Update every 3 seconds


# Creating the GUI window
root = tk.Tk()
root.title("Visible Planets Information")

# Text area to display the planet data
text_area = tk.Text(root, height=15, width=50, font="Arial 14")
text_area.pack()

# Start updating the data
update_data()

root.mainloop()
