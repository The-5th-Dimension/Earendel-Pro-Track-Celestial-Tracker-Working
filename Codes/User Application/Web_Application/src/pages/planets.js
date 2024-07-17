// Filename - pages/planets.js

import React, { useEffect, useState } from 'react';
import { getDatabase, ref, set } from 'firebase/database';
import { app } from './firebase';

const Planets = () => {
  const [userLocation, setUserLocation] = useState(null);

  useEffect(() => {
    // Get user's location when the component mounts
    if ('geolocation' in navigator) {
      navigator.geolocation.getCurrentPosition(
        position => {
        //   const { latitude, longitude } = position.coords;
        //   setUserLocation({ latitude, longitude });
		const { latitude, longitude } = position.coords;
		let gps = 'GPS ' + latitude + ',' + longitude
        setUserLocation(gps);
        },
        error => console.error('Error getting user location:', error)
      );
    } else {
      console.error('Geolocation is not supported by this browser.');
    }
  }, []);

  const db = getDatabase(app);

  const handleItemClick = (itemName) => {
    if (userLocation) {
      const userLocationRef = ref(db, 'Location');
      set(userLocationRef, userLocation);

      const planetRef = ref(db, 'Planet');
      set(planetRef, itemName);

      console.log('Flower variable updated to:', itemName);
      console.log('User location updated to:', userLocation);
    } else {
      console.error('User location not available.');
    }
  };
  
  const handleMouseEnter = (e) => {
    e.target.style.backgroundColor = 'black';
    e.target.style.color = 'white';
  }

  const handleMouseLeave = (e) => {
    e.target.style.backgroundColor = '#ccc';
    e.target.style.color = 'black';
  }

  return (
    <div style={{ padding: '20px' }}>
      <h1 style={{ fontSize: '2em', textAlign: 'center', marginBottom: '20px' }}>Planets</h1>
      <div style={{ display: 'grid', gridTemplateColumns: 'repeat(auto-fill, minmax(150px, 1fr))', gridGap: '20px' }}>
        <div onClick={() => handleItemClick('Sun')} style={{ backgroundColor: '#ccc', padding: '20px', borderRadius: '8px', cursor: 'pointer', textAlign: 'center' }}
        onMouseEnter={handleMouseEnter}
        onMouseLeave={handleMouseLeave}
        >
        Sun</div>
        <div onClick={() => handleItemClick('Mercury')} style={{ backgroundColor: '#ccc', padding: '20px', borderRadius: '8px', cursor: 'pointer', textAlign: 'center' }}
        onMouseEnter={handleMouseEnter}
        onMouseLeave={handleMouseLeave}
        >Mercury</div>
        <div onClick={() => handleItemClick('Venus')} style={{ backgroundColor: '#ccc', padding: '20px', borderRadius: '8px', cursor: 'pointer', textAlign: 'center' }}
        onMouseEnter={handleMouseEnter}
        onMouseLeave={handleMouseLeave}
        >Venus</div>
        <div onClick={() => handleItemClick('Mars')} style={{ backgroundColor: '#ccc', padding: '20px', borderRadius: '8px', cursor: 'pointer', textAlign: 'center' }}
        onMouseEnter={handleMouseEnter}
        onMouseLeave={handleMouseLeave}
        >Mars</div>
        <div onClick={() => handleItemClick('Jupiter')} style={{ backgroundColor: '#ccc', padding: '20px', borderRadius: '8px', cursor: 'pointer', textAlign: 'center' }}
        onMouseEnter={handleMouseEnter}
        onMouseLeave={handleMouseLeave}
        >Jupiter</div>
        <div onClick={() => handleItemClick('Saturn')} style={{ backgroundColor: '#ccc', padding: '20px', borderRadius: '8px', cursor: 'pointer', textAlign: 'center' }}
        onMouseEnter={handleMouseEnter}
        onMouseLeave={handleMouseLeave}
        >Saturn</div>
        <div onClick={() => handleItemClick('Uranus')} style={{ backgroundColor: '#ccc', padding: '20px', borderRadius: '8px', cursor: 'pointer', textAlign: 'center' }}
        onMouseEnter={handleMouseEnter}
        onMouseLeave={handleMouseLeave}
        >Uranus</div>
        <div onClick={() => handleItemClick('Neptune')} style={{ backgroundColor: '#ccc', padding: '20px', borderRadius: '8px', cursor: 'pointer', textAlign: 'center' }}
        onMouseEnter={handleMouseEnter}
        onMouseLeave={handleMouseLeave}
        >Neptune</div>
        <div onClick={() => handleItemClick('Moon')} style={{ backgroundColor: '#ccc', padding: '20px', borderRadius: '8px', cursor: 'pointer', textAlign: 'center' }}
        onMouseEnter={handleMouseEnter}
        onMouseLeave={handleMouseLeave}
        >Moon</div>
      </div>
    </div>
  );
};

export default Planets;

