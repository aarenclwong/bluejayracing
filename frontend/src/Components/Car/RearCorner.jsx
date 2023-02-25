import { STLLoader } from 'three/examples/jsm/loaders/STLLoader';
import { useLoader} from '@react-three/fiber';


const debug = true;
function RearCorner (props) {
  const { scale, flip } = props;
  let mesh = useLoader(
    STLLoader,
    './public/models/lowminpolyrear.STL'
  );
  let scale_new = JSON.parse(JSON.stringify(scale));
 
  let position = [];
  let rotation = [];
  if (flip) {
    position = [0, -0.025, .255];
    scale_new[0]*=-1
    rotation = [-0.1, -Math.PI, 0.01];
  } else {
    position = [0, -0.025, .255];
    rotation = [-0.1, -Math.PI, -0.01];
  }


  return debug && (
    <group>
      <group scale={scale_new} rotation={rotation} position={position}>
          <mesh geometry={mesh}><meshLambertMaterial color="red" /></mesh>
          
        </group>
    </group>
  );
};


export default RearCorner;