<h1>Earendel Pro-Track: IoT-Based Celestial Object Tracker</h1>

<h2><a href="https://github.com/linukaratnayake">Linuka Ratnayake</a>, <a href="https://github.com/YasiruDEX">Yasiru Basnayake</a>, <a href="https://github.com/KumuthuDeZoysa">Kumuthu De Zoysa</a>, <a href="https://github.com/KavinduJ2001">Kavindu Jayathissa</a>, <a href="https://github.com/ehele">Aruna Ehelepola</a>,  <a href="">Dhanushka Weerakoon</a></h2>

  
<h2>Overview</h2>
<h3>Introduction</h3>
<p>
    "Earendel Pro-Track" is a project that aims to design a telescope mount capable of automatically locating and keeping track of stellar objects. The desired stellar object can be selected through the user interface, and once that information is transfered to the telescope mount in the form of celestial coordinates, it turns to that stellar object, and starts observing.
</p>

<h3>Features</h3>
<ul>
    <li>No need to horizontally level the telescope mount.</li>
    <li>No need to start by pointing to the direction of North or the North Star.
    <li>Integration with online databases to obtain real-time celestial locations.</li>
    <li>Mobile app interface for easy controlling for the user.</li>
    <li>IoT communication for transmitting mount orientation data.</li>
    <li>Carefully designed for smooth and accurate celestial tracking.</li>
</ul>

<h2>Research and Development</h2>

<h3>Coordinate Systems and Convertion</h3>

| **Altitude - Azimuth** | **Right Ascension - Declination** |
|:--:|:--:|
| <img src="Project%20Details%20(Documents%20and%20Media)/Images/alt_az.png" style = "width: 80%">|![Altitude Azimuth](Project%20Details%20(Documents%20and%20Media)/Images/ra_dec.gif)|

These are two main coordinates systems used in astronomy.
Coordinates given in the latter are relatively constant and can be obtained from databases. They then need to be converted to the former, taking into consideration the user's location and the date and time.

The location and date and time are acquired from the sensors and the internet, and converted with the custom-written libraries.

<b>In this project, the conversion from Right Ascension and Declination coordinates to Altitude and Azimuth coordinates was improved by accounting for the tilt of the telescope mount. For further details, please refer to the following personal repository.

<a href="https://github.com/linukaratnayake/RA-DEC-to-ALT-AZ-Tilted-Axes-Coordinate-Convertion-for-Stellar-Objects">ALT-AZ Coordinates for Stellar Objects when Axes are Tilted or Rotated</a></b>

<h2>Software Development</h2>
<h3>Mobile App</h3>

<h2>PCB Design</h2>

<h2>Mechanical Design</h2>