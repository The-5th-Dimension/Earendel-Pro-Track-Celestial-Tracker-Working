// Filename - "./components/Navbar.js

import React from "react";
import { Nav, NavLink, NavMenu } from "./NavbarElements";

const Navbar = () => {
	return (
		<>
			<Nav>
				<NavMenu>
					<NavLink to="/about" activeStyle>
						About
					</NavLink>
					<NavLink to="/stars" activeStyle>
						Stars
					</NavLink>
					<NavLink to="/planets" activeStyle>
						Planets
					</NavLink>
				</NavMenu>
			</Nav>
		</>
	);
};

export default Navbar;
