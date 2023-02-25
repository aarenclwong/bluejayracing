import { useTrimesh } from "@react-three/cannon";
import { useLoader } from "@react-three/fiber";
import { useRef } from "react";
import { GLTFLoader } from "three/examples/jsm/loaders/GLTFLoader";


function GroundFeature() {
  const result = useLoader(GLTFLoader, "../../../models/ramp.glb");
  
  const geometry = result.scene.children[0].geometry;

  const scale = 1;
  const position = geometry.attributes.position
    for (let i = 0; i < position.count; i++) {
      position.setXYZ(i, position.getX(i) * scale, position.getY(i) * 1, position.getZ(i) * scale)
    }
  
  const vertices = geometry.attributes.position.array;
  const indices  = geometry.index.array;

  console.log(indices);
  console.log(vertices);

  const [ref] = useTrimesh(
    () => ({
      args: [vertices, indices],
      mass: 0,
      type: "Static",
    }),
    useRef(null)
  );

  return (
    <group ref={ref}>
      <mesh>
          <primitive object={result.scene} geometry={geometry}/>
          <meshBasicMaterial color="blue" opacity={0.3} />
      </mesh>
    </group>
      
    
    
  )
}

export default GroundFeature;