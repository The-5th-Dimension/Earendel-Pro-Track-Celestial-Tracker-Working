<h1>Earendel Pro-Track: IoT-Based Celestial Object Tracker</h1>

<h2><a href="https://github.com/linukaratnayake">Linuka Ratnayake</a>, <a href="https://github.com/YasiruDEX">Yasiru Basnayake</a>, <a href="https://github.com/KumuthuDeZoysa">Kumuthu De Zoysa</a>, <a href="https://github.com/KavinduJ2001">Kavindu Jayathissa</a>, <a href="https://github.com/ehele">Aruna Ehelepola</a>,  <a href="">Dhanushka Weerakoon</a></h2>

  
<h2>Overview</h2>
<h3>Introduction</h3>
<p>
    "Earendel Pro-Track" is a project that aims to design a telescope mount capable of automatically locating and keeping track of stellar objects. The desired stellar object can be selected through the user interface, and once that information is transferred to the telescope mount in the form of celestial coordinates, it turns to that stellar object, and starts observing.
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


https://github.com/user-attachments/assets/d0daafc0-86b6-4ca8-b112-ab7fa79acf01


To better understand the project and its problem-solution scenario, deliverables and outcomes, refer to <a href="Project Details (Documents and Media)/Project Overview Video/Earendel_Pro_Track _The_5th_Dimension.mp4">this</a> video.

<h2>Research and Development</h2>

<h3>Coordinate Systems and Conversion</h3>

| **Altitude - Azimuth** | **Right Ascension - Declination** |
|:--:|:--:|
| ![ALT-AZ](Project%20Details%20(Documents%20and%20Media)/Images/Coordinate%20Systems/alt_az.png) | <img src="Project%20Details%20(Documents%20and%20Media)/Images/Coordinate%20Systems/ra_dec.png" style="width: 94.5%">|

These are two main coordinates systems used in astronomy.
Coordinates given in the latter are relatively constant and can be obtained from databases. They then need to be converted to the former, taking into consideration the user's location and the date and time.

The location and date and time are acquired from the sensors and the internet, and converted with the custom-written libraries.

<b>In this project, the conversion from Right Ascension and Declination coordinates to Altitude and Azimuth coordinates was improved by accounting for the tilt of the telescope mount. For further details, please refer to the following personal repository.

<a href="https://github.com/linukaratnayake/RA-DEC-to-ALT-AZ-Tilted-Axes-Coordinate-Convertion-for-Stellar-Objects">linukaratnayake/RA-DEC-to-ALT-AZ-Tilted-Axes-Coordinate-Convertion-for-Stellar-Objects</a></b>

**Repository Content**

<ul>
<li>Algorithm to convert Right Ascension and Declination coordinates to Altitude and Azimuth coordinates.</li>
<li>Mathematical derivation of an algorithm to compensate for the tilt in the coordinate axes.</li>
<li>Python implementation of the algorithms for testing and as a proof of concept.</li>
<li>C/C++ implementation of the algorithms to be used in the actual device.</li>
</ul>

<h2>Software Development</h2>

In the project, it was aimed to provide the flexibility to the user such that it is possible to use a mobile device or a computer to control the telescope mount. This includes developing a mobile application (currently Android, plan to extend to iOS), and a web interface, through which the user can select the desired stellar object.

Furthermore, software development includes designing of databases to store data of stars and planets, as well as handling user details.

<h3>Mobile App</h3>

| ![Home Screen](Project%20Details%20(Documents%20and%20Media)/Images/Mobile%20App/1.jpg) | ![Home Screen - Location Permission](Project%20Details%20(Documents%20and%20Media)/Images/Mobile%20App/2.jpg)|
|:--:|:--:|
| ![Stars](Project%20Details%20(Documents%20and%20Media)/Images/Mobile%20App/3.jpg) | ![Planets](Project%20Details%20(Documents%20and%20Media)/Images/Mobile%20App/4.jpg)|

<h3>Web Application</h3>

| ![Home Screen](Project%20Details%20(Documents%20and%20Media)/Images/Web%20App/1.PNG) | ![Home Screen - Location Permission](Project%20Details%20(Documents%20and%20Media)/Images/Web%20App/2.PNG)|
|:--:|:--:|
| ![Stars](Project%20Details%20(Documents%20and%20Media)/Images/Web%20App/3.PNG) | ![Planets](Project%20Details%20(Documents%20and%20Media)/Images/Web%20App/4.PNG)|


For codes and further details of the user application and the inclusion of databases, refer <a href="Codes/User Application/">here</a>.

<h2>PCB Design</h2>

<img src="Project Details (Documents and Media)/Images/PCB/PCB.png" style="width: 80%; margin-left: auto; margin-right: auto; display: block;">

A custom 2-layer PCB is designed using **Altium Designer**.

**Features of the PCB**
<ul>
<li>Division of synchronous and asynchronous processing parts between two microcontrollers, to reduce latency, and seamless and smoother movements.</li>
<li>2 power-up methods: DC barrel jack up to 12V, and USB type C port.</li>
<li>Compact design with on-board mounted stepper motor drivers, and control switches.</li>
<li>External connection ports for integrating accelerometer, magnetometer, and GPS module.</li>
</ul>

For PCB design files, refer <a href="PCB Design">here</a>.

<!-- <b>In the second version of the PCB, several identified issues were resolved, together with the addition of some more features. For further details, please refer to the following personal repository.

<a href="https://github.com/YasiruDEX?tab=repositories">[repo_name]</a></b> -->

<h2>Mechanical Design</h2>

<img src="Project Details (Documents and Media)/Images/Enclosure/Enclosure.png" style="width: 60%; margin-left: auto; margin-right: auto; display: block;">

Metal structure is designed to support the weight of the telescope, motors, and other components, with a 3D printed enclosure to enhance the visual appeal. **SOLIDWORKS** and **Blender** are used extensively for designing.

For structure and enclosure design files, and details, refer <a href="Physical Design">here</a>.
