import { useTrimesh } from "@react-three/cannon";
import { useLoader } from "@react-three/fiber";
import { useRef } from "react";
import { GLTFLoader } from "three/examples/jsm/loaders/GLTFLoader";

function GroundFeature() {
  const result = useLoader(GLTFLoader, "../../../models/ramp.glb");

  const geometry = result.scene.children[0].geometry;
  
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
    <mesh position={[0,0,0]}>
      <boxGeometry args={[1,1,1]} />
      <primitive object={result} geometry={geometry}/>
      <meshBasicMaterial color="red" opacity={0.3} />
    </mesh>
    
  )
}

export default GroundFeature;