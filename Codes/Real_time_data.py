from selenium import webdriver
from selenium.webdriver.common.by import By
import time

Planets = ["Sun", "Mercury", "Venus", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"]
Moons = ["Ceres", "Pallas", "Juno", "Vesta", "Pluto"]

Bodies = Planets + Moons

# Initialize the WebDriver (you might need to specify the path to your browser driver)
driver = webdriver.Chrome()  # Change this to your preferred browser driver

# Open the webpage
driver.get("http://cosinekitty.com/solar_system.html")  # Replace with your website URL

try:
    while True:
        for i in range(0, len(Bodies)):
            # Find the element by its CSS selector
            RA = driver.find_element(By.CSS_SELECTOR, "#" + Bodies[i] + "_RA").text
            DEC = driver.find_element(By.CSS_SELECTOR, "#" + Bodies[i] + "_DEC").text

            print((Bodies[i]+"            ")[0:15], "RA:", RA, "   DEC:", DEC)

        time.sleep(1)  # Wait for 1 second before repeating
        print("\n")
        
except KeyboardInterrupt:
    # Handle keyboard interruption (Ctrl+C) to close the browser gracefully
    driver.quit()
