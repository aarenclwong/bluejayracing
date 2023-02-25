import { useTrimesh } from "@react-three/cannon";
import { useLoader } from "@react-three/fiber";
import { useRef } from "react";
import { STLLoader } from 'three/examples/jsm/loaders/STLLoader';
import { GLTFLoader } from "three/examples/jsm/loaders/GLTFLoader";


function Wedge() {
  const result = useLoader(GLTFLoader, "./models/wedge.glb");
  // let mesh = useLoader(STLLoader,'./models/wedge.stl');
  
  const geometry =result.scene.children[0].geometry;


  const scale = .5;
  const position = geometry.attributes.position
    for (let i = 0; i < position.count; i++) {
      position.setXYZ(i, position.getX(i) * scale, position.getY(i) * scale, position.getZ(i) * scale)
    }
  
  const vertices = geometry.attributes.position.array;
  const indices  = geometry.index.array;


  const [ref] = useTrimesh(
    () => ({
      args: [vertices, indices],
      mass: 0,
      type: "Static",
    }),
    useRef(null)
  );

  return (
    <group>
      <mesh>
          <primitive object={result.scene} geometry={geometry}/>
          <meshBasicMaterial color="blue" opacity={0.3} />
      </mesh>
    </group>
      
    
    
  )
}

export default Wedge;