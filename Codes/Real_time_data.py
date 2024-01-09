from selenium import webdriver
from selenium.webdriver.common.by import By

Planets = ["Sun", "Mercury", "Venus", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"]

# Initialize the WebDriver (you might need to specify the path to your browser driver)
driver = webdriver.Chrome()  # Change this to your preferred browser driver

# Open the webpage
driver.get("http://cosinekitty.com/solar_system.html")  # Replace with your website URL

for i in range(0, len(Planets)):
    # Find the element by its CSS selector
    RA = driver.find_element(By.CSS_SELECTOR, "#" + Planets[i] + "_RA").text
    DEC = driver.find_element(By.CSS_SELECTOR, "#" + Planets[i] + "_DEC").text

    print((Planets[i]+"            ")[0:15], "RA:", RA, "   DEC: " , DEC )

# Close the browser window
driver.quit()