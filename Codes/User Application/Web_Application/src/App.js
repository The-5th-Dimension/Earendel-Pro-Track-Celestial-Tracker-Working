// Filename - App.js

import React from "react";
import Navbar from "./components/Navbar";
import {
	BrowserRouter as Router,
	Routes,
	Route,
} from "react-router-dom";
import Home from "./pages/index";
import About from "./pages/about";
import Planets from "./pages/planets";
import Stars from "./pages/stars";

function App() {
	return (
		<Router>
			<Navbar />
			<Routes>
				<Route exact path="/" element={<Home />} />
				<Route path="/about" element={<About />} />
				<Route
					path="/stars"
					element={<Stars />}
				/>
				<Route 
					path="/planets" 
					element={<Planets />} />
			</Routes>
		</Router>
	);
}

export default App;
