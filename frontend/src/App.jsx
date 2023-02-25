import { useState } from "react";
import PlaybackRateMenuButtonExmaple from "./Components/Player";
import Map from "./Components/Map.jsx";
import World from "./Components/World.jsx"

function App() {
  return (
    <>
      <World></World>
      <Map position={[39.32845515755447, -76.62242889404298]}></Map>
      <PlaybackRateMenuButtonExmaple></PlaybackRateMenuButtonExmaple>
    </>
  );
}

export default App;
