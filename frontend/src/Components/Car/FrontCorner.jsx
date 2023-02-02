import { STLLoader } from 'three/examples/jsm/loaders/STLLoader';
import { useLoader} from '@react-three/fiber';


const debug = true;
function FrontCorner (props) {
  const { scale, flip } = props;
  let mesh = useLoader(
    STLLoader,
    '../models/front_corner.STL'
  );
  let scale_new = JSON.parse(JSON.stringify(scale));
 
  const rotation = [-0, -Math.PI, 0];
  let position = [];
  if (flip) {
    position = [-0.21, -.12, .26];
    scale_new[0]*=-1
  } else {
    position = [0.21, -.12, .26];
  }

  

  return debug && (
    <group>
      <group scale={scale_new} rotation={rotation} position={position}>
          <mesh geometry={mesh}><meshLambertMaterial color="red" /></mesh>
          
        </group>
    </group>
  );
};


export default FrontCorner;