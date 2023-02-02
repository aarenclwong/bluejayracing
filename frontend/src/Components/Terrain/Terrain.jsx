import { usePlane } from "@react-three/cannon";
import "../../../style.css";
import { useRef, useEffect } from 'react';
import Path from "./Path";


function Terrain() {
	const [ref] = usePlane(() => ({
		type: 'Static',
		rotation: [-Math.PI / 2, 0, 0],
	}), useRef(null));
	return (
		<>
		<mesh ref={ref} rotation={[-Math.PI / 2, 0, 0]}>
			<planeGeometry attach="geometry" args={[12, 12]} />
			<meshLambertMaterial attach="material" color="lightblue" />
		</mesh>
		<Path/>
		</>
	);
}


export default Terrain;