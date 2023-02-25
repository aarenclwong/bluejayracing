import { createRoot } from 'react-dom/client'
import { Canvas, useThree } from '@react-three/fiber'
import { OrbitControls, Stars, Box } from "@react-three/drei";
import { Physics } from "@react-three/cannon";
import "../../style.css";
import Car from './Car/Car.jsx';
import Terrain from './Terrain/Terrain.jsx';
import Perspective from './Views/Perspective';
import { useState } from 'react';
import { useEffect } from 'react';


function World(props) {
	const [thirdPerson, setThirdPerson] = useState(false);
	const [cameraPosition, setCameraPosition] = useState([-6, 3.9, 6.21]);

	useEffect(() => {
		function keydownHandler(e) {
			if (e.key == "k") {
				if (thirdPerson) setCameraPosition([-6, 3.9, 6.21 + Math.random() * .01]);
			setThirdPerson(!thirdPerson);
			}
		}

		window.addEventListener("keydown", keydownHandler);
		return () => window.removeEventListener("keydown", keydownHandler);
	}, [thirdPerson]);



  return (
    <>
      <Canvas camera={{ fov: 75, position: [10, 10, -10]}} frameloop="demand" dpr={2}>
		    <Stars />
		    <ambientLight intensity={.5} />
		    <spotLight position={[100, 15, 10]} angle={0.3} />

				<Perspective cameraPosition={cameraPosition} thirdPerson={thirdPerson}/>

		    <Physics broadphase="SAP" gravity={[0, -2.6, 0]}>
			    <Car thirdPerson={thirdPerson}/>
			    <Terrain />
		    </Physics>
	    </Canvas>
    </>
  );


}

export default World;