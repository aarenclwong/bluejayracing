import { createRoot } from 'react-dom/client'
import { Canvas, useThree } from '@react-three/fiber'
import { OrbitControls, Stars, Box } from "@react-three/drei";
import { Physics, usePlane, useBox } from "@react-three/cannon";
import "../../style.css";
import Car from './Car/Car.jsx';
import Terrain from './Terrain/Terrain.jsx';


function World(props) {
  return (
    <>
      <Canvas camera={{ fov: 75, position: [10, 10, -10]}}>
		    <OrbitControls />
		    <Stars />
				
		    <ambientLight intensity={.5} />
		    <spotLight position={[100, 15, 10]} angle={0.3} />
		    <Physics broadphase="SAP" gravity={[0, -2.6, 0]}>
			    <Car />
			    <Terrain />
		    </Physics>
	    </Canvas>
    </>
  );


}

export default World;