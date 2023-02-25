import {  OrbitControls, PerspectiveCamera } from "@react-three/drei";



function Perspective(props) {
  const {cameraPosition, thirdPerson} = props;
  return(
    <>
      <PerspectiveCamera makeDefault position={cameraPosition} fov={40} />
      {!thirdPerson && (
        <OrbitControls target={[-2.64, -.71, .03]}/>
      )}
    </>
  );

}


export default Perspective;