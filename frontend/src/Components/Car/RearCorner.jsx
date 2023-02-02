import { STLLoader } from 'three/examples/jsm/loaders/STLLoader';
import { useLoader} from '@react-three/fiber';


const debug = true;
function RearCorner (props) {
  const { scale, flip } = props;
  let mesh = useLoader(
    STLLoader,
    '../models/rear_corner.STL'
  );
  let scale_new = JSON.parse(JSON.stringify(scale));
 
  let position = [];
  if (flip) {
    position = [-0.19, -.14, .29];
    scale_new[0]*=-1
  } else {
    position = [0.19, -.14, .29];
  }

  const rotation = [-0.05, -Math.PI, 0];

  return debug && (
    <group>
      <group scale={scale_new} rotation={rotation} position={position}>
          <mesh geometry={mesh}><meshLambertMaterial color="red" /></mesh>
          
        </group>
    </group>
  );
};


export default RearCorner;