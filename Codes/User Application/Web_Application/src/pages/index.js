// Filename - App.js

import React, { Component } from "react";

class App extends Component {
	render() {
		const myStyle = {
			backgroundImage: `url(${
				process.env.PUBLIC_URL + "/indexnew.png"
			})`,
			height: "100vh",
			marginTop: "-70px",
			fontSize: "50px",
			backgroundSize: "cover",
			backgroundRepeat: "no-repeat",
		};
		return (
			<div style={myStyle}>
			</div>
		);
	}
}

export default App;
