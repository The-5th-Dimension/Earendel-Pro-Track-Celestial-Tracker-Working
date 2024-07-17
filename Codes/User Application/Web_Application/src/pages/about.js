// Filename - pages/about.js

import React from "react";

const About = () => {
    return (
        <div style={{
            textAlign: 'center',
            paddingTop: '5vh', /* Adjust the top padding to your preference */
            minHeight: '100vh', /* Ensure the div takes at least the full height of the viewport */
            backgroundImage: `url(${process.env.PUBLIC_URL}/../bg.png)`, /* Add the path to your background image */
            backgroundSize: 'cover', /* Cover the entire container with the background image */
            backgroundPosition: 'center', /* Center the background image */
            backgroundColor: '#123', /* Fallback background color if image not available */
            color: '#fff', /* Change text color to white for better readability */
            padding: '20px' /* Add padding for content */
        }}>
            <h1 style={{ fontSize: '1.5em', marginBottom: '20px' }}>
                Welcome to the Future of Stargazing!
            </h1>
            <p>
                Embark on a celestial journey like never before with our revolutionary IoT-based telescope mount. 
                Say goodbye to tedious manual adjustments and leveling woes - our innovative web interface puts the universe at your fingertips!
            </p>
            <h1 style={{ fontSize: '1.5em', marginBottom: '20px' }}>
                Explore the Cosmos Effortlessly:
            </h1>
            <p>
            Select your favorite stars or planets with a simple click, 
            and watch in awe as our intelligent telescope mount automatically adjusts its position, 
            providing you with a seamless stargazing experience.
            </p>
            <h1 style={{ fontSize: '1.5em', marginBottom: '20px' }}>
            Unleash Your Curiosity:
            </h1>
            <p>
            Whether you're a seasoned astronomer or a curious novice, 
            our intuitive interface empowers you to discover the mysteries of the universe with ease. 
            No complex controls or confusing manuals - just pure astronomical exploration.
            </p>
            <h1 style={{ fontSize: '1.5em', marginBottom: '20px' }}>
            Access Anytime, Anywhere:
            </h1>
            <p>
            With our responsive web UI, take command of your telescope mount from the comfort of your home or on the go. 
            All you need is an internet connection and a thirst for cosmic discovery.
            </p>
        </div>
    );
};

export default About;

